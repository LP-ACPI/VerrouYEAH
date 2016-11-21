//
// Created by Valentin on 21/11/16.
//
//
// Classe de TEST pour la gestion des events à l'arrache, elle ne sert à rien qu'à
// à faire marcher les events pour l'instant
//

#ifndef PROJECT_ACTION_H
#define PROJECT_ACTION_H

#include <string>
#include <ctime>

class Action{
public:
    long date;//Une date pour tier et comparer
    std::string chemin_source; //Des attributs qui servent à rien
    std::string chemin_destination;
    int type;

    Action(long d,std::string source, std::string destination,int t):
            date(d),chemin_source(source),chemin_destination(destination),type(t)
    {}
    static bool cmp(Action& a1, Action a2)
    {
        return a1.date > a2.date;
    }
};
#endif //PROJECT_ACTION_H
