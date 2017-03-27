
// Files includes --------------------------
#include "Offer.h"

// Project includes ------------------------
#include "Exception.h"

// Qt includes -----------------------------
#include <QJsonDocument>
#include <QJsonObject>

//-----------------------------------------------------------------------------------------------------------------------------

const QString Offer::_CONST::FILENAME_EXTENSION(".offer.json");

const QString Offer::_CONST::JSON::NAME("name");

//-----------------------------------------------------------------------------------------------------------------------------

Offer::Offer(QObject *parent)
  : QObject(parent)
  , m_Name()
  , m_QList_Parts()
  , m_Modified(true)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer::setName(const QString &name)
{
  m_Name = name;
  emit changed();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer::save(const QString &filename)
{
  if(   filename.isEmpty()
     && m_QFileInfo.fileName().isEmpty())
  {
    throw Exception(tr("Filename not specified"));
  }

  if(filename.isEmpty() == false)
    m_QFileInfo.setFile(filename);

  QJsonDocument qJsonDocument;
  qJsonDocument.setObject(Offer::toJsonObject());

  QFile qFile(m_QFileInfo.filePath());
  if(qFile.open(QIODevice::WriteOnly | QIODevice::Text)
     == false)
  {
    throw Exception(tr("Can't open '%1' for writing").arg(m_QFileInfo.filePath()));
  }

  qFile.write(qJsonDocument.toJson());
}

//-----------------------------------------------------------------------------------------------------------------------------

QJsonObject Offer::toJsonObject() const
{
  QJsonObject qJsonObject_Root;
  qJsonObject_Root.insert(_CONST::JSON::NAME,
                          m_Name);

  return qJsonObject_Root;
}

