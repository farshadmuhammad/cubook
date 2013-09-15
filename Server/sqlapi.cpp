#include "sqlapi.h"


SQLApi::SQLApi()
{
    add = new addWrapper;
    get = new getWrapper;
    update = new updatewrapper;
    remove = new removeWrapper;
}
