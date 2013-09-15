#include "windowcontrol.h"
#include "flashfeedwindowhandler.h"
#include "loginwindowhandler.h"
#include "profilewindowhandler.h"
#include "flashsegmentwindowhandler.h"
#include "filterwindowhandler.h"
#include <QDebug>


const int WindowControl::PROFILE_PAGE = 1;
const int WindowControl::FLASHFEED_PAGE = 2;
const int WindowControl::FLASHSEGMENT_PAGE = 3;
const int WindowControl::FILTER_PAGE = 4;

WindowControl::WindowControl()
{
}

void WindowControl::changeWindow()
{
    LoginWindowHandler mLogon;
    mLogon.run();
}


void WindowControl::changeWindow(int i, clientCache *mCache)
	//i is the page that you are going to
	//client cache is a reference to the cache
{
   if(i == PROFILE_PAGE){
       ProfileWindowHandler mProfile;
       mProfile.run(mCache);
   }
   else if(i == FLASHFEED_PAGE){
       FlashFeedWindowHandler mFeed;
       mFeed.run(mCache);
   }
   else if(i == FLASHSEGMENT_PAGE){
       FlashSegmentWindowHandler mSegment;
       mSegment.run(mCache);
   }
   else if(i == FILTER_PAGE){
       FilterWindowHandler mFilter;
       mFilter.run(mCache);
   }

}
