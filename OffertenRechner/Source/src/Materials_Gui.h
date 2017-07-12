#ifndef MATERIALS_GUI_H
#define MATERIALS_GUI_H

// Qt includes -----------------------------
#include <QWidget>
#include <QMap>

// Forward declarations --------------------
namespace Ui { class Materials_Gui; }
class Material;

class Materials_Gui : public QWidget
{
  Q_OBJECT

public:

  explicit Materials_Gui(QWidget *parent = 0);
  ~Materials_Gui();

  void loadMaterials(const QString &materialFilesLocation);

  bool isEmpty() const;
  Material *first();
  Material *getMaterial(const QString &materialName);

  QList<Material *> getList();

private slots:

  void on_m_QTreeWidget_doubleClicked(const QModelIndex &index);

private:

  Ui::Materials_Gui *m_Ui;

  // Link to materials
  QMap<QString, Material * > m_QMap_Materials;

};

#endif // MATERIALS_GUI_H
