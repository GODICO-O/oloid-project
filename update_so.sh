#!/bin/bash
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Integrasi Visual Hook"
git push

echo ""
echo "🌍 CEK BROWSER SEKARANG!"
echo "Tunggu sampai centang hijau di GitHub Actions kelar."
read -p "Kalau sudah kelar, tekan [ENTER] buat lanjut download..."

echo "📥 Mendownload hasil build..."
RUN_ID=$(gh run list --workflow="build-core" --limit 1 --json databaseId -q '.[0].databaseId')
gh run download $RUN_ID --name oloid-core-so --dir ./tmp_download

echo "📦 Mengekstrak ke Storage (/sdcard/)..."
unzip -o ./tmp_download/oloid-core-so.zip -d ./tmp_download
mv ./tmp_download/liboloid_core.so /sdcard/liboloid_core.so

echo "🧹 Bersihin sampah..."
rm -rf ./tmp_download

echo "✅ BERES! File liboloid_core.so udah nangkring di storage utama."
echo "Tinggal tempel pake APK Editor dan cek Logcat! ⚡"
