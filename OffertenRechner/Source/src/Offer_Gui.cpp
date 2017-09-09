
// Files includes --------------------------
#include "Offer_Gui.h"
#include "ui_Offer_Gui.h"

// Project includes ------------------------
#include "Exception.h"
#include "Material.h"
#include "Materials_Gui.h"
#include "Offer.h"
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
                     Materials_Gui *materials_Gui,
                     QWidget *parent)
  : QWidget(parent)
  , m_Ui(new Ui::Offer_Gui)
  , m_Offer(offer)
  , m_Settings(settings)
  , m_Materials_Gui(materials_Gui)
  , m_CurrentPart(NULL)
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

  if(m_Offer->getPartsList().isEmpty())
  {
    m_CurrentPart = m_Offer->addNewPart();
  }
  else
  {
    m_CurrentPart = m_Offer->getPartsList().first();
  }

  // Clear materials in Gui
  m_Ui->m_QComboBox_Material->clear();

  // Load Material files
  foreach (Material *material, m_Materials_Gui->getList())
  {
    m_Ui->m_QComboBox_Material->addItem(material->getName());
  }

  connect(m_CurrentPart,
          SIGNAL(changed()),
          SLOT(slot_Part_Changed()));

  slot_Part_Changed();
}

//-----------------------------------------------------------------------------------------------------------------------------

Offer_Gui::~Offer_Gui()
{
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
  foreach (Part *part, m_Offer->getPartsList())
  {
    QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(m_Ui->m_QTreeWidget);
    qTreeWidgetItem->setText(Column_Position,   QString::number(part->getPosition()));
    qTreeWidgetItem->setText(Column_Quantity,   QString::number(part->getCount()));
    qTreeWidgetItem->setText(Column_Name,       part->getName());
    qTreeWidgetItem->setText(Column_Size,       QString("%1x%2").arg(part->getWidth_mm())
                                                                .arg(part->getHeight_mm()));
    qTreeWidgetItem->setText(Column_Thickness,  QString::number(part->getThickness_mm()));
    qTreeWidgetItem->setText(Column_CutLength,  QString::number(part->getCutLenght_m()));
    if(part->getMaterial() != NULL)
    {
      qTreeWidgetItem->setText(Column_Material, part->getMaterial()->getName());
    }
    qTreeWidgetItem->setText(Column_Price,      QString::number(part->getPrice()   , 'f', 2));
    qTreeWidgetItem->setText(Column_PriceTotal, QString::number(part->getPriceTot(), 'f', 2));

    m_Ui->m_QTreeWidget->addTopLevelItem(qTreeWidgetItem);

    total += part->getPriceTot();
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

  Material *material = m_Materials_Gui->getMaterial(value);

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

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QLineEdit_Name_textChanged(const QString &arg1)
{
  m_CurrentPart->setName(arg1);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Offer_Gui::on_m_QCheckBox_MaterialIncluded_toggled(bool checked)
{
  m_CurrentPart->setMaterialIncluded(checked);
}
