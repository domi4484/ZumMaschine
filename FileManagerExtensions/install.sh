#!/bin/bash

SCRIPT_DIRECTORY="$(dirname "$0")"

echo
echo "--------------------"
echo "Install Dependencies"
echo "--------------------"
echo
sudo apt-get install -y python-nemo python-nautilus pstoedit
# OpenSUSE installare anche typelib-1_0-Nautilus-3_0 e typelib-1_0-Nemo-3_0

echo
echo "----------------"
echo "Install EpsToDxf"
echo "----------------"
echo
cd EpsToDxf
source install.sh
cd ..

echo
echo "-------------------"
echo "Install ZumMaschine"
echo "-------------------"
echo
cd ZumMaschine
source install.sh
cd ..
  
