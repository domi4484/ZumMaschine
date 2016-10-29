
# Install in ~/.local/share/nemo-python/extensions

from gi.repository import Nemo, GObject

import getpass
import os

class ColumnExtension(GObject.GObject, Nemo.MenuProvider):
  def __init__(self):
    pass

  def menu_activate_cb(self, menu, file):
    print "menu_activate_cb",file

  def get_file_items(self, window, files):

    # Only one file
    if len(files) != 1:
      return
        
    file = files[0]

    # Only dxf files
    if not file.get_name().endswith(".dxf"):
      return

    print file.get_location()

    # Only in auftraege folder
    if "Auftraege" not in file.get_location():
      return

    item = Nemo.MenuItem(name  = "Zum Maschine kopieren",
                         label = "Zum Maschine kopieren",
                         tip   = "Zum Maschine kopieren %s" % file.get_name(),
                         icon  = "/home/" + getpass.getuser() + "/.local/share/nemo-python/extensions/ZumMaschine.png"
                        )
    item.connect('activate', self.menu_activate_cb, file)
    
    return [item]
