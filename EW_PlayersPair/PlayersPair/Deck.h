#ifndef DECK_H
#define DECK_H

#include "Card.h" 
#include "Hand.h"
#include <vector>

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck();

    void shuffle();

    void split(Hand& hand1, Hand& hand2, Hand& hand3, Hand& hand4);

    Card drawCard();

    void printDeck();
};

#endif

