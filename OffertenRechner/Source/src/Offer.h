#ifndef OFFER_H
#define OFFER_H

// Project includes ------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QObject>
#include <QFileInfo>

// Forward declaration ---------------------
class Materials_Gui;

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
      static const QString VALUE_NAME;
      static const QString ARRAY_PARTS;
    }; // JSON
  }; // _CONST

  explicit Offer(Materials_Gui *materials_Gui,
                 QObject *parent = 0);
  virtual ~Offer();

  void setName(const QString &name);

  QString   getName() const { return m_Name; }
  QString   getFilename() const { return m_QFileInfo.fileName(); }
  QFileInfo getFileInfo() const { return m_QFileInfo; }

  Part *addNewPart();
  Part *getPart(int position) const;
  QList<Part *> getPartsList() const;

  bool isModified() const { return m_Modified; }
  void open(const QString &filename);
  void save(const QString &filename = QString());

  void fromJsonObject(const QJsonObject &qJsonObject_Root);
  QJsonObject toJsonObject() const;

signals:

  void changed();

private slots:

  void slot_part_changed();

private:

  // Link to materials gui
  Materials_Gui *m_Materials_Gui;

  QString   m_Name;
  QFileInfo m_QFileInfo;

  QList<Part *> m_QList_Parts;

  bool m_Modified;
};

#endif // OFFER_H
