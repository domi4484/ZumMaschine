
// File includes ---------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QComboBox>

Part::Part(QObject *parent) :
  QObject(parent),
  m_Name_mm     (),
  m_Width_mm    (),
  m_Height_mm   (),
  m_Thick_mm    (),
  m_CutLenght_m (),
  m_Material    (),
  m_QLineEdit_Name           (NULL),
  m_QDoubleSpinBox_Width     (NULL),
  m_QDoubleSpinBox_Height    (NULL),
  m_QDoubleSpinBox_Thick     (NULL),
  m_QDoubleSpinBox_CutLenght (NULL),
  m_QComboBox_Material       (NULL),
  m_QTreeWidgetItem (NULL)
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void Part::setupTreeWidgetItem(QTreeWidgetItem *qTreeWidgetItem)
{
  m_QTreeWidgetItem = qTreeWidgetItem;

  if(m_QTreeWidgetItem == NULL)
    return;

  m_QLineEdit_Name = new QLineEdit();
  m_QTreeWidgetItem->treeWidget()->setItemWidget(m_QTreeWidgetItem,
                                                 0,
                                                 m_QLineEdit_Name);
  m_QLineEdit_Name->setText(m_Name_mm);

  m_QDoubleSpinBox_Width = new QDoubleSpinBox();
  m_QTreeWidgetItem->treeWidget()->setItemWidget(m_QTreeWidgetItem,
                                                 1,
                                                 m_QDoubleSpinBox_Width);
  m_QDoubleSpinBox_Width->setValue(m_Width_mm);

  m_QDoubleSpinBox_Height = new QDoubleSpinBox();
  m_QTreeWidgetItem->treeWidget()->setItemWidget(m_QTreeWidgetItem,
                                                 2,
                                                 m_QDoubleSpinBox_Height);
  m_QDoubleSpinBox_Height->setValue(m_Height_mm);

  m_QDoubleSpinBox_Thick = new QDoubleSpinBox();
  m_QTreeWidgetItem->treeWidget()->setItemWidget(m_QTreeWidgetItem,
                                                 3,
                                                 m_QDoubleSpinBox_Thick);
  m_QDoubleSpinBox_Thick->setValue(m_Thick_mm);

  m_QDoubleSpinBox_CutLenght = new QDoubleSpinBox();
  m_QTreeWidgetItem->treeWidget()->setItemWidget(m_QTreeWidgetItem,
                                                 4,
                                                 m_QDoubleSpinBox_CutLenght);
  m_QDoubleSpinBox_CutLenght->setValue(m_CutLenght_m);


//  m_QTreeWidgetItem->setText(5, m_Material);
}

//-----------------------------------------------------------------------------------------------------------------------------

QTreeWidgetItem *Part::getTreeWidgetItem() const
{
  return m_QTreeWidgetItem;
}
