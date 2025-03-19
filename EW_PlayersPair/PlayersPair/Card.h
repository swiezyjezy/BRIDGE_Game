#pragma once
#include<iostream>

class Card
{
private:
	int Rank;
	char Suit;

public:
	Card(int Rank, char Suit);

	int getRank();

	char getSuit();

	void printCard(std::string side);

};

