#include "tourSet.h"

std::vector<City *> TourSet::cityList;

void TourSet::addCity(City * destCity)
{
    cityList.push_back(destCity);
}

City * TourSet::getCity (int index)
{
    return cityList[index];
}

int TourSet::cityCount()
{
    return cityList.size();
}

std::vector<City *>* TourSet::getCityList()
{
    return &cityList;
}