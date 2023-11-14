#!/bin/sh
# Copy necessary DLLs to root directory
BASEDIR=$(dirname "$0")
cp -f /mingw64/bin/libbrotlicommon.dll ./
cp -f /mingw64/bin/libbrotlidec.dll ./
cp -f /mingw64/bin/libcrypto-3-x64.dll ./
cp -f /mingw64/bin/libcurl-4.dll ./
cp -f /mingw64/bin/libiconv-2.dll ./
cp -f /mingw64/bin/libidn2-0.dll ./
cp -f /mingw64/bin/libintl-8.dll ./
cp -f /mingw64/bin/libnghttp2-14.dll ./
cp -f /mingw64/bin/libpsl-5.dll ./
cp -f /mingw64/bin/libssh2-1.dll ./
cp -f /mingw64/bin/libssl-3-x64.dll ./
cp -f /mingw64/bin/libunistring-5.dll ./
cp -f /mingw64/bin/libwinpthread-1.dll ./
cp -f /mingw64/bin/libzstd.dll ./
cp -f /mingw64/bin/zlib1.dll ./
strip ./osu-utils.exe
strip ./*.dll
command -v upx && upx --ultra-brute ./osu-utils.exe
command -v upx && upx --ultra-brute ./*.dll
