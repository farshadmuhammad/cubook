#include "messageprotocol.h"
/*Note
  This is essentially a static class: All methods in this class must be static
  This class will cover the creation of all methods to send requests, replies, and updates
  */
const QString MessageProtocol::MessageProtocol::REPLY = "reply";
const QString MessageProtocol::MessageProtocol::UPDATE = "update";
const QString MessageProtocol::REQUEST = "request";


const QString MessageProtocol::MessageProtocol::UNRECOGNIZED = "UNRECOGNIZED";
const QString MessageProtocol::MessageProtocol::CONTENTS = "CONTENTS";
const QString MessageProtocol::MessageProtocol::UNAVAILABLE = "UNAVAILABLE";
const QString MessageProtocol::MessageProtocol::UNAUTHORIZED = "UNAUTHORIZED";

//Authentication
const QString MessageProtocol::AUTHENTICATE = "Authenticate";
const QString MessageProtocol::UNAUTHENTICATE = "Unauthenticate";

//Get Messages
const QString MessageProtocol::GET_BOARD_LIST = "GetBoardList";
const QString MessageProtocol::GET_NEWSFLASHES = "GetNewsflashes";
const QString MessageProtocol::GET_PROFILES = "GetProfiles";
const QString MessageProtocol::GET_NEWSFLASH_IDS = "GetNewsflashIDs";
const QString MessageProtocol::FILTER_BOARD = "FilterBoard";

//Creation Messages
const QString MessageProtocol::NEW_NEWSFLASH = "NewNewsflash";
const QString MessageProtocol::NEW_SEGMENT = "NewSegment";
const QString MessageProtocol::CREATE_NEWSFLASH = "CreateNewsflash";
const QString MessageProtocol::CREATE_SEGMENT = "CreateSegment";

//Deletion Messages
const QString MessageProtocol::DELETE_NEWSFLASH = "DeleteNewsflash";
const QString MessageProtocol::DELETE_SEGMENT = "DeleteSegment";
const QString MessageProtocol::NEWSFLASH_DELETED = "NewsflashDeleted";
const QString MessageProtocol::SEGMENT_DELETED = "SegmentDeleted";

//Update Messages
const QString MessageProtocol::UPDATE_PROFILE = "UpdateProfile";
const QString MessageProtocol::PROFILE_UPDATE = "ProfileUpdate";

//Response Message but not like the other responses
const QString MessageProtocol::REQUEST_FAILED = "RequestFailed";
const QString MessageProtocol::REQUEST_SUCCEEDED = "RequestSucceeded";
MessageProtocol::MessageProtocol()
{
}

//************************************************PRIVATE SECTION*********************************************

//This function adds the XML version to the beginning of any request message
void MessageProtocol::addXMLVersion(QDomDocument &message){
    QDomProcessingInstruction xmlversion = message.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    message.insertBefore(xmlversion, message.firstChild());
}
//REQUESTS
//This functions makes a request based on given category and type
QDomElement MessageProtocol::createRequest(QDomDocument &message, QString a_category, QString a_type){
    QDomElement request = message.createElement("request");
    request.setAttribute("category", a_category);
    request.setAttribute("type", a_type);
    return request;
}

QByteArray MessageProtocol::finalizeRequest(QDomDocument &message, QDomElement request){
    QByteArray buffer;
    message.appendChild(request);
    addXMLVersion(message);
    buffer.append(message.toByteArray());
    return buffer;
}

//REPLIES
QDomElement MessageProtocol::createReply(QDomDocument &message, QString a_category, QString a_type){
    QDomElement reply = message.createElement("reply");
    reply.setAttribute("category", a_category);
    reply.setAttribute("type", a_type);
    return reply;
}

QByteArray MessageProtocol::finalizeReply(QDomDocument &message, QDomElement reply){
    QByteArray buffer;
    message.appendChild(reply);
    addXMLVersion(message);
    buffer.append(message.toByteArray());
    return buffer;
}

//UPDATES
QDomElement MessageProtocol::createUpdate(QDomDocument &message, QString a_category, QString a_type){
    QDomElement update = message.createElement("update");
    update.setAttribute("category", a_category);
    update.setAttribute("type", a_type);
    return update;
}

QByteArray MessageProtocol::finalizeUpdate(QDomDocument &message, QDomElement update){
    QByteArray buffer;
    message.appendChild(update);
    addXMLVersion(message);
    buffer.append(message.toByteArray());
    return buffer;
}



