#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include "bird.h"

class YellowBird: public Bird
{
public:
    YellowBird(float,QPointF,QPixmap);
    virtual void special();
};

#endif // YELLOWBIRD_H
