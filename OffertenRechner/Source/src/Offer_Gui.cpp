
// Files includes --------------------------
#include "Offer_Gui.h"
#include "ui_Offer_Gui.h"

// Project includes ------------------------
#include "Exception.h"
#include "Material.h"
#include "Settings.h"
#include "Settings_Gui.h"

// Qt includes -----------------------------
#include <QDebug>
#include <QTimer>
#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QTreeWidgetItem>

//-----------------------------------------------------------------------------------------------------------------------------

Offer_Gui::Offer_Gui(Offer *offer,
                     Settings *settings,
                     QMap<QString, Material *> *qMap_Materials,
                     QWidget *parent) :
  QWidget(parent),
  m_Ui(new Ui::Offer_Gui),
  m_Offer(offer),
  m_Settings(settings),
  m_QMap_Materials(qMap_Materials),
  m_CurrentPart(NULL),
  m_QList_Parts()
{
  // Qt ui setup
  m_Ui->setupUi(this);

  m_Ui->m_QTreeWidget->setColumnWidth(Column_Position,   30);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Quantity,   30);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Name,       150);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Size,       60);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Thickness,  50);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_CutLength,  60);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Material,   100);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Price,      50);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_PriceTotal, 50);

  // Default Piece
  Part *part = new Part(m_QMap_Materials);
  m_QList_Parts.append(part);
  m_CurrentPart = part;

  // Clear materials in Gui
  m_Ui->m_QComboBox_Material->clear();

  // Load Material files
  foreach (Material *material, m_QMap_Materials->values())
  {
    m_Ui->m_QComboBox_Material->addItem(material->getName());
  }

  connect(part,
          SIGNAL(changed()),
          SLOT(slot_Part_Changed()));

  slot_Part_Changed();
}

//-----------------------------------------------------------------------------------------------------------------------------

Offer_Gui::~Offer_Gui()
{
  while(m_QList_Parts.isEmpty() == false)
  {
    delete m_QList_Parts.takeLast();
  }

  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::slot_Part_Changed()
{
  m_Ui->m_QLineEdit_Name                         ->setText(m_CurrentPart->getName());
  m_Ui->m_QSpinBox_Pieces                        ->setValue(m_CurrentPart->getCount());
  m_Ui->m_QDoubleSpinBox_Width                   ->setValue(m_CurrentPart->getWidth_mm());
  m_Ui->m_QDoubleSpinBox_Height                  ->setValue(m_CurrentPart->getHeight_mm());
  m_Ui->m_QDoubleSpinBox_CutLength               ->setValue(m_CurrentPart->getCutLenght_m());
  m_Ui->m_QCheckBox_MaterialIncluded             ->setChecked(m_CurrentPart->getMaterialIncluded());
  if(m_CurrentPart->getMaterial() != NULL)
  {
    m_Ui->m_QComboBox_Material                     ->setCurrentText(m_CurrentPart->getMaterial()->getName());
  }
  else
  {
    m_Ui->m_QComboBox_Material                     ->setCurrentIndex(0);
  }
  m_Ui->m_QComboBox_Thickness                    ->setCurrentText(QString::number(m_CurrentPart->getThickness_mm()));
  m_Ui->m_QSpinBox_MaterialKostenProQuadratMeter ->setValue(m_CurrentPart->getMaterialSurfaceValue());
  m_Ui->m_QSpinBox_SchneidkostenProMeter         ->setValue(m_CurrentPart->getMaterialCutValue());

  m_Ui->m_QLabel_MaterialKostenEinzeln ->setText(QString::number(m_CurrentPart->getMaterialPrice()    , 'f', 2));
  m_Ui->m_QLabel_MaterialKosten        ->setText(QString::number(m_CurrentPart->getMaterialPriceTot() , 'f', 2));
  m_Ui->m_QLabel_SchneidKostenEinzeln  ->setText(QString::number(m_CurrentPart->getCutPrice()         , 'f', 2));
  m_Ui->m_QLabel_SchneidKosten         ->setText(QString::number(m_CurrentPart->getCutPriceTot()      , 'f', 2));
  m_Ui->m_QLabel_TotalEinzeln          ->setText(QString::number(m_CurrentPart->getPrice()            , 'f', 2));
  m_Ui->m_QLabel_Total                 ->setText(QString::number(m_CurrentPart->getPriceTot()         , 'f', 2));

  updatePartsList();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QAction_File_Settings_triggered()
{
  Settings_Gui settings_Gui(m_Settings,
                            this);
  if(settings_Gui.exec() == QDialog::Rejected)
    return;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QSpinBox_Pieces_valueChanged(int arg1)
{
  m_CurrentPart->setCount(arg1);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QDoubleSpinBox_Width_valueChanged(double arg1)
{
  m_CurrentPart->setWidth_mm(arg1);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QDoubleSpinBox_Height_valueChanged(double arg1)
{
  m_CurrentPart->setHeight_mm(arg1);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QDoubleSpinBox_CutLength_valueChanged(double arg1)
{
  m_CurrentPart->setCutLenght_m(arg1);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::updatePartsList()
{
  m_Ui->m_QTreeWidget->clear();

  double total = 0.0;
  for (int i=0; i<m_QList_Parts.size(); i++)
  {
    QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(m_Ui->m_QTreeWidget);
    qTreeWidgetItem->setText(Column_Position,   QString::number(i));
    qTreeWidgetItem->setText(Column_Quantity,   QString::number(m_QList_Parts.at(i)->getCount()));
    qTreeWidgetItem->setText(Column_Name,       m_QList_Parts.at(i)->getName());
    qTreeWidgetItem->setText(Column_Size,       QString("%1x%2").arg(m_QList_Parts.at(i)->getWidth_mm())
                                                                .arg(m_QList_Parts.at(i)->getHeight_mm()));
    qTreeWidgetItem->setText(Column_Thickness,  QString::number(m_QList_Parts.at(i)->getThickness_mm()));
    qTreeWidgetItem->setText(Column_CutLength,  QString::number(m_QList_Parts.at(i)->getCutLenght_m()));
    if(m_QList_Parts.at(i)->getMaterial() != NULL)
    {
      qTreeWidgetItem->setText(Column_Material,   m_QList_Parts.at(i)->getMaterial()->getName());
    }
    qTreeWidgetItem->setText(Column_Price,      QString::number(m_QList_Parts.at(i)->getPrice()   , 'f', 2));
    qTreeWidgetItem->setText(Column_PriceTotal, QString::number(m_QList_Parts.at(i)->getPriceTot(), 'f', 2));

    m_Ui->m_QTreeWidget->addTopLevelItem(qTreeWidgetItem);

    total += m_QList_Parts.at(i)->getPriceTot();
  }
  m_Ui->m_QLabel_ListTotal->setText(QString::number(total));
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QComboBox_Thickness_currentIndexChanged(const QString &value)
{
  if(value.isEmpty())
    return;

  if (m_CurrentPart == NULL)
    return;

  m_CurrentPart->setThickness_mm(value.toDouble());
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QComboBox_Material_currentIndexChanged(const QString &value)
{

  Material *material = m_QMap_Materials->value(value);

  if(m_CurrentPart != NULL)
  {
    m_CurrentPart->setMaterial(material);
  }

  m_Ui->m_QComboBox_Thickness->clear();
  foreach (double thickness, material->getThicknessList())
  {
    m_Ui->m_QComboBox_Thickness->addItem(QString::number(thickness));
  }
}
