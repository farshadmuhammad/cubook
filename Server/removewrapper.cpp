#include "removewrapper.h"

removeWrapper::removeWrapper()
{

}

void removeWrapper::closeDatabase(){
    db->close();
    delete db;
    QSqlDatabase::removeDatabase("remconnect");
}

bool removeWrapper::openDatabase(){
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "remconnect"));
    db->setDatabaseName("CUBook");
    return db->open();
}

bool removeWrapper:: removeUser(int userID){
    openDatabase();
    bool check = false;

    if(db->isOpen()){
       QSqlQuery newQ(*db);
        //qDebug()<<"Database is open for removal";
        check = newQ.exec(QString("delete from Users where UserId=%1").arg(userID));

    }
    closeDatabase();
    return check;
}

bool removeWrapper::removeNewsFlashPost(int newsFlashPostID){
    openDatabase();
    bool check = false;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from NewsFlashPost where newsFlashID=%1").arg(newsFlashPostID));

        newQ.next();

        if(newQ.isValid()){
        newQ.exec(QString("delete from NewsFlashPost where NewsFlashID=%1")
                          .arg(newsFlashPostID));

        }
        else{

            return false;
        }
    }
    closeDatabase();
    return check;
}

bool removeWrapper:: removeFlashSegment(int FlashSegmentID){
    openDatabase();
    bool check = false;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        check = newQ.exec(QString("SELECT * from FlashSegment where FlashSegmentID=%1").arg(FlashSegmentID));
        newQ.next();
        if(newQ.isValid()){
        //qDebug()<<"Database is open for removal";
        newQ.exec(QString("delete from FlashSegment where FlashSegmentID=%1")
                          .arg(FlashSegmentID));
              }
        else{
            return false;
        }
    }
    closeDatabase();
    return check;
}

bool removeWrapper::removeFlashBoard(int flashBoardID){
    openDatabase();
    bool check = false;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        //qDebug()<<"Database is open for removal";
        check = newQ.exec(QString("delete from FlashBoard where FlashBoardID=%1")
                          .arg(flashBoardID));

    }
    closeDatabase();
    return check;
}

bool removeWrapper:: removeFilter(int filterID){
    openDatabase();
    bool check = false;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        //qDebug()<<"Database is open for removal";
        check = newQ.exec(QString("delete from Filter where FilterID=%1")
                          .arg(filterID));

    }
    closeDatabase();
    return check;
}

bool removeWrapper::removeAttachment(int attachmentID){
    openDatabase();
    bool check = false;

    if(db->isOpen()){
        QSqlQuery newQ(*db);
        //qDebug()<<"Database is open for removal";
        check = newQ.exec(QString("delete from Attachments where AttachmentID=%1")
                          .arg(attachmentID));

    }
    closeDatabase();
    return check;
}
