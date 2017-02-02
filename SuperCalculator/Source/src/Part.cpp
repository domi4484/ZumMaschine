#include "Part.h"

Part::Part(QObject *parent) :
  QObject(parent),
  m_Name_mm(),
  m_Width_mm(),
  m_Height_mm(),
  m_Thick_mm(),
  m_CutLenght_m(),
  m_Material()
{

}

void Part::setTreeWidgetItem(QTreeWidgetItem *qTreeWidgetItem)
{
  m_QTreeWidgetItem = qTreeWidgetItem;

  if(m_QTreeWidgetItem == NULL)
    return;

  m_QTreeWidgetItem->
}

QTreeWidgetItem *Part::getTreeWidgetItem() const
{
  return m_QTreeWidgetItem;
}
