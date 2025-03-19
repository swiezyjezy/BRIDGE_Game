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


void Deck::split(char* Ncards[], char* Ecards[], char* Scards[], char* Wcards[])
{
    


    for (size_t i = 0; i < cards.size(); ++i) 
    {    
        std::string cardStr;
        if (cards[i].getRank() < 10)
        {
            cardStr += (char)(cards[i].getRank()+48);

        }
        else if (cards[i].getRank() == 10)
        {
            cardStr += "10";
        }
        else if (cards[i].getRank() == 11)
        {
            cardStr += "11";
        }
        else if (cards[i].getRank() == 12)
        {
            cardStr += "12";
        }
        else if (cards[i].getRank() == 13)
        {
            cardStr += "13";
        }
        else if (cards[i].getRank() == 14)
        {
            cardStr += "14";
        }
        cardStr += cards[i].getSuit();
        
        
        if (i % 4 == 0) 
        {
            Ncards[i / 4] = _strdup(cardStr.c_str());
        }
        else if (i % 4 == 1)
        {
            Ecards[i / 4] = _strdup(cardStr.c_str());
        }
        else if (i % 4 == 2)
        {
            Scards[i / 4] = _strdup(cardStr.c_str());
        }
        else if (i % 4 == 3)
        {
            Wcards[i / 4] = _strdup(cardStr.c_str());
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
