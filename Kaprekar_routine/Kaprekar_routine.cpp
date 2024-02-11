// Kaprekar_routine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

#define _MAX_DIGITS 8
using namespace std;

typedef long long LLONG;
std::map<LLONG, std::vector<LLONG>> _kaprekar_routine_map;

void getKaprekarRoutine(LLONG number, int nDigits)
{
	char* error = NULL;
	vector<LLONG> kaprekarSequence;
	std::string strNum(to_string(number));
	kaprekarSequence.push_back(number);

	while (1)
	{
		LLONG ascendingNumber = 0ll, descendingNumber = 0ll, newNumber = 0ll;;
		std::vector<int> randomNumber, ascendingArrangement, descendingArrangement;

		if (strNum.size() < nDigits)
		{
			int diff = nDigits - strNum.size();
			for (int i = 0; i < diff; i++)
				strNum.push_back('0');
		}

		for (int i = 0; i < strNum.size(); i++)
			randomNumber.push_back(strNum[i] - '0');

		ascendingArrangement = randomNumber;
		descendingArrangement = randomNumber;

		std::sort(ascendingArrangement.begin(), ascendingArrangement.end(), std::greater<int>());
		std::sort(descendingArrangement.begin(), descendingArrangement.end(), std::less<int>());

		char strAscendingNumber[_MAX_DIGITS + 1] = "", strdescendingNumber[_MAX_DIGITS + 1] = " ";
		for (int i = 0; i < ascendingArrangement.size(); i++)
		{
			strAscendingNumber[i] = '0' + ascendingArrangement[i];
		}
		for (int i = 0; i < descendingArrangement.size(); i++)
		{
			strdescendingNumber[i] = '0' + descendingArrangement[i];
		}

		ascendingNumber = strtoll(strAscendingNumber, &error, 10);
		descendingNumber = strtoll(strdescendingNumber, &error, 10);

		newNumber = ascendingNumber - descendingNumber;

		if (std::find(kaprekarSequence.begin(), kaprekarSequence.end(), newNumber) != kaprekarSequence.end())
			break;

		strNum = to_string(newNumber);
		kaprekarSequence.push_back(newNumber);
	}

	_kaprekar_routine_map[number] = kaprekarSequence;
	return;
}
int main()
{
	char* error = NULL;
	int nDigits = 0;
	cout << "Enter the number of digits for determining kaprekar constants and kaprekar routine" << "\t";

	cin >> nDigits;
	if (nDigits <= 0 || nDigits > 50)
	{
		std::cout << "Limit exceeded, Maximum number of digits allowed is 49" << std::endl;
		return -1;
	}

	LLONG minNumber = 0ll, maxNumber = 0ll;
	
	char* pMinNumber = NULL, * pMaxNumber = NULL;
	pMinNumber = (char*)calloc(sizeof(char), nDigits);
	pMaxNumber = (char*)calloc(sizeof(char), nDigits);

	if (!pMinNumber || !pMaxNumber)
	{
		std::cout << "Unable to allocate memory to fix the limit numbers for specified digits." << std::endl;
		return -2;
	}

	memset(pMinNumber, '0', sizeof(char) * nDigits);
	memset(pMaxNumber, '9', sizeof(char) * nDigits);

	pMinNumber[0] = '1';
	
	minNumber = strtoll(pMinNumber, &error, 10);
	if (error == pMinNumber)
	{
		std::cout << "Unable to convert minimum number to llong" << std::endl;
		return -3;
	}
	maxNumber = strtoll(pMaxNumber, &error, 10);
	if (error == pMaxNumber)
	{
		std::cout << "Unable to convert maximum number to llong" << std::endl;
		return -4;
	}

	
	for (LLONG num = minNumber; num <= maxNumber; num++)
		getKaprekarRoutine(num, nDigits);

	if (_kaprekar_routine_map.size())
	{
		cout << "Kaprekar routine for numbers from " << minNumber << " to " << maxNumber << " is " << std::endl;
		for (auto it = _kaprekar_routine_map.begin(); it != _kaprekar_routine_map.end(); it++)
		{
			cout << it->first << " : ";
			for (auto data = it->second.begin(); data != it->second.end(); ++data)
				cout << *data << "->";
			
			cout << "\n";
		}

		cout << "Non trivial kaprekar constants from " << minNumber << " to " << maxNumber << " is " << std::endl;
		for (auto it = _kaprekar_routine_map.begin(); it != _kaprekar_routine_map.end(); it++)
		{
			if (it->second.size() != 1)
				continue;

			cout << it->first;
			cout << "\n";
		}
	}

	free(pMinNumber);
	free(pMaxNumber);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
