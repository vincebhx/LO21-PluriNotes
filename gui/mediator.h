#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <vector>

class Widget;
/*!
 * \brief The Mediator class : Design Pattern Mediator : assure l'échange d'informations entre les différentes tout en conservant l'indépendance
 * de ces fenêtres entre elles, le mediator est un singleton
 */
class Mediator
{
public:
    /*!
     * \brief addComponent : ajoute un composant de type Widget au Mediator
     * \param w : Widget
     */
    void addComponent(Widget* w);
    /*!
     * \brief instance : in
     * \return
     */
    static Mediator* instance() ;
    void disributeMessage(Widget* sender, QString msg);

private:
    Mediator() : component() {};
    std::vector<Widget*> component;
    static Mediator* _instance;
};

class Widget
{
protected :
    Mediator* med;

public:
    Widget() : med(Mediator::instance()){};
    virtual void sendMessage(QString msg) { med->disributeMessage(this, msg); }
    virtual void receiveMessage(){};
    virtual QString getCode() = 0;
    virtual void receiveMessageCorbeille(){};
    virtual void receiveMessageARelation() {};
    virtual void receiveMessageMRelation() {};


};

#endif // MEDIATOR_H
