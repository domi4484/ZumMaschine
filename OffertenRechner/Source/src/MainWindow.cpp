
// Files includes --------------------------
#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes ------------------------
#include "Exception.h"
#include "Material.h"
#include "Materials_Gui.h"
#include "Settings.h"
#include "Settings_Gui.h"
#include "Offer.h"
#include "Offer_Gui.h"

// Qt includes -----------------------------
#include <QDebug>
#include <QDockWidget>
#include <QFileDialog>
#include <QTimer>
#include <QFileSystemModel>
#include <QFileSystemWatcher>
#include <QMessageBox>
#include <QTreeWidgetItem>

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_Ui(new Ui::MainWindow),
  m_Settings(NULL),
  m_QDockWidget_MaterialsGui(NULL),
  m_Materials_Gui(NULL),
  m_QMap_Offers()
{
  // Qt ui setup
  m_Ui->setupUi(this);

  setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                                   .arg(QApplication::applicationVersion()));

  m_Ui->m_QTabWidget->clear();

  // Settings
  m_Settings = new Settings(this);

  // Load materials
  m_QDockWidget_MaterialsGui = new QDockWidget(tr("Materials"),
                                               this);
  m_Materials_Gui = new Materials_Gui(m_QDockWidget_MaterialsGui);
  m_QDockWidget_MaterialsGui->setWidget(m_Materials_Gui);
  m_QDockWidget_MaterialsGui->setFloating(false);
  MainWindow::addDockWidget(Qt::RightDockWidgetArea,
                            m_QDockWidget_MaterialsGui);
  try
  {
    m_Materials_Gui->loadMaterials(m_Settings->get_MaterialsDirectory());
  }
  catch(const Exception &exception)
  {
    QMessageBox::critical(this,
                          tr("Error opening material file."),
                          exception.GetText());
  }

  // TODO load last offers

  // Default Offer
  if(   m_QMap_Offers.isEmpty()
     && m_Materials_Gui->isEmpty() == false)
  {
    Offer *offer = new Offer(m_Materials_Gui);
    offer->setName("New");
    Offer_Gui *offer_Gui = new Offer_Gui(offer,
                                         m_Settings,
                                         m_Materials_Gui,
                                         this);
    m_QMap_Offers.insert(offer,
                         offer_Gui);

    m_Ui->m_QTabWidget->addTab(offer_Gui,
                               offer->getName());

    connect(offer,
            SIGNAL(changed()),
            SLOT(slot_Offer_Changed()));
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  closeOffers();

  delete m_Materials_Gui;
  delete m_QDockWidget_MaterialsGui;

  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::slot_Offer_Changed()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_New_triggered()
{
  // Check materials loaded
  if(m_Materials_Gui->isEmpty())
  {
    QMessageBox::critical(this,
                          tr("Error no material files loaded."),
                          tr("Please check your settings."));
    return;
  }

  Offer *offer = new Offer(m_Materials_Gui);
  offer->setName("New");
  Offer_Gui *offer_Gui = new Offer_Gui(offer,
                                       m_Settings,
                                       m_Materials_Gui,
                                       this);
  m_QMap_Offers.insert(offer,
                       offer_Gui);

  m_Ui->m_QTabWidget->addTab(offer_Gui,
                             offer->getName());

  connect(offer,
          SIGNAL(changed()),
          SLOT(slot_Offer_Changed()));
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Open_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this,
                                                  tr("Open offer document"),
                                                  QString(),
                                                  "*" + Offer::_CONST::FILENAME_EXTENSION);

  if(filename.isEmpty())
    return;

  QFileInfo qFileInfo(filename);

  // Check if already open
  foreach (Offer *offer, m_QMap_Offers.keys())
  {
    if(offer->getFileInfo() == qFileInfo)
    {
      m_Ui->m_QTabWidget->setCurrentWidget(m_QMap_Offers.value(offer));
      return;
    }
  }

  // Open offer
  Offer *offer = new Offer(m_Materials_Gui);
  try
  {
    offer->open(filename);
    Offer_Gui *offer_Gui = new Offer_Gui(offer,
                                         m_Settings,
                                         m_Materials_Gui,
                                         this);
    m_QMap_Offers.insert(offer,
                         offer_Gui);

    m_Ui->m_QTabWidget->addTab(offer_Gui,
                               offer->getName());

    m_Ui->m_QTabWidget->setCurrentWidget(offer_Gui);

    connect(offer,
            SIGNAL(changed()),
            SLOT(slot_Offer_Changed()));
  }
  catch(const Exception &exception)
  {
    QMessageBox::critical(this,
                          tr("Error opening offer."),
                          exception.GetText());

    delete offer;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Save_triggered()
{
  try
  {
    Offer_Gui *offer_Gui = qobject_cast<Offer_Gui *>(m_Ui->m_QTabWidget->currentWidget());
    Offer *offer = offer_Gui->getOffer();
    if(offer->isModified() == false)
      return;

    if(offer->getFilename().isEmpty())
    {
      QString filename = QFileDialog::getSaveFileName(this,
                                                      tr("Save offer"),
                                                      "",
                                                      "*" + Offer::_CONST::FILENAME_EXTENSION);

      if(filename.isEmpty())
        return;

      if(filename.endsWith(Offer::_CONST::FILENAME_EXTENSION) == false)
      {
        filename.append(Offer::_CONST::FILENAME_EXTENSION);
      }

      offer->save(filename);
    }
    else
    {
      offer->save();
    }
  }
  catch(const Exception &exception)
  {
    QMessageBox::critical(this,
                          tr("Error saving offer."),
                          exception.GetText());
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_SaveAs_triggered()
{

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

void MainWindow::loadOffers()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::closeOffers()
{
  for(int i = m_QMap_Offers.size() -1; i >= 0; i--)
  {
    delete m_QMap_Offers.values().at(i);
    delete m_QMap_Offers.keys().at(i);
  }
  m_QMap_Offers.clear();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QTabWidget_tabCloseRequested(int index)
{
  Offer_Gui *offer_Gui = (Offer_Gui *)m_Ui->m_QTabWidget->widget(index);
  Offer *offer = offer_Gui->getOffer();

  if(offer->isModified() == true)
  {
    if(QMessageBox::question(this,
                             tr("File close"),
                             tr("The file '%1' has unsaved changes. Do you want to ignore changes and close it?").arg(offer->getFilename()))
       == QMessageBox::No)
    {
      return;
    }
  }

  m_QMap_Offers.take(offer);
  delete offer_Gui;
  delete offer;
}
