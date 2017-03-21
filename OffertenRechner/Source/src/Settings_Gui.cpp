
// Files includes --------------------------
#include "Settings_Gui.h"
#include "ui_Settings_Gui.h"

// Project includes ------------------------
#include "Settings.h"

// Qt includes -----------------------------
#include <QFileDialog>

//-----------------------------------------------------------------------------------------------------------------------------

Settings_Gui::Settings_Gui(Settings *settings,
                           QWidget *parent) :
  QDialog(parent),
  m_Ui(new Ui::Settings_Gui),
  m_Settings(settings)
{
  m_Ui->setupUi(this);

  m_Ui->m_QLineEdit_Mirror_Source->setText(m_Settings->get_Mirror_DirectorySource());
  m_Ui->m_QLineEdit_Mirror_Destination->setText(m_Settings->get_Mirror_DirectoryDestination());
  m_Ui->m_QCheckBox_MirrorActive->setChecked(m_Settings->get_Mirror_Active());

  // Signals/slots
  connect(this,
          SIGNAL(accepted()),
          SLOT(slot_Dialog_accepted()));
}

//-----------------------------------------------------------------------------------------------------------------------------

Settings_Gui::~Settings_Gui()
{
  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings_Gui::slot_Dialog_accepted()
{
  m_Settings->set_Mirror_DirectorySource(m_Ui->m_QLineEdit_Mirror_Source->text());
  m_Settings->set_Mirror_DirectoryDestination(m_Ui->m_QLineEdit_Mirror_Destination->text());
  m_Settings->set_Mirror_Active(m_Ui->m_QCheckBox_MirrorActive->isChecked());
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings_Gui::on_m_QToolButton_Mirror_Source_clicked()
{
  QString sourceDirectory = QFileDialog::getExistingDirectory(this,
                                                              tr("Select source directory for mirroring"));

  if(sourceDirectory.isEmpty())
    return;

  m_Ui->m_QLineEdit_Mirror_Source->setText(sourceDirectory);
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings_Gui::on_m_QToolButton_Mirror_Destination_clicked()
{
  QString destinationDirectory = QFileDialog::getExistingDirectory(this,
                                                                   tr("Select destination directory for mirroring"));

  if(destinationDirectory.isEmpty())
    return;

  m_Ui->m_QLineEdit_Mirror_Destination->setText(destinationDirectory);
}
