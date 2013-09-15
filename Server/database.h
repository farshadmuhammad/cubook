#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QtCore>
class Database
{
public:
    Database();

    bool createDatabase();
    bool openDatabase();
    void closeDatabase();
    bool createUserTable();
    bool createNewsFlashPostTable();
    bool createFilterTable();
    bool createAttachmentTable();
    bool createFlashBoardTable();
    bool createFlashSegmentTable();

    QSqlDatabase *db;
};

#endif // DATABASE_H
