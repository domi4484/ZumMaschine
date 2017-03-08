
// File includes ---------------------------
#include "Part.h"

// Projekt includes ------------------------
#include "Material.h"

// Qt includes -----------------------------

Part::Part(QObject *parent) :
  QObject(parent),
  m_Position     (),
  m_Name         (),
  m_Count        (),
  m_Width_mm     (),
  m_Height_mm    (),
  m_Thickness_mm (),
  m_CutLenght_m  (),
  m_Material     (NULL),
  m_Surface_m2       (0.0),
  m_Volume_m3        (0.0),
  m_MaterialPrice    (0.0),
  m_MaterialPriceTot (0.0),
  m_CutPrice         (0.0),
  m_CutPriceTot      (0.0),
  m_Price            (0.0),
  m_PriceTot         (0.0)
{
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

void Part::setMaterial(Material *material)
{
  m_Material = material;
  calculate();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::calculate()
{
  if(m_Material == NULL)
    return;

  m_Surface_m2 = (m_Width_mm/1000.0) * (m_Height_mm/1000.0);
  m_Volume_m3 = m_Surface_m2 * m_Thickness_mm/1000.0;

  m_MaterialPrice = m_Surface_m2 * m_Material->getSurfaceValue(m_Thickness_mm);
  m_MaterialPriceTot = m_MaterialPrice * m_Count;

  m_CutPrice = m_CutLenght_m * m_Material->getCutValue(m_Thickness_mm);
  m_CutPriceTot = m_CutPrice * m_Count;

  m_Price = m_MaterialPrice + m_CutPrice;
  m_PriceTot = m_Price * m_Count;
}

