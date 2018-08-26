
# Install in ~/.local/share/nemo-python/extensions

# V1.0.0

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

#------------------------------------------------------------------------------------------------------------------------------

def debug(message):
    print("EpsToDxf: " + message)

#------------------------------------------------------------------------------------------------------------------------------

class EpsToDxfConverter:
  
  def __init__(self):
    pass
  
  #------------------------------------------------------------------------------------------------------------------------------
  
  def setSourceFilename(self, sourceFilename):
      self._sourceFilename = sourceFilename
      
  #------------------------------------------------------------------------------------------------------------------------------
  
  def setDestinationFilename(self, destinationFilename):
      self._destinationFilename = destinationFilename
      
  #------------------------------------------------------------------------------------------------------------------------------
      
  def executeConversion(self):
    
    debug("Convert '" + self._sourceFilename + "' to '" + self._destinationFilename + "'")    
    
    # Prepare command
    command = ['pstoedit', '-f', 'dxf:-mm' , self._sourceFilename, self._destinationFilename]
    # pstoedit -f "dxf_s: -mm -splineaspolyline -splineprecision 8"  OldCaptain_300x300_3.eps OldCaptain_300x300_3.dxf
    debug("Command: " + " ".join(command))    
    
    # Execute
    process = subprocess.Popen(command, stdout=subprocess.PIPE)
    output, error = process.communicate()
    debug("pstoedit output: " + str(output))
    debug("pstoedit error: " + str(error))
    debug("Conversion finished")
      
  
#------------------------------------------------------------------------------------------------------------------------------
  

class EpsToDxfExtension(GObject.GObject, FileManager.MenuProvider):

  def __init__(self):
    pass

  #------------------------------------------------------------------------------------------------------------------------------

  def menu_activate_cb(self, menu, file):
  
    # Get complete filename path
    filenameEps = file.get_uri()[len("//file:"):]

    # Default result filename
    filenameDxf = filenameEps.replace('.eps', '.dxf')
    
    epsToDxfConverter = EpsToDxfConverter()
    epsToDxfConverter.setSourceFilename(filenameEps)
    epsToDxfConverter.setDestinationFilename(filenameDxf)
    epsToDxfConverter.executeConversion()
    
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



def main():
  
  debug("Executing main()")
  
  epsToDxfConverter = EpsToDxfConverter()
  epsToDxfConverter.setSourceFilename("source.eps")
  epsToDxfConverter.setDestinationFilename("source.dxf")
  epsToDxfConverter.executeConversion()

if __name__ == "__main__":
  main()

    
