#include "clientcache.h"
#include "commmanager.h"
#include "clienttranslator.h"



CommManager::CommManager(QObject *parent) :
    QObject(parent)
{


}

void CommManager::setClientCache(clientCache *cache){
    mCache = cache;
}

void CommManager::connectTo(){


    QString filename = ":/Config/serverproperties.txt";
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //qDebug() << "Could not open file for reading";
        return;
    }


    ip = file.readLine();
    port = file.readLine();

    file.close();


    sock = new QTcpSocket(this);
    sock->connectToHost(ip, port.toInt());

    connect(sock, SIGNAL(connected()), this, SLOT(connected()));
    connect(sock, SIGNAL(disconnected()), this, SLOT(disconnected()));
  //  connect(sock, SIGNAL(readyRead()), this, SLOT(incommingMessage()));

}


void CommManager::connected(){
    qDebug() << "Connected to Server " << ip.append("... on port " + port);
}

void CommManager::disconnected(){
    //qDebug() << "Client connected! in disconnected";
}

void CommManager::incommingMessage(){

    QByteArray message;
    QByteArray process_message;
    QList<QByteArray> tempmessages;
    do{
        message += sock->readAll();
        sock->waitForReadyRead(500);
    }while(sock->bytesAvailable());

    tempmessages = message.split('\0');
    foreach(QByteArray temp, tempmessages){
        if(!temp.isEmpty() || !temp.isNull())
            if (temp.length() > 5)
                messages.append(temp);
    }
    if(!messages.isEmpty())
        process_message = messages.takeFirst();
    else
        process_message = "";

    if(process_message != ""){
   //     qDebug() << "MESSAGE STARTS HERE: " << process_message;
      //  qDebug() << "SIZE OF MESSAGE: " << process_message.size();


      //  qDebug() << "Message Received" << message;
        QString message_name = ClientTranslator::getMessageName(process_message);
        QString message_type = ClientTranslator::getMessageType(process_message);
        //QString message_category = ClientTranslator::getMessageCategory(message);

        if(message_name == MessageProtocol::REPLY){

            if(message_type == MessageProtocol::AUTHENTICATE){
                if(!last_message_types.isEmpty()){
                    last_message_types.removeFirst();
                }
                else{
                    qDebug() << "Tried to remove an empty list";
                }
                loginEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::GET_BOARD_LIST){
                if(!last_message_types.isEmpty()){
                    last_message_types.removeFirst();
                }
                else{
                    qDebug() << "Tried to remove an empty list";
                }
                getBoardListEmitter(process_message,true);
            }
            else if(message_type == MessageProtocol::GET_NEWSFLASHES){
                if(!last_message_types.isEmpty()){
                    last_message_types.removeFirst();
                }
                else{
                    qDebug() << "Tried to remove an empty list";
                }
               getNewsFlashesEmitter(process_message,true);
            }
            else if(message_type == MessageProtocol::GET_PROFILES){
                if(!last_message_types.isEmpty()){
                    last_message_types.removeFirst();
                }
                else{
                    qDebug() << "Tried to remove an empty list";
                }
                getProfilesEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::GET_NEWSFLASH_IDS){
                if(!last_message_types.isEmpty()){
                    last_message_types.removeFirst();
                }
                else{
                    qDebug() << "Tried to remove an empty list";
                }
                getNewsFlashIDsEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::REQUEST_FAILED){
                requestFailedEmitter(message);
            }
            else if(message_type == MessageProtocol::REQUEST_SUCCEEDED){
                requestSucceededEmitter(message);
            }

            else{
                qDebug() << "Error in Reply Message";
            }
        }
        else if (message_name == MessageProtocol::UPDATE){

            if(message_type == MessageProtocol::NEW_NEWSFLASH){
                newNewsFlashEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::NEW_SEGMENT){
                newSegmentEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::PROFILE_UPDATE){
                profileUpdateEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::NEWSFLASH_DELETED){
                newsFlashDeletedEmitter(process_message, true);
            }
            else if(message_type == MessageProtocol::SEGMENT_DELETED){
                segmentDeletedEmitter(process_message, true);
            }
            else{
                //qDebug() << "Error in Message Update";
            }
        }
        else{
           // //qDebug() << "Message was neither Update or Reply";
        }
    }
    if(!messages.isEmpty()){
        if(!messages.first().isEmpty()){
            sock->waitForBytesWritten(500);
            incommingMessage();
        }
    }
}

