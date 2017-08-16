#ifndef TSP_TOUR_SET_H
#define TSP_TOUR_SET_H

#include "city.h"
#include <vector>

class TourSet
{
public:
    static void addCity(City * destCity);
    static City * getCity (int index);
    static int cityCount();
    static std::vector<City *>* getCityList();

private:
    static std::vector<City *> cityList;
};

#endif // TSP_TOUR_SET_H
