#pragma once
#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand {
private:
    std::vector<Card> cards;

public:
    Hand();

    void addCard(const Card& card);

    int ShowPower();

    int ShowPower(char Suit);

    int findHighestCard();

    bool isSuitInHand(char suit);

    int findHighestCard(char suit); // znajduje najlepsza karte w kolorze

    int findWorstCard();

    int findWorstCard(char suit); // znajduje najgorszą karte w kolorze

    Card drawCard();

    std::vector<Card>& getCards();

    char findSuitWithMostCards();

    int findSuitCardNumber(char suit);



    void mergeHands(Hand& dest);

    void printHand();
};

#endif // HAND_H
