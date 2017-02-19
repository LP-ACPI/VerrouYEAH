#include "Scheduler.h"
#include <chrono>

using namespace std;

Scheduler Scheduler::instance = Scheduler();

void Scheduler::saveLoop()
{
    for(auto it = saves.begin();it != saves.end();++it)
        if(it->getFrequency().isNow())
            it->saveData();


    if(loop)
    {
        this_thread::sleep_for(chrono::seconds(60));
        saveLoop();
    }
}


void Scheduler::start()
{
    if(!loop)
    {
        loop = true;
        th = new thread([this] {saveLoop();});
    }
}

void Scheduler::stop()
{
    if(loop)
    {
        loop = false;
        th->join();
        delete(th);
    }
}
void Scheduler::add(Backup& backup)
{
    saves.push_back(backup);
}
void Scheduler::addFromUser(User* user)
{
    for (auto iterator = user->getBackups().begin(); iterator != user->getBackups().end(); ++iterator)
        saves.push_back(*iterator);
}

void Scheduler::remove(Backup& backup)
{
    for(auto it = saves.begin();it != saves.end();++it)
        if(*it == backup)
            saves.erase(it);
}
