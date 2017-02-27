#ifndef PART_H
#define PART_H

// Qt includes -----------------------------
#include <QObject>
#include <QTreeWidgetItem>

// Forward declarations --------------------
class QDoubleSpinBox;
class QComboBox;

class Part : public QObject
{
  Q_OBJECT
public:

  explicit Part(QObject *parent = 0);

  void setupTreeWidgetItem(QTreeWidgetItem *qTreeWidgetItem);
  QTreeWidgetItem *getTreeWidgetItem() const;

  void setName(const QString &name);
  void setCount(int count);
  void setWidth_mm(double width_mm);
  void setHeight_mm(double height_mm);
  void setThickness_mm(double thickness_mm);
  void setCutLenght_m(double cutLength_m);
  void setMaterial();

  QString getName()         const { return m_Name;         }
  int     getCount()        const { return m_Count;        }
  double  getWidth_mm()     const { return m_Width_mm;     }
  double  getHeight_mm()    const { return m_Height_mm;    }
  double  getThickness_mm() const { return m_Thickness_mm; }
  double  getCutLenght_m()  const { return m_CutLenght_m;  }
  QString getMaterial()     const { return m_Material;     }

  double getSurface_m2()       const { return m_Surface_m2;       }
  double getVolume_m3()        const { return m_Volume_m3;        }
  double getMaterialPrice()    const { return m_MaterialPrice;    }
  double getMaterialPriceTot() const { return m_MaterialPriceTot; }

  double getCutPrice()         const { return m_CutPrice;         }
  double getCutPriceTot()      const { return m_CutPriceTot;      }

  double getPrice() const { return m_Price; }

signals:

  void changed();

public slots:

private:

  QString m_Name;
  int     m_Count;
  double  m_Width_mm;
  double  m_Height_mm;
  double  m_Thickness_mm;
  double  m_CutLenght_m;
  QString m_Material;

  double m_Surface_m2;
  double m_Volume_m3;
  double m_MaterialPrice;
  double m_MaterialPriceTot;
  double m_CutPrice;
  double m_CutPriceTot;

  double m_Price;

  QLineEdit      *m_QLineEdit_Name;
  QDoubleSpinBox *m_QDoubleSpinBox_Width;
  QDoubleSpinBox *m_QDoubleSpinBox_Height;
  QDoubleSpinBox *m_QDoubleSpinBox_Thick;
  QDoubleSpinBox *m_QDoubleSpinBox_CutLenght;
  QComboBox      *m_QComboBox_Material;

  // Link to QTreeWidgetItem
  QTreeWidgetItem *m_QTreeWidgetItem;

  void calculate();
};

#endif // PART_H
