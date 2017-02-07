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

  void on_m_QSpinBox_Pieces_valueChanged(int arg1);

  void on_m_QDoubleSpinBox_Width_valueChanged(double arg1);

  void on_m_QDoubleSpinBox_Height_valueChanged(double arg1);

  void on_m_QDoubleSpinBox_Thickness_valueChanged(double arg1);

  void on_m_QDoubleSpinBox_CutLength_valueChanged(double arg1);

private:

  Ui::MainWindow *m_Ui;

  Settings *m_Settings;

  QList<Part *> m_QList_Pieces;
};

#endif // MAINWINDOW_H
