
// Files includes --------------------------
#include "MainWindow.h"
#include "ui_MainWindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_Ui(new Ui::MainWindow),
  m_CurrentPart(NULL),
  m_QList_Parts()
{
  // Qt ui setup
  m_Ui->setupUi(this);

  setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                                   .arg(QApplication::applicationVersion()));

  m_Ui->m_QTreeWidget->setColumnWidth(Column_Position,   30);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Quantity,   30);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Name,       150);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Size,       60);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Thickness,  50);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_CutLength,  60);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Material,   100);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_Price,      50);
  m_Ui->m_QTreeWidget->setColumnWidth(Column_PriceTotal, 50);

  // Settings
  m_Settings = new Settings(this);

  // Default Piece
  Part *part = new Part();
  m_QList_Parts.append(part);
  m_CurrentPart = part;

  // Load materials
  loadMaterials();

  // Update parts
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  while(m_QList_Parts.isEmpty() == false)
  {
    delete m_QList_Parts.takeLast();
  }

  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Settings_triggered()
{
  Settings_Gui settings_Gui(m_Settings,
                            this);
  if(settings_Gui.exec() == QDialog::Rejected)
    return;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Exit_triggered()
{
  QApplication::quit();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QSpinBox_Pieces_valueChanged(int arg1)
{
  m_CurrentPart->setCount(arg1);
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QDoubleSpinBox_Width_valueChanged(double arg1)
{
  m_CurrentPart->setWidth_mm(arg1);
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QDoubleSpinBox_Height_valueChanged(double arg1)
{
  m_CurrentPart->setHeight_mm(arg1);
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QDoubleSpinBox_CutLength_valueChanged(double arg1)
{
  m_CurrentPart->setCutLenght_m(arg1);
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::loadMaterials()
{
  // Get material files
  QDir qDir(Material::_CONST::LOCATION);
  QFileInfoList qFileInfoList = qDir.entryInfoList(QStringList() << "*" + Material::_CONST::FILENAME_EXTENSION,
                                                   QDir::Files);

  if(qFileInfoList.isEmpty())
  {
     QMessageBox::critical(this,
                           tr("Error opening material file."),
                           tr("No material files found in '%1'.").arg(qDir.absolutePath()));
  }

  // Clear materials in Gui
  m_Ui->m_QComboBox_Material->clear();

  // Load Material files
  foreach (QFileInfo qFileInfo, qFileInfoList)
  {
    Material *material = new Material(qFileInfo);
    try
    {
      material->Load();
      m_QMap_Materials.insert(material->getName(),
                              material);

      m_Ui->m_QComboBox_Material->addItem(material->getName());
    }
    catch(const Exception &exception)
    {
      QMessageBox::critical(this,
                            tr("Error opening material file."),
                            exception.GetText());
    }
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::updatePart()
{
  m_Ui->m_QLabel_MaterialKostenEinzeln ->setText(QString::number(m_CurrentPart->getMaterialPrice()));
  m_Ui->m_QLabel_MaterialKosten        ->setText(QString::number(m_CurrentPart->getMaterialPriceTot()));
  m_Ui->m_QLabel_SchneidKostenEinzeln  ->setText(QString::number(m_CurrentPart->getCutPrice()));
  m_Ui->m_QLabel_SchneidKosten         ->setText(QString::number(m_CurrentPart->getCutPriceTot()));
  m_Ui->m_QLabel_TotalEinzeln          ->setText(QString::number(m_CurrentPart->getPrice()));
  m_Ui->m_QLabel_Total                 ->setText(QString::number(m_CurrentPart->getPriceTot()));

  updatePartsList();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::updatePartsList()
{
  m_Ui->m_QTreeWidget->clear();

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
    qTreeWidgetItem->setText(Column_Material,   m_QList_Parts.at(i)->getMaterial()->getName());
    qTreeWidgetItem->setText(Column_Price,      QString::number(m_QList_Parts.at(i)->getPrice()));
    qTreeWidgetItem->setText(Column_PriceTotal, QString::number(m_QList_Parts.at(i)->getPriceTot()));

    m_Ui->m_QTreeWidget->addTopLevelItem(qTreeWidgetItem);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QComboBox_Thickness_currentIndexChanged(const QString &value)
{
  if(value.isEmpty())
    return;

  m_CurrentPart->setThickness_mm(value.toDouble());
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QComboBox_Material_currentIndexChanged(const QString &value)
{
  qDebug() << "on_m_QComboBox_Material_currentIndexChanged";

  Material *material = m_QMap_Materials.value(value);
  m_CurrentPart->setMaterial(material);

  m_Ui->m_QComboBox_Thickness->clear();
  foreach (double thickness, material->getThicknessList())
  {
    m_Ui->m_QComboBox_Thickness->addItem(QString::number(thickness));
  }
}
