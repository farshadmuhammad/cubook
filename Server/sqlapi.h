#ifndef SQLAPI_H
#define SQLAPI_H
#include "getwrapper.h"
#include "addwrapper.h"
#include "removewrapper.h"
#include "updatewrapper.h"
#include "database.h"
#include "messageprotocol.h"
#include "flashboard.h"



class SQLApi
{
public:
    getWrapper *get;
    addWrapper *add;
    removeWrapper *remove;
   updatewrapper *update;



    SQLApi();
};

#endif // SQLAPI_H
