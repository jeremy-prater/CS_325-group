#include "tour.h"

static auto randomShuffle = std::default_random_engine{};

Tour::Tour ()
{
    fitness = 0;
    distance = 0;
	for (int index = 0; index < TourSet::cityCount(); index++)
	{
		tour.push_back(NULL);
	}
}

void Tour::generate()
{
	tour.clear();
    std::vector<City *> * cityList = TourSet::getCityList();
    std::copy(cityList->begin(), cityList->end(), back_inserter(tour));
    std::shuffle(tour.begin(), tour.end(), randomShuffle);
}

City * Tour::getCity (int position)
{
    return tour[position];
}

void Tour::setCity (int position, City * city)
{
    tour[position] = city;
    fitness = 0;
    distance = 0;
}

double Tour::getFitness()
{
    if (fitness == 0)
    {
        fitness = 1 / (double)getDistance();
    }
    return fitness;
}
int Tour::getDistance()
{
    if (distance == 0)
    {
        int tourDistance = 0;
        for (size_t cityIndex = 0; cityIndex < tour.size(); cityIndex++)
        {
            City * startCity = getCity(cityIndex);
            City * endCity;
            if (cityIndex + 1 < tour.size())
            {
                endCity = getCity (cityIndex + 1);
            }
            else
            {
                endCity = getCity (0);
            }
            tourDistance += startCity->distanceTo(endCity);
        }
        distance = tourDistance;
    }
    return distance;
}
int Tour::tourLength()
{
    return tour.size();
}

bool Tour::containsCity(City * city)
{
    if (std::find(tour.begin(), tour.end(), city) != tour.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Tour::ToString() {
	printf("|");
	for (int i = 0; i < tourLength(); i++)
	{
		City * curCity = getCity(i);
		printf("%d %d", curCity->getX(), curCity->getY());
		printf("|");
	}
	printf("\n");
}