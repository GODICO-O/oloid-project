#!/bin/bash
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Perbaikan Jalur Download"
git push

echo ""
echo "🌍 CEK BROWSER SEKARANG!"
echo "Link: https://github.com/GODICO-O/oloid-project/actions"
echo "Tunggu sampai centang hijau kelar."
read -p "Kalau sudah kelar, tekan [ENTER] buat lanjut download..."

echo "📥 Mendownload hasil build terbaru..."
# Kita ambil ID dari run terakhir tanpa peduli nama workflow
RUN_ID=$(gh run list --limit 1 --json databaseId -q '.[0].databaseId')

if [ -z "$RUN_ID" ]; then
    echo "❌ Error: Gagal dapet ID Run terbaru!"
    exit 1
fi

# Download artifact-nya
gh run download $RUN_ID --name oloid-core-so --dir ./tmp_download

echo "📦 Mengekstrak ke Storage (/sdcard/)..."
if [ -f "./tmp_download/oloid-core-so.zip" ]; then
    unzip -o ./tmp_download/oloid-core-so.zip -d ./tmp_download
    mv ./tmp_download/liboloid_core.so /sdcard/liboloid_core.so
    echo "✅ BERES! File liboloid_core.so udah nangkring di storage utama."
else
    echo "❌ Error: File zip nggak ketemu! Cek apakah Artifact namanya beneran 'oloid-core-so'."
fi

echo "🧹 Bersihin sampah..."
rm -rf ./tmp_download
echo "Tinggal tempel pake APK Editor dan cek Logcat! ⚡"
