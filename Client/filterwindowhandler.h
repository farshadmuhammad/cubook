#ifndef FILTERWINDOWHANDLER_H
#define FILTERWINDOWHANDLER_H

#include <QObject>
#include <QMessageBox>
#include "clientcache.h"
#include "filterwindow.h"
#include "ui_filterwindow.h"
#include "flashboard.h"
#include "windowcontrol.h"

class FilterWindowHandler : public QObject
{
    Q_OBJECT
public:
    explicit FilterWindowHandler(QObject *parent = 0);
    void run(clientCache *cache);
    void change();
signals:

public slots:
    void allButtonClicked();
    void addButtonClicked();
    void removeButtonClicked();
    void noneButtonClicked();
    void cancelButtonClicked();
    void saveButtonClicked();
    void updatedFilter(bool updated);

private:
    clientCache *mCache;
    FilterWindow mWindow;
    QList<FlashBoard> mFilter;
};

#endif // FILTERWINDOWHANDLER_H