//************************************************END PRIVATE SECTION*********************************************






//************************************************ENTITY SECTION*********************************************
void MessageProtocol::appendPicture(QDomDocument &message, QDomElement &request, CUPicture a_picture){
    QDomElement picture = message.createElement("picture");
    picture.setAttribute("format", a_picture.getFormat());
    QDomElement binarydata = message.createElement("binarydata");
    QDomText picdata = message.createTextNode(a_picture.toBytes());
    binarydata.appendChild(picdata);
    picture.appendChild(binarydata);
    request.appendChild(picture);
}

void MessageProtocol::appendURL(QDomDocument &message, QDomElement &links, CUUrl a_url){
    QDomElement link = message.createElement("link");
    QDomElement url = message.createElement("url");
    QDomText urldata = message.createTextNode(a_url.getLink().toString());
    QDomElement linktext = message.createElement("text");
    QDomText linktextdata = message.createTextNode(a_url.getPageName());
    url.appendChild(urldata);
    linktext.appendChild(linktextdata);
    link.appendChild(url);
    link.appendChild(linktext);
    links.appendChild(link);
}

//NEWS FLASH
void MessageProtocol::appendNewsFlash(QDomDocument &message, QDomElement &request, NewsFlash a_newsflash){
    QDomElement newsflash = message.createElement("newsflash");
    QDomElement pictures = message.createElement("pictures");
    QDomElement links = message.createElement("links");
    QDomElement text = message.createElement("text");
    QDomText textdata = message.createTextNode(a_newsflash.getText());
    text.appendChild(textdata);
  //  newsflash.setAttribute("newsflash_id", a_newsflash.getNewsFlashID());
    newsflash.setAttribute("author_id", a_newsflash.getAuthorID());
    newsflash.setAttribute("flashboard_id", a_newsflash.getFlashBoardID());
    newsflash.setAttribute("segment_id", a_newsflash.getSegmentID());
    newsflash.appendChild(text);
    newsflash.appendChild(pictures);
    newsflash.appendChild(links);

    foreach (CUPicture temp, a_newsflash.getPictures()){

        appendPicture(message,pictures,temp);
    }

    foreach (CUUrl temp, a_newsflash.getURLs()){
        appendURL(message, links, temp);
    }

    request.appendChild(newsflash);
}

//FLASH SEGMENT
void MessageProtocol::appendFlashSegment(QDomDocument &message, QDomElement &request, FlashSegment a_flashsegment){
    QDomElement segment = message.createElement("segment");
    //segment.setAttribute("segment_id", a_flashsegment.getSegmentID());
    segment.setAttribute("flashboard_id", a_flashsegment.getFlashboardID());
    segment.setAttribute("name", a_flashsegment.getName());
    request.appendChild(segment);
}


//USER PROFILE
void MessageProtocol::appendUserProfile(QDomDocument &message, QDomElement &request, UserProfile a_userprofile){
    QDomElement profile = message.createElement("profile");
    profile.setAttribute("user_id", a_userprofile.getUserID());
    profile.setAttribute("user_type", a_userprofile.getUserType());

    QDomElement nickname = message.createElement("nickname");
    QDomText nicknamedata = message.createTextNode(a_userprofile.getNickname());
    nickname.appendChild(nicknamedata);
    profile.appendChild(nickname);

    QDomElement realname = message.createElement("realname");
    QDomText realnamedata = message.createTextNode(a_userprofile.getRealName());
    realname.appendChild(realnamedata);
    profile.appendChild(realname);

    QDomElement loginid = message.createElement("login_id");
    QDomText loginiddata = message.createTextNode(a_userprofile.getLoginID());
    loginid.appendChild(loginiddata);
    profile.appendChild(loginid);

    appendPicture(message,profile,a_userprofile.getPicture());
    request.appendChild(profile);
}

