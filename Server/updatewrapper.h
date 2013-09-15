#ifndef UPDATEWRAPPER_H
#define UPDATEWRAPPER_H
#include "updatewrapper.h"
#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QtCore>
class updatewrapper
{
public:
    updatewrapper();
    bool changeFilter(int, QString, int);
    bool changeAvatar(int,QString);
    bool changePhoto(int,QString);
    bool openDatabase();
    void closeDatabase();
    bool changeFilter(int user_id);

    QSqlDatabase *db;
};

#endif // UPDATEWRAPPER_H
