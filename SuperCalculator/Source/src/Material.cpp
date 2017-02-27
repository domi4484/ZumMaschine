
// File includes ---------------------------
#include "Material.h"

// Project includes ------------------------
#include "Exception.h"

// Qt includes -----------------------------
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

//-----------------------------------------------------------------------------------------------------------------------------

const QString Material::_CONST::LOCATION           ("Werkstoffen");
const QString Material::_CONST::FILENAME_EXTENSION (".material.json");

const QString Material::_CONST::JSON::NAME ("name");

//-----------------------------------------------------------------------------------------------------------------------------

Material::Material(const QFileInfo &qFileInfo) :
  m_QFileInfo(qFileInfo)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void Material::Load()
{
  if(m_QFileInfo.exists() == false)
    throw Exception(QString("File '%1' does not exist").arg(m_QFileInfo.filePath()));

  QFile qFile(m_QFileInfo.filePath());
  if(qFile.open(QIODevice::ReadOnly | QIODevice::Text)
     == false)
  {
    throw Exception(QString("Can't open '%1'").arg(m_QFileInfo.filePath()));
  }

  QString fileContent = qFile.readAll();
  qFile.close();

  QJsonParseError qJsonParseError;
  QJsonDocument qJsonDocument = QJsonDocument::fromJson(fileContent.toUtf8(),
                                                        &qJsonParseError);

  if(qJsonParseError.error != QJsonParseError::NoError)
  {
    throw Exception(QString("Can't parse '%1' -> %2").arg(m_QFileInfo.filePath())
                                                     .arg(qJsonParseError.errorString()));
  }

  QJsonObject qJsonObject = qJsonDocument.object();
  QJsonValue qJsonValue_Name = qJsonObject.value(_CONST::JSON::NAME);
  m_Name = qJsonValue_Name.toString();
}

//-----------------------------------------------------------------------------------------------------------------------------

QString Material::Name() const
{
  return m_Name;
}

//-----------------------------------------------------------------------------------------------------------------------------
