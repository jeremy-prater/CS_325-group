#ifndef TSP_CITY_H
#define TSP_CITY_H

class City
{
public:
    City(int newX, int newY);

    int getX();
    int getY();

    // return int to match program spec
    int distanceTo(City * destCity);

private:
    int x;
    int y;
};

#endif // TSP_CITY_H