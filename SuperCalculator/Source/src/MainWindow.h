#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Project includes ------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QMainWindow>
#include <QSystemTrayIcon>

// Forward declarations --------------------
namespace Ui { class MainWindow; }
class Settings;
class QFileSystemModel;
class QFileSystemWatcher;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    
private slots:

  void on_m_QAction_File_Settings_triggered();
  void on_m_QAction_File_Exit_triggered();

private:

  Ui::MainWindow *m_Ui;

  Settings *m_Settings;

  QList<Part *> m_QList_Pieces;
};

#endif // MAINWINDOW_H
