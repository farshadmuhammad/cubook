#ifndef MESSAGEPROTOCOL_H
#define MESSAGEPROTOCOL_H

#include <QString>
#include <QDebug>
#include <QtXml>
#include "newsflash.h"
#include "flashboard.h"
#include "flashsegment.h"
#include "cupicture.h"
#include "cuurl.h"
#include "userprofile.h"
class MessageProtocol
{
public:
        static const QString UNRECOGNIZED;
        static const QString CONTENTS;
        static const QString UNAUTHORIZED;
        static const QString UNAVAILABLE;

    MessageProtocol();
    //Request Section
    static QByteArray createAuthenticateRequest(QString a_userid, QString a_password);
    static QByteArray createUnauthenticateRequest();
    static QByteArray createGetNewsFlashIDsRequest(QString userid);
    static QByteArray createGetNewsFlashIDsRequest();
    static QByteArray createGetNewsFlashIDsRequest(QList<QString> flashboardlist);
    static QByteArray createGetBoardListRequest();
    static QByteArray createGetNewsflashesRequest(QList<QString> newsflashlist);
    static QByteArray createGetProfilesRequest(QList<QString> userlist);
    static QByteArray createCreateNewsflashRequest(NewsFlash a_newsflash);
    static QByteArray createCreateSegmentRequest(FlashSegment a_flashsegment);
    static QByteArray createUpdateProfileRequest(CUPicture a_picture); //TO BE DONE
    static QByteArray createUpdateProfileRequest(QString a_nickname);
    static QByteArray createFilterBoardRequest(QList<FlashBoard> flashboards);
    static QByteArray createDeleteNewsflashRequest(QList<NewsFlash> newsflashes);
    static QByteArray createDeleteSegmentRequest(QList<FlashSegment> segments);


    //Reply Section
    static QByteArray createGetBoardListReply(QList<FlashBoard> flashboards);
    static QByteArray createGetNewsflashesReply(QList<NewsFlash> newsflashes);
    static QByteArray createGetProfilesReply(QList<UserProfile> profiles);
    static QByteArray createAuthenticateReply(UserProfile profile);
    static QByteArray createGetNewsflashIDsReply(QList<QString> newsflashes);

    static QByteArray createRequestSucceededReply(int id);
    static QByteArray createRequestFailedReply(QString exception_code);


    //Update Section
    static QByteArray createNewNewsflashUpdate(NewsFlash newsflash);
    static QByteArray createNewSegmentUpdate(FlashSegment segment);
    static QByteArray createProfileUpdateUpdate(UserProfile profile);
    static QByteArray createNewsflashDeletedUpdate(int id);
    static QByteArray createSegmentDeletedUpdate(int id);

private:
    static void addXMLVersion(QDomDocument &message);
    static QDomElement createRequest(QDomDocument &message, QString a_category, QString a_type);
    static QByteArray finalizeRequest(QDomDocument &message, QDomElement request);

    static QDomElement createReply(QDomDocument &message, QString a_category, QString a_type);
    static QByteArray finalizeReply(QDomDocument &message, QDomElement reply);

    static QDomElement createUpdate(QDomDocument &message, QString a_category, QString a_type);
    static QByteArray finalizeUpdate(QDomDocument &message, QDomElement update);

    static void appendPicture(QDomDocument &message, QDomElement &request, CUPicture a_picture);
    static void appendURL(QDomDocument &message, QDomElement &request, CUUrl a_url);
    static void appendNewsFlash(QDomDocument &message, QDomElement &request, NewsFlash a_newsflash);
    static void appendFlashSegment(QDomDocument &message, QDomElement &request, FlashSegment a_flashsegment);
    static void appendUserProfile(QDomDocument &message, QDomElement &request, UserProfile a_userprofile);
    static void appendFlashBoard(QDomDocument &message, QDomElement &request, FlashBoard a_flashboard);
};

#endif // MESSAGEPROTOCOL_H
