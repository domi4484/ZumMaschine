
# Install in ~/.local/share/nemo-python/extensions

from gi.repository import GObject

import getpass
import os
import shutil
import subprocess

# Nemo or Nautilus
scriptPath = os.path.realpath(__file__)
if "nemo-python/extensions" in scriptPath:
  from gi.repository import Nemo as FileManager
else:
  from gi.repository import Nautilus as FileManager


class EpsToDxfExtension(GObject.GObject, FileManager.MenuProvider):

  def __init__(self):
    pass

  #------------------------------------------------------------------------------------------------------------------------------

  def menu_activate_cb(self, menu, file):
  
    # Get complete filename path
    filenameEps = file.get_uri()[len("//file:"):]

    # Default result filename
    filenameDxf = filenameEps.replace('.eps', '.dxf')
    
    # Copy dxf file
    command = ['pstoedit', '-f', 'dxf:-mm' , filenameEps, filenameDxf]
    # pstoedit -f "dxf_s: -mm -splineaspolyline -splineprecision 8"  OldCaptain_300x300_3.eps OldCaptain_300x300_3.dxf
    process = subprocess.Popen(command, stdout=subprocess.PIPE)
    output, error = process.communicate()
    self.debug("pstoedit output: " + output)
    self.debug("pstoedit error: " + str(error))
    self.debug("")
    self.debug("File " + filenameEps + " converted to " + filenameDxf)
    
  #------------------------------------------------------------------------------------------------------------------------------

  def get_file_items(self, window, files):
    # Only one file
    if len(files) != 1:
      return
        
    file = files[0]

    # Only eps files
    if not file.get_name().endswith(".eps"):
      return

    # Create menu item
    item = FileManager.MenuItem(name  = "Zumdxfkonvertieren",
                                label = "Zum dxf konvertieren",
                                tip   = "Zum dxf konvertieren %s" % file.get_name(),
                                icon  = "/home/" + getpass.getuser() + "/.local/share/customcut/FileManagerExtensions/EpsToDxf/Dxf.png"
                               )
    item.connect('activate', self.menu_activate_cb, file)
    
    return [item]

  #------------------------------------------------------------------------------------------------------------------------------

  def debug(self, message):
    print("EpsToDxf: " + message)

    
