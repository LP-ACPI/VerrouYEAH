//
// Created by Valentin on 21/11/16.
//

#ifndef EVENTS_H
#define EVENTS_H

#include "action.h"
#include <list>

#define EVENTS_LOOP 1*1000

typedef std::list<Action> ActionList;

class Events {
    std::list<Action> fifo; //Une liste des actions à faire tirée par date
    int end; //flag de fin de recherche des actions à faire
    void start_loop();//Boucle de recherche
public:
    Events():end(0){}
    void start();//Lance la boucle de recherche dans un thread
    void stop(){//Coupe la boucle de recherche
        end = 1;
    }
    void check();//Vérifie si l'action qui a la date la plus faible doit est faite ou pas
    Events& add(Action& a)//Ajout d'une action à la liste, et réorganisation
    {
        fifo.push_front(a);
        fifo.sort(Action::cmp);
        return *this;
    }
};


#endif //PROJECT_EVENTS_H
