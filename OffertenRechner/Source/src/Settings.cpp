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

QString Settings::get_MaterialsDirectory()
{
  return QSettings::value("MaterialsDirectory",
                          "").toString();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings::set_MaterialsDirectory(const QString &directory)
{
  QSettings::setValue("MaterialsDirectory",
                      directory);
}