//FLASH BOARD
void MessageProtocol::appendFlashBoard(QDomDocument &message, QDomElement &request, FlashBoard a_flashboard){
    QDomElement flashboard = message.createElement("flashboard");
    flashboard.setAttribute("flashboard_id", a_flashboard.getFlashboardID());
    QDomElement name = message.createElement("name");
    QDomText namedata = message.createTextNode(a_flashboard.getName());
    name.appendChild(namedata);
    flashboard.appendChild(name);
    QDomElement segments = message.createElement("segments");
    foreach (FlashSegment temp, a_flashboard.getSegments()){
        QDomElement segment = message.createElement("segment");
        segment.setAttribute("segment_id", temp.getSegmentID());
        segment.setAttribute("Name", temp.getName());
        segments.appendChild(segment);
    }
    flashboard.appendChild(segments);
    QDomElement filtered = message.createElement("filtered");
    if (a_flashboard.isFiltered())
        filtered.setAttribute("visible", "true");
    else
        filtered.setAttribute("visible", "false");
    flashboard.appendChild(filtered);
    request.appendChild(flashboard);
}


//************************************************END ENTITY SECTION*********************************************



//************************************************AUTHENTICATION *********************************************



QByteArray MessageProtocol::createAuthenticateRequest(QString a_userid, QString a_password){
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "Authenticate");

    QDomElement loginid = message.createElement("loginid");
    QDomElement password = message.createElement("password");
    QDomElement extensions = message.createElement("extensions");

    loginid.setAttribute("username", a_userid);
    password.setAttribute("password", a_password);


    request.appendChild(loginid);
    request.appendChild(password);
    request.appendChild(extensions);

    return finalizeRequest(message, request);
}

QByteArray MessageProtocol::createUnauthenticateRequest(){
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "Unauthenticate");
    return finalizeRequest(message,request);
}

QByteArray MessageProtocol::createAuthenticateReply(UserProfile profile){

    QDomDocument message;
    QDomElement reply = createReply(message, "nonobject", "Authenticate");
    QDomElement user = message.createElement("user");
    qDebug()<<profile.getUserID();
    user.setAttribute("user_id",profile.getUserID());
    reply.appendChild(user);

    return finalizeReply(message, reply);

}

//************************************************END AUTHENTICATION *********************************************










//******************************************GET NEWS FLASH IDS SECTION***************************************************

/*Note:
  These methods can be modified to include a Max Number of posts OR an ID Range if necessary
  */

//By User ID

QByteArray MessageProtocol::createGetNewsFlashIDsRequest(int userid){
    QByteArray buffer;
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "GetNewsflashIDs");
    QDomElement user = message.createElement("user");
    user.setAttribute("user_id", userid);
    request.appendChild(user);
    return finalizeRequest(message, request);
}

//By Flash Segment
QByteArray MessageProtocol::createGetNewsFlashIDsRequest(FlashSegment a_segment ){
    QByteArray buffer;
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "GetNewsflashIDs");
    QDomElement segment = message.createElement("segment");
    segment.setAttribute("segment_id", a_segment.getSegmentID());
    segment.setAttribute("flashboard_id", a_segment.getFlashboardID());
    request.appendChild(segment);
    return finalizeRequest(message, request);
}

//By FlashBoard IDs
QByteArray MessageProtocol::createGetNewsFlashIDsRequest(QList<QString> flashboardlist){
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "GetNewsflashIDs");
    QDomElement flashboards = message.createElement("flashboards");
    foreach (QString temp, flashboardlist){
        QDomElement flashboard = message.createElement("flashboard");
        flashboard.setAttribute("flashboard_id", temp);
        flashboards.appendChild(flashboard);
    }
    request.appendChild(flashboards);

    return finalizeRequest(message,request);
}

QByteArray MessageProtocol::createGetNewsflashIDsReply(QList<NewsFlash> newsflashes){
    QDomDocument message;
    QDomElement reply = createReply(message, "nonobject", "GetNewsflashIDs");
    foreach (NewsFlash temp, newsflashes){
        QDomElement newsflashid = message.createElement("newsflash");
        newsflashid.setAttribute("newsflash_id", temp.getNewsFlashID());
        reply.appendChild(newsflashid);
    }
    return finalizeReply(message,reply);
}


//******************************************END GET NEWS FLASH IDS SECTION***************************************************















//****************************************** GET BOARD LIST SECTION***************************************************


QByteArray MessageProtocol::createGetBoardListRequest(){
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "GetBoardList");
    return finalizeRequest(message, request);
}

QByteArray MessageProtocol::createGetBoardListReply(QList<FlashBoard> flashboards){
    QDomDocument message;
    QDomElement reply = createReply(message, "object", "GetBoardList");
    foreach (FlashBoard temp, flashboards){
        appendFlashBoard(message,reply,temp);
    }
    return finalizeReply(message,reply);
}

