#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Project includes ------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMap>

// Forward declarations --------------------
namespace Ui { class MainWindow; }
class Settings;
class Material;
class QFileSystemModel;
class QFileSystemWatcher;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

  enum Enum_TreeWidget_Columns
  {
    Column_Position,
    Column_Quantity,
    Column_Name,
    Column_Size,
    Column_Thickness,
    Column_CutLength,
    Column_Material,
    Column_Price,
    Column_PriceTotal
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    
private slots:

  void slot_Part_Changed();

  void on_m_QAction_File_Settings_triggered();
  void on_m_QAction_File_Exit_triggered();

  void on_m_QSpinBox_Pieces_valueChanged(int arg1);
  void on_m_QDoubleSpinBox_Width_valueChanged(double arg1);
  void on_m_QDoubleSpinBox_Height_valueChanged(double arg1);
  void on_m_QDoubleSpinBox_CutLength_valueChanged(double arg1);

  void on_m_QComboBox_Thickness_currentIndexChanged(const QString &value);
  void on_m_QComboBox_Material_currentIndexChanged(const QString &value);

private:

  Ui::MainWindow *m_Ui;

  Settings *m_Settings;

  QMap<QString, Material *> m_QMap_Materials;

  Part *m_CurrentPart;
  QList<Part *> m_QList_Parts;

  void loadMaterials(const QString &materialsDirectory);

  void updatePartsList();
};

#endif // MAINWINDOW_H
