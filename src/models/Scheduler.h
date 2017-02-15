#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <thread>
#include <unistd.h>
#include "Backup.h"

class Scheduler {
    static Scheduler instance;
    std::vector<Backup> saves;
    std::thread* th;
    bool loop;

    Scheduler():saves(std::vector<Backup>()),loop(false),th(NULL)
    {}
    void saveLoop();

public:
    static Scheduler& getInstance()
    {
        return instance;
    }
    void start();
    void stop();
    void add(Backup& backup);
    void remove(Backup& backup);
};

#endif //SCHEDULER_H
