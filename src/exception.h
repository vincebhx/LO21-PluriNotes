#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>
#include <QString>

class Exception: public QException {
private:
    QString info;
public:
    Exception(const QString& info): info(info) {}

    void raise() const { throw(*this); }
    Exception* clone() const { return new Exception(*this); }
    QString getInfo() const { return info; }
};

#endif // EXCEPTION_H
