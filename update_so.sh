#!/bin/bash
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Fix Artifact Download"
git push

echo ""
echo "🌍 CEK BROWSER SEKARANG!"
echo "Link: https://github.com/GODICO-O/oloid-project/actions"
echo "Pastikan build sudah 'Success' (Centang Hijau)."
read -p "Kalau sudah kelar, tekan [ENTER] buat lanjut download..."

echo "📥 Mendownload hasil build terbaru..."
RUN_ID=$(gh run list --limit 1 --json databaseId -q '.[0].databaseId')

if [ -z "$RUN_ID" ]; then
    echo "❌ Error: Gagal dapet ID Run terbaru!"
    exit 1
fi

# Kita download TANPA spesifik nama, biar dia ambil semua yang ada
gh run download $RUN_ID --dir ./tmp_download

echo "📦 Mencari dan memindahkan file .so ke Storage..."
# Cari file liboloid_core.so di folder manapun di dalam tmp_download
SO_FILE=$(find ./tmp_download -name "liboloid_core.so" | head -n 1)

if [ -f "$SO_FILE" ]; then
    mv "$SO_FILE" /sdcard/liboloid_core.so
    echo "✅ BERES! liboloid_core.so sudah dipindah ke /sdcard/."
else
    echo "❌ Error: File .so tidak ditemukan di dalam artifact!"
    echo "Isi folder download adalah:"
    ls -R ./tmp_download
fi

echo "🧹 Bersihin sampah..."
rm -rf ./tmp_download
echo "Silakan cek di storage utama lo! ⚡"
