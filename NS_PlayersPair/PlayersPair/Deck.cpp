#include "Deck.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "Hand.h"


Deck::Deck()
{
    for (char suit : {'h', 's', 'd', 'c'}) {
        for (int rank = 2; rank <= 14; rank++) {
            cards.push_back(Card(rank, suit));
        }
    }
}

void Deck::shuffle()
{
    srand(time(NULL));
    for (int i = 0; i < 1000; i++)
    {
        int index1 = rand() % 52;
        int index2 = rand() % 52;
        std::swap(cards[index1], cards[index2]);
    }
}


void Deck::split(Hand& hand1, Hand& hand2, Hand& hand3, Hand& hand4)
{
    for (size_t i = 0; i < cards.size(); ++i) {
        if (i % 4 == 0) {
            hand1.addCard(cards[i]);
        }
        else if (i % 4 == 1)
        {
            hand2.addCard(cards[i]);
        }
        else if (i % 4 == 2)
        {
            hand3.addCard(cards[i]);
        }
        else if (i % 4 == 3)
        {
            hand4.addCard(cards[i]);
        }
    }
    cards.clear(); // Usuwamy karty z talii po rozdzieleniu
}



void Deck::printDeck() {
    for (auto& card : cards)
    {
        card.printCard("face"); // Wywo³ujemy metodê printCard z klasy Card dla ka¿dej karty w talii
    }
}


Card Deck::drawCard()
{
    // Sprawdzamy, czy talia nie jest pusta
    if (!cards.empty()) {

        Card topCard = cards.back();

        cards.pop_back();

        return topCard;
    }
    else
    {
        // Jeœli talia jest pusta, zwracamy kartê z wartoœci¹ 0 i pustym znakiem koloru
        return Card(0, ' ');
    }
}
