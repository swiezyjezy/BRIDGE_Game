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

    void split(char* Ncards[], char* Ecards[], char* Scards[], char* Wcards[]);

    Card drawCard();

    void printDeck();
};

#endif

