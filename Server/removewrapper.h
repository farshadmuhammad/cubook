#ifndef REMOVEWRAPPER_H
#define REMOVEWRAPPER_H
#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QDir>
class removeWrapper
{
public:
    removeWrapper();


    bool removeUser(int userID);
    bool removeNewsFlashPost(int newsFlashPostID);
    bool removeFlashSegment(int FlashSegmentID);
    bool removeFlashBoard(int flashBoardID);
    bool removeFilter(int filterID);
    bool removeAttachment(int attachmentID);
    bool openDatabase();
    void closeDatabase();
    QSqlDatabase *db;
};

#endif // REMOVEWRAPPER_H
