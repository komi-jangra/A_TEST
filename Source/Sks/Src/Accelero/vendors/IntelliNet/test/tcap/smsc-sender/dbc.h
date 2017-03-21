#ifndef _NPREQ_TEST_DBC_H
#define _NPREQ_TEST_DBC_H

#include <its++.h>
#include <dbc_server.h>
#include <string>

using namespace std;
using namespace its;

class NPREQ_DbcServer : public DbcServer
{
public: 

	NPREQ_DbcServer(const std::string& nameParam)
        : DbcServer(nameParam)

    {};

    virtual ~NPREQ_DbcServer()
    {};

    virtual void DoCommand(std:: istream& commandLine);

};

#endif


