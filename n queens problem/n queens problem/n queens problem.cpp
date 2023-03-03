#include <iostream>
#include <vector>

using namespace std;

int main()
{
	constexpr auto queens = 5; //change number for more/less solutions
	constexpr int numberCount = queens * queens;

	const unsigned long long maxValue = pow(2, numberCount); //anzahl an möglichen Lösungen
	const unsigned long long minValue = pow(2, numberCount - queens);

	vector<bool*>solutions;

	for (unsigned long long n = minValue; n < maxValue; n++)
	{
		bool chessboard[numberCount] = {};
		int numberOnes = 0;
		unsigned long long testNumber = n;

		for (int j = numberCount - 1; j > -1; j--) //converting into binary
		{
			if (testNumber % 2 == 1)
			{
				numberOnes++;
				chessboard[j] = 1;
				if (numberOnes > queens)
				{
					break;
				}
			}
			else
			{
				chessboard[j] = 0;
			}
			testNumber = testNumber / 2;
		}

		if (numberOnes != queens)
		{
			continue;
		}
		short positions[queens] = {};

		string buffer;
		short row = 0;
		bool isValid = true;

		for (short i = 0; i < numberCount; i++)
		{
			buffer += chessboard[i];
			if ((i + 1) % (queens) != 0)
				continue;

			// translate to array
			unsigned short numberQueens = 0;
			for (short j = 0; j < queens; j++)
			{
				if (buffer[j] == 1)
				{
					positions[row] = j;
					numberQueens++;
				}
			}
			row++;

			if (numberQueens != 1) {
				isValid = false;
				break;
			}
			buffer = "";
		}

		for (short i = 0; i < queens; i++)
		{
			if (!isValid)
				break;

			for (short j = 0; j < queens; j++)
			{
				if (
					i != j &&
					(
						abs(i - j) == abs(positions[i] - positions[j])
						||
						positions[i] == positions[j]
						)
					)
				{
					isValid = false;
					break;
				}
			}
		}
		if (isValid) //valid solutions pushed into vector of valid solutions
		{
			solutions.push_back(chessboard);
			for (int i = 1; i < numberCount + 1; i++)
			{
				if (i % queens == 0)
				{
					cout << chessboard[i - 1] << "\n";
				}
				else
				{
					cout << chessboard[i - 1];
				}
			}
			cout << "Solution is valid!\n\n";
		}
		*positions = {};
	}
	cout << "\n" << "Solutions found: " << solutions.size() << "\n";
	return 0;
}