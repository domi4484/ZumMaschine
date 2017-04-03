
// Files includes --------------------------
#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes ------------------------
#include "Exception.h"
#include "Material.h"
#include "Settings.h"
#include "Settings_Gui.h"
#include "Offer.h"
#include "Offer_Gui.h"

// Qt includes -----------------------------
#include <QDebug>
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
  loadMaterials(m_Settings->get_MaterialsDirectory());

  // TODO load last offers

  // Default Offer
  if(m_QMap_Offers.isEmpty())
  {
    Offer *offer = new Offer();
    offer->setName("New");
    Offer_Gui *offer_Gui = new Offer_Gui(offer,
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
  closeMaterials();

  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::slot_Offer_Changed()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_New_triggered()
{

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
  Offer *offer = new Offer();
  try
  {
    offer->open(filename);
    Offer_Gui *offer_Gui = new Offer_Gui(offer,
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
    if(offer->modified() == false)
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

}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::loadMaterials(const QString &materialsDirectory)
{
  // Get material files
  QDir qDir(materialsDirectory);
  QFileInfoList qFileInfoList = qDir.entryInfoList(QStringList() << "*" + Material::_CONST::FILENAME_EXTENSION,
                                                   QDir::Files);

  if(qFileInfoList.isEmpty())
  {
     QMessageBox::critical(this,
                           tr("Error opening material file."),
                           tr("No material files found in '%1'.").arg(qDir.absolutePath()));
  }

  // Load Material files
  foreach (QFileInfo qFileInfo, qFileInfoList)
  {
    Material *material = new Material(qFileInfo);
    try
    {
      material->Load();
      m_QMap_Materials.insert(material->getName(),
                              material);
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

void MainWindow::closeMaterials()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::loadOffers()
{

}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::closeOffers()
{
  for(int i = m_QMap_Materials.size() -1; i <= 0; i--)
  {
    delete m_QMap_Offers.values().at(i);
    delete m_QMap_Offers.keys().at(i);
  }
}



