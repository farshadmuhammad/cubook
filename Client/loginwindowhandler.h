#ifndef LOGINWINDOWHANDLER_H
#define LOGINWINDOWHANDLER_H

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "clientcache.h"
#include "windowcontrol.h"
#include "clientcache.h"
#include <QObject>
#include <QMessageBox>

/*This class contains the methods to direct and control the login window*/

class LoginWindowHandler : public QObject
{
    Q_OBJECT
public:
    explicit LoginWindowHandler(QObject *parent = 0);
    void run();
signals:

public slots:
    void login();
    void change(bool success);
    void getProfiles(bool success);
    void getBoardList(bool success);
    void getPosts(bool success);

private:
    LoginWindow mWindow;
    clientCache *mCache;

};

#endif // LOGINWINDOWHANDLER_H
