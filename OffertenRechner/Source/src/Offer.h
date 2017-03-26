#ifndef OFFER_H
#define OFFER_H

// Project includes ------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QObject>

class Offer : public QObject
{
  Q_OBJECT
public:

  explicit Offer(QObject *parent = 0);

  void setName(const QString &name);

  QString getName() const { return m_Name; }
  QString getFilename() const { return m_Filename; }

  bool modified() const { return m_Modified; }
  void save(const QString &filename);

signals:

  void changed();

private:

  QString m_Name;
  QString m_Filename;

  QList<Part *> m_QList_Parts;

  bool m_Modified;
};

#endif // OFFER_H
