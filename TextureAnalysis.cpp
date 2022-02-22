// TextureAnalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
// https://open.kattis.com/problems/textureanalysis

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string DecideIfEven(string row)
{
	vector<char> pattern;
	bool findPattern = true;
	int patternSize;
	int patternInd = 0;
	string::iterator rowIter = row.begin();
	rowIter = row.begin();
	char startChar = *rowIter;
	rowIter++;
	while (rowIter != row.end())
	{
		char c = *rowIter;
		if (findPattern)
		{
			if (c != startChar)
			{
				pattern.push_back(c);
				rowIter++;
				continue;
			}
			else
			{
				findPattern = false;
				pattern.push_back(c);
				patternSize = pattern.size();
				rowIter++;
				continue;
			}
		}
		
		// Check if pattern match.
		if (c != pattern[patternInd])
		{
			return "NOT EVEN";
		}

		patternInd++;

		if (patternInd == patternSize)
		{
			patternInd = 0;
		}
		rowIter++;
	}

	return "EVEN";
}

int main()
{
	// Problem info:
	// At most 2000 lines
	// At most 1000 chars per line.
	vector<string> result;
	string line;
	while (getline(cin, line))
	{
		if (line == "END")
		{
			break;
		}

		result.push_back(DecideIfEven(line));
	}

	for (size_t i = 0; i < result.size(); i++)
	{
		cout << i + 1 << ' ' << result[i] << "\n";
	}
}
