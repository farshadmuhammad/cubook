#ifndef CLIENTTRANSLATOR_H
#define CLIENTTRANSLATOR_H

#include <QByteArray>
#include <QtXml>
#include "userprofile.h"
#include "newsflash.h"
#include "flashboard.h"
#include "flashsegment.h"

class ClientTranslator
{
public:
    ClientTranslator();

    //STATIC ERROR CONSTS

    static const QString CONTENTS;
    static const QString UNRECOGNIZED;
    static const QString UNAVAILABLE;
    static const QString UNAUTHORIZED;


    //GENERAL
    static QString getMessageName(QByteArray message);
    static QString getMessageType(QByteArray message);
    static QString getMessageCategory(QByteArray message);
    static bool isValidXML(QByteArray message);
    static QString getMessageAttribute(QDomDocument a, QString element, QString attribute);
    static QString getMessageElement(QDomDocument, QString);
    static QList<QString> getMessageElementList(QDomDocument,QString,QString);
    static QList<QString> getMessageElementNodeList(QDomDocument,QString);
    static QString getRootMessageAttribute(QDomDocument,QString);



    //REPLIES
    static QList<FlashBoard> processGetBoardListReply(QByteArray message);
    static QList<NewsFlash> processGetNewsflashesReply(QByteArray message);
    static QList<UserProfile> processGetProfilesReply(QByteArray message);
    static QString processAuthenticateReply(QByteArray message);
    static QList<QString> processGetNewsflashIDsReply(QByteArray message);

    static int processRequestSucceededReply(QByteArray message);
    static QString processRequestFailedReply(QByteArray message);

    //UPDATES
    static NewsFlash processNewNewsflashUpdate(QByteArray message);
    static FlashSegment processNewSegmentUpdate(QByteArray message);
    static UserProfile processProfileUpdateUpdate(QByteArray message);
    static int processNewsflashDeletedUpdate(QByteArray message);
    static int processSegmentDeletedUpdate(QByteArray message);

};

#endif // CLIENTTRANSLATOR_H