//LOGIN
/************************************************************************/

//SEND
void CommManager::login(QString user_id){
    connectTo();
    last_message_types.append(MessageProtocol::AUTHENTICATE);
    //qDebug() << "Logging in with user id:" << user_id << "...";
    sock->write(MessageProtocol::createAuthenticateRequest(user_id, "I AM A PASSWORD"));
    sock->waitForReadyRead(500);
    incommingMessage();


}

//REPLY
void CommManager::loginEmitter(QByteArray message, bool success){


    if(success){
        QString user_id;
        user_id = ClientTranslator::processAuthenticateReply(message);
        //qDebug() << "UserID Returned from Server: " << user_id;
        mCache->setUserId(user_id);

        emit(loginSignal(true));
    }
    else{
        //qDebug() << MessageProtocol::REQUEST_FAILED;
        QString exception;
        exception = ClientTranslator::processRequestFailedReply(message);
        emit(loginSignal(false));
    }





}

//LOGOUT
/************************************************************************/

//SEND
void CommManager::logout(){
    //qDebug() << "Logging out...";
    last_message_types.append(MessageProtocol::UNAUTHENTICATE);
    sock->write(MessageProtocol::createUnauthenticateRequest());
    sock->waitForReadyRead(500);
    incommingMessage();
}
//REPLY
void CommManager::logoutEmitter(QByteArray message, bool success){
    if (success)
        sock->close();
    emit(logoutSignal(success));
}

//UPDATE PROFILE (THE REPLY)
/************************************************************************/
//SEND
void CommManager::updateProfile(UserProfile a_profile){
    last_message_types.append(MessageProtocol::UPDATE_PROFILE);
    mCache->setTempProfile(a_profile);
    //qDebug() << "Updating server with new user profile...";
    sock->write(MessageProtocol::createUpdateProfileRequest(a_profile));
    sock->waitForReadyRead(5000);
    incommingMessage();

}
//REPLY
void CommManager::updateProfileEmitter(QByteArray message, bool success){
    message = message;


    emit(updateProfileReplySignal(success));

}


//PROFILE UDPATE (THE UPDATE)
/************************************************************************/


//UPDATE
void CommManager::profileUpdateEmitter(QByteArray message, bool success){
    //qDebug() << MessageProtocol::PROFILE_UPDATE;
    UserProfile updated_profile;
    updated_profile = ClientTranslator::processProfileUpdateUpdate(message);
    if(success){
        if(updated_profile.getUserID() == mCache->getUserId()){
            if (!updated_profile.getPicture().getPicture().isNull()){
                mCache->setPhoto(updated_profile.getPicture());
            }
            if (!updated_profile.getNickname().isEmpty()){
                mCache->setAvatar(updated_profile.getNickname());
            }

        }
        for(int i = 0; i < mCache->getProfileList().size(); i++){
            if (!updated_profile.getPicture().getPicture().isNull()){
                mCache->getProfileList()[i].setPicture(updated_profile.getPicture());
            }
            if (!updated_profile.getNickname().isEmpty()){
                mCache->getProfileList()[i].setNickname(updated_profile.getNickname());
            }
        }
    }
    else{
        //qDebug() << "Bad things happened in the profile update.";
    }
    emit(updateProfileUpdateSignal(success));

}


//GET BOARD LIST
/************************************************************************/
//SEND
void CommManager::getBoardList(){
    //qDebug() << "Attempting to get List of FlashBoards...";
    last_message_types.append(MessageProtocol::GET_BOARD_LIST);
    sock->write(MessageProtocol::createGetBoardListRequest());

    sock->waitForReadyRead(5000);
    incommingMessage();
    //getBoardListEmitter("Fake", true);
}
//REPLY
void CommManager::getBoardListEmitter(QByteArray message, bool success){
    if (success){
        QList<FlashBoard> flashboards;
        flashboards = ClientTranslator::processGetBoardListReply(message);
        mCache->setCourseList(flashboards);
        emit(getBoardListSignal(success));
    }
    else{
        //qDebug() << MessageProtocol::REQUEST_FAILED;
        QString exception;
        exception = ClientTranslator::processRequestFailedReply(message);
        emit(getBoardListSignal(success));
    }

}


