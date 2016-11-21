//
// Created by Valentin on 21/11/16.
//
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>
#include "events.h"
using namespace std;

int main() {
    long t = time(0);
    //Planification de 3 Actions
    // Action n'est qu'une classe de test pour Events)

    long t1 = t-2;
    Action a1 = Action(t1,"source...","destination...",0);

    long t2 = t+2;
    Action a2 = Action(t2,"source...","destination...",0);

    long t3 = t+15;
    Action a3 = Action(t3,"source...","destination...",0);

    //Défition d'une liste d'évènement Events
    Events e;
    //Ajouts des Actions
    e.add(a1).add(a2).add(a3);

    cout << "Lancement de la boucle de lecture des events : " << endl;
    e.start();
    cout << ">> wait!" << endl;
    //On met en pause le programme principale 10 secondes pour simuler l'éxécution en tâche de fond
    this_thread::sleep_for(chrono::milliseconds(10*1000));
    cout << ">> stop!" << endl;
    e.stop();
    return(0);
}

