#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes -----------------------------
#include <QMainWindow>
#include <QSystemTrayIcon>

// Forward declarations --------------------
namespace Ui { class MainWindow; }
class Settings;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    
private slots:

  void on_m_QAction_File_Settings_triggered();
  void on_m_QAction_File_Exit_triggered();

  void slot_QSystemTrayIcon_activated(QSystemTrayIcon::ActivationReason activationReason);

protected:

  virtual void changeEvent(QEvent* qEvent);

private:

  Ui::MainWindow *m_Ui;

  QSystemTrayIcon m_QSystemTrayIcon;

  Settings *m_Settings;

};

#endif // MAINWINDOW_H
