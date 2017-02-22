#ifndef MATERIAL_H
#define MATERIAL_H

// Qt includes -----------------------------
#include <QFileInfo>
#include <QString>

class Material
{
public:

  class _CONST
  {
  public:
    static const QString LOCATION;
    static const QString FILENAME_EXTENSION;

    class JSON
    {
    public:
      static const QString NAME;
    }; // JSON
  }; // _CONST

  Material(const QFileInfo &qFileInfo);

  void Load();

  QString Name() const;

private:

  QFileInfo m_QFileInfo;

  QString m_Name;
};

#endif // MATERIAL_H
