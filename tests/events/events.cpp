//
// Created by Valentin on 21/11/16.
//

#include "events.h"
#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

void Events::start()
{
    thread *t = new thread(&Events::start_loop,this);
    t->detach();
}
void Events::start_loop()
{
    while(!this->end){
        this->check();
        this_thread::sleep_for(chrono::milliseconds(EVENTS_LOOP));
    }
}
void Events::check()
{
    long now = time(0);
    cout << "Recherche d'action à faire...   ";
    if(fifo.back().date <= now)
    {
        cout << "Trouvé ! Event dépassé de : " << (fifo.back().date - now) << " secondes." << endl;
        fifo.pop_back();
    }
    else
    {
        cout << "Rien. Prochain event dans : " << (fifo.back().date - now) << " secondes." << endl;
    }
}
