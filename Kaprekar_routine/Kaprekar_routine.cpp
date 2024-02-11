// Kaprekar_routine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <thread>
#include <mutex>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

using namespace std;

typedef long long LLONG;

mutex map_lock;
map<LLONG, std::vector<LLONG>> _kaprekar_routine_map;

void getKaprekarRoutine(LLONG start, LLONG end, int nDigits)
{
	for (LLONG number = start; number <= end; number++)
	{
		char* error = NULL;
		vector<LLONG> kaprekarSequence;
		std::string strNum(to_string(number));
		kaprekarSequence.push_back(number);

		while (1)
		{
			LLONG ascendingNumber = 0ll, descendingNumber = 0ll, newNumber = 0ll;;

			std::string ascendingArrangement, descendingArrangement;
			//std::vector<int> randomNumber, ascendingArrangement, descendingArrangement;

			if (strNum.size() < nDigits)
			{
				int diff = nDigits - strNum.size();
				for (int i = 0; i < diff; i++)
					strNum.insert(strNum.begin(), '0');
			}

			ascendingArrangement = strNum;
			descendingArrangement = strNum;

			sort(ascendingArrangement.begin(), ascendingArrangement.end(), greater<char>());
			sort(descendingArrangement.begin(), descendingArrangement.end(), less<char>());

			ascendingNumber = strtoll(ascendingArrangement.c_str(), &error, 10);

			if (error == ascendingArrangement.c_str())
				continue;

			descendingNumber = strtoll(descendingArrangement.c_str(), &error, 10);
			if (error == descendingArrangement.c_str())
				continue;

			newNumber = ascendingNumber - descendingNumber;

			if (std::find(kaprekarSequence.begin(), kaprekarSequence.end(), newNumber) != kaprekarSequence.end())
				break;

			strNum = to_string(newNumber);
			kaprekarSequence.push_back(newNumber);
		}

		map_lock.lock();
		if (kaprekarSequence.size() == 1)
			_kaprekar_routine_map[number] = kaprekarSequence;
		map_lock.unlock();
	}

	return;
}

int main()
{
	char* error = NULL;
	int numDigits = 0, numThreads = 1;;
	LLONG minNumber = 0ll, maxNumber = 0ll;
	char* pMinNumber = NULL, * pMaxNumber = NULL;
	vector<thread> threadList;

	cout << "Enter the number of digits for determining kaprekar constants and kaprekar routine" << "\t";
	cin >> numDigits;

	if (numDigits <= 0 || numDigits > 50)
	{
		std::cout << "Limit exceeded, Maximum number of digits allowed is 49" << std::endl;
		return -1;
	}

	pMinNumber = (char*)calloc(numDigits, sizeof(char));
	pMaxNumber = (char*)calloc(numDigits, sizeof(char));

	if (!pMinNumber || !pMaxNumber)
	{
		std::cout << "Unable to allocate memory to fix the limit numbers for specified digits." << std::endl;
		return -2;
	}

	memset(pMinNumber, '0', sizeof(char) * numDigits);
	memset(pMaxNumber, '9', sizeof(char) * numDigits);

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

#ifdef _WIN32
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	numThreads = sysinfo.dwNumberOfProcessors;
#else
	numThreads = sysconf(_SC_NPROCESSORS_ONLN);
#endif

	LLONG range_per_thread = ((maxNumber - minNumber) + 1) / numThreads;
	for (int i = 0; i < numThreads; i++)
	{
		LLONG start = minNumber + (i * range_per_thread);
		LLONG end = start + range_per_thread - 1;
		threadList.emplace_back(getKaprekarRoutine, start, end, numDigits);
	}

	for (auto& t : threadList)
		t.join();
	
	if (_kaprekar_routine_map.size())
	{
		/*cout << "Kaprekar routine for numbers from " << minNumber << " to " << maxNumber << " is " << std::endl;
		for (auto it = _kaprekar_routine_map.begin(); it != _kaprekar_routine_map.end(); it++)
		{
			cout << it->first << " : ";
			for (auto data = it->second.begin(); data != it->second.end(); ++data)
				cout << *data << "->";
			
			cout << "\n";
		}*/

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
