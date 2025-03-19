#include "Player.h"

Player::Player(char name, Hand& hand)
{
	this->Name = name;
	this->hand = hand;
}

void Player::SetPartner(Player* partner)
{
	this->Partner = partner;
}

Player* Player::getPartner()
{
	return Partner;
}

char Player::getName()
{
	return Name;
}

Hand& Player::getHand()
{
	return hand;
}