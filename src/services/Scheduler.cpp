#include "Scheduler.h"
#include <chrono>
#include <algorithm>

using namespace std;

void Scheduler::saveLoop()
{
    for(auto it = saves.begin();it != saves.end();++it)
            if(it->getFrequency().isNow()){
                it->saveData();
            }

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
void Scheduler::add(Backup &backup)
{
    saves.push_back(backup);
}
void Scheduler::addFromUser(User *user)
{
    for (Backup bc : user->getBackups())
        add(bc);
}

void Scheduler::remove(Backup &backup)
{
            saves.remove(backup);
}
void Scheduler::replace(const Backup &oldBackup,Backup &newBackup)
{
    for(auto it = saves.begin();it != saves.end();++it)
        if(oldBackup.getKey() == it->getKey())
           (*it) = newBackup;
}


