#include "updatewrapper.h"

updatewrapper::updatewrapper()
{

}
bool updatewrapper::openDatabase(){
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "upconnect"));
    db->setDatabaseName("CUBook");
    return db->open();
}
void updatewrapper::closeDatabase(){
    db->close();
    delete db;
    QSqlDatabase::removeDatabase("upconnect");
}

bool updatewrapper::changeFilter(int fbID, QString vis, int user_id){
    openDatabase();
    bool check = false;
    QSqlQuery newQ(*db);
        if(db->isOpen()){
          newQ.exec(QString("Select * from Filter where UserID=%1").arg(user_id));
          newQ.next();
          QList<QString> flashboard;
          if(newQ.isValid()){
          flashboard.append(newQ.value(2).toString());
          flashboard.append(newQ.value(4).toString());
          flashboard.append(newQ.value(6).toString());
          flashboard.append(newQ.value(8).toString());
          flashboard.append(newQ.value(10).toString());
          }
          if(flashboard.contains(QString::number(fbID))){
              if(flashboard.indexOf(QString::number(fbID)) == 0){
                  newQ.exec(QString("Update Filter set Filtered1='%1' where UserID=%2").arg(vis).arg(user_id));

              }
              if(flashboard.indexOf(QString::number(fbID)) == 1){
                  newQ.exec(QString("Update Filter set Filtered2='%1' where UserID=%2").arg(vis).arg(user_id));
              }
              if(flashboard.indexOf(QString::number(fbID)) == 2){
                  newQ.exec(QString("Update Filter set Filtered3='%1' where UserID=%2").arg(vis).arg(user_id));
              }
              if(flashboard.indexOf(QString::number(fbID)) == 3){
                  newQ.exec(QString("Update Filter set Filtered4='%1' where UserID=%2").arg(vis).arg(user_id));
              }
              if(flashboard.indexOf(QString::number(fbID)) == 4){
                  newQ.exec(QString("Update Filter set Filtered5='%1' where UserID=%2").arg(vis).arg(user_id));
              }
          check = true;
          }

}
        closeDatabase();
        return check;
}

bool updatewrapper::changeFilter(int user_id){
    openDatabase();
    bool check = false;
    QSqlQuery newQ(*db);
        if(db->isOpen()){
          newQ.exec(QString("Select * from Filter where UserID=%1").arg(user_id));
          newQ.next();
          QList<QString> flashboard;
          if(newQ.isValid()){
          flashboard.append(newQ.value(2).toString());
          flashboard.append(newQ.value(4).toString());
          flashboard.append(newQ.value(6).toString());
          flashboard.append(newQ.value(8).toString());
          flashboard.append(newQ.value(10).toString());
          }


                  newQ.exec(QString("Update Filter set Filtered1='false' where UserID=%1").arg(user_id));


                  newQ.exec(QString("Update Filter set Filtered2='false' where UserID=%1").arg(user_id));

                  newQ.exec(QString("Update Filter set Filtered3='false' where UserID=%1").arg(user_id));


                  newQ.exec(QString("Update Filter set Filtered4='false' where UserID=%1").arg(user_id));

                  newQ.exec(QString("Update Filter set Filtered5='false' where UserID=%1").arg(user_id));
                   check = true;

        }




        closeDatabase();
        return check;
}

bool updatewrapper::changeAvatar(int userID, QString Ava){
    openDatabase();
    bool check = false;
    QSqlQuery newQ(*db);
        if(db->isOpen()){
            check = newQ.exec(QString("UPDATE Users SET Avatar='%2' "
                                      "WHERE UserID=%1")
                              .arg(userID).arg(Ava));
        }
        closeDatabase();
        return check;
}

bool updatewrapper::changePhoto(int userID, QString filepath){
    openDatabase();
    bool check = false;
    QSqlQuery newQ(*db);
        if(db->isOpen()){
            check = newQ.exec(QString("UPDATE Users SET Photo='%2' "
                                      "WHERE UserID=%1")
                              .arg(userID).arg(filepath));
        }
        closeDatabase();
        return check;
}
