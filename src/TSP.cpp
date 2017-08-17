#include <stdio.h>
#include "tourGA.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#define NUMT 24

int main(int argc, char *argv[])
{
	// Seed random number generator
	srand(time(NULL));

	if (argc != 2)
	{
		cout << "Incorrect number of arguments!" << endl << endl << "Usage : cs325-group <input file>" << endl << endl;
		exit (-1);
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

    omp_set_num_threads(NUMT);
    cout <<  "Using " << NUMT << "threads." << endl;

	// Initialize population
	TourPopulation * pop = new TourPopulation(TourSet::cityCount() * 10, true);
	cout << "Initial distance: " << pop->getFittest()->getDistance() << endl;

	// Evolve population for 100 generations
	pop = TourGA::evolvePopulation(pop);
	for (int i = 0; i < TourSet::cityCount() * 1000; i++) {
		pop = TourGA::evolvePopulation(pop);
	}

	// Print final results
	Tour * finalTour = pop->getFittest();
	cout << "Finished" << endl;
	cout << "Final distance: " << finalTour->getDistance() << endl;
	cout << "Solution: " << endl;
	
	cout << "Writing to file [" << outFile << "]" << endl;
	outputFile << finalTour->getDistance() << endl;
	finalTour->WriteData(&outputFile);
	outputFile.close();

	return 0;
}