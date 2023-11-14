#!/bin/sh
vmake='make'
mkdir -p build
autoreconf --install
cd build
sh ../configure
cpunum=$(grep -c ^processor /proc/cpuinfo)
$vmake -j $cpunum

if test $MSYSTEM
then
chmod +x ../winfix.sh
sh ../winfix.sh
fi
