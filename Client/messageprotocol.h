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

    //Message Names
    static const QString REPLY;
    static const QString UPDATE;
    static const QString REQUEST;

    //Authentication
    static const QString AUTHENTICATE;
    static const QString UNAUTHENTICATE;

    //Get Messages
    static const QString GET_BOARD_LIST;
    static const QString GET_NEWSFLASHES;
    static const QString GET_PROFILES;
    static const QString GET_NEWSFLASH_IDS;
    static const QString FILTER_BOARD;

    //Creation Messages
    static const QString NEW_NEWSFLASH;
    static const QString NEW_SEGMENT;
    static const QString CREATE_NEWSFLASH;
    static const QString CREATE_SEGMENT;

    //Deletion Messages
    static const QString DELETE_NEWSFLASH;
    static const QString DELETE_SEGMENT;
    static const QString NEWSFLASH_DELETED;
    static const QString SEGMENT_DELETED;

    //Update Messages
    static const QString UPDATE_PROFILE;
    static const QString PROFILE_UPDATE;

    //Response Message but not like the other responses
    static const QString REQUEST_FAILED;
    static const QString REQUEST_SUCCEEDED;
    static const QString UNRECOGNIZED;
    static const QString CONTENTS;
    static const QString UNAUTHORIZED;
    static const QString UNAVAILABLE;

    MessageProtocol();
    //Request Section
    static QByteArray createAuthenticateRequest(QString a_userid, QString a_password);
    static QByteArray createUnauthenticateRequest();
    static QByteArray createGetNewsFlashIDsRequest(int userid);
    static QByteArray createGetNewsFlashIDsRequest(FlashSegment a_segment);
    static QByteArray createGetNewsFlashIDsRequest(QList<QString> flashboardlist);
    static QByteArray createGetBoardListRequest();
    static QByteArray createGetNewsflashesRequest(QList<QString> newsflashlist);
    static QByteArray createGetProfilesRequest(QList<QString> userlist);
    static QByteArray createCreateNewsflashRequest(NewsFlash a_newsflash);
    static QByteArray createCreateSegmentRequest(FlashSegment a_flashsegment);
    static QByteArray createUpdateProfileRequest(CUPicture a_picture); //TO BE DONE
    static QByteArray createUpdateProfileRequest(QString a_nickname);
    static QByteArray createUpdateProfileRequest(UserProfile a_profile);
    static QByteArray createFilterBoardRequest(QList<FlashBoard> flashboards);
    static QByteArray createDeleteNewsflashRequest(QString newsflash_id);
    static QByteArray createDeleteSegmentRequest(QString segment_id);


    //Reply Section
    static QByteArray createGetBoardListReply(QList<FlashBoard> flashboards);
    static QByteArray createGetNewsflashesReply(QList<NewsFlash> newsflashes);
    static QByteArray createGetProfilesReply(QList<UserProfile> profiles);
    static QByteArray createAuthenticateReply(UserProfile profile);
    static QByteArray createGetNewsflashIDsReply(QList<NewsFlash> newsflashes);

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
