#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication qApplication(argc, argv);

  // Application informations
  qApplication.setOrganizationName   ("Lowerspot");
  qApplication.setOrganizationDomain ("lowerspot.com");
  qApplication.setApplicationName    ("Drawings Mirror");
  qApplication.setApplicationVersion ("V0.0.1");


  MainWindow mainWindow;
  mainWindow.show();
  
  return qApplication.exec();
}
