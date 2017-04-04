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
class Offer;
class Offer_Gui;
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

  void slot_Offer_Changed();

  void on_m_QAction_File_New_triggered();
  void on_m_QAction_File_Open_triggered();
  void on_m_QAction_File_Save_triggered();
  void on_m_QAction_File_SaveAs_triggered();
  void on_m_QAction_File_Settings_triggered();
  void on_m_QAction_File_Exit_triggered();

  void on_m_QTabWidget_tabCloseRequested(int index);

private:

  Ui::MainWindow *m_Ui;

  Settings *m_Settings;

  QMap<QString, Material *> m_QMap_Materials;

  QMap<Offer *, Offer_Gui*> m_QMap_Offers;

  void loadMaterials(const QString &materialsDirectory);
  void closeMaterials();

  void loadOffers();
  void closeOffers();
};

#endif // MAINWINDOW_H
