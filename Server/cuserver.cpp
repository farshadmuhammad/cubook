#include "cuserver.h"

CUServer::CUServer(QObject *parent) :
    QTcpServer(parent)
{

}



void CUServer::startServer(){
    if (listen(QHostAddress::Any,2212)){
        qDebug() << "Listening on port: " << "2212";
    }
    else{
        qDebug() << "Close the other servers please!";
    }
}



void CUServer::incomingConnection(int handle){
    for (int i = 0; i < clients.size() ;i++){
        if (!clients[i]->getSocket()->isOpen()){
            clients[i]->conflictingConnection();
            clients.removeAt(i);
        }
    }

    CUClient *client = new CUClient(this);
    client->setSocket(handle);
    connect(client,SIGNAL(newUpdateSignal(QByteArray)), this, SLOT(pushNewMessage(QByteArray)));
    connect(client,SIGNAL(conflictingConnectionSignal(int)), this, SLOT(checkConflictingConnection(int)));

    clients.append(client);
}


void CUServer::checkConflictingConnection(int user_id){
    user_id = user_id;
    /*int count = 0;
    qDebug() << "Got to check connections 1324";
    for (int i = 0; i<clients.size(); i++){
        if (clients[i]->getUserID() == user_id){
            count++;
        }
        if (clients[i]->getUserID() == user_id && count > 1){
            qDebug() << "Theres a conflicting connection";
            clients[i]->conflictingConnection();
        }
    }*/
}

void CUServer::pushNewMessage(QByteArray message){
    //qDebug() << "Pushing Update to all connected clients";
    foreach(CUClient * client, clients){
        //qDebug() << "Sending update to: " << client->getUserID();
        client->pushMessage(message);
    }
}


