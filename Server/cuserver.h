#ifndef CUSERVER_H
#define CUSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QList>
#include <cuclient.h>

class CUServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit CUServer(QObject *parent = 0);
    void startServer();


public slots:
    void pushNewMessage(QByteArray message);
    void checkConflictingConnection(int user_id);
private:
    QList<CUClient*> clients;

protected:
    void incomingConnection(int handle);

signals:



};

#endif // CUSERVER_H
