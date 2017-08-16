#include <stdio.h>
#include "tourGA.h"

int main()
{
	srand(time(NULL));
	// Create and add our cities
	City * city= new City(60, 200);
	TourSet::addCity(city);
	City * city2 = new City(180, 200);
	TourSet::addCity(city2);
	City * city3 = new City(80, 180);
	TourSet::addCity(city3);
	City * city4 = new City(140, 180);
	TourSet::addCity(city4);
	City * city5 = new City(20, 160);
	TourSet::addCity(city5);
	City * city6 = new City(100, 160);
	TourSet::addCity(city6);
	City * city7 = new City(200, 160);
	TourSet::addCity(city7);
	City * city8 = new City(140, 140);
	TourSet::addCity(city8);
	City * city9 = new City(40, 120);
	TourSet::addCity(city9);
	City * city10 = new City(100, 120);
	TourSet::addCity(city10);
	City * city11 = new City(180, 100);
	TourSet::addCity(city11);
	City * city12 = new City(60, 80);
	TourSet::addCity(city12);
	City * city13 = new City(120, 80);
	TourSet::addCity(city13);
	City * city14 = new City(180, 60);
	TourSet::addCity(city14);
	City * city15 = new City(20, 40);
	TourSet::addCity(city15);
	City * city16 = new City(100, 40);
	TourSet::addCity(city16);
	City * city17 = new City(200, 40);
	TourSet::addCity(city17);
	City * city18 = new City(20, 20);
	TourSet::addCity(city18);
	City * city19 = new City(60, 20);
	TourSet::addCity(city19);
	City * city20 = new City(160, 20);
	TourSet::addCity(city20);

	// Initialize population
	TourPopulation * pop = new TourPopulation(1500, true);
	printf ("Initial distance: %d\n", pop->getFittest()->getDistance());

	// Evolve population for 100 generations
	pop = TourGA::evolvePopulation(pop);
	for (int i = 0; i < 500; i++) {
		pop = TourGA::evolvePopulation(pop);
	}

	// Print final results
	printf("Finished\n");
	printf("Final distance: %d\n", pop->getFittest()->getDistance());
	printf("Solution:\n");
	pop->getFittest()->ToString();

	return 0;
}