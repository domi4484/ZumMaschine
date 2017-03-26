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

  explicit Offer(QObject *parent = 0);

  void setName(const QString &name);

  QString getName() const { return m_Name; }
  QString getFilename() const { return m_QFileInfo.fileName(); }

  bool modified() const { return m_Modified; }
  void save(const QString &filename = QString());

signals:

  void changed();

private:

  QString   m_Name;
  QFileInfo m_QFileInfo;

  QList<Part *> m_QList_Parts;

  bool m_Modified;
};

#endif // OFFER_H
