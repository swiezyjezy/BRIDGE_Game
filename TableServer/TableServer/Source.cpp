//#include<iostream>
//#include <windows.h>
//#include"Card.h"
//#include"Deck.h"
//#include"Hand.h"
//#include"Player.h"
//
//
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//
//void playCard(Player& P, char* Contract, int* PlayedCard)
//{
//	if (PlayedCard[0] == 0 && PlayedCard[1] == 0) // jezeli zagrywasz jako pierwszy daj najsilniejsza karte jaka posiadasz
//	{
//		int index = P.getHand().findHighestCard();
//		PlayedCard[0] = P.getHand().getCards()[index].getRank();
//		PlayedCard[1] = P.getHand().getCards()[index].getSuit();
//
//		P.getHand().getCards().erase(P.getHand().getCards().begin() + index);
//	}
//	else
//	{
//		int index = 0; // indeks granej karty w tablicy PlayedCart
//		while (PlayedCard[index] != 0)
//		{
//			index += 2;
//
//		}
//		char suit = PlayedCard[1]; // wymagany kolor
//		int highestRankPlayed = 0;
//		for (int i = 0; i < 3; i++)
//		{
//			if (PlayedCard[i * 2] > highestRankPlayed)
//			{
//				highestRankPlayed = PlayedCard[i * 2];
//			}
//		}
//		// czy mam kolor
//		if (P.getHand().isSuitInHand(suit)) // jezeli tak
//		{
//			// czy moge przebic
//			if (P.getHand().getCards()[P.getHand().findHighestCard(suit)].getRank() > highestRankPlayed) // jezeli tak przebij
//			{
//				//index to index granej karty w tablicy PlayedCard
//				PlayedCard[index] = P.getHand().getCards()[P.getHand().findHighestCard(suit)].getRank();
//				PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findHighestCard(suit)].getSuit();
//				P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findHighestCard(suit));
//			}
//			else // w przeciwnym razie
//			{
//				// najslabsza karta tego koloru
//				PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard(suit)].getRank();
//				PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard(suit)].getSuit();
//				P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard(suit));
//			}
//		}
//		else // jezeli nie mam koloru
//		{
//			//sprawdzam czy mam kolor atutowy
//			char atutSuit = Contract[2];
//			if (P.getHand().isSuitInHand(atutSuit)) // jezeli mam kolor atutowy na reku
//			{
//				bool atutPlayed = false;
//				for (int i = 0; i < 3; i++) // sprawdzam czy ktos zagral kolor atutowy
//				{
//					if (PlayedCard[1 + (i * 2)] == (int)atutSuit)
//					{
//						atutPlayed = true;
//						break;
//					}
//				}
//				if (atutPlayed) // jezeli ktos zagral juz karte atutowa
//				{
//					int maxAtutPlayed = 0;
//					for (int i = 0; i < 3; i++) // znajduje najwyzsza karte atutowa
//					{
//						if (PlayedCard[i * 2] > maxAtutPlayed && PlayedCard[1 + (i * 2)] == (int)atutSuit)
//						{
//							maxAtutPlayed = PlayedCard[i * 2];
//						}
//					}
//					// czy moge go przebic
//					if (P.getHand().getCards()[P.getHand().findHighestCard(atutSuit)].getRank() > maxAtutPlayed)
//					{
//						// jezeli tak przebij
//						PlayedCard[index] = P.getHand().getCards()[P.getHand().findHighestCard(atutSuit)].getRank();
//						PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findHighestCard(atutSuit)].getSuit();
//						P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findHighestCard(atutSuit));
//					}
//					else // jezeli nie zagraj najslabsza karte
//					{
//						PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard()].getRank();
//						PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard()].getSuit();
//						P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard());
//					}
//				}
//				else // jezeli karta atutowa nie zostala zagrana
//				{
//					//zagraj naslabszy atut
//					PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard(atutSuit)].getRank();
//					PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard(atutSuit)].getSuit();
//					P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard(atutSuit));
//				}
//			}
//			else // jezeli nie zagrywam najgorsza mozliwa karte
//			{
//				PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard()].getRank();
//				PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard()].getSuit();
//				P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard());
//			}
//		}
//	}
//}
//
////funkcja zagrywa 4 karty i sprawdza kto wygral
//char playTurn(Player& N, Player& E, Player& S, Player& W, char* StartingPlayer, char* Contract, int* PlayedCard)
//{
//	if (*StartingPlayer == 'N')
//	{
//		playCard(N, Contract, PlayedCard);
//
//		COORD position = { 53,7 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[0] <= 10)
//		{
//			std::cout << PlayedCard[0] << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[1];
//		}
//		Sleep(2000);
//
//		playCard(E, Contract, PlayedCard);
//
//		position = { 70,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[2] <= 10)
//		{
//			std::cout << PlayedCard[2] << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[3];
//		}
//		Sleep(2000);
//
//		playCard(S, Contract, PlayedCard);
//
//		position = { 53,19 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[4] <= 10)
//		{
//			std::cout << PlayedCard[4] << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[5];
//		}
//		Sleep(2000);
//
//		playCard(W, Contract, PlayedCard);
//
//		position = { 38,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[6] <= 10)
//		{
//			std::cout << PlayedCard[6] << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[7];
//		}
//		Sleep(2000);
//
//
//		// sprawdzamy kto wygral
//		bool isAtutPlayed = false;
//		char atutSuit = Contract[2];
//		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
//		{
//			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
//			{
//				isAtutPlayed = true;
//				break;
//			}
//		}
//		int WinerIndex = 100;
//		if (isAtutPlayed)
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		else
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed)
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		if (WinerIndex == 0)
//		{
//			return 'N';
//		}
//		else if (WinerIndex == 1)
//		{
//			return 'E';
//		}
//		else if (WinerIndex == 2)
//		{
//			return 'S';
//		}
//		else if (WinerIndex == 3)
//		{
//			return 'W';
//		}
//		return 0;
//	}
//	else if (*StartingPlayer == 'E')
//	{
//
//		playCard(E, Contract, PlayedCard);
//
//		COORD position = { 70,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[0] <= 10)
//		{
//			std::cout << PlayedCard[0] << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[1];
//		}
//		Sleep(2000);
//
//		playCard(S, Contract, PlayedCard);
//
//		position = { 53,19 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[2] <= 10)
//		{
//			std::cout << PlayedCard[2] << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[3];
//		}
//		Sleep(2000);
//
//		playCard(W, Contract, PlayedCard);
//
//		position = { 38,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[4] <= 10)
//		{
//			std::cout << PlayedCard[4] << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[5];
//		}
//		Sleep(2000);
//
//		playCard(N, Contract, PlayedCard);
//
//		position = { 53,7 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[6] <= 10)
//		{
//			std::cout << PlayedCard[6] << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[7];
//		}
//		Sleep(2000);
//		// sprawdzamy kto wygral
//		bool isAtutPlayed = false;
//		char atutSuit = Contract[2];
//		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
//		{
//			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
//			{
//				isAtutPlayed = true;
//				break;
//			}
//		}
//		int WinerIndex = 100;
//		if (isAtutPlayed)
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		else
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed)
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		if (WinerIndex == 0)
//		{
//			return 'E';
//		}
//		else if (WinerIndex == 1)
//		{
//			return 'S';
//		}
//		else if (WinerIndex == 2)
//		{
//			return 'W';
//		}
//		else if (WinerIndex == 3)
//		{
//			return 'N';
//		}
//		return 0;
//	}
//	else if (*StartingPlayer == 'S')
//	{
//		playCard(S, Contract, PlayedCard);
//		COORD position = { 53,19 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[0] <= 10)
//		{
//			std::cout << PlayedCard[0] << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[1];
//		}
//		Sleep(2000);
//
//
//		playCard(W, Contract, PlayedCard);
//		position = { 38,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[2] <= 10)
//		{
//			std::cout << PlayedCard[2] << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[3];
//		}
//		Sleep(2000);
//
//
//		playCard(N, Contract, PlayedCard);
//		position = { 53,7 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[4] <= 10)
//		{
//			std::cout << PlayedCard[4] << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[5];
//		}
//		Sleep(2000);
//
//		playCard(E, Contract, PlayedCard);
//		position = { 70,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[6] <= 10)
//		{
//			std::cout << PlayedCard[6] << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[7];
//		}
//		Sleep(2000);
//
//
//		// sprawdzamy kto wygral
//		bool isAtutPlayed = false;
//		char atutSuit = Contract[2];
//		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
//		{
//			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
//			{
//				isAtutPlayed = true;
//				break;
//			}
//		}
//		int WinerIndex = 100;
//		if (isAtutPlayed)
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		else
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed)
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		if (WinerIndex == 0)
//		{
//			return 'S';
//		}
//		else if (WinerIndex == 1)
//		{
//			return 'W';
//		}
//		else if (WinerIndex == 2)
//		{
//			return 'N';
//		}
//		else if (WinerIndex == 3)
//		{
//			return 'E';
//		}
//		return 0;
//	}
//	else if (*StartingPlayer == 'W')
//	{
//		playCard(W, Contract, PlayedCard);
//		COORD position = { 38,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[0] <= 10)
//		{
//			std::cout << PlayedCard[0] << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[1];
//		}
//		else if (PlayedCard[0] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[1];
//		}
//		Sleep(2000);
//
//
//		playCard(N, Contract, PlayedCard);
//		position = { 53,7 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[2] <= 10)
//		{
//			std::cout << PlayedCard[2] << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[3];
//		}
//		else if (PlayedCard[2] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[3];
//		}
//		Sleep(2000);
//
//		playCard(E, Contract, PlayedCard);
//		position = { 70,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[4] <= 10)
//		{
//			std::cout << PlayedCard[4] << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[5];
//		}
//		else if (PlayedCard[4] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[5];
//		}
//		Sleep(2000);
//
//		playCard(S, Contract, PlayedCard);
//		position = { 53,19 };
//		SetConsoleCursorPosition(hConsole, position);
//		if (PlayedCard[6] <= 10)
//		{
//			std::cout << PlayedCard[6] << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 11)
//		{
//			std::cout << "J" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 12)
//		{
//			std::cout << "Q" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 13)
//		{
//			std::cout << "K" << (char)PlayedCard[7];
//		}
//		else if (PlayedCard[6] == 14)
//		{
//			std::cout << "A" << (char)PlayedCard[7];
//		}
//		Sleep(2000);
//
//		// sprawdzamy kto wygral
//		bool isAtutPlayed = false;
//		char atutSuit = Contract[2];
//		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
//		{
//			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
//			{
//				isAtutPlayed = true;
//				break;
//			}
//		}
//		int WinerIndex = 100;
//		if (isAtutPlayed)
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		else
//		{
//			int maxPlayed = 0;
//			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
//			{
//				if (PlayedCard[i * 2] > maxPlayed)
//				{
//					maxPlayed = PlayedCard[i * 2];
//					WinerIndex = i;
//				}
//			}
//		}
//		if (WinerIndex == 0)
//		{
//			return 'W';
//		}
//		else if (WinerIndex == 1)
//		{
//			return 'N';
//		}
//		else if (WinerIndex == 2)
//		{
//			return 'E';
//		}
//		else if (WinerIndex == 3)
//		{
//			return 'S';
//		}
//		return 0;
//	}
//	return 0;
//}
//
//void actionPhase(Player& N, Player& E, Player& S, Player& W, char* Contract)
//{
//	int PlayedCards[8] = { 0,0,0,0,0,0,0,0 }; // karty zagrane pierwszy index to wartosc, drugi index to kolor
//	char AttackingPlayer = Contract[0];
//	char Suit;
//	char StartingPlayer = 'N';
//	if (Contract[0] == 'N')
//	{
//		StartingPlayer = 'E';
//	}
//	else if (Contract[0] == 'E')
//	{
//		StartingPlayer = 'S';
//	}
//	else if (Contract[0] == 'S')
//	{
//		StartingPlayer = 'W';
//	}
//	else if (Contract[0] == 'W')
//	{
//		StartingPlayer = 'N';
//	}
//
//	int WinnedTurns[] = { 0,0,0,0 };
//	Player Players[] = { N,E,S,W };
//
//	//std::cout << "\nKontrakt gracza " << Contract[0] << " na " << Contract[1] << " " << Contract[2];
//
//	for (int i = 0; i < 13; i++)
//	{
//		for (int j = 0; j < 8; j++)
//		{
//			PlayedCards[j] = 0;
//		}
//		COORD position = { 53,7 };
//		SetConsoleCursorPosition(hConsole, position);
//		std::cout << "   ";
//		position = { 70,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		std::cout << "   ";
//		position = { 53,19 };
//		SetConsoleCursorPosition(hConsole, position);
//		std::cout << "   ";
//		position = { 38,13 };
//		SetConsoleCursorPosition(hConsole, position);
//		std::cout << "   ";
//
//		Sleep(1500);
//		char winner = playTurn(N, E, S, W, &StartingPlayer, Contract, PlayedCards);
//		if (winner == 'N')
//		{
//			WinnedTurns[0]++;
//			StartingPlayer = 'N';
//
//			position = { 63,1 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << WinnedTurns[0];
//		}
//		else if (winner == 'E')
//		{
//			WinnedTurns[1]++;
//			StartingPlayer = 'E';
//
//			position = { 73,1 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << WinnedTurns[1];
//		}
//		else if (winner == 'S')
//		{
//			WinnedTurns[2]++;
//			StartingPlayer = 'S';
//
//			position = { 83,1 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << WinnedTurns[2];
//		}
//		else if (winner == 'W')
//		{
//			WinnedTurns[3]++;
//			StartingPlayer = 'W';
//
//			position = { 93,1 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << WinnedTurns[3];
//		}
//		//std::cout << "\nwygral gracz: " << winner;
//	}
//	int NS_Points = WinnedTurns[0] + WinnedTurns[2];
//	int EW_Points = WinnedTurns[1] + WinnedTurns[3];
//	if (AttackingPlayer == 'N' || AttackingPlayer == 'S')
//	{
//		int requiredPoints = (int)Contract[1] - 48 + 6;
//		if (NS_Points >= requiredPoints)
//		{
//			system("cls");
//			COORD position = { 40,10 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << "Kontrakt druzyny NS wypelniony";
//			Sleep(2000);
//		}
//		else
//		{
//			system("cls");
//			COORD position = { 40,10 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << "Kontrakt druzyny NS nie wypelniony";
//			Sleep(2000);
//		}
//	}
//	else if (AttackingPlayer == 'E' || AttackingPlayer == 'W')
//	{
//		int requiredPoints = (int)Contract[1] - 48 + 6;
//		if (EW_Points >= requiredPoints)
//		{
//			system("cls");
//			COORD position = { 40,10 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << "Kontrakt druzyny EW wypelniony";
//			Sleep(2000);
//		}
//		else
//		{
//			system("cls");
//			COORD position = { 40,10 };
//			SetConsoleCursorPosition(hConsole, position);
//			std::cout << "Kontrakt druzyny EW nie wypelniony";
//			Sleep(2000);
//		}
//	}
//
//}
//
//
//
//int main2()
//{
//
//
//	Deck deck;
//
//	Hand N_Hand;
//	Hand E_Hand;
//	Hand S_Hand;
//	Hand W_Hand;
//
//	Player N_Player('N', N_Hand);
//	Player E_Player('E', E_Hand);
//	Player S_Player('S', S_Hand);
//	Player W_Player('W', W_Hand);
//
//	N_Player.SetPartner(&S_Player);
//	E_Player.SetPartner(&W_Player);
//	S_Player.SetPartner(&N_Player);
//	W_Player.SetPartner(&E_Player);
//
//
//	COORD position = { 50,10 };
//	SetConsoleCursorPosition(hConsole, position);
//
//	deck.shuffle();
//
//	//deck.split();
//
//	std::cout << "Faza licytacji !";
//	Sleep(2000);
//	system("cls");
//
//
//	char contract[3];
//
//
//	position = { 55,9 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'N';
//
//	position = { 45,13 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'W';
//
//	position = { 65,13 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'E';
//
//	position = { 55,17 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'S';
//
//
//
//	bidingPhase(N_Player, E_Player, S_Player, W_Player, 'N', contract);
//
//
//	system("cls");
//
//
//	position = { 5,1 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << "kontrakt gracza: " << contract[0] << " na " << contract[1] << "-" << contract[2];
//
//
//
//	position = { 60,1 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << "N: 0";
//
//	position = { 70,1 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << "E: 0";
//
//	position = { 80,1 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << "S: 0";
//
//	position = { 90,1 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << "W: 0";
//
//
//
//
//	position = { 55,9 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'N';
//
//	position = { 45,13 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'W';
//
//	position = { 65,13 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'E';
//
//	position = { 55,17 };
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << 'S';
//
//
//
//	actionPhase(N_Player, E_Player, S_Player, W_Player, contract);
//
//
//
//
//	position = { 35,28 };
//
//	SetConsoleCursorPosition(hConsole, position);
//	std::cout << "koniec";
//
//
//
//	return 0;
//}