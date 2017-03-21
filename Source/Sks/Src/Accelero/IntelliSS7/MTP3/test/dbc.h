#ifndef APP_DBC_SERVER_H
#define APP_DBC_SERVER_H

#include <its++.h>
#include <dbc_server.h>
#include <string>

class AppDbcServer : public its::DbcServer
{
public:
    AppDbcServer(const std::string& nameParam) : its::DbcServer(nameParam)
    {};

    virtual ~AppDbcServer()
    {};

    virtual void DoCommand(std::istream& commandLine);
};

#endif /* APP_DBC_SERVER_H */
