#ifndef OFFER_H
#define OFFER_H

// Project includes ------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QObject>
#include <QFileInfo>

class Offer : public QObject
{
  Q_OBJECT
public:

  class _CONST
  {
  public:
    static const QString FILENAME_EXTENSION;

    class JSON
    {
    public:
      static const QString NAME;
    }; // JSON
  }; // _CONST

  explicit Offer(QObject *parent = 0);

  void setName(const QString &name);

  QString   getName() const { return m_Name; }
  QString   getFilename() const { return m_QFileInfo.fileName(); }
  QFileInfo getFileInfo() const { return m_QFileInfo; }

  bool modified() const { return m_Modified; }
  void open(const QString &filename);
  void save(const QString &filename = QString());

  void fromJsonObject(const QJsonObject &qJsonObject_Root);
  QJsonObject toJsonObject() const;

signals:

  void changed();

private:

  QString   m_Name;
  QFileInfo m_QFileInfo;

  QList<Part *> m_QList_Parts;

  bool m_Modified;
};

#endif // OFFER_H
