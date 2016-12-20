
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
  m_QSystemTrayIcon(),
  m_QFileSystemModel(NULL),
  m_QFileSystemWatcher(NULL)
{
  // Qt ui setup
  m_Ui->setupUi(this);

  m_QSystemTrayIcon.setIcon(QIcon(":/Icons/Icons/ZumMaschine.png"));
  m_QSystemTrayIcon.show();

  // Settings
  m_Settings = new Settings(this);

  // Filesystem model
  m_QFileSystemModel = new QFileSystemModel;
  m_QFileSystemModel->setRootPath(m_Settings->get_Mirror_DirectorySource());
  m_Ui->m_QTreeView_FileSystem->setModel(m_QFileSystemModel);
  m_Ui->m_QTreeView_FileSystem->setRootIndex(m_QFileSystemModel->index(m_Settings->get_Mirror_DirectorySource()));

  // Filesystem watcher
  m_QFileSystemWatcher = new

  // Signals slot
  connect(&m_QSystemTrayIcon,
          SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
          SLOT(slot_QSystemTrayIcon_activated(QSystemTrayIcon::ActivationReason)));

  // Hide main window
  QTimer::singleShot(0, this, SLOT(hide()));
}

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
  delete m_QFileSystemModel;

  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Settings_triggered()
{
  Settings_Gui settings_Gui(m_Settings,
                            this);
  if(settings_Gui.exec() == QDialog::Rejected)
    return;

  m_QFileSystemModel->setRootPath(m_Settings->get_Mirror_DirectorySource());
  m_Ui->m_QTreeView_FileSystem->setRootIndex(m_QFileSystemModel->index(m_Settings->get_Mirror_DirectorySource()));
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Exit_triggered()
{
  QApplication::quit();
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::slot_QSystemTrayIcon_activated(QSystemTrayIcon::ActivationReason activationReason)
{
  switch (activationReason)
  {
  case QSystemTrayIcon::Unknown:
  {
    setVisible(!isVisible());
    break;
  }
  case QSystemTrayIcon::Context:
  {
    setVisible(!isVisible());
    break;
  }
  case QSystemTrayIcon::DoubleClick:
  {
    setVisible(!isVisible());
    break;
  }
  case QSystemTrayIcon::Trigger:
  {
    setVisible(!isVisible());
    break;
  }
  case QSystemTrayIcon::MiddleClick:
  {
    setVisible(!isVisible());
    break;
  }
  default:
    break;
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::changeEvent(QEvent* qEvent)
{
  switch (qEvent->type())
  {
  case QEvent::WindowStateChange:
  {
    if (this->windowState() & Qt::WindowMinimized)
    {
      QTimer::singleShot(0, this, SLOT(hide()));
    }

    break;
  }
  default:
    break;
  }

  QMainWindow::changeEvent(qEvent);
}

//-----------------------------------------------------------------------------------------------------------------------------
