#ifndef FLASHSEGMENTWINDOWHANDLER_H
#define FLASHSEGMENTWINDOWHANDLER_H

#include <QObject>
#include <QMessageBox>
#include <QInputDialog>
#include "windowcontrol.h"
#include "clientcache.h"
#include "flashsegmentwindow.h"
#include "ui_flashsegmentwindow.h"

class FlashSegmentWindowHandler : public QObject
{
    Q_OBJECT
public:
    explicit FlashSegmentWindowHandler(QObject *parent = 0);
    void run(clientCache *cache);
    void change();
    bool segmentExsists(QString segment_name);

signals:

public slots:
    void itemChanged(QListWidgetItem *current, QListWidgetItem *old);
    void okButtonClicked();
    void addButtonClicked();
    void addSegmentUpdate(bool success);
    void deleteButtonClicked();
   // void deleteSegmentReplyReturn(bool updated);
    void deleteSegmentUpdate(bool success);
    void viewButtonClicked();
    void changeReply(bool success);
private:
    clientCache *mCache;
    FlashSegmentWindow mWindow;

};

#endif // FLASHSEGMENTWINDOWHANDLER_H
