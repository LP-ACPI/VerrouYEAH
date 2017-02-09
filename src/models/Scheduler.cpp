#include "Scheduler.h"
Scheduler Scheduler::instance = Scheduler();

static Scheduler& Scheduler::getInstance()
{
    return instance;
}

void Scheduler::start()
{
    if(!loop)
    {
        loop = true;
        th = new std::thread([this] {saveLoop();});
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

void Scheduler::remove(Backup& backup)
{
    for(auto it = saves.begin();it != saves.end();++it)
        if(*it == backup)
            saves.erase(it);
}
