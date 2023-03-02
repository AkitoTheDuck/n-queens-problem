#include <iostream>
#include <vector>

using namespace std;

int main()
{
	constexpr auto damen = 5; //anzahl der Damen, die platziert werden sollen
	constexpr int stellenAnzahl = damen * damen; //wie viele Felder es insgesamt gibt

	const unsigned long long maxWert = pow(2, stellenAnzahl); //anzahl an möglichen Lösungen
	const unsigned long long minWert = pow(2, stellenAnzahl - damen);

	vector<bool*>solutions;

	for (unsigned long long n = minWert; n < maxWert; n++)
	{
		bool schachbrett[stellenAnzahl] = {};
		int anzahlEinser = 0;
		unsigned long long Testzahl = n;

		for (int j = stellenAnzahl - 1; j > -1; j--) //Dezimalzahl wird in ein Binärwert umgewandelt
		{
			// raufzählen, wenn 1 berechnet wird
			if (Testzahl % 2 == 1)
			{
				anzahlEinser++;
				schachbrett[j] = 1;
				if (anzahlEinser > damen)
				{
					break;
				}
			}
			else
			{
				schachbrett[j] = 0;
			}
			Testzahl = Testzahl / 2;
		}
		if (anzahlEinser != damen)
		{
			continue;
		}
		short positionen[damen] = {};

		string buffer;
		short zeile = 0;
		bool isValid = true;
		for (short i = 0; i < stellenAnzahl; i++)
		{
			buffer += schachbrett[i];
			if ((i + 1) % (damen) != 0)
				continue;

			// translate to array
			unsigned short anzahlDamen = 0;
			for (short j = 0; j < damen; j++)
			{
				if (buffer[j] == 1)
				{
					positionen[zeile] = j;
					anzahlDamen++;
				}
			}
			zeile++;

			if (anzahlDamen != 1) {
				isValid = false;
				break;
			}
			buffer = "";
		}

		for (short i = 0; i < damen; i++)
		{
			if (!isValid)
				break;

			for (short j = 0; j < damen; j++)
			{
				if (
					i != j &&
					(
						abs(i - j) == abs(positionen[i] - positionen[j])
						||
						positionen[i] == positionen[j]
						)
					)
				{
					isValid = false;
					break;
				}
			}
		}
		if (isValid)
		{
			solutions.push_back(schachbrett);
			for (int i = 1; i < stellenAnzahl + 1; i++)
			{
				if (i % damen == 0)
				{
					cout << schachbrett[i - 1] << "\n";
				}
				else
				{
					cout << schachbrett[i - 1];
				}
			}
			cout << "Solution is valid!\n\n";
		}
		*positionen = {};
	}
	cout << "\n" << "Solutions found: " << solutions.size() << "\n";
	return 0;
}