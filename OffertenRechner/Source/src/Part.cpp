
// File includes ---------------------------
#include "Part.h"

// Projekt includes ------------------------
#include "Material.h"
#include "Materials_Gui.h"

// Qt includes -----------------------------


//-----------------------------------------------------------------------------------------------------------------------------

const QString Part::_CONST::JSON::VALUE_POSITION         ("Position");
const QString Part::_CONST::JSON::VALUE_NAME             ("Name");
const QString Part::_CONST::JSON::VALUE_COUNT            ("Count");
const QString Part::_CONST::JSON::VALUE_WIDTH_MM         ("Width_mm");
const QString Part::_CONST::JSON::VALUE_HEIGHT_MM        ("Height_mm");
const QString Part::_CONST::JSON::VALUE_THICKNESS_MM     ("Thickness_mm");
const QString Part::_CONST::JSON::VALUE_CUTLENGTH_M      ("CutLength_m");
const QString Part::_CONST::JSON::VALUE_MATERIALINCLUDED ("MaterialIncluded");
const QString Part::_CONST::JSON::VALUE_MATERIALNAME     ("MaterialName");

//-----------------------------------------------------------------------------------------------------------------------------

Part::Part(Materials_Gui *materials_Gui,
           QObject *parent) :
  QObject(parent),
  m_Materials_Gui   (materials_Gui),
  m_Position         (),
  m_Name             (),
  m_Count            (),
  m_Width_mm         (),
  m_Height_mm        (),
  m_Thickness_mm     (0.0),
  m_CutLenght_m      (),
  m_MaterialIncluded (true),
  m_Material         (NULL),
  m_Surface_m2       (0.0),
  m_Volume_m3        (0.0),
  m_MaterialPrice    (0.0),
  m_MaterialPriceTot (0.0),
  m_CutPrice         (0.0),
  m_CutPriceTot      (0.0),
  m_Price            (0.0),
  m_PriceTot         (0.0)
{
  if(materials_Gui->isEmpty() == false)
  {
    m_Material = materials_Gui->first();
    m_Thickness_mm = m_Material->getThicknessList().first();
  }

  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setPosition(int position)
{
  m_Position = position;
  emit changed();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setName(const QString &name)
{
  m_Name = name;
  emit changed();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setCount(int count)
{
  m_Count = count;
  calculate();

}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setWidth_mm(double width_mm)
{
  m_Width_mm = width_mm;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setHeight_mm(double height_mm)
{
  m_Height_mm = height_mm;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setThickness_mm(double thickness_mm)
{
  m_Thickness_mm = thickness_mm;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setCutLenght_m(double cutLength_m)
{
  m_CutLenght_m = cutLength_m;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setMaterialIncluded(bool included)
{
  m_MaterialIncluded = included;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setMaterial(Material *material)
{
  m_Material = material;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

double Part::getMaterialSurfaceValue() const
{
  if(m_Material == NULL)
      return 0.0;

  return m_Material->getSurfaceValue(m_Thickness_mm);
}

//-----------------------------------------------------------------------------------------------------------------------------

double Part::getMaterialCutValue() const
{
  if(m_Material == NULL)
      return 0.0;

  return m_Material->getCutValue(m_Thickness_mm);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::fromJsonObject(const QJsonObject &qJsonObject_Root)
{
  m_Position = qJsonObject_Root.value(_CONST::JSON::VALUE_POSITION).toInt();
  m_Name     = qJsonObject_Root.value(_CONST::JSON::VALUE_NAME).toString();

  m_Count            = qJsonObject_Root.value(_CONST::JSON::VALUE_COUNT).toInt();
  m_Width_mm         = qJsonObject_Root.value(_CONST::JSON::VALUE_WIDTH_MM).toDouble();
  m_Height_mm        = qJsonObject_Root.value(_CONST::JSON::VALUE_HEIGHT_MM).toDouble();
  m_Thickness_mm     = qJsonObject_Root.value(_CONST::JSON::VALUE_THICKNESS_MM).toDouble();
  m_CutLenght_m      = qJsonObject_Root.value(_CONST::JSON::VALUE_CUTLENGTH_M).toDouble();
  m_MaterialIncluded = qJsonObject_Root.value(_CONST::JSON::VALUE_MATERIALINCLUDED).toBool();

  QString materialName = qJsonObject_Root.value(_CONST::JSON::VALUE_MATERIALNAME).toString();
  m_Material = m_Materials_Gui->getMaterial(materialName);

  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

QJsonObject Part::toJsonObject() const
{
  QJsonObject qJsonObject_Root;

  qJsonObject_Root.insert(_CONST::JSON::VALUE_POSITION,         m_Position);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_NAME,             m_Name);

  qJsonObject_Root.insert(_CONST::JSON::VALUE_COUNT,            m_Count);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_WIDTH_MM,         m_Width_mm);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_HEIGHT_MM,        m_Height_mm);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_THICKNESS_MM,     m_Thickness_mm);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_CUTLENGTH_M,      m_CutLenght_m);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_MATERIALINCLUDED, m_MaterialIncluded);
  qJsonObject_Root.insert(_CONST::JSON::VALUE_MATERIALNAME,     m_Material->getName());

  return qJsonObject_Root;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::calculate()
{
  if(m_Material == NULL)
    return;

  m_Surface_m2 = (m_Width_mm/1000.0) * (m_Height_mm/1000.0);
  m_Volume_m3 = m_Surface_m2 * m_Thickness_mm/1000.0;

  m_MaterialPrice = m_Surface_m2 * m_Material->getSurfaceValue(m_Thickness_mm) * m_MaterialIncluded;
  m_MaterialPriceTot = m_MaterialPrice * m_Count;

  m_CutPrice = m_CutLenght_m * m_Material->getCutValue(m_Thickness_mm);
  m_CutPriceTot = m_CutPrice * m_Count;

  m_Price = m_MaterialPrice + m_CutPrice;
  m_PriceTot = m_Price * m_Count;

  emit changed();
}

