#ifndef  ABSTARGET_H
#define ABSTARGET_H

#include <iostream>
#include "json.hpp"

class AbsTarget
{

    static int counter;

protected:
    std::string targetTag;
    std::string targetPath;
    std::string targetType;
    int targetId;

public:

    AbsTarget(const AbsTarget&);

    AbsTarget(std::string tag = "", std::string path="", std::string type ="" )
        : targetTag(tag), targetPath(path), targetType(type)
    {  targetId = counter++; }

    virtual ~AbsTarget() {}

    std::string getTag() const
    { return targetTag;    }
    std::string getPath() const
    { return targetPath;    }
    std::string getType() const
    { return targetType;    }
    std::string getId() const
    { return std::to_string(targetId);    }

    void setTag(const std::string tag)
    { targetTag = tag;    }
    void setType(const std::string type)
    { targetType = type;    }
    void setPath(const std::string path)
    { targetPath = path;    }
    void setId(const std::string id)
    {    targetId =  atoi(id.c_str());   }

    virtual nlohmann::json to_json() const =0;
    bool operator ==(const AbsTarget &targ)
    { return std::to_string(targetId) == targ.getId(); }
    bool operator !=(const AbsTarget &targ)
    {   return !(operator ==(targ));    }
    void operator=(const AbsTarget &ftpTarget){
        targetTag  = ftpTarget.getTag();
        targetPath = ftpTarget.getPath();
        targetType = ftpTarget.getType();
        setId(ftpTarget.getId());
    }


   friend nlohmann::json& operator <<(nlohmann::json&, const AbsTarget&);

};

#endif // TARGET_H
