#include "flashsegment.h"

FlashSegment::FlashSegment()
{
}

//Get Methods
int FlashSegment::getSegmentID(){return segment_id;}
int FlashSegment::getFlashboardID(){return flashboard_id;}
QString FlashSegment::getName(){return name;}


//Set Methods
void FlashSegment::setSegmentID(int a_segment_id){
    segment_id = a_segment_id;
}
void FlashSegment::setFlashboardID(int a_flashboard_id){
    flashboard_id = a_flashboard_id;
}
void FlashSegment::setName(QString a_name){
    name = a_name;
}
