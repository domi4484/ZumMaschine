#ifndef OFFERGUI_H
#define OFFERGUI_H

// Project includes ------------------------
#include "Part.h"

// Qt includes -----------------------------
#include <QWidget>
#include <QSystemTrayIcon>

// Forward declarations --------------------
namespace Ui { class Offer_Gui; }
class Offer;
class Settings;
class Material;
class Materials_Gui;
class QFileSystemModel;
class QFileSystemWatcher;

class Offer_Gui : public QWidget
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

  explicit Offer_Gui(Offer *offer,
                     Settings *settings,
                     Materials_Gui *qMap_Materials,
                     QWidget *parent = 0);
  ~Offer_Gui();
    
  Offer *getOffer() const { return m_Offer; }

private slots:

  void slot_Part_Changed();

  void on_m_QAction_File_Settings_triggered();

  void on_m_QSpinBox_Pieces_valueChanged(int arg1);
  void on_m_QDoubleSpinBox_Width_valueChanged(double arg1);
  void on_m_QDoubleSpinBox_Height_valueChanged(double arg1);
  void on_m_QDoubleSpinBox_CutLength_valueChanged(double arg1);

  void on_m_QComboBox_Thickness_currentIndexChanged(const QString &value);
  void on_m_QComboBox_Material_currentIndexChanged(const QString &value);

private:

  Ui::Offer_Gui *m_Ui;

  // Link to offer
  Offer * m_Offer;

  // Lik to settings
  Settings *m_Settings;

  // Link to materials gui
  Materials_Gui *m_Materials_Gui;

  Part *m_CurrentPart;
  QList<Part *> m_QList_Parts;

  void updatePartsList();
};

#endif // OFFERGUI_H
