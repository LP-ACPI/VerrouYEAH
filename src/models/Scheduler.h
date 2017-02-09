#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <thread>
#include <unistd.h>
#include "Backup.h"

class Scheduler {
    static Scheduler instance;
    bool loop;
    std::thread* th;
    std::vector<Backup> saves;

    Scheduler():saves(std::vector<Backup>()),loop(false),th(NULL)
    {}

    void saveLoop()
    {
        for(auto it = saves.begin();it != saves.end();++it)
            if(it->getFrequency().isNow())
                it->saveData();

        if(loop)
            saveLoop();
    }

public:
    static Scheduler& getInstance();
    void start();
    void stop();
    void add(Backup& backup);
    void remove(Backup& backup);
};

#endif //SCHEDULER_H
