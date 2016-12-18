
// Files includes --------------------------
#include "MainWindow.h"
#include "ui_MainWindow.h"

// Project includes ------------------------
#include "Settings.h"
#include "Settings_Gui.h"

// Qt includes -----------------------------
#include <QDebug>
#include <QTimer>

//-----------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_Ui(new Ui::MainWindow),
  m_QSystemTrayIcon()
{
  // Qt ui setup
  m_Ui->setupUi(this);

  m_QSystemTrayIcon.setIcon(QIcon(":/Icons/Icons/ZumMaschine.png"));
  m_QSystemTrayIcon.show();

  // Settings
  m_Settings = new Settings(this);

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
  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_m_QAction_File_Settings_triggered()
{
  Settings_Gui settings_Gui(m_Settings,
                            this);
  settings_Gui.exec();
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
