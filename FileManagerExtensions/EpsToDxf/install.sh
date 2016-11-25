#!/bin/bash

echo "------------"
echo "Install icon"
echo "------------"
echo
mkdir -p ~/.local/share/lowercut/FileManagerExtensions/EpsToDxf/
cp -v Dxf.png ~/.local/share/lowercut/FileManagerExtensions/EpsToDxf/

echo
echo "----------------------"
echo "Install Nemo extension"
echo "----------------------"
echo
NEMO_EXTENSIONS=~/.local/share/nemo-python/extensions
mkdir -p $NEMO_EXTENSIONS
cp -v EpsToDxf.py $NEMO_EXTENSIONS
echo
nemo -q

echo
echo "--------------------------"
echo "Install Nautilus extension"
echo "--------------------------"
echo
NAUTILUS_EXTENSIONS=~/.local/share/nautilus-python/extensions
mkdir -p $NAUTILUS_EXTENSIONS
cp -v EpsToDxf.py $NAUTILUS_EXTENSIONS
echo
nemo -q

