#ifndef TSP_TOUR_MANAGER_H
#define TSP_TOUR_MANAGER_H

#include <vector>
#include <algorithm>
#include <random>
#include <iterator>

#include "city.h"
#include "tourSet.h"

class Tour
{
public:
    Tour ();
    void generate();
    City * getCity (int position);
    void setCity (int position, City * city);
    double getFitness();
    int getDistance();
    int tourLength();
    bool containsCity(City * city);
	void ToString();

private:
    std::vector<City *> tour;
    int distance;
    double fitness;
};

#endif // TSP_TOUR_MANAGER_H