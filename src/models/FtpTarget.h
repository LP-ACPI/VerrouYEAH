#ifndef FTPTARGET_H
#define FTPTARGET_H

#include "absTarget.h"

class FtpTarget : public AbsTarget
{
    std::string host;
    std::string username;
    std::string password;
    std::string port;
public:

    FtpTarget(std::string tag = "", std::string path="", std::string type ="FTP")
        : AbsTarget(tag,path,type)
    {}

    std::string getHost() const;
    std::string getUserName() const;
    std::string getFtpPass() const;
    std::string getPort() const;

    void setHost(const std::string);
    void setUserName(const std::string);
    void setFtpPass(const std::string);
    void setPort(const std::string);

    void operator =(const FtpTarget&) ;

    virtual nlohmann::json to_json() const override;

};

#endif // FTPTARGET_H
