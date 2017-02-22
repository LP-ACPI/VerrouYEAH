#ifndef TARGET_H
#define TARGET_H

#include "absTarget.h"
#include <json.hpp>

class Target : public AbsTarget
{
public:
    Target(std::string tag = "", std::string path="", std::string type ="NORMAL")
        : AbsTarget(tag,path,type)
    {}

    virtual bool isFtp() const override
    {   return false;   }

    virtual nlohmann::json to_json() const override;

};

#endif // TARGET_H
