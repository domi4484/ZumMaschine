
# Install in ~/.local/share/nemo-python/extensions

from gi.repository import GObject

from gi.repository import Nemo as FileManager
#from gi.repository import Nautilus as FileManager

import getpass
import os
import shutil

class ZumMaschineExtension(GObject.GObject, FileManager.MenuProvider):

  DEFAULT_BASE_FOLDER     = "Auftraege"
  DEFAULT_MASCHINE_FOLDER = "Maschine"

  def __init__(self):
    pass

  #------------------------------------------------------------------------------------------------------------------------------

  def menu_activate_cb(self, menu, file):
  
    # Get complete filename path
    filename = file.get_uri()[len("//file:"):]

    # Get directory structure till Autraege
    folders = filename.split("/")
    folders.pop(-1) # Remove filename
    
    for i, folder in enumerate(folders):
      if folder == self.DEFAULT_BASE_FOLDER:
        folders[i] = self.DEFAULT_MASCHINE_FOLDER
       
    # Prepare copy path
    copyPath = "/".join(folders)
       
    # Create directory 
    try:
      os.makedirs(copyPath)
    except:
      self.debug("Cant' create directories: " + copyPath)
      return
    
    # Copy dxf file
    shutil.copy(filename,
                copyPath)
    
    self.debug("File " + filename + " copied to " + copyPath)
    
  #------------------------------------------------------------------------------------------------------------------------------

  def get_file_items(self, window, files):

    # Only one file
    if len(files) != 1:
      return
        
    file = files[0]

    # Only dxf files
    if not file.get_name().endswith(".dxf"):
      return

    # Only in auftraege folder
    if self.DEFAULT_BASE_FOLDER not in file.get_uri():
      return

    # Create menu item
    item = FileManager.MenuItem(name  = "Zum Maschine kopieren",
                                label = "Zum Maschine kopieren",
                                tip   = "Zum Maschine kopieren %s" % file.get_name(),
                                icon  = "/home/" + getpass.getuser() + "/.local/share/customcut/FileManagerExtensions/ZumMaschine/ZumMaschine.png"
                               )
    item.connect('activate', self.menu_activate_cb, file)
    
    return [item]

  #------------------------------------------------------------------------------------------------------------------------------

  def debug(self, message):
    print "ZumMaschine: " + message

    
