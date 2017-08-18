#include <stdio.h>
#include "tourGA.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "stdlib.h"
#include "string.h"

using namespace std;
using namespace std::chrono;

#define NUMT 24

#define MIN_TOURNAMENT  5
#define MIN_ELITE       5
#define MIN_POPULATION  15

#define WORKPERTHREAD 30000

#define RATIO_ELITE      0.750f
#define RATIO_TOURNAMENT 0.450f
#define RATIO_POPULATION 1.000f

void printUsage()
{
	cout << "Incorrect number of arguments!" << endl << endl;
	cout << "Usage : cs325-group <input file> -t <180>           -- Run for 180 seconds" << endl;
	cout << "Usage : cs325-group <input file> -m <mindistance>   -- Run until (min distance * 1.25) is found" << endl << endl;
	exit (-1);
}

int main(int argc, char *argv[])
{
	// Seed random number generator
	srand(time(NULL));

	if (argc != 4)
	{
		printUsage();
	}

	int mode = -1;
	int condition = atoi(argv[3]);
	if (strcmp (argv[2], "-t") == 0)
	{
		mode = 0;
	}
	else if (strcmp (argv[2], "-m") == 0)
	{
		mode = 1;
		condition *= 1.25;
	}
	else
	{
		printUsage();
	}

	ofstream outputFile;
	string outFile(argv[1]);
	outFile.append(".tour");
	outputFile.open(outFile);
	if (!outputFile.is_open())
	{
		cout << "unable to open [" << outFile << "] for writing!" << endl << endl;
		exit(-2);
	}

	ifstream inputFile;
	inputFile.open(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "unable to open [" << argv[1] << "] for reading!" << endl << endl;
		exit(-3);
	}

	string str;
	cout << "Reading file [" << argv[1] << "]" << endl;
    while (getline(inputFile, str))
    {
        stringstream ss(str);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> vstrings(begin, end);
		//copy(vstrings.begin(), vstrings.end(), ostream_iterator<string>(cout, "\n"));

		int index = stoi(vstrings[0]);
		int x = stoi(vstrings[1]);
		int y = stoi(vstrings[2]);
		City * newCity = new City (index, x, y);
		TourSet::addCity(newCity);
    }
	inputFile.close();
	cout << "Read Complete! [" << TourSet::cityCount() << "] Cities. Beginning TSP." << endl;

	TourGA::mutationRate = 1;

	// Find the normalized load factor
	double normalF = (NUMT * WORKPERTHREAD) / TourSet::cityCount();

	TourGA::elitism = normalF * RATIO_ELITE;
	TourGA::tournamentSize = normalF * RATIO_TOURNAMENT;
	int popCount = normalF * RATIO_POPULATION;

	if (TourGA::elitism < MIN_ELITE)
	{
		TourGA::elitism = MIN_ELITE;
	}

	if (popCount < MIN_POPULATION)
	{
		popCount = MIN_POPULATION;
	}

	if (TourGA::tournamentSize < MIN_TOURNAMENT)
	{
		TourGA::tournamentSize = MIN_TOURNAMENT;
	}

    omp_set_num_threads(NUMT);
    cout <<  "Using " << NUMT << " threads." << endl;
	if (mode == 0)
	{
		cout << "Running for " << condition << " seconds..." << endl;
	}
	else if (mode == 1)
	{
		cout << "Running until path length " << condition << " is found..." << endl;
	}

	cout << "Using Population Count " << popCount << endl;
	cout << "Using Elite Count " << TourGA::elitism << endl;
	cout << "Using Tournament Count " << TourGA::tournamentSize << endl;

	// Initialize population
	TourPopulation * pop = new TourPopulation(popCount, true);

	pop = TourGA::evolvePopulation(pop);
	int counter = 0;
	int progress = 0;
	int lastDistance = 0;
	int baseRate = TourGA::mutationRate;
	int minDistance = pop->getFittest()->getDistance();

	cout << "Initial distance: " << minDistance << endl;
	Tour * bestTour = pop->getFittest();

	bool running = true;
	uint64_t startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	uint64_t updateTime = startTime + 1000;
	uint64_t averageLoop = 0;
	uint64_t endTime = startTime + (3 * 60000);
	while (running)
	{
		pop = TourGA::evolvePopulation(pop);

		uint64_t currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

		if (averageLoop == 0)
		{
			averageLoop = currentTime - startTime;
			cout << "Average loop execution time " << averageLoop << "ms." << endl;
		}

		// Update min distance
		if (minDistance > pop->getFittest()->getDistance())
		{
			bestTour = pop->getFittest();
			minDistance = bestTour->getDistance();
		}

		if (((mode == 0) && ((currentTime + (averageLoop * 2)) >= endTime)) || ((mode == 1) && (minDistance <= condition)))
		{
			running = false;
		}

		// Adaptive Mutation
		/*if (lastDistance == pop->getFittest()->getDistance())
		{
			if (TourGA::mutationRate < 20)
			{
				TourGA::mutationRate++;
				//cout << "Mutation Rate : [" << TourGA::mutationRate << "]" << endl;
			}
		}
		else if (TourGA::mutationRate > baseRate)
		{
			//TourGA::mutationRate /= 2;
			TourGA::mutationRate = baseRate;
			//cout << "Mutation Rate : [" << TourGA::mutationRate << "]" << endl;
		}
		lastDistance = pop->getFittest()->getDistance();*/

		if (currentTime >= updateTime)
		{
			updateTime += 1000;
			cout <<  (int)((currentTime - startTime) / 1000.0f) << " seconds execution...  Min path [" << minDistance << "]" << endl;
		}
	}

	// Print final results
	Tour * finalTour = pop->getFittest();
	cout << "Finished in " << (duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - startTime) << " ms." << endl;
	cout << "Final distance: " << finalTour->getDistance() << endl;
	cout << "Solution: " << endl;

	cout << "Writing to file [" << outFile << "]" << endl;
	outputFile << finalTour->getDistance() << endl;
	finalTour->WriteData(&outputFile);
	outputFile.close();

	return 0;
}
