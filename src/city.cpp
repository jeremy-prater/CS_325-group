#include "city.h"
#include <math.h>

City::City(int newIndex, int newX, int newY)
{
    index = newIndex;
    x = newX;
    y = newY;
}

int City::getX()
{
    return x;
}

int City::getY()
{
    return y;
}

int City::getIndex()
{
    return index;
}

// return int to match program spec
int City::distanceTo(City * destCity)
{
    int dx = getX() - destCity->getX();
    int dy = getY() - destCity->getY();
    return (int)sqrt ((dx*dx) + (dy*dy));
}
