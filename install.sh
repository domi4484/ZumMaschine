#!/bin/bash

echo "Install icon"
mkdir -p ~/.local/share/ZumMaschine
cp ZumMaschine.png ~/.local/share/ZumMaschine/

echo "Install Nemo extension"
NEMO_EXTENSIONS=~/.local/share/nemo-python/extensions
mkdir -p $NEMO_EXTENSIONS
cp ZumMaschineNemo.py $NEMO_EXTENSIONS

echo "Install Nautilus extension"
NAUTILUS_EXTENSIONS=~/.local/share/nautilus-python/extensions
mkdir -p $NAUTILUS_EXTENSIONS
cp ZumMaschineNautilus.py $NAUTILUS_EXTENSIONS

