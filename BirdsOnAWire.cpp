// BirdsOnAWire.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://open.kattis.com/problems/birds/statistics

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main()
{
	string line;
	string storeChars;
	int i = 0;
	vector<int> firstLine;

	// Use a set that orders position of birds.
	set<int> birdPositions;
	while (std::getline(cin, line))
	{
		if (i == 0)
		{
			int j = 0;
			for (char c : line)
			{
				if (c != ' ')
				{
					storeChars.push_back(c);
				}
				else if (c == ' ')
				{
					firstLine.push_back(stoi(storeChars));
					storeChars.clear();
				}
			}

			firstLine.push_back(stoi(storeChars));
			storeChars.clear();
			i += 1;
			continue;
		}

		birdPositions.insert(stoi(line));


	}

	int lengthOfWire = firstLine[0];
	int distance = firstLine[1];
	int presentBirds = firstLine[2];

	long newBirds = 0;

	// Cannot sit closer than 6 units to any of the poles.
	if (lengthOfWire <= 12)
	{
		cout << 0;
		return 0;
	}

	int k = 0;
	set<int>::iterator presBirdsIt = birdPositions.begin();

	// If no birds sit on the wire.
	if (presBirdsIt == birdPositions.end())
	{
		newBirds = lengthOfWire - 12;
		newBirds = (newBirds / distance) + 1;
		cout << newBirds;
		return 0;
	}
	
	int prevBird = *presBirdsIt;
	int firstBird = prevBird;
	presBirdsIt++;
	while (presBirdsIt != birdPositions.end())
	{
		int nextBird = *presBirdsIt;
		newBirds += (nextBird - prevBird) / distance - 1;
		prevBird = nextBird;

		presBirdsIt++;
	}


	newBirds += (lengthOfWire - 6 - prevBird) / distance;
	newBirds += (firstBird - 6) / distance;
	cout << newBirds;

}
