#ifndef EXCEPTION_H
#define EXCEPTION_H

// Qt includes -----------------------------
#include <QException>

class Exception : public QException
{
public:
  Exception(const QString &text);

  QString GetText() const;

private:

  QString m_Text;
};

#endif // EXCEPTION_H
