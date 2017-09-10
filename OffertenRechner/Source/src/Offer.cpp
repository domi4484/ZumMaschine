
// Files includes --------------------------
#include "Offer.h"

// Project includes ------------------------
#include "Exception.h"
#include "Materials_Gui.h"

// Qt includes -----------------------------
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

//-----------------------------------------------------------------------------------------------------------------------------

const QString Offer::_CONST::FILENAME_EXTENSION(".offer.json");

const QString Offer::_CONST::JSON::VALUE_NAME("Name");
const QString Offer::_CONST::JSON::ARRAY_PARTS("Parts");

//-----------------------------------------------------------------------------------------------------------------------------

Offer::Offer(Materials_Gui *materials_Gui,
             QObject *parent)
  : QObject(parent)
  , m_Materials_Gui(materials_Gui)
  , m_Name()
  , m_QFileInfo()
  , m_QList_Parts()
  , m_Modified(false)
{
}

//-----------------------------------------------------------------------------------------------------------------------------

Offer::~Offer()
{
  foreach (Part *part, m_QList_Parts)
  {
    delete part;
  }
  m_QList_Parts.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer::setName(const QString &name)
{
  m_Name = name;
  emit changed();
}

//-----------------------------------------------------------------------------------------------------------------------------

Part *Offer::addNewPart()
{
  Part *part = new Part(m_Materials_Gui);
  m_QList_Parts.append(part);
  part->setPosition(m_QList_Parts.size());

  QObject::connect(part,
                   SIGNAL(changed()),
                   SLOT(slot_part_changed()));

  return part;
}

//-----------------------------------------------------------------------------------------------------------------------------

Part *Offer::getPart(int position) const
{
  foreach (Part *part, m_QList_Parts)
  {
    if(part->getPosition() == position)
      return part;
  }

  return NULL;
}

//-----------------------------------------------------------------------------------------------------------------------------

QList<Part *> Offer::getPartsList() const
{
  return m_QList_Parts;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer::open(const QString &filename)
{
  if(filename.isEmpty())
  {
    throw Exception(tr("Filename not specified"));
  }

  m_QFileInfo.setFile(filename);
  m_Name = m_QFileInfo.baseName();

  QFile qFile(m_QFileInfo.filePath());
  if(qFile.open(QIODevice::ReadOnly | QIODevice::Text)
     == false)
  {
    throw Exception(tr("Can't open '%1' for reading").arg(m_QFileInfo.filePath()));
  }

  QJsonDocument qJsonDocument = QJsonDocument::fromJson(qFile.readAll());

  Offer::fromJsonObject(qJsonDocument.object());
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

  if(m_Name != m_QFileInfo.baseName())
    m_Name = m_QFileInfo.baseName();

  QJsonDocument qJsonDocument;
  qJsonDocument.setObject(Offer::toJsonObject());

  QFile qFile(m_QFileInfo.filePath());
  if(qFile.open(QIODevice::WriteOnly | QIODevice::Text)
     == false)
  {
    throw Exception(tr("Can't open '%1' for writing").arg(m_QFileInfo.filePath()));
  }

  qFile.write(qJsonDocument.toJson());

  m_Modified = false;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer::fromJsonObject(const QJsonObject &qJsonObject_Root)
{
  // Clear current parts
  foreach (Part *part, m_QList_Parts)
  {
    delete part;
  }
  m_QList_Parts.clear();

//  m_Name = qJsonObject_Root.value(_CONST::JSON::VALUE_NAME).toString();

  m_QList_Parts.clear();
  QJsonArray qJsonArray_Parts = qJsonObject_Root.value(_CONST::JSON::ARRAY_PARTS).toArray();
  foreach (QJsonValue qJSonValue_Part, qJsonArray_Parts)
  {
    Part *part = new Part(m_Materials_Gui,
                          this);
    part->fromJsonObject(qJSonValue_Part.toObject());

    m_QList_Parts.append(part);

    connect(part,
            SIGNAL(changed()),
            SLOT(slot_part_changed()));
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

QJsonObject Offer::toJsonObject() const
{
  QJsonObject qJsonObject_Root;
  qJsonObject_Root.insert(_CONST::JSON::VALUE_NAME,
                          m_Name);

  if(m_QList_Parts.isEmpty() == false)
  {
    QJsonArray qJsonArray_Parts;

    foreach (Part *part, m_QList_Parts)
    {
      qJsonArray_Parts.append(part->toJsonObject());
    }

    qJsonObject_Root.insert(_CONST::JSON::ARRAY_PARTS,
                            qJsonArray_Parts);
  }

  return qJsonObject_Root;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer::slot_part_changed()
{
  m_Modified = true;
  emit changed();
}

