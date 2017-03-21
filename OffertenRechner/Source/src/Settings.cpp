/********************************************************************
 *                                                                 *
 * Lowerspot                                                       *
 *                                                                 *
 * Author:       Damiano Lombardi                                  *
 * Created:      26.05.2015                                        *
 *                                                                 *
 * Copiright (c) 2015 Damiano Lombardi                             *
 *                                                                 *
********************************************************************/

// Files includes --------------------------
#include "Settings.h"

//-----------------------------------------------------------------------------------------------------------------------------

Settings::Settings(QObject *parent) :
  QSettings(parent)
{
}

//-----------------------------------------------------------------------------------------------------------------------------

Settings::~Settings()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

QString Settings::get_Mirror_DirectorySource()
{
  return QSettings::value("Mirror_DirectorySource",
                          "").toString();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings::set_Mirror_DirectorySource(const QString &directorySource)
{
  QSettings::setValue("Mirror_DirectorySource",
                      directorySource);
}

//-----------------------------------------------------------------------------------------------------------------------------

QString Settings::get_Mirror_DirectoryDestination()
{
  return QSettings::value("Mirror_DirectoryDestination",
                          "").toString();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings::set_Mirror_DirectoryDestination(const QString &directoryDestination)
{
  QSettings::setValue("Mirror_DirectoryDestination",
                      directoryDestination);
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Settings::get_Mirror_Active()
{
  return QSettings::value("Mirror_Active",
                          false).toBool();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings::set_Mirror_Active(bool active)
{
  QSettings::setValue("Mirror_Active",
                      active);
}

//-----------------------------------------------------------------------------------------------------------------------------
