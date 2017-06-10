#include "mediator.h"
#include <iostream>

Mediator* Mediator::_instance = 0;


/*Mediator::Mediator()
{
   component = std::vector<Widget*>;
}*/

void Mediator::addComponent(Widget* w) {
    component.push_back(w);
    std::cout << "ok";
}

Mediator *Mediator::instance() {
    if(_instance == 0) {
        _instance = new Mediator;
    }
    return _instance;
}

void Mediator::disributeMessage(Widget* sender, QString msg)
{
    for (unsigned int i =0 ; i < this->component.size() ; i++) {
        QString s1 = sender->getCode();
        QString s2 = component[i]->getCode();
        std::cout << "s1 : " << s1.toStdString() << "    s2 : "<< s2.toStdString() << "\n";
        if (s1 != s2) {
            component[i]->receiveMessage();
            std::cout << "message envoye a component i _=\n";
        }
    }
}
