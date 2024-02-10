// Kaprekar_routine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	/*int nDigits = 0;
	cout << "Enter the number of digits for determining kaprekar constants and kaprekar routine" << "\t";

	cin >> nDigits;
	if (nDigits <= 0 || nDigits > 13)
	{
		std::cout << "Limit exceeded, Maximum number of digits allowed is 12" << std::endl;
		return -1;
	}*/

	char* error = NULL;
	long long number = 0ll;
	std::unordered_set<long long> kaprekarSequence;
	char sRandomNumber[13] = "124581157762";
	number = strtoll(sRandomNumber, &error, 10);
	kaprekarSequence.insert(number);

	while (1)
	{
		long long ascendingNumber = 0ll, descendingNumber = 0ll;
		std::vector<int> randomNumber, ascendingArrangement, descendingArrangement;
		for (int i = 0; i < strlen(sRandomNumber); i++)
			randomNumber.push_back(sRandomNumber[i] - '0');

		ascendingArrangement = randomNumber;
		descendingArrangement = randomNumber;

		std::sort(ascendingArrangement.begin(), ascendingArrangement.end(), std::greater<int>());
		std::sort(descendingArrangement.begin(), descendingArrangement.end(), std::less<int>());

		char strAscendingNumber[13] = "", strdescendingNumber[13] = " ";
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

		number = ascendingNumber - descendingNumber;

		if (kaprekarSequence.find(number) != kaprekarSequence.end())
			break;

		std::string newNumber(to_string(number));
		for (int i = 0; i < newNumber.size(); i++)
			sRandomNumber[i] = newNumber[i];

		kaprekarSequence.insert(number);
	}

	std::cout << "Kaprekar constant is " << number <<endl;
	std::cout << "Kaprekar sequence is" << endl;

	for (const auto& num : kaprekarSequence)
		std::cout << num << "->";

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
