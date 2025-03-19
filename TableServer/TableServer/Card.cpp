#include "Card.h"
#include<iostream>
#include <windows.h>

Card::Card(int rank, char suit)
{
	Rank = rank;
	Suit = suit;
}

int Card::getRank()
{
	return Rank;
}

char Card::getSuit()
{
	return Suit;
}


void Card::printCard(std::string side)
{


	std::string face[]
	{
		"\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
		"\xB3         \xB3",
		"\xB3         \xB3",
		"\xB3         \xB3",
		"\xB3         \xB3",
		"\xB3         \xB3",
		"\xB3         \xB3",
		"\xB3         \xB3",
		"\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"
	};
	if (Suit == 'h')
	{
		face[4][5] = 'H';
	}
	else if (Suit == 's')
	{
		face[4][5] = 'S';
	}
	else if (Suit == 'd')
	{
		face[4][5] = 'D';
	}
	else if (Suit == 'c')
	{
		face[4][5] = 'C';
	}

	if (Rank >= 2 && Rank <= 9)
	{
		char sign = Rank + 48;
		face[1][1] = sign;
		face[7][9] = sign;
	}
	else if (Rank == 10)
	{
		face[1][1] = '1';
		face[1][2] = '0';
		face[7][9] = '0';
		face[7][8] = '1';
	}
	else if (Rank == 11)
	{
		face[1][1] = 'J';
		face[7][9] = 'J';
	}
	else if (Rank == 12)
	{
		face[1][1] = 'Q';
		face[7][9] = 'Q';
	}
	else if (Rank == 13)
	{
		face[1][1] = 'K';
		face[7][9] = 'K';
	}
	else if (Rank == 14)
	{
		face[1][1] = 'A';
		face[7][9] = 'A';
	}

	std::string back[]
	{

		"\xDA\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xBF",
		"\xB3\xB0\xB0\xB1\xB1\xB0\xB0\xB1\xB1\xB0\xB3",
		"\xB3\xB1\xB0\xB0\xB1\xB1\xB0\xB0\xB1\xB1\xB3",
		"\xB3\xB1\xB1\xB0\xB0\xB1\xB1\xB0\xB0\xB1\xB3",
		"\xB3\xB0\xB1\xB1\xB0\xB0\xB1\xB1\xB0\xB0\xB3",
		"\xB3\xB0\xB0\xB1\xB1\xB0\xB0\xB1\xB1\xB0\xB3",
		"\xB3\xB1\xB0\xB0\xB1\xB1\xB0\xB0\xB1\xB1\xB3",
		"\xB3\xB1\xB1\xB0\xB0\xB1\xB1\xB0\xB0\xB1\xB3",
		"\xC0\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xD9"
	};
	if (side == "face")
	{
		for (int i = 0; i < 9; i++)
		{
			std::cout << face[i] << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			std::cout << back[i] << std::endl;
		}
	}



}

