#include "cuclient.h"


CUClient::CUClient(QObject *parent) :
    QObject(parent)
{
    user_id = 0;
    QThreadPool::globalInstance()->setMaxThreadCount(15);
}


int CUClient::getUserID(){
    return user_id;
}

void CUClient::setSocket(int descriptor){

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);
    //qDebug() << "A Client has connected!";
}
QTcpSocket * CUClient::getSocket(){
    return socket;
}

void CUClient::connected(){

}


void CUClient::disconnected(){
    //qDebug() << "Client has disconnected!";
    socket->close();
}


void CUClient::readyRead(){
    QByteArray ba;
    QByteArray update;
    do{
        ba += socket->readAll();
        socket->flush();
        socket->waitForReadyRead(50);
    }while(socket->bytesAvailable());


    ////qDebug() << "Message Receieved: \n" << ba;



    CUTask *cutask = new CUTask(&ba, &update, user_id);
    cutask->setAutoDelete(true);
    connect(cutask, SIGNAL(result(QByteArray)),this,SLOT(taskResult(QByteArray)),Qt::QueuedConnection);
    connect(cutask, SIGNAL(userID(int)),this,SLOT(getUserID(int)), Qt::QueuedConnection);
    connect(cutask, SIGNAL(newUpdate(QByteArray)), this, SLOT(newUpdate(QByteArray)));
    if (!update.isEmpty()){
        pushMessage(update);
    }
    QThreadPool::globalInstance()->start(cutask);

}

void CUClient::taskResult(QByteArray ba){
    ////qDebug() << "Making a Reply:" << ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::ReadWrite);
    socket->isOpen();
     socket->write(buffer.buffer());
    socket->flush();

}

void CUClient::pushMessage(QByteArray buffer){
    ////qDebug() << "Writing to buffer:" << buffer;
   // //qDebug() << "Size of the buffer." << buffer.size();
    socket->flush();
    socket->write(buffer);
\
}

void CUClient::newUpdate(QByteArray update){
    //qDebug() << "\n Emitting Update to Server:" << update;
    update.append('\0');
    emit(newUpdateSignal(update));
}

void CUClient::conflictingConnection(){
 //   //qDebug() << "Closing a socket due to a conflicting connection";
 //   socket->write(MessageProtocol::createRequestFailedReply(MessageProtocol::UNAVAILABLE));
 //   socket->close();
}

void CUClient::getUserID(int a_user_id){
    user_id = a_user_id;
    //qDebug() <<"Got user id:" << user_id;
    emit(conflictingConnectionSignal(a_user_id));
}