//******************************************END GET BOARD LIST SECTION***************************************************









//****************************************** GET NEWS FLASHES LIST SECTION***************************************************


QByteArray MessageProtocol::createGetNewsflashesRequest(QList<QString> newsflashlist){
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "GetNewsflashes");
    QDomElement newsflashes = message.createElement("newsflashes");
    foreach (QString temp,newsflashlist){
        QDomElement newsflash = message.createElement("newsflash");
        newsflash.setAttribute("newsflash_id", temp);
        newsflashes.appendChild(newsflash);
    }
    request.appendChild(newsflashes);
    return finalizeRequest(message, request);
}

QByteArray MessageProtocol::createGetNewsflashesReply(QList<NewsFlash> newsflashes){
    QDomDocument message;
    QDomElement reply = createReply(message, "object", "GetNewsflashes");
    foreach (NewsFlash temp, newsflashes){
        appendNewsFlash(message, reply, temp);
    }
    return finalizeReply(message, reply);
}

//****************************************** END GET NEWS FLASHES SECTION***************************************************




//****************************************** GET PROFILE LIST SECTION***************************************************

QByteArray MessageProtocol::createGetProfilesRequest(QList<QString> userlist){
    QDomDocument message;
    QDomElement request = createRequest(message, "query", "GetProfiles");
    QDomElement users = message.createElement("users");
    foreach (QString temp, userlist){
        QDomElement user = message.createElement("user");
        user.setAttribute("user_id", temp);
        users.appendChild(user);
    }
    request.appendChild(users);
    return finalizeRequest(message, request);
}


 QByteArray MessageProtocol::createGetProfilesReply(QList<UserProfile> profiles){
     QDomDocument message;
     QDomElement reply = createReply(message, "object", "GetProfiles");
     foreach (UserProfile temp, profiles){
         appendUserProfile(message, reply, temp);
     }
     return finalizeReply(message, reply);
 }

//****************************************** END GET PROFILE LIST SECTION***************************************************










//****************************************** CREATE NEWS FLASH SECTION***************************************************

QByteArray MessageProtocol::createCreateNewsflashRequest(NewsFlash a_newsflash){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "CreateNewsFlash");
    appendNewsFlash(message, request, a_newsflash);
    return finalizeRequest(message, request);
}





//****************************************** END CREATE NEWS FLASH SECTION***************************************************



//****************************************** CREATE SEGMENT SECTION***************************************************

QByteArray MessageProtocol::createCreateSegmentRequest(FlashSegment a_flashsegment){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "CreateSegment");
    appendFlashSegment(message, request, a_flashsegment);
    return finalizeRequest(message, request);
}

//****************************************** END CREATE SEGMENT SECTION***************************************************



//****************************************** UPDATE PROFILE SECTION***************************************************
QByteArray MessageProtocol::createUpdateProfileRequest(CUPicture a_picture){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "UpdateProfile");
    QDomElement profile = message.createElement("profile");
    appendPicture(message,profile,a_picture);

    request.appendChild(profile);
    return finalizeRequest(message, request);
}

QByteArray MessageProtocol::createUpdateProfileRequest(QString a_nickname){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "UpdateProfile");
    QDomElement profile = message.createElement("profile");


    QDomElement nickname = message.createElement("nickname");
    QDomText nicknamedata;
    nicknamedata.setData(a_nickname);
    nickname.appendChild(nicknamedata);
    profile.appendChild(nickname);

    request.appendChild(profile);
    return finalizeRequest(message, request);
}

QByteArray MessageProtocol::createUpdateProfileRequest(UserProfile a_profile){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "UpdateProfile");
    QDomElement profile = message.createElement("profile");

    QDomElement nickname = message.createElement("nickname");
    QDomText nicknamedata = message.createTextNode(a_profile.getNickname());
    nickname.appendChild(nicknamedata);
    profile.appendChild(nickname);

    appendPicture(message,profile,a_profile.getPicture());

    request.appendChild(profile);
    return finalizeRequest(message, request);
}

//****************************************** END UPDATE PROFILE  SECTION***************************************************




//****************************************** FILTER BOARD SECTION***************************************************

