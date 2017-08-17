#ifndef TSP_TOUR_GA_H
#define TSP_TOUR_GA_H

#include "tourPop.h"

class TourGA
{
public:
    static int mutationRate;
    static TourPopulation * evolvePopulation(TourPopulation * pop);
    static Tour * crossover (Tour * parent1, Tour * parent2);
    static void mutate(Tour * tour);
    static Tour * tournamentSelection(TourPopulation * pop);


private:
    static int tournamentSize;
    static int elitism;
};

#endif // TSP_TOUR_GA_H