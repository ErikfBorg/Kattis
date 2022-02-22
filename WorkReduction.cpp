// WorkReduction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;
int trackCaseToPrint = 1;
typedef std::pair<long, string> AgencyScore;
struct Agency
{
	int ARate;
	int BRate;
	string Name;

	Agency()
	{
	}

	Agency(int aRate, int bRate, string name) : ARate(aRate), BRate(bRate), Name(name)
	{
	}
};

bool CompareAgency(const AgencyScore& a, const AgencyScore& b)
{
	if (a.first != b.first)
	{
		return a.first > b.first;
	}
	else
	{
		if (a.second.compare(b.second) == -1)
		{
			return true;
		}

		return false;
	}
}

long CalculateCost(int startWorkLoad, int endWorkLoad, Agency agency)
{
	// If startWorkLoad == endWorkLoad, no work
	// If ARate is free => no cost.
	// If BRate is free => no cost if that scores even, which we cannot count on.
	if (startWorkLoad == endWorkLoad || agency.ARate == 0)
	{
		return 0;
	}

	// Need to land exactly on the endWorkLoad.
	long cost = 0;
	int start = startWorkLoad;

	// Go until we would have to use A-rate.
	while (start >= 2 * endWorkLoad)
	{
		// Amount of work left is rounded down, so we gain 1 work if remainder != 0.
		// Example:
		// If we have 100 / 2 = 50
		// If we have 101 / 2 = 50.5 => 50

		// If we have 25 / 2 = 12.5 => 25 - 12.5 = 12.5 => 12. Win = 25 - 12 = 13.
		// If we have 25 + 1 / 2 => 13. 25 - 13 = 12. Win = 13. And we can skip checking if there is a remainder.
		int bReduction = (start + 1) / 2;

		// If the win by divison * ARate < BRate, go for A
		bool possibleToGoForB = false;
		if (bReduction * agency.ARate > agency.BRate)
		{
			cost += agency.BRate;
			start /= 2;
		}
		else
		{
			//cost += agency.ARate;
			//start -= 1;
			break;
		}
	}

	return cost + (start - endWorkLoad) * agency.ARate;
}

void CalcAndRank(int startWorkLoad, int endWorkLoad, vector<Agency> agencies)
{
	set<AgencyScore> agencyScores;
	for (Agency agency : agencies)
	{
		long cost = CalculateCost(startWorkLoad, endWorkLoad, agency);
		agencyScores.insert(AgencyScore(cost, agency.Name));
	}

	cout << "Case " << trackCaseToPrint << "\n";
	set<AgencyScore>::iterator iter;
	for (iter = agencyScores.begin(); iter != agencyScores.end(); iter++)
	{
		AgencyScore thisAgency = *iter;
		cout << thisAgency.second << " " << thisAgency.first << "\n";
	}

	trackCaseToPrint += 1;
}

int main()
{

	string line;
	int i = 0;
	int nrOfCasesToFollow = 0;
	bool readingCase = false;
	bool caseInfo = false;
	int startWorkLoad;
	int endWorkLoad;
	int nrOfCases;
	int atCaseNr = 0;
	vector<Agency> agencies;
	while (std::getline(cin, line))
	{
		if (i == 0)
		{
			nrOfCasesToFollow = stoi(line);
			i++;
			caseInfo = true;
			continue;
		}
		if (caseInfo && !readingCase)
		{
			vector<int> storeInfo;
			string nr;
			for (char c : line)
			{
				if (c != ' ')
				{
					nr.push_back(c);
				}
				else if (c == ' ')
				{
					storeInfo.push_back(stoi(nr));
					nr.clear();
				}
			}
			storeInfo.push_back(stoi(nr));
			nr.clear();

			startWorkLoad = storeInfo[0];
			endWorkLoad = storeInfo[1];
			nrOfCases = storeInfo[2];
			readingCase = true;
		}
		else if (readingCase)
		{
			if (atCaseNr == nrOfCases)
			{
				readingCase = false;
				continue;
			}

			Agency agency;
			int colonPosition = line.find(':');
			int commaPosition = line.find(',');
			agency.Name = line.substr(0, colonPosition);
			agency.ARate = stoi(line.substr(colonPosition + 1, commaPosition - 1));
			agency.BRate = stoi(line.substr(commaPosition + 1, line.length() - 1));
			agencies.push_back(agency);
			atCaseNr++;

			if (atCaseNr == nrOfCases)
			{
				readingCase = false;

				// Calculate and rank agencies.
				CalcAndRank(startWorkLoad, endWorkLoad, agencies);

				// Reset.
				agencies.clear();
				atCaseNr = 0;
			}
		}

	}
}