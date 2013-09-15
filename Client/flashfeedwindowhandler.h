#ifndef FLASHFEEDWINDOWHANDLER_H
#define FLASHFEEDWINDOWHANDLER_H

#include <QObject>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include "flashfeedwindow.h"
#include "ui_flashfeedwindow.h"
#include "clientcache.h"
#include "windowcontrol.h"
#include "newsflash.h"


class FlashFeedWindowHandler : public QObject
{
    Q_OBJECT
public:
    explicit FlashFeedWindowHandler(QObject *parent = 0);
    void run(clientCache *cache);
    QString formatText(NewsFlash newsflash, bool full_version);
    void loadPosts();
    void readPost(NewsFlash selected_post);
signals:

public slots:
    void goHome();
    void logout();
    void menu(int index);
    void attachmentMenu(int index);
    void sendButtonClicked();
    void postOneSelect();
    void postTwoSelect();
    void postThreeSelect();
    void postFourSelect();
    void postFiveSelect();
    void postOneDeleteButton();
    void postTwoDeleteButton();
    void postThreeDeleteButton();
    void postFourDeleteButton();
    void postFiveDeleteButton();
    void previous();
    void next();
    void viewUserButton();
    void displayPosts(bool success);
    void logoutReply(bool success);
    void updateProfileUpdate(bool success);
    void newPostReply(bool success);
private:
    clientCache *mCache;
    FlashFeedWindow mWindow;
    QGraphicsScene *scene;
    QList<CUPicture> tPictures;
    QList<CUUrl> tUrls;
    QString tCourse;

};

#endif // FLASHFEEDWINDOWHANDLER_H
