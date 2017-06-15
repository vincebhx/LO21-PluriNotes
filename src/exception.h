#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>
#include <QString>

class Exception: public QException {
private:
    /**
     * @brief info : l'information de l'exception.
     */
    QString info;
public:
    /**
     * @brief Exception : constructeur de l'exception
     * @param info : l'information de l'exception.
     */
    Exception(const QString& info): info(info) {}

    /**
     * @brief raise : permet de lancer l'exception courante.
     */
    void raise() const { throw(*this); }
    /**
     * @brief clone : recopie de l'exception courante.
     * @return Retourne une copie de l'exception courante.
     */
    Exception* clone() const { return new Exception(*this); }
    /**
     * @brief getInfo : permet d'accéder à l'information de l'exception.
     * @return  Retourne l'information de l'exception.
     */
    QString getInfo() const { return info; }
};

#endif // EXCEPTION_H
