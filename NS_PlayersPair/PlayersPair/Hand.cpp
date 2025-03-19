#include "Hand.h"
#include <iostream>

Hand::Hand()
{
}

// Implementacja metody dodaj¹cej kartê do rêki
void Hand::addCard(const Card& card)
{
    cards.push_back(card);
}




int Hand::ShowPower()
{
    int Power = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].getRank() > 10)
            Power += cards[i].getRank() - 10;
    }
    return Power;
}

int Hand::ShowPower(char Suit)
{
    int Power = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].getSuit() == Suit)
        {
            if (cards[i].getRank() > 10)
                Power += cards[i].getRank() - 10;
        }
    }
    return Power;
}


int Hand::findHighestCard() // zwraca indeks najwyzszej karty
{
    int max = 0;
    int index = 0;

    for (int i = 0; i < cards.size(); i++)
    {
        if (max < cards[i].getRank())
        {
            max = cards[i].getRank();
            index = i;
        }
    }

    return index;
}

bool Hand::isSuitInHand(char suit)
{
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].getSuit() == suit)
        {
            return true;
        }
    }
    return false;
}

int Hand::findHighestCard(char suit)
{
    int max = 0;
    int index = 0;

    for (int i = 0; i < cards.size(); i++)
    {
        if (max < cards[i].getRank() && cards[i].getSuit() == suit)
        {
            max = cards[i].getRank();
            index = i;
        }
    }
    return index;
}

int Hand::findWorstCard()
{
    int min = 14;
    int index = 0;

    for (int i = 0; i < cards.size(); i++)
    {
        if (min > cards[i].getRank())
        {
            min = cards[i].getRank();
            index = i;
        }
    }

    return index;
}

int Hand::findWorstCard(char suit)
{
    int min = 14;
    int index = 0;

    for (int i = 0; i < cards.size(); i++)
    {
        if (min > cards[i].getRank() && cards[i].getSuit() == suit)
        {
            min = cards[i].getRank();
            index = i;
        }
    }

    return index;
}

Card Hand::drawCard()
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

std::vector<Card>& Hand::getCards()
{
    return cards;
}


char Hand::findSuitWithMostCards()
{
    int s = 0, h = 0, c = 0, d = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].getSuit() == 's')
            s++;
        else if (cards[i].getSuit() == 'h')
            h++;
        else if (cards[i].getSuit() == 'c')
            c++;
        else if (cards[i].getSuit() == 'd')
            d++;
    }
    if (s >= h && s >= c && s >= d)
    {
        return 's';
    }
    else if (h >= s && h >= c && h >= d)
    {
        return 'h';
    }
    else if (d >= s && d >= c && d >= h)
    {
        return 'd';
    }
    else if (c >= s && c >= h && c >= d)
    {
        return 'c';
    }
}

int Hand::findSuitCardNumber(char suit)
{
    int number = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i].getSuit() == suit)
            number++;
    }
    return number;
}

// Implementacja metody do wydrukowania kart w rêce
void Hand::printHand()
{
    for (auto& card : cards)
    {
        card.printCard("face");
    }
}

// Funkcja do dodawania jednej rêki do drugiej i usuwania kart z pierwszej rêki
void Hand::mergeHands(Hand& dest)
{
    for (auto& card : cards)
    {
        dest.addCard(card);
    }
    cards.clear(); // Usuniêcie kart z pierwszej rêki
}
