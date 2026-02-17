#!/bin/bash
echo "🚀 Memulai Push ke GitHub..."
git add .
git commit -m "Visi KLOS: Fix Artifact Name Mismatch"
git push

echo "⏳ Menunggu GitHub Actions memulai build..."
sleep 5

RUN_ID=$(gh run list --limit 1 --json databaseId -q '.[0].databaseId')

if [ -z "$RUN_ID" ]; then
    echo "❌ Gagal dapet ID Run!"
    exit 1
fi

echo "📺 Memantau Log Build (ID: $RUN_ID) secara Real-time..."
echo "--------------------------------------------------------"
gh run watch $RUN_ID --exit-status

STATUS=$(gh run view $RUN_ID --json conclusion -q '.conclusion')

if [ "$STATUS" == "success" ]; then
    echo "--------------------------------------------------------"
    echo "✅ Build Sukses! Sedot semua artifact yang ada..."
    rm -rf ./tmp_download
    mkdir -p ./tmp_download
    
    # KUNCI: Download TANPA flag --name biar dia ambil semuanya
    gh run download $RUN_ID --dir ./tmp_download
    
    echo "📦 Memindahkan library ke /sdcard/..."
    # Cari semua file .so di dalam folder download (rekursif)
    find ./tmp_download -name "*.so" -exec cp {} /sdcard/ \;

    if [ -f "/sdcard/liboloid_core.so" ]; then
        echo "✨ MANTAP! liboloid_core.so sudah mendarat di /sdcard/."
        ls -lh /sdcard/liboloid_core.so
    else
        echo "❌ Waduh, liboloid_core.so tetep nggak ketemu!"
        echo "Isi folder download tadi:"
        ls -R ./tmp_download
    fi
else
    echo "❌ Build GAGAL di GitHub."
fi

rm -rf ./tmp_download
