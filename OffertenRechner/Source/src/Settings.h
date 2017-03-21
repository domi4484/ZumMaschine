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

#ifndef SETTINGS_H
#define SETTINGS_H

// Qt includes -----------------------------
#include <QSettings>

class Settings : public QSettings
{
  Q_OBJECT

public:

  // Constructor
  explicit Settings(QObject *parent = 0);
  virtual ~Settings();

public slots:

  // Application settings
  QString get_Mirror_DirectorySource();
  void    set_Mirror_DirectorySource(const QString &directorySource);
  QString get_Mirror_DirectoryDestination();
  void    set_Mirror_DirectoryDestination(const QString &directoryDestination);
  bool    get_Mirror_Active();
  void    set_Mirror_Active(bool active);
};

#endif // SETTINGS_H
