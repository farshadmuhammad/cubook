#ifndef FLASHSEGMENT_H
#define FLASHSEGMENT_H

#include <QString>

class FlashSegment
{
public:
    FlashSegment();

    int getSegmentID();
    int getFlashboardID();
    QString getName();

    void setSegmentID(int a_segment_id);
    void setFlashboardID(int a_flashboard_id);
    void setName(QString a_name);

private:
    QString name;
    int segment_id, flashboard_id;
};

#endif // FLASHSEGMENT_H
