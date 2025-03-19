#pragma once
#include"Hand.h"
class Player
{
private:
	char Name;
	Hand hand;
	Player* Partner;
public:
	Player(char Name, Hand& hand);

	void SetPartner(Player* partner);

	Player* getPartner();

	char getName();

	Hand& getHand();
};

