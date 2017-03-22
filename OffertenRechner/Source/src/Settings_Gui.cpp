
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

  m_Ui->m_QLineEdit_MaterialsDirectory->setText(m_Settings->get_MaterialsDirectory());

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
  m_Settings->set_MaterialsDirectory(m_Ui->m_QLineEdit_MaterialsDirectory->text());
}

//-----------------------------------------------------------------------------------------------------------------------------

void Settings_Gui::on_m_QToolButton_MaterialsDirectory_clicked()
{
  QString materialsDirectory = QFileDialog::getExistingDirectory(this,
                                                                 tr("Select materials directory"));

  if(materialsDirectory.isEmpty())
    return;

  m_Ui->m_QLineEdit_MaterialsDirectory->setText(materialsDirectory);
}
