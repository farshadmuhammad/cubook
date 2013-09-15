#ifndef ADDWRAPPER_H
#define ADDWRAPPER_H

#include <QtSql>
#include <QDebug>
#include <QFile>
#include <QDir>
class addWrapper
{
public:
    addWrapper();
    bool addUser(int userID, QString avaName, QString name, int accType, QString Photo);
    bool addNewsFlashPost(QString newsFlash, int FlashBoard, int userID,
                          int flashSegmentID, int Attachment, QString date);
    bool addFlashBoard(int flashBoardID, QString flashBoardName);
    bool addFilter(int filterID, int userID, int flashBoardID1,  int flashBoardID2,
                    int flashBoardID3, int,int);
    bool addFlashSegment(int flashSegmentID,QString flashSegmentName,
                         int flashBoardID);
    bool addAttachments(int attachmentID, int newsFlashPostID, QString fileP);
    bool addLinks(int,QString);
    bool openDatabase();
    void closeDatabase();
    QSqlDatabase *db;
};

#endif // ADDWRAPPER_H
