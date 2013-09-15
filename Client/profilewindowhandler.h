#ifndef PROFILEWINDOWHANDLER_H
#define PROFILEWINDOWHANDLER_H
#include "windowcontrol.h"
#include "profilewindow.h"
#include "ui_profilewindow.h"
#include <QObject>

class ProfileWindowHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProfileWindowHandler(QObject *parent = 0);
    void run(clientCache* cache);
    bool firstTimeSaved();
    void errorBox();
signals:

public slots:
    void goHome();
    void logout();
    void upload();
    void cancel();
    void save();
    void change(bool recieved);
    void logoutReply(bool success);
    void updateReply(bool success);
private:
    clientCache *mCache;
    ProfileWindow mWindow;
    QImage uploaded_photo;
    QString ext;
};

#endif // PROFILEWINDOWHANDLER_H
