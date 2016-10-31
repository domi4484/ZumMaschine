
# Install in ~/.local/share/nemo-python/extensions

from gi.repository import GObject

#from gi.repository import Nemo as FileManager
from gi.repository import Nautilus as FileManager

import getpass
import os
import shutil

class ColumnExtension(GObject.GObject, FileManager.MenuProvider):

  DEFAULT_BASE_FOLDER     = "Auftraege"
  DEFAULT_MASCHINE_FOLDER = "Maschine"

  def __init__(self):
    pass

  def menu_activate_cb(self, menu, file):
  
    # Get directory structure till Autraege
    folders = file.get_uri().split("/")
    folders.pop(-1) # Remove filename
    
    foundFolders = list()
    foundBaseFolder = False
    for currentFolder in folders:
      if currentFolder == self.DEFAULT_BASE_FOLDER:
        foundBaseFolder = True
        continue
        
      if foundBaseFolder:
        foundFolders.append(currentFolder)
       
    # Prepare copy path
    copyPathList = [".." for x in range(len(foundFolders) + 1)]
    copyPathList.append(self.DEFAULT_MASCHINE_FOLDER)
    copyPathList = copyPathList + foundFolders
    copyPath = "/".join(copyPathList)
       
    # Create directory 
    try:
      os.makedirs(copyPath)
    except:
      print "copyPath: " + copyPath
    
    # Copy dxf file
    shutil.copy(file.get_uri()[7:],
                copyPath)
    

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
                                icon  = "/home/" + getpass.getuser() + "/.local/share/ZumMaschine/ZumMaschine.png"
                               )
    item.connect('activate', self.menu_activate_cb, file)
    
    return [item]
    
