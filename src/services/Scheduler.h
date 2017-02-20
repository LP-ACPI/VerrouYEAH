#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <thread>
#include <unistd.h>
#include "../models/Backup.h"
#include "../models/User.h"

class Scheduler  {

    std::list<Backup> saves;
    std::thread* th;
    bool loop;

    Scheduler()
        :   saves(std::list<Backup>()),
            th(NULL),
            loop(false)
    {}
    void saveLoop();

public:
    static Scheduler& getInstance()
    {      static Scheduler instance;
            return instance;    }

    void start();
    void stop();
    void add(Backup &backup);
    void addFromUser(User* user);
    void remove(Backup &backup);
    void clear()
    {
        saves.clear();
    }
};

#endif //SCHEDULER_H
