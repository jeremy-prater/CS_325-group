#include "tourPop.h"

TourPopulation::TourPopulation(int populationSize, bool init)
{
    popSize = populationSize;
    tours = (Tour **) malloc (populationSize * sizeof (Tour *));
    if (init)
    {
        for (int index=0; index < populationSize; index++)
        {
            Tour * newTour = new Tour();
            newTour->generate();
            saveTour(index, newTour);
        }
    }
}

void TourPopulation::saveTour(int index, Tour * newTour)
{
	tours[index] = newTour;
}

Tour * TourPopulation::getTour(int index)
{
    return tours[index];
}

Tour * TourPopulation::getFittest(double minFit)
{
    Tour * fittest = tours[0];
    for (size_t index = 1; index < popSize; index++)
    {
        double testFit = getTour(index)->getFitness();
        if ((fittest->getFitness() <= testFit) && (testFit > minFit))
        {
            fittest = getTour(index);
        }
    }
	return fittest;
}

int TourPopulation::populationSize()
{
    return popSize;
}
