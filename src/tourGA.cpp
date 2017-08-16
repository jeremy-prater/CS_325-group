#include "tourGA.h"

int TourGA::mutationRate = 5;
int TourGA::tournamentSize = 5;
bool TourGA::elitism = true;

TourPopulation * TourGA::evolvePopulation(TourPopulation * pop)
{
    TourPopulation * newPop = new TourPopulation(pop->populationSize(), false);
    int elitismOffset = 0;
    if (TourGA::elitism)
    {
		newPop->saveTour(0, pop->getFittest());
        elitismOffset = 1;
    }

    for (int eIndex = elitismOffset; eIndex < newPop->populationSize(); eIndex++)
    {
        Tour * parent1 = tournamentSelection(pop);
        Tour * parent2 = tournamentSelection(pop);
        Tour * child = crossover(parent1, parent2);
        newPop->saveTour(eIndex, child);
    }

    for (int eIndex = elitismOffset; eIndex < newPop->populationSize(); eIndex++)
    {
        mutate(newPop->getTour(eIndex));
    }

    return newPop;
}

Tour * TourGA::crossover (Tour * parent1, Tour * parent2)
{
    Tour * child = new Tour();
    int startPos = (int)rand() % parent1->tourLength();
    int endPos = (int)rand() % parent1->tourLength();
    for (int index = 0; index < child->tourLength(); index++)
    {
        if ((startPos < endPos) && (index > startPos) && (index < endPos))
        {
            child->setCity(index, parent1->getCity(index));
        }
        else if (startPos > endPos)
        {
            if (!((index < startPos) && (index > endPos)))
            {
                child->setCity (index, parent1->getCity(index));
            }
        }
    }
    for (int index = 0; index < parent2->tourLength(); index++)
    {
        if (!child->containsCity(parent2->getCity(index)))
        {
            for (int innerLoop = 0; innerLoop < child->tourLength(); innerLoop++)
            {
                if (child->getCity(innerLoop) == NULL)
                {
                    child->setCity(innerLoop, parent2->getCity(index));
                    break;
                }
            }
        }
    }
    return child;
}

void TourGA::mutate(Tour * tour)
{
    for (int index1 = 0; index1 < tour->tourLength(); index1++)
    {
        if (rand() % 100 < TourGA::mutationRate)
        {
            int index2 = rand() % tour->tourLength();
            City * city1 = tour->getCity(index1);
            City * city2 = tour->getCity(index2);
            tour->setCity (index2, city1);
            tour->setCity (index1, city2);
        }
    }
}

Tour * TourGA::tournamentSelection(TourPopulation * pop)
{
    TourPopulation * tournament = new TourPopulation(TourGA::tournamentSize, false);

    for (int index = 0; index < TourGA::tournamentSize; index++)
    {
        int randomIndex = (int) rand() % pop->populationSize();
        tournament->saveTour(index, pop->getTour(randomIndex));
    }
    return tournament->getFittest();
}