QByteArray MessageProtocol::createFilterBoardRequest(QList<FlashBoard> flashboards){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "FilterBoard");
    foreach(FlashBoard temp, flashboards){
        QDomElement flashboard = message.createElement("flashboard");
        flashboard.setAttribute("flashboard_id", temp.getFlashboardID());
        if(temp.isFiltered()){
            flashboard.setAttribute("visible", "true");
        }
        else{
            flashboard.setAttribute("visible", "false");
        }
        request.appendChild(flashboard);
    }
    return finalizeRequest(message, request);
}

//****************************************** END FILTER BOARD  SECTION***************************************************






//****************************************** DELETE NEWS FLASH SECTION***************************************************

QByteArray MessageProtocol::createDeleteNewsflashRequest(QString newsflash_id){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "DeleteNewsflash");

    QDomElement newsflash = message.createElement("newsflash");
    newsflash.setAttribute("newsflash_id", newsflash_id);
    request.appendChild(newsflash);

    return finalizeRequest(message, request);
}

//****************************************** END DELETE NEWS FLASH  SECTION***************************************************





//****************************************** DELETE SEGMENT SECTION***************************************************

QByteArray MessageProtocol::createDeleteSegmentRequest(QString segment_id){
    QDomDocument message;
    QDomElement request = createRequest(message, "modify", "DeleteSegment");

    QDomElement segment = message.createElement("segment");
    segment.setAttribute("segment_id", segment_id);
    request.appendChild(segment);

    return finalizeRequest(message, request);
}

//****************************************** END DELETE SEGMENT  SECTION***************************************************




//****************************************** REQUEST SUCCEEDED/FAILED SECTION***************************************************

//Returns the ID of the object created OR -1 if the request did not involve creating an object
QByteArray MessageProtocol::createRequestSucceededReply(int id){
    QDomDocument message;
    QDomElement reply = message.createElement("reply");
    reply.setAttribute("category", "nonobject");
    reply.setAttribute("type", "RequestSucceeded");
    reply.setAttribute("id",id);
    message.appendChild(reply);
    return finalizeReply(message,reply);
}

/*TYPES OF EXCEPTIONS:
    UNRECOGNIZED = The server doesn't understand the Request (protocol violation or unsupported extension).
    CONTENTS = The request contained invalid contents.
    UNAVAILABLE = The request is unavailable in the current state of the requesting client.
    UNAUTHORIZED = The client is aunauthorized to make this request.
    */

QByteArray MessageProtocol::createRequestFailedReply(QString exception_code){
    QDomDocument message;
    QDomElement reply = message.createElement("reply");
    reply.setAttribute("category", "nonobject");
    reply.setAttribute("type", "RequestFailed");
    reply.setAttribute("exception",exception_code);
    message.appendChild(reply);
    return finalizeReply(message,reply);
}

//****************************************** END REQUEST SUCCEEDED/FAILED SECTION***************************************************


//****************************************** UPDATES SECTION************************************************************************

QByteArray MessageProtocol::createNewNewsflashUpdate(NewsFlash newsflash){
    QDomDocument message;
    QDomElement update = createUpdate(message,"object","NewNewsflash");
    appendNewsFlash(message,update,newsflash);
    return finalizeUpdate(message,update);
}

QByteArray MessageProtocol::createNewSegmentUpdate(FlashSegment segment){
    QDomDocument message;
    QDomElement update = createUpdate(message,"object","NewSegment");
    appendFlashSegment(message,update,segment);
    return finalizeUpdate(message,update);
}

QByteArray MessageProtocol::createProfileUpdateUpdate(UserProfile profile){
    QDomDocument message;
    QDomElement update = createUpdate(message,"object","ProfileUpdate");
    appendUserProfile(message,update,profile);
    return finalizeUpdate(message,update);
}

QByteArray MessageProtocol::createNewsflashDeletedUpdate(int id){
    QDomDocument message;
    QDomElement update = createUpdate(message,"delete","NewsflashDeleted");
    QDomElement newsflash = message.createElement("newsflash");
    newsflash.setAttribute("newsflash_id",id);
    update.appendChild(newsflash);
    return finalizeUpdate(message,update);
}

QByteArray MessageProtocol::createSegmentDeletedUpdate(int id){
    QDomDocument message;
    QDomElement update = createUpdate(message,"delete","SegmentDeleted");
    QDomElement segment = message.createElement("segment");
    segment.setAttribute("segment_id",id);
    update.appendChild(segment);
    return finalizeUpdate(message,update);
}

//******************************************END UPDATES SECTION************************************************************************
