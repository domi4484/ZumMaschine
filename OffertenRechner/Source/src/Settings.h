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
  QString get_MaterialsDirectory();
  void    set_MaterialsDirectory(const QString &directory);
};

#endif // SETTINGS_H
