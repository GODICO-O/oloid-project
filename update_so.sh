#!/bin/bash
# Visi KLOS: Otomasi Tanpa Batas
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Real-time Automation Build"
git push

echo "⏳ Menunggu GitHub Actions memulai build..."
sleep 5

# Ambil ID Run terbaru
RUN_ID=$(gh run list --limit 1 --json databaseId -q '.[0].databaseId')

if [ -z "$RUN_ID" ]; then
    echo "❌ Gagal dapet ID Run!"
    exit 1
fi

echo "📺 Memantau Log Build (ID: $RUN_ID) secara Real-time..."
echo "--------------------------------------------------------"
# Nonton log secara langsung di terminal
gh run watch $RUN_ID --exit-status

# Cek apakah build sukses
STATUS=$(gh run view $RUN_ID --json conclusion -q '.conclusion')

if [ "$STATUS" == "success" ]; then
    echo "--------------------------------------------------------"
    echo "✅ Build Sukses! Menunggu API Artifact siap..."
    sleep 3 # Jeda krusial biar nggak 'no artifact matches'
    
    echo "📥 Mendownload paket rakitan oloid-package..."
    rm -rf ./tmp_download
    mkdir -p ./tmp_download
    
    # Loop kecil buat mastiin download dapet (anti-latency)
    RETRY=0
    while [ $RETRY -lt 3 ]; do
        gh run download $RUN_ID --name oloid-package --dir ./tmp_download && break
        echo "🔄 Nyoba download ulang (Percobaan $((RETRY+1)))..."
        sleep 5
        RETRY=$((RETRY+1))
    done

    echo "📦 Memindahkan library ke /sdcard/..."
    if [ -f "./tmp_download/liboloid_core.so" ]; then
        cp ./tmp_download/*.so /sdcard/
        echo "✨ SEMUA BERES! liboloid_core.so & libdobby.so mendarat di /sdcard/."
        ls -lh /sdcard/libdobby.so /sdcard/liboloid_core.so
    else
        echo "❌ Waduh, file tetep nggak ada di dalem folder!"
        ls -R ./tmp_download
    fi
else
    echo "❌ Build GAGAL di GitHub. Cek log di atas buat cari erornya!"
fi

rm -rf ./tmp_download
