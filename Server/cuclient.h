#ifndef CUCLIENT_H
#define CUCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include <cutask.h>
#include "messageprotocol.h"
#include "messagetranslator.h"

class CUClient : public QObject
{
    Q_OBJECT
public:

    explicit CUClient(QObject *parent = 0);
    void setSocket(int descriptor);
    int getUserID();
    void pushMessage(QByteArray buffer);
    void conflictingConnection();
    QTcpSocket * getSocket();
signals:
    void newUpdateSignal(QByteArray);
    void conflictingConnectionSignal(int a_user_id);
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(QByteArray ba);
    void getUserID(int a_user_id);
    void newUpdate(QByteArray update);

private:
    QTcpSocket *socket;
    int user_id;
    MessageTranslator translator;

};

#endif // CUCLIENT_H
