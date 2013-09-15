#ifndef FLASHBOARD_H
#define FLASHBOARD_H

#include <QList>
#include "flashsegment.h"

class FlashBoard
{
public:
    FlashBoard();

    QString getName();
    QList<FlashSegment> getSegments();
    bool isFiltered();
    int getFlashboardID();
    void setFlashBoardID(int);
    void setName(QString a_name);
    void addSegment(FlashSegment a_segment);
    void setFiltered(bool a_filtered);

private:
    int flashboard_id;
    QString name;
    QList<FlashSegment> segments;
    bool filtered;
};

#endif // FLASHBOARD_H
