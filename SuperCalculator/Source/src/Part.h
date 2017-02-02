#ifndef PART_H
#define PART_H

// Qt includes -----------------------------
#include <QObject>
#include <QTreeWidgetItem>

class Part : public QObject
{
  Q_OBJECT
public:

  explicit Part(QObject *parent = 0);

  void setTreeWidgetItem(QTreeWidgetItem *qTreeWidgetItem);
  QTreeWidgetItem *getTreeWidgetItem() const;

signals:

public slots:

private:

  QString m_Name_mm;
  double  m_Width_mm;
  double  m_Height_mm;
  double  m_Thick_mm;
  double  m_CutLenght_m;
  QString m_Material;

  // Link to QTreeWidgetItem
  QTreeWidgetItem *m_QTreeWidgetItem;
};

#endif // PART_H
