#!/bin/bash

function installExtensionZumMaschine
{
  echo "------------"
  echo "Install icon"
  echo "------------"
  echo
  mkdir -p ~/.local/share/customcut/FileManagerExtensions/ZumMaschine/
  cp -v ZumMaschine.png ~/.local/share/customcut/FileManagerExtensions/ZumMaschine/

  echo
  echo "----------------------"
  echo "Install Nemo extension"
  echo "----------------------"
  echo
  NEMO_EXTENSIONS=~/.local/share/nemo-python/extensions
  rm $NEMO_EXTENSIONS/ZumMaschineNemo.py
  mkdir -p $NEMO_EXTENSIONS
  cp -v ZumMaschine.py $NEMO_EXTENSIONS
  echo
  nemo -q

  echo
  echo "--------------------------"
  echo "Install Nautilus extension"
  echo "--------------------------"
  echo
  NAUTILUS_EXTENSIONS=~/.local/share/nautilus-python/extensions
  rm $NEMO_EXTENSIONS/ZumMaschineNautilus.py
  mkdir -p $NAUTILUS_EXTENSIONS
  cp -v ZumMaschine.py $NAUTILUS_EXTENSIONS
  echo
  nautilus -q
}

installExtensionZumMaschine

