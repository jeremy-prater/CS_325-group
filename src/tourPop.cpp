#include "tourPop.h"

TourPopulation::TourPopulation(int populationSize, bool init)
{
    for (int index=0; index < populationSize; index++)
    {
        tours.push_back(NULL);
        if (init)
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

Tour * TourPopulation::getFittest(double minFit = 0)
{
    Tour * fittest = tours[0];
    for (size_t index = 1; index < tours.size(); index++)
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
    return tours.size();
}
