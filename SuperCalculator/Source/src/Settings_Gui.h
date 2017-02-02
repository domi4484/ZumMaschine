#ifndef SETTINGS_GUI_H
#define SETTINGS_GUI_H

// Qt includes -----------------------------
#include <QDialog>

// Forward declarations --------------------
namespace Ui { class Settings_Gui; }
class Settings;

class Settings_Gui : public QDialog
{
  Q_OBJECT

public:

  explicit Settings_Gui(Settings *settings, QWidget *parent = 0);
  ~Settings_Gui();

private slots:

  void slot_Dialog_accepted();

  void on_m_QToolButton_Mirror_Source_clicked();
  void on_m_QToolButton_Mirror_Destination_clicked();

private:

  Ui::Settings_Gui *m_Ui;

  // Link to settings
  Settings *m_Settings;
};

#endif // SETTINGS_GUI_H
