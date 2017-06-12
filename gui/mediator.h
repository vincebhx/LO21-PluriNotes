#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
//#include "widget.h"
#include <vector>

class Widget;
//class Mediator;

class Mediator
{
public:

    void addComponent(Widget* w);
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
    //QString code;

public:
    Widget() : med(Mediator::instance()){};
    virtual void sendMessage() { med->disributeMessage(this, "hello"); }
    virtual void receiveMessage() = 0;
    virtual QString getCode() = 0;


};

#endif // MEDIATOR_H