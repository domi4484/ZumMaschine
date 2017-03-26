
// Project includes ------------------------
#include "MainWindow.h"

// Qt includes -----------------------------
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication qApplication(argc, argv);

  // Application informations
  qApplication.setOrganizationName   ("Lowerspot");
  qApplication.setOrganizationDomain ("lowerspot.com");
  qApplication.setApplicationName    ("Parts Calculator");
  qApplication.setApplicationVersion ("V0.0.2");


  MainWindow mainWindow;
  mainWindow.show();
  
  return qApplication.exec();
}