//GET NEWS FLASHES
/************************************************************************/

//SEND
void CommManager::getNewsFlashes(QList<QString> newsflashids){
    //qDebug() << "Attempting to get List of NewsFlashes...";
    last_message_types.append(MessageProtocol::GET_NEWSFLASHES);
    sock->write(MessageProtocol::createGetNewsflashesRequest(newsflashids.mid(0,15)));
    sock->waitForReadyRead(5000);
    incommingMessage();

}
//REPLY
void CommManager::getNewsFlashesEmitter(QByteArray message, bool success){
   // //qDebug() << message;
    //qDebug() << "Got Here";
    if(success){
        QList<NewsFlash> newsflashes;
        newsflashes = ClientTranslator::processGetNewsflashesReply(message);
        mCache->setPosts(newsflashes);

        //Get the author IDs out of the posts we just made and then get the authors of the posts
        QList<QString> author_ids;
        foreach(NewsFlash temp, newsflashes){
            if(!author_ids.contains(QString::number(temp.getAuthorID())))
            author_ids.append(QString::number(temp.getAuthorID()));
        }

        getProfiles(author_ids);
    }
    else{

        emit(getPostsSignal(false));
    }


}


//GET PROFILES
/************************************************************************/
//SEND
void CommManager::getProfiles(QList<QString> user_ids){
    //qDebug() << "Getting profiles from server: " << user_ids;
    last_message_types.append(MessageProtocol::GET_PROFILES);
    sock->write(MessageProtocol::createGetProfilesRequest(user_ids));
    sock->waitForReadyRead(5000);
    incommingMessage();

}
//REPLY
void CommManager::getProfilesEmitter(QByteArray message, bool success){

    QList<UserProfile> user_profiles;


    user_profiles = ClientTranslator::processGetProfilesReply(message);
  //  //qDebug() << user_profiles[0].getLoginID() << user_profiles[0].getNickname() << user_profiles[0].getRealName() << user_profiles[0].getUserType();
    if(!user_profiles.isEmpty()){
        if (success && mCache->getName().isEmpty()){
            //We are looking at our own profile, should only occur during a login attempt
            //qDebug() << "Our own profile was returned";
            mCache->setProfile(user_profiles[0]);
            //qDebug() << mCache->getAvatar() << mCache ->getName() << mCache->isStudent() <<mCache->getUserId();
            emit(getProfilesSignal(success));
        }
        else if(mCache->getName().isEmpty() && !success){
            emit(getProfilesSignal(success));
        }
        else if(!mCache->getName().isEmpty() && success){
            mCache->setAuthorIDs(user_profiles);
            emit(getPostsFilterSignal(success));
            emit(getPostsSegmentSignal(success));
            emit(getPostsFlashFeedSignal(success));
            emit(getPostsLoginSignal(success));
            //qDebug() << "These are the available messages: " << messages;

        }
        else{
            emit(getPostsSignal(success));

        }
    }

}


//GET NEWSFLASH IDS
/************************************************************************/

//SEND
void CommManager::getNewsFlashIDs(QList<QString> flashboards){
    //qDebug() << "Getting News Flash IDs from server using a list of flashboard ids...";
  //  //qDebug() << MessageProtocol::createGetNewsFlashIDsRequest(flashboards);
    last_message_types.append(MessageProtocol::GET_NEWSFLASH_IDS);
    sock->flush();
    sock->write(MessageProtocol::createGetNewsFlashIDsRequest(flashboards));
    sock->waitForReadyRead(500);
    incommingMessage();

    //getNewsFlashesEmitter("FAKE", true);
}

//SEND
void CommManager::getNewsFlashIDs(FlashSegment seg){
    //qDebug() << "Getting News Flash IDs from server using a segment...";
    last_message_types.append(MessageProtocol::GET_NEWSFLASH_IDS);
    sock->write(MessageProtocol::createGetNewsFlashIDsRequest(seg));
    sock->waitForReadyRead(500);
    incommingMessage();
}

