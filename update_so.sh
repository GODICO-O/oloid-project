#!/bin/bash
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Manifestasi Dobby Real"
git push

echo ""
echo "🌍 CEK BROWSER SEKARANG!"
echo "Link: https://github.com/GODICO-O/oloid-project/actions"
read -p "Kalau sudah centang hijau (Success), tekan [ENTER]..."

echo "📥 Mendownload hasil build terbaru..."
# Hapus folder lama biar bersih
rm -rf ./tmp_download
mkdir -p ./tmp_download

# Ambil ID run terbaru
RUN_ID=$(gh run list --limit 1 --json databaseId -q '.[0].databaseId')

# Download dengan nama spesifik 'oloid-package'
gh run download $RUN_ID --name oloid-package --dir ./tmp_download

echo "📦 Memindahkan library ke /sdcard/..."
if [ -f "./tmp_download/liboloid_core.so" ]; then
    cp ./tmp_download/*.so /sdcard/
    echo "✅ BERHASIL! liboloid_core.so & libdobby.so sudah di /sdcard/."
    ls -lh /sdcard/libdobby.so /sdcard/liboloid_core.so
else
    echo "❌ Error: File masih nggak ketemu di artifact!"
    ls -R ./tmp_download
fi

rm -rf ./tmp_download
