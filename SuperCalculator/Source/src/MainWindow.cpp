
// Files includes --------------------------
#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes ------------------------
#include "Settings.h"
#include "Settings_Gui.h"

// Qt includes -----------------------------
#include <QDebug>
#include <QTimer>
#include <QFileSystemModel>
#include <QFileSystemWatcher>

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_Ui(new Ui::MainWindow),
  m_CurrentPart(NULL),
  m_QList_Parts()
{
  // Qt ui setup
  m_Ui->setupUi(this);

  // Settings
  m_Settings = new Settings(this);

  // Default Piece
  Part *part = new Part();
  m_QList_Parts.append(part);
  m_CurrentPart = part;

  QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem();
  m_Ui->m_QTreeWidget->addTopLevelItem(qTreeWidgetItem);
  part->setupTreeWidgetItem(qTreeWidgetItem);
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

void MainWindow::on_m_QDoubleSpinBox_Thickness_valueChanged(double arg1)
{
  m_CurrentPart->setThickness_mm(arg1);
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QDoubleSpinBox_CutLength_valueChanged(double arg1)
{
  m_CurrentPart->setCutLenght_m(arg1);
  updatePart();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::updatePart()
{
  m_Ui->m_QLabel_Total->setText(QString::number(m_CurrentPart->getPrice()));
}