//SEND
void CommManager::getNewsFlashIDs(int user_id){
    //qDebug() << "Getting News Flash IDs from server using a user id...";
    last_message_types.append(MessageProtocol::GET_NEWSFLASH_IDS);
    sock->write(MessageProtocol::createGetNewsFlashIDsRequest(user_id));
    sock->waitForReadyRead(500);
    incommingMessage();

}

//REPLY
void CommManager::getNewsFlashIDsEmitter(QByteArray message, bool success){
    if (success){
        mCache->clearPostIDs();
        QList<QString> newsflash_ids;
    //    //qDebug() << message;
        newsflash_ids = ClientTranslator::processGetNewsflashIDsReply(message);
        for (int i = 0; i < newsflash_ids.size(); i++){
            mCache->addPostID(newsflash_ids[i]);
        }
        if(newsflash_ids.size() > 15){
            getNewsFlashes(newsflash_ids.mid(0,15));
        }
        else{
            getNewsFlashes(newsflash_ids);
        }
    }
    else{
        emit getPostsSignal(false);

    }
}

//NEW NEWSFLASHES
/************************************************************************/

//SEND
void CommManager::newNewsFlash(NewsFlash newsflash){
    //qDebug() << "Creating new news flash on server...";
    last_message_types.append(MessageProtocol::CREATE_NEWSFLASH);
    sock->write(MessageProtocol::createCreateNewsflashRequest(newsflash));
    sock->waitForReadyRead(500);
    incommingMessage();


}


//UPDATE
void CommManager::newNewsFlashEmitter(QByteArray message, bool success){
    if (success){
        NewsFlash a_newsflash;
        a_newsflash = ClientTranslator::processNewNewsflashUpdate(message);
        mCache->addNewPost(a_newsflash);

    }
    else{

    }
    emit(newNewsFlashSignal(success));
}

//NEW SEGMENT
/************************************************************************/

//SEND
void CommManager::newSegment(FlashSegment segment){
    //qDebug() << "Creating new segment on server...";
    last_message_types.append(MessageProtocol::CREATE_SEGMENT);
    sock->write(MessageProtocol::createCreateSegmentRequest(segment));
    sock->waitForReadyRead(500);
    incommingMessage();

}

//UPDATE
void CommManager::newSegmentEmitter(QByteArray message, bool success){
    //qDebug() << MessageProtocol::NEW_SEGMENT;
    QList<FlashBoard> templist = mCache->getCourseList();

    if (success){
        FlashSegment new_segment;
        new_segment = ClientTranslator::processNewSegmentUpdate(message);
        for (int i = 0; i < mCache->getCourseList().size(); i++){
            if(mCache->getCourseList()[i].getFlashboardID() == new_segment.getFlashboardID())
                templist[i].addSegment(new_segment);

        }
        mCache->setCourseList(templist);

    }
    emit(newSegmentSignal(success));
}




//NEWS FLASH DELETED
/************************************************************************/

//SEND
void CommManager::newsFlashDeleted(QString id){
    //qDebug() << "Deleting News Flash on Server ID: " << id;
    last_message_types.append(MessageProtocol::NEWSFLASH_DELETED);
    sock->write(MessageProtocol::createDeleteNewsflashRequest(id));
    sock->waitForReadyRead(500);
    incommingMessage();

}


//UPDATE
void CommManager::newsFlashDeletedEmitter(QByteArray message, bool success){
    //qDebug() << MessageProtocol::NEWSFLASH_DELETED;
    QString newsflash_id;
    newsflash_id = ClientTranslator::processNewsflashDeletedUpdate(message);
    emit(newsFlashDeletedSignal(success));
}

//SEGMENT DELETED
/************************************************************************/

//SEND
void CommManager::segmentDeleted(QString id){
    //qDebug() << "Deleting Segment on Server ID: " << id;
    last_message_types.append(MessageProtocol::SEGMENT_DELETED);
    sock->write(MessageProtocol::createDeleteSegmentRequest(id));
    sock->waitForReadyRead(500);
    incommingMessage();
}



