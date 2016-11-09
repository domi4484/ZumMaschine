#!/bin/bash

echo "------------"
echo "Install icon"
echo "------------"
echo
mkdir -p ~/.local/share/ZumMaschine
cp -v ZumMaschine.png ~/.local/share/ZumMaschine/

echo
echo "----------------------"
echo "Install Nemo extension"
echo "----------------------"
echo
sudo apt-get install python-nemo
echo
NEMO_EXTENSIONS=~/.local/share/nemo-python/extensions
mkdir -p $NEMO_EXTENSIONS
cp -v ZumMaschineNemo.py $NEMO_EXTENSIONS

echo
echo "--------------------------"
echo "Install Nautilus extension"
echo "--------------------------"
echo
sudo apt-get install python-nautilus
echo
NAUTILUS_EXTENSIONS=~/.local/share/nautilus-python/extensions
mkdir -p $NAUTILUS_EXTENSIONS
cp -v ZumMaschineNautilus.py $NAUTILUS_EXTENSIONS

