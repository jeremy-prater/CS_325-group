#ifndef TSP_TOUR_POP_H
#define TSP_TOUR_POP_H

#include "tour.h"

class TourPopulation
{
public:
    TourPopulation(int populationSize, bool init);
    void saveTour(int index, Tour * tour);
    Tour * getTour(int index);
    Tour * getFittest();
    int populationSize();

private:
    std::vector<Tour *> tours;
};

#endif // TSP_TOUR_POP_H
