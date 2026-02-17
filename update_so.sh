#!/bin/bash
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Deploying Dobby Surgical Kit"
git push

echo ""
echo "🌍 CEK BROWSER SEKARANG!"
echo "Link: https://github.com/GODICO-O/oloid-project/actions"
read -p "Kalau sudah centang hijau, tekan [ENTER]..."

echo "📥 Mendownload paket lengkap..."
RUN_ID=$(gh run list --limit 1 --json databaseId -q '.[0].databaseId')
gh run download $RUN_ID --dir ./tmp_download

echo "📦 Memindahkan semua library ke /sdcard/..."
find ./tmp_download -name "*.so" -exec cp {} /sdcard/ \;

echo "🧹 Bersih-bersih..."
rm -rf ./tmp_download

echo "✅ SELESAI! Cek /sdcard/ lo sekarang."
echo "Harusnya ada liboloid_core.so DAN libdobby.so."
echo "Tempel KEDUA-DUANYA ke folder lib/arm64-v8a/ di APK GD! ⚡"
