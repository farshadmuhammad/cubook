#ifndef CUTASK_H
#define CUTASK_H

#include <QRunnable>
#include <QDebug>
#include <QObject>
#include "messagetranslator.h"
#include "messageprotocol.h"

class CUTask : public QObject,  public QRunnable
{
    Q_OBJECT
public:
    CUTask(QByteArray *a_message, QByteArray *an_update, int a_user_id);
signals:
    void result(QByteArray a_message);
    void newUpdate(QByteArray);
    void userID(int a_user_id);
protected:
    void run();
private:
    QByteArray message;
    QByteArray update;
    MessageTranslator translator;
    int user_id;
};

#endif // CUTASK_H
