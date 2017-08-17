#ifndef TSP_CITY_H
#define TSP_CITY_H

class City
{
public:
    City(int newIndex, int newX, int newY);

    int getIndex();
    int getX();
    int getY();

    // return int to match program spec
    int distanceTo(City * destCity);

private:
    int x;
    int y;
    int index;
};

#endif // TSP_CITY_H