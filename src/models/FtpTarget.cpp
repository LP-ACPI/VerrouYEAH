#include "FtpTarget.h"

using json=nlohmann::json;

std::string FtpTarget::getHost() const
{ return host;    }

std::string FtpTarget::getUserName() const
{ return username;    }

std::string FtpTarget::getFtpPass() const
{ return password;    }

std::string FtpTarget::getPort() const
{ return port;    }


void FtpTarget::setHost(const std::string _host)
{ host = _host;    }

void FtpTarget::setUserName(const std::string _username)
{ username = _username;    }

void FtpTarget::setFtpPass(const std::string _pass)
{ password = _pass;    }

void FtpTarget::setPort(const std::string _port)
{ port = _port;    }


void FtpTarget::operator=(const FtpTarget &ftpTarget){
    host = ftpTarget.getHost();
    username = ftpTarget.getUserName();
    password = ftpTarget.getFtpPass();
    targetTag  = ftpTarget.getTag();
    targetPath = ftpTarget.getPath();
    targetType = ftpTarget.getType();
    port = ftpTarget.getPort();
    setId(ftpTarget.getId());
}

nlohmann::json FtpTarget::to_json() const{
    json j = {{getTag(), {
            {"type", getType()},
            {"path", getPath()},
            {"host", getHost()},
            {"port", getPort()},
            {"username", getUserName()},
            {"pass", getFtpPass()}
          }
    }};
    return j;
}
