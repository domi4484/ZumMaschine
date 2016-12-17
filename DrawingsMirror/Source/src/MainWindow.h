#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes -----------------------------
#include <QMainWindow>
#include <QSystemTrayIcon>

// Forward declarations --------------------
namespace Ui { class MainWindow; }
class RulerDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    
private slots:

  void slot_QSystemTrayIcon_activated(QSystemTrayIcon::ActivationReason activationReason);

protected:

  virtual void changeEvent(QEvent* qEvent);

private:

  Ui::MainWindow *m_Ui;

  QSystemTrayIcon m_QSystemTrayIcon;

};

#endif // MAINWINDOW_H
