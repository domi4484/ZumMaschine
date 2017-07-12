
// Files includes --------------------------
#include "Materials_Gui.h"
#include "ui_Materials_Gui.h"

// Project includes ------------------------
#include "Exception.h"
#include "Material.h"

// Qt includes -----------------------------
#include <QDir>
#include <QMessageBox>

//-----------------------------------------------------------------------------------------------------------------------------

Materials_Gui::Materials_Gui(QWidget *parent)
  : QWidget(parent)
  , m_Ui(new Ui::Materials_Gui)
  , m_QMap_Materials()
{
  m_Ui->setupUi(this);
}

//-----------------------------------------------------------------------------------------------------------------------------

Materials_Gui::~Materials_Gui()
{
  delete m_Ui;
}

//-----------------------------------------------------------------------------------------------------------------------------

void Materials_Gui::loadMaterials(const QString &materialFilesLocation)
{
  // Get material files
  QDir qDir(materialFilesLocation);
  QFileInfoList qFileInfoList = qDir.entryInfoList(QStringList() << "*" + Material::_CONST::FILENAME_EXTENSION,
                                                   QDir::Files);

  if(qFileInfoList.isEmpty())
  {
    QMessageBox::critical(this,
                          tr("Error loading materials."),
                          tr("No material files found in '%1'.").arg(qDir.absolutePath()));
    return;
  }

  // Load Material files
  foreach (QFileInfo qFileInfo, qFileInfoList)
  {
    Material *material = new Material(qFileInfo);
    try
    {
      material->Load();
      m_QMap_Materials.insert(material->getName(),
                              material);
    }
    catch(const Exception &exception)
    {
      QMessageBox::critical(this,
                            tr("Error opening material file '%1'.").arg(qFileInfo.fileName()),
                            exception.GetText());
    }
  }

  foreach (Material *material, m_QMap_Materials)
  {
    QTreeWidgetItem *qTreeWidgetItem = new QTreeWidgetItem(m_Ui->m_QTreeWidget);
    qTreeWidgetItem->setText(0, material->getName());
    m_Ui->m_QTreeWidget->addTopLevelItem(qTreeWidgetItem);
  }
}

//-----------------------------------------------------------------------------------------------------------------------------

bool Materials_Gui::isEmpty() const
{
  return m_QMap_Materials.isEmpty();
}

//-----------------------------------------------------------------------------------------------------------------------------

Material *Materials_Gui::first()
{
  return m_QMap_Materials.first();
}

//-----------------------------------------------------------------------------------------------------------------------------

Material *Materials_Gui::getMaterial(const QString &materialName)
{
  return m_QMap_Materials.value(materialName,
                                NULL);
}

//-----------------------------------------------------------------------------------------------------------------------------

QList<Material *> Materials_Gui::getList()
{
  return m_QMap_Materials.values();
}

//-----------------------------------------------------------------------------------------------------------------------------

void Materials_Gui::on_m_QTreeWidget_doubleClicked(const QModelIndex &index)
{

}
