
// Files includes --------------------------
#include "Offer.h"

// Project includes ------------------------
#include "Exception.h"

// Qt includes -----------------------------
#include <QJsonDocument>
#include <QJsonObject>

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
     && m_QFileInfo.exists() == false)
  {
    throw Exception(tr("Filename not specified"));
  }

  QJsonObject qJsonObject_Document;
  qJsonObject_Document.insert(/*_CONST::JSON::*/"NAME",
                              m_Name);

  QJsonDocument qJsonDocument;
  qJsonDocument.setObject(qJsonObject_Document);

  QFile qFile(m_QFileInfo.filePath());
  if(qFile.open(QIODevice::WriteOnly | QIODevice::Text)
     == false)
  {
    throw Exception(tr("Can't open '%1' for writing").arg(m_QFileInfo.filePath()));
  }

  qFile.write(qJsonDocument.toJson());
}

