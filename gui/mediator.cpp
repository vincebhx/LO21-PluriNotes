#include "mediator.h"
#include <iostream>

Mediator* Mediator::_instance = 0;


/*Mediator::Mediator()
{
   component = std::vector<Widget*>;
}*/

void Mediator::addComponent(Widget* w) {
    component.push_back(w);
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
        if (msg == "Note"){
            if (s1 != s2) {
                component[i]->receiveMessage();
            }
        }
        else if (msg == "Corbeille"){
            if (s1 != s2) {
                component[i]->receiveMessageCorbeille();
            }
        }

        else if (msg == "Ajout Relation"){
            if (s1 != s2) {
                component[i]->receiveMessageARelation();
            }
        }

        else if (msg == "Modifier Relation"){
            if (s1 != s2) {
                component[i]->receiveMessageMRelation();
            }
        }
    }
}


