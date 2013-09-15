#ifndef MESSAGETRANSLATOR_H
#define MESSAGETRANSLATOR_H
#include <QtXml>
#include <QByteArray>
#include "flashsegment.h"
#include "filter.h"
#include "newsflash.h"
#include "cupicture.h"
#include "cuurl.h"
#include "userprofile.h"
#include "sqlapi.h"
#include "messageprotocol.h"
#include <QImageReader>
#include <QCoreApplication>
class MessageTranslator
{
public:
    SQLApi *api;

    QByteArray checkXML(QByteArray message, QByteArray& update, int * a_user_id);
    QString getMessageAttribute(QDomDocument ,QString,QString);
    QString getMessageType(QDomDocument);
    QString getMessageElement(QDomDocument, QString);
    QByteArray processAuthReq(QByteArray, int *a_user_id);
    QByteArray processNewsFlashCreation(QByteArray, QByteArray&, int);
    QString getRootMessageAttribute(QDomDocument, QString);
    QByteArray processDelFlashSegm(QByteArray, QByteArray&);
    QByteArray processDelNewsFlash(QByteArray, QByteArray&);
    QByteArray processCreateSegment(QByteArray, QByteArray&);
    QList<QString> getMessageElementList(QDomDocument,QString,QString);
    QByteArray processGetProfileReq(QByteArray);
    QByteArray processGetNewsFlashIDs(QByteArray);
    QByteArray processGetNewsFlash(QByteArray);
    QList<QByteArray> getMessageNodeElementList(QDomDocument doc, QString ele);
    QList<QString> getMessageNodeElementListStrings(QDomDocument doc, QString ele);
    QByteArray processGetBoardList(int);
    QByteArray processUpdateFilter(QByteArray, int);
    QByteArray processUpdateProfile(QByteArray, int, QByteArray&);
    bool isValidXML(QDomDocument);
    QByteArray processUnauthenticate(QByteArray message, int user_id);
    int userID;


    MessageTranslator();
};

#endif // MESSAGETRANSLATOR_H
