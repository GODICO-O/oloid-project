#!/bin/bash
echo "🚀 Memulai proses Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Auto-update library visual"
git push

echo "⏳ Menunggu GitHub Actions memproses build (sekitar 30-40 detik)..."
# Tunggu sebentar biar workflow-nya mulai jalan
sleep 45

echo "📥 Mendownload file oloid-core-so.zip terbaru..."
# Mengambil artifact terbaru menggunakan GitHub CLI (Pastikan gh auth login sudah dilakukan)
RUN_ID=$(gh run list --workflow="build-core" --limit 1 --json databaseId -q '.[0].databaseId')
gh run download $RUN_ID --name oloid-core-so --dir ./tmp_download

echo "📦 Mengekstrak dan memindahkan ke Storage Utama..."
unzip -o ./tmp_download/oloid-core-so.zip -d ./tmp_download
mv ./tmp_download/liboloid_core.so /sdcard/liboloid_core.so

echo "🧹 Membersihkan file sampah..."
rm -rf ./tmp_download

echo "✅ SELESAI! File liboloid_core.so sudah siap di folder utama internal storage (/sdcard/)."
echo "Silakan tempel ke APK GD pake APK Editor! ⚡"
