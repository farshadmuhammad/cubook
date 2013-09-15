#ifndef COMMMANAGER_H
#define COMMMANAGER_H
#include <QString>
#include <QObject>
#include <QTcpSocket>
#include <QtCore>
#include <QDebug>
#include <QTimer>
#include "messageprotocol.h"
#include "userprofile.h"
class clientCache;


class CommManager : public QObject
{
    Q_OBJECT
public:
    //Setup
    explicit CommManager(QObject *parent = 0);
    void setClientCache(clientCache *cache);
    void connectTo();

    //The functions called by other handelers
    //These functions are outgoing
    void login(QString user_id);
    void updateProfile(UserProfile a_profile);
    void getBoardList();
    void getNewsFlashes(QList<QString> newsflashids);
    void getProfiles(QList<QString> user_ids);
    void getNewsFlashIDs(QList<QString> flashboards);
    void getNewsFlashIDs(FlashSegment seg);
    void getNewsFlashIDs(int user_id);
    void newNewsFlash(NewsFlash newsflash);
    void newSegment(FlashSegment segment);
    void newsFlashDeleted(QString id);
    void segmentDeleted(QString id);
    void updateFilter(QList<FlashBoard> flashboards);
    void logout();


    //Signal Emitters
    //These functions are used to make code look cleaner essentially
    void loginEmitter(QByteArray message, bool success);
    void updateProfileEmitter(QByteArray message, bool success);
    void getBoardListEmitter(QByteArray message, bool success);
    void getNewsFlashesEmitter(QByteArray message, bool success);
    void getProfilesEmitter(QByteArray message, bool success);
    void getNewsFlashIDsEmitter(QByteArray message, bool success);
    void newNewsFlashEmitter(QByteArray message, bool success);
    void newSegmentEmitter(QByteArray message, bool success);
    void profileUpdateEmitter(QByteArray message, bool success);
    void newsFlashDeletedEmitter(QByteArray message, bool success);
    void segmentDeletedEmitter(QByteArray message, bool success);
    void updateFilterEmitter(QByteArray message, bool success);
    void requestFailedEmitter(QByteArray message);
    void requestSucceededEmitter(QByteArray message);
    void logoutEmitter(QByteArray message, bool success);

public slots:
    void disconnected();
    void connected();
    void incommingMessage();


signals:
    void loginSignal(bool logged_in);
    void logoutSignal(bool updated);
    void updateProfileReplySignal(bool updated);
    void getBoardListSignal(bool updated);
    void getNewsFlashesSignal(bool updated);
    void getProfilesSignal(bool updated);
    void getPostsSignal(bool updated);
    void newSegmentSignal(bool updated);
    void newNewsFlashSignal(bool updated);

    void updateProfileUpdateSignal(bool updated);
    void newsFlashDeletedSignal(bool updated);
    void segmentDeletedSignal(bool updated);
    void updateFilterSignal(bool updated);

    void newSegmentReplySignal(bool updated);
    void segmentDeletedReplySignal(bool updated);

    void getPostsFilterSignal(bool success);
    void getPostsSegmentSignal(bool success);
    void getPostsFlashFeedSignal(bool success);
    void getPostsLoginSignal(bool success);


public slots:


private:
    QTcpSocket *sock;
    clientCache *mCache;
    QString ip, port;
    QList<QString> last_message_types;
    QList<QByteArray> messages;


};

#endif // COMMMANAGER_H