//UPDATE
void CommManager::segmentDeletedEmitter(QByteArray message, bool success){
    if(success){


        QString segment_id;
        segment_id = ClientTranslator::processSegmentDeletedUpdate(message);
        QList<FlashBoard> templist;
        templist = mCache->getCourseList();
        QList<FlashSegment> templistssegments;
        for (int i = 0; i <templist.size(); i++){
            templistssegments = templist[i].getSegments();
            for (int j = 0; j < templistssegments.size(); j++){
                if(templistssegments[j].getSegmentID()==segment_id.toInt()){
                    templistssegments.removeAt(j);
                }
            }
            templist[i].setSegments(templistssegments);
        }
        mCache->setCourseList(templist);

    }
    else{
            //qDebug() << "Failure trying to delete segment";
    }

    emit(segmentDeletedSignal(success));
}

//UPDATE FILTER
/************************************************************************/

//SEND
void CommManager::updateFilter(QList<FlashBoard> flashboards){
    //qDebug() << MessageProtocol::FILTER_BOARD;
    mCache->setTempFilter(flashboards);
    last_message_types.append(MessageProtocol::FILTER_BOARD);
    sock->write(MessageProtocol::createFilterBoardRequest(flashboards));

    sock->waitForReadyRead(500);
    incommingMessage();
}

//REPLY
void CommManager::updateFilterEmitter(QByteArray message, bool success){

    if(success){
        mCache->setFilter(mCache->getTempFilter());
        QList<QString> flashboard_ids;
        foreach(FlashBoard temp, mCache->getCourseList()){
            if(temp.isFiltered())
                flashboard_ids.append(QString::number(temp.getFlashboardID()));
        }

        getNewsFlashIDs(flashboard_ids);
    }
    else{
        //qDebug() << "Something failed in updating the filter";

    }

    emit(updateFilterSignal(success));
}


//REQUEST FAILED AND SUCCEEDED
/************************************************************************/

//REPLY
void CommManager::requestFailedEmitter(QByteArray message){
    //qDebug() << MessageProtocol::REQUEST_FAILED;
    QString info;
    info = ClientTranslator::processRequestFailedReply(message);
    if(last_message_types.first() == MessageProtocol::AUTHENTICATE){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        loginEmitter(message,false);

    }
    else if(last_message_types.first() == MessageProtocol::UNAUTHENTICATE){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        logoutEmitter(message,false);
    }
    else if (last_message_types.first() == MessageProtocol::UPDATE_PROFILE){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        updateProfileEmitter(message,false);
    }
    else if (last_message_types.first() == MessageProtocol::FILTER_BOARD){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        updateFilterEmitter(message,false);
    }
    else if (last_message_types.first() == MessageProtocol::NEW_SEGMENT){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        newSegmentEmitter(message,false);
    }
    else if (last_message_types.first() == MessageProtocol::SEGMENT_DELETED){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        segmentDeletedEmitter(message,false);
    }
    else if (last_message_types.first() == MessageProtocol::CREATE_NEWSFLASH){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
    }
    else{
        if(!last_message_types.isEmpty()){
             last_message_types.removeFirst();
             //qDebug() << "Tried to remove an empty list and received a message in request failure we didn't know what to do with.";
        }
    }
    sock->waitForReadyRead(500);
    incommingMessage();
}

//REPLY
void CommManager::requestSucceededEmitter(QByteArray message){
    //qDebug() << MessageProtocol::REQUEST_SUCCEEDED;
    int id;
    id = ClientTranslator::processRequestSucceededReply(message);
    if (last_message_types.first() == MessageProtocol::UNAUTHENTICATE){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        logoutEmitter(message,true);

    }
    else if (last_message_types.first() == MessageProtocol::UPDATE_PROFILE){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        updateProfileEmitter(message,true);
    }
    else if (last_message_types.first() == MessageProtocol::FILTER_BOARD){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
        updateFilterEmitter(message,true);
    }
    else if (last_message_types.first() == MessageProtocol::CREATE_SEGMENT){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
    }
    else if (last_message_types.first() == MessageProtocol::SEGMENT_DELETED){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
    }
    else if (last_message_types.first() == MessageProtocol::CREATE_NEWSFLASH){
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
        }
        else{
            //qDebug() << "Tried to remove an empty list";
        }
    }

    else{
        if(!last_message_types.isEmpty()){
            last_message_types.removeFirst();
            //qDebug() << "Error in request succeeded type";
        }
        else{
            //qDebug() << "Tried to remove an empty list and received a message in request succeeded we didn't know what to do with.";
        }
    }
    sock->waitForReadyRead(500);
    incommingMessage();

}




