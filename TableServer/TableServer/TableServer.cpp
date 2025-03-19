#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include"Card.h"
#include"Deck.h"
#include"Hand.h"
#include"Player.h"

#pragma comment(lib, "ws2_32.lib")
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void clearBuffer(char* buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] = 0;
    }
}

void cardsToString(char* cards[], char* cardstr, int size)
{
    
    int charindex = 0;
    for (int i = 0; i < size; i++)
    {
        int cardSize = strlen(cards[i]);
        for (int j = 0; j < cardSize; j++)
        {
            cardstr[charindex] = cards[i][j];
            charindex++;
        }
    }
    cardstr[charindex] = '\0';
}

void bidingPhase(char StartingPlayer, char* Contract, SOCKET& NS_Socket, SOCKET& EW_Socket)
{
    // kolejnosc kolorow
    // trefl, karo, kier, pik, bez atu
    //  C      D     H     S      B

    Contract[0] = '\0'; // pierwszy znak to nazwa gracza; drugi wartosc; trzeci kolor
    Contract[1] = '\0';
    Contract[2] = '\0';

    char Round[4] = { 'N','E','S','W'};

    int i = 0;

    if (StartingPlayer == 'N') i = 0;
    else if (StartingPlayer == 'E') i = 1;
    else if (StartingPlayer == 'S') i = 2;
    else if (StartingPlayer == 'W') i = 3;

    int PassCounter = 0;
    char buffer[1024];
    int val = 0;
    COORD position;

    while (true)
    {
        //wysyla procesowi sygnal do bidowania wraz z aktualnym kontraktem
        if (Round[i] == 'N' || Round[i] == 'S')
        {
            if (Round[i] == 'N')
            {
                buffer[0] = 'N';
                buffer[1] = Contract[0];
                buffer[2] = Contract[1];
                buffer[3] = Contract[2];
            }
            else if (Round[i] == 'S')
            {
                buffer[0] = 'S';
                buffer[1] = Contract[0];
                buffer[2] = Contract[1];
                buffer[3] = Contract[2];
            }
            send(NS_Socket, buffer, strlen(buffer),0);

            clearBuffer(buffer, 1024);
            val = recv(NS_Socket, buffer, sizeof(buffer), 0);
            if (!strcmp(buffer, "pass"))
            {
                // std::cout << "gracz pasowal\n";
                if (Round[i] == 'N')
                {
                    position = { 54,7 };
                }
                else if (Round[i] == 'S')
                {
                    position = { 54,19 };
                }
                SetConsoleCursorPosition(hConsole, position);
                std::cout << "pass";
                PassCounter++;
            }
            else
            {

                //std::cout << buffer[1] << buffer[2] << buffer[3] << "\n";
                if (Round[i] == 'N')
                {
                    position = { 54,7 };
                }
                else if (Round[i] == 'S')
                {
                    position = { 54,19 };
                }
                SetConsoleCursorPosition(hConsole, position);
              
                PassCounter = 0;
                Contract[0] = buffer[1];
                Contract[1] = buffer[2];
                Contract[2] = buffer[3];
                std::cout << Contract[1] << Contract[2];
            }
        }
        else if(Round[i] == 'E' || Round[i] == 'W')
        {
            if (Round[i] == 'E')
            {
                buffer[0] = 'E';
                buffer[1] = Contract[0];
                buffer[2] = Contract[1];
                buffer[3] = Contract[2];
            }
            else if (Round[i] == 'W')
            {
                buffer[0] = 'W';
                buffer[1] = Contract[0];
                buffer[2] = Contract[1];
                buffer[3] = Contract[2];
            }
            send(EW_Socket, buffer, strlen(buffer), 0);


            clearBuffer(buffer, 1024);
            val = recv(EW_Socket, buffer, sizeof(buffer), 0);
            if (!strcmp(buffer, "pass"))
            {
                if (Round[i] == 'E')
                {
                    position = { 70,13 };
                }
                else if (Round[i] == 'W')
                {
                    position = { 34,13 };
                }
                SetConsoleCursorPosition(hConsole, position);
                std::cout << "pass";
                //std::cout << "gracz pasowal\n";
                PassCounter++;
            }
            else
            {
                if (Round[i] == 'E')
                {
                    position = { 70,13 };
                }
                else if (Round[i] == 'W')
                {
                    position = { 35,13 };
                }
                SetConsoleCursorPosition(hConsole, position);

                PassCounter = 0;
                Contract[0] = buffer[1];
                Contract[1] = buffer[2];
                Contract[2] = buffer[3];
                std::cout << Contract[1] << Contract[2];
            }
        }

        
        Sleep(1500);

        if (PassCounter == 3)
        {
            send(EW_Socket, "done", strlen("done"), 0);
            send(NS_Socket, "done", strlen("done"), 0);
            break;
        }

        i++;
        if (i == 4) i = 0;
    }
   // Sleep(1000);

    

    position = { 40,22 };
    SetConsoleCursorPosition(hConsole, position);
    std::cout << "Wygrywa kontrakt gracza: " << Contract[0] << " " << Contract[1] << "-" << Contract[2];
    Sleep(3000);

    system("cls");
}

void cardsInformations(char* arr, char* Contract, int* PlayedCards, char Player)
{
	clearBuffer(arr, 1024);
	arr[0] = Player;
	int index;
	for (int i = 1; i < 4; i++)
	{
		arr[i] = Contract[i - 1];
		index = i;
	}
	index++;
	for (int j = 0; j < 8; j++)
	{
		if (PlayedCards[j] >= 10 && PlayedCards[j] <= 14) // liczba dwu cyfrowa
		{
			arr[index] = (PlayedCards[j] / 10) + 48;
			index++;
			arr[index] = (PlayedCards[j] % 10) + 48;
			index++;
		}
		else if(PlayedCards[j] >= 2 && PlayedCards[j] <= 9) // liczba 1 cyfrowa
		{
			arr[index] = PlayedCards[j] + 48;
			index++;
		}
		else if(PlayedCards[j] >= 97 && PlayedCards[j] <= 122) // litera
		{
			arr[index] = (char)PlayedCards[j];
			index++;
		}
		else
		{
			arr[index] = 0;
			index++;
		}
	}
}

void strToPlayedCards(int* PlayedCard, char* buffer)
{
	int end = 0;
	int index = 0;
	int rank = 0;
	while (end < 8)
	{
		if (buffer[index] <= 57) // jezeli to cyfra
		{
			rank = rank * 10 + buffer[index] - 48;
			index++;
		}
		else if (buffer[index] >= 97)// jezeli litera
		{
			PlayedCard[end] = rank;
			end++;
			PlayedCard[end] = buffer[index];
			end++;
			index++;
			rank = 0;
		}
		else
		{
			PlayedCard[end] = 0;
			end++;
			index++;
			rank = 0;
		}
	}
}

char playTurn(char* StartingPlayer, char* Contract, int* PlayedCard, SOCKET& NS_Socket, SOCKET& EW_Socket)
{
	char buffer[1024];
	int val = 0;

	if (*StartingPlayer == 'N')
	{
		clearBuffer(buffer, 1024);


		//playCard(N, Contract, PlayedCard); 

		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'N');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, strlen(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);


		COORD position = { 53,7 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[0] <= 10)
		{
			std::cout << PlayedCard[0] << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 11)
		{
			std::cout << "J" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 13)
		{
			std::cout << "K" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 14)
		{
			std::cout << "A" << (char)PlayedCard[1];
		}
		Sleep(2000);

		//playCard(E, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'E');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, strlen(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		position = { 70,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[2] <= 10)
		{
			std::cout << PlayedCard[2] << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 11)
		{
			std::cout << "J" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 13)
		{
			std::cout << "K" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 14)
		{
			std::cout << "A" << (char)PlayedCard[3];
		}
		Sleep(2000);

		//playCard(S, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'S');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, strlen(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		position = { 53,19 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[4] <= 10)
		{
			std::cout << PlayedCard[4] << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 11)
		{
			std::cout << "J" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 13)
		{
			std::cout << "K" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 14)
		{
			std::cout << "A" << (char)PlayedCard[5];
		}
		Sleep(2000);

		//playCard(W, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'W');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, strlen(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		position = { 38,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[6] <= 10)
		{
			std::cout << PlayedCard[6] << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 11)
		{
			std::cout << "J" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 13)
		{
			std::cout << "K" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 14)
		{
			std::cout << "A" << (char)PlayedCard[7];
		}
		Sleep(2000);


		// sprawdzamy kto wygral
		bool isAtutPlayed = false;
		char atutSuit = Contract[2];
		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
		{
			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
			{
				isAtutPlayed = true;
				break;
			}
		}
		int WinerIndex = 100;
		if (isAtutPlayed)
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		else
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed)
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		if (WinerIndex == 0)
		{
			return 'N';
		}
		else if (WinerIndex == 1)
		{
			return 'E';
		}
		else if (WinerIndex == 2)
		{
			return 'S';
		}
		else if (WinerIndex == 3)
		{
			return 'W';
		}
		return 0;
	}
	else if (*StartingPlayer == 'E')
	{

		//playCard(E, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'E');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		COORD position = { 70,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[0] <= 10)
		{
			std::cout << PlayedCard[0] << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 11)
		{
			std::cout << "J" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 13)
		{
			std::cout << "K" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 14)
		{
			std::cout << "A" << (char)PlayedCard[1];
		}
		Sleep(2000);

		//playCard(S, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'S');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		position = { 53,19 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[2] <= 10)
		{
			std::cout << PlayedCard[2] << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 11)
		{
			std::cout << "J" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 13)
		{
			std::cout << "K" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 14)
		{
			std::cout << "A" << (char)PlayedCard[3];
		}
		Sleep(2000);

		//playCard(W, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'W');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		position = { 38,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[4] <= 10)
		{
			std::cout << PlayedCard[4] << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 11)
		{
			std::cout << "J" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 13)
		{
			std::cout << "K" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 14)
		{
			std::cout << "A" << (char)PlayedCard[5];
		}
		Sleep(2000);

		//playCard(N, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'N');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, strlen(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);

		position = { 53,7 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[6] <= 10)
		{
			std::cout << PlayedCard[6] << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 11)
		{
			std::cout << "J" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 13)
		{
			std::cout << "K" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 14)
		{
			std::cout << "A" << (char)PlayedCard[7];
		}
		Sleep(2000);
		// sprawdzamy kto wygral
		bool isAtutPlayed = false;
		char atutSuit = Contract[2];
		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
		{
			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
			{
				isAtutPlayed = true;
				break;
			}
		}
		int WinerIndex = 100;
		if (isAtutPlayed)
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		else
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed)
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		if (WinerIndex == 0)
		{
			return 'E';
		}
		else if (WinerIndex == 1)
		{
			return 'S';
		}
		else if (WinerIndex == 2)
		{
			return 'W';
		}
		else if (WinerIndex == 3)
		{
			return 'N';
		}
		return 0;
	}
	else if (*StartingPlayer == 'S')
	{
		//playCard(S, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'S');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		COORD position = { 53,19 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[0] <= 10)
		{
			std::cout << PlayedCard[0] << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 11)
		{
			std::cout << "J" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 13)
		{
			std::cout << "K" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 14)
		{
			std::cout << "A" << (char)PlayedCard[1];
		}
		Sleep(2000);


		//playCard(W, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'W');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		position = { 38,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[2] <= 10)
		{
			std::cout << PlayedCard[2] << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 11)
		{
			std::cout << "J" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 13)
		{
			std::cout << "K" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 14)
		{
			std::cout << "A" << (char)PlayedCard[3];
		}
		Sleep(2000);


		//playCard(N, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'N');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		position = { 53,7 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[4] <= 10)
		{
			std::cout << PlayedCard[4] << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 11)
		{
			std::cout << "J" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 13)
		{
			std::cout << "K" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 14)
		{
			std::cout << "A" << (char)PlayedCard[5];
		}
		Sleep(2000);

		//playCard(E, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'E');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		position = { 70,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[6] <= 10)
		{
			std::cout << PlayedCard[6] << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 11)
		{
			std::cout << "J" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 13)
		{
			std::cout << "K" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 14)
		{
			std::cout << "A" << (char)PlayedCard[7];
		}
		Sleep(2000);


		// sprawdzamy kto wygral
		bool isAtutPlayed = false;
		char atutSuit = Contract[2];
		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
		{
			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
			{
				isAtutPlayed = true;
				break;
			}
		}
		int WinerIndex = 100;
		if (isAtutPlayed)
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		else
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed)
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		if (WinerIndex == 0)
		{
			return 'S';
		}
		else if (WinerIndex == 1)
		{
			return 'W';
		}
		else if (WinerIndex == 2)
		{
			return 'N';
		}
		else if (WinerIndex == 3)
		{
			return 'E';
		}
		return 0;
	}
	else if (*StartingPlayer == 'W')
	{
		//playCard(W, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'W');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		COORD position = { 38,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[0] <= 10)
		{
			std::cout << PlayedCard[0] << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 11)
		{
			std::cout << "J" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 13)
		{
			std::cout << "K" << (char)PlayedCard[1];
		}
		else if (PlayedCard[0] == 14)
		{
			std::cout << "A" << (char)PlayedCard[1];
		}
		Sleep(2000);


		//playCard(N, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'N');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		position = { 53,7 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[2] <= 10)
		{
			std::cout << PlayedCard[2] << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 11)
		{
			std::cout << "J" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 13)
		{
			std::cout << "K" << (char)PlayedCard[3];
		}
		else if (PlayedCard[2] == 14)
		{
			std::cout << "A" << (char)PlayedCard[3];
		}
		Sleep(2000);

		//playCard(E, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'E');
		send(EW_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(EW_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		position = { 70,13 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[4] <= 10)
		{
			std::cout << PlayedCard[4] << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 11)
		{
			std::cout << "J" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 13)
		{
			std::cout << "K" << (char)PlayedCard[5];
		}
		else if (PlayedCard[4] == 14)
		{
			std::cout << "A" << (char)PlayedCard[5];
		}
		Sleep(2000);

		//playCard(S, Contract, PlayedCard);
		//  wysyla sygnal do gracza 
		cardsInformations(buffer, Contract, PlayedCard, 'S');
		send(NS_Socket, buffer, strlen(buffer), 0);
		clearBuffer(buffer, 1024);
		val = recv(NS_Socket, buffer, sizeof(buffer), 0);
		strToPlayedCards(PlayedCard, buffer);
		position = { 53,19 };
		SetConsoleCursorPosition(hConsole, position);
		if (PlayedCard[6] <= 10)
		{
			std::cout << PlayedCard[6] << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 11)
		{
			std::cout << "J" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 12)
		{
			std::cout << "Q" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 13)
		{
			std::cout << "K" << (char)PlayedCard[7];
		}
		else if (PlayedCard[6] == 14)
		{
			std::cout << "A" << (char)PlayedCard[7];
		}
		Sleep(2000);

		// sprawdzamy kto wygral
		bool isAtutPlayed = false;
		char atutSuit = Contract[2];
		for (int i = 0; i < 4; i++) // czy zostal zagrany atut
		{
			if (PlayedCard[1 + (i * 2)] == (int)Contract[2])
			{
				isAtutPlayed = true;
				break;
			}
		}
		int WinerIndex = 100;
		if (isAtutPlayed)
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed && PlayedCard[1 + (i * 2)] == (int)Contract[2])
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		else
		{
			int maxPlayed = 0;
			for (int i = 0; i < 4; i++) // szukamy najwyzsza karte
			{
				if (PlayedCard[i * 2] > maxPlayed)
				{
					maxPlayed = PlayedCard[i * 2];
					WinerIndex = i;
				}
			}
		}
		if (WinerIndex == 0)
		{
			return 'W';
		}
		else if (WinerIndex == 1)
		{
			return 'N';
		}
		else if (WinerIndex == 2)
		{
			return 'E';
		}
		else if (WinerIndex == 3)
		{
			return 'S';
		}
		return 0;
	}
	return 0;
}

void actionPhase(SOCKET& NS_Socket, SOCKET& EW_Socket, char* Contract)
{
    int PlayedCards[8] = { 0,0,0,0,0,0,0,0 }; // karty zagrane pierwszy index to wartosc, drugi index to kolor
    char AttackingPlayer = Contract[0];
    char Suit;
    char StartingPlayer = 'N';
    if (Contract[0] == 'N')
    {
        StartingPlayer = 'E';
    }
    else if (Contract[0] == 'E')
    {
        StartingPlayer = 'S';
    }
    else if (Contract[0] == 'S')
    {
        StartingPlayer = 'W';
    }
    else if (Contract[0] == 'W')
    {
        StartingPlayer = 'N';
    }

    int WinnedTurns[] = { 0,0,0,0 };
    char Players[4] = { 'N','E','S','W' };


    //std::cout << "\nKontrakt gracza " << Contract[0] << " na " << Contract[1] << " " << Contract[2];

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            PlayedCards[j] = 0;
        }
        COORD position = { 53,7 };
        SetConsoleCursorPosition(hConsole, position);
        std::cout << "   ";
        position = { 70,13 };
        SetConsoleCursorPosition(hConsole, position);
        std::cout << "   ";
        position = { 53,19 };
        SetConsoleCursorPosition(hConsole, position);
        std::cout << "   ";
        position = { 38,13 };
        SetConsoleCursorPosition(hConsole, position);
        std::cout << "   ";

        Sleep(1500);
        char winner = playTurn ( &StartingPlayer, Contract, PlayedCards, NS_Socket, EW_Socket);
        if (winner == 'N')
        {
            WinnedTurns[0]++;
            StartingPlayer = 'N';

            position = { 63,1 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << WinnedTurns[0];
        }
        else if (winner == 'E')
        {
            WinnedTurns[1]++;
            StartingPlayer = 'E';

            position = { 73,1 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << WinnedTurns[1];
        }
        else if (winner == 'S')
        {
            WinnedTurns[2]++;
            StartingPlayer = 'S';

            position = { 83,1 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << WinnedTurns[2];
        }
        else if (winner == 'W')
        {
            WinnedTurns[3]++;
            StartingPlayer = 'W';

            position = { 93,1 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << WinnedTurns[3];
        }
        //std::cout << "\nwygral gracz: " << winner;
    }
    int NS_Points = WinnedTurns[0] + WinnedTurns[2];
    int EW_Points = WinnedTurns[1] + WinnedTurns[3];
    if (AttackingPlayer == 'N' || AttackingPlayer == 'S')
    {
        int requiredPoints = (int)Contract[1] - 48 + 6;
        if (NS_Points >= requiredPoints)
        {
            system("cls");
            COORD position = { 40,10 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << "Kontrakt druzyny NS wypelniony";
            Sleep(2000);
        }
        else
        {
            system("cls");
            COORD position = { 40,10 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << "Kontrakt druzyny NS nie wypelniony";
            Sleep(2000);
        }
    }
    else if (AttackingPlayer == 'E' || AttackingPlayer == 'W')
    {
        int requiredPoints = (int)Contract[1] - 48 + 6;
        if (EW_Points >= requiredPoints)
        {
            system("cls");
            COORD position = { 40,10 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << "Kontrakt druzyny EW wypelniony";
            Sleep(2000);
        }
        else
        {
            system("cls");
            COORD position = { 40,10 };
            SetConsoleCursorPosition(hConsole, position);
            std::cout << "Kontrakt druzyny EW nie wypelniony";
            Sleep(2000);
        }
    }

}


int main() 
{
    WSADATA wsaData;
    SOCKET server_socket, NS_client_socket, EW_client_socket;
    struct sockaddr_in server_address, NS_client_address, EW_client_address;
    int NS_client_address_length = sizeof(NS_client_address);
    int EW_client_address_length = sizeof(EW_client_address);
    char buffer[1024] = { 0 };
    const int PORT = 65432;


    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
    {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    // Prepare the server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the address and port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) 
    {
        std::cerr << "Bind failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // Start listening for connections
    if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR) 
    {
        std::cerr << "Listen failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // Accept incoming connection
    if ((NS_client_socket = accept(server_socket, (struct sockaddr*)&NS_client_address, &NS_client_address_length)) == INVALID_SOCKET)
    {
        std::cerr << "Accept failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    // Accept incoming connection
    if ((EW_client_socket = accept(server_socket, (struct sockaddr*)&EW_client_address, &EW_client_address_length)) == INVALID_SOCKET)
    {
        std::cerr << "Accept failed" << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return -1;
    }

    std::cout << "Server ready to operate\n";

    Deck deck;

    deck.shuffle();

    char* Ncards[13];
    char* Ecards[13];
    char* Scards[13];
    char* Wcards[13];

    deck.split(Ncards, Ecards, Scards, Wcards);


    char cardStr[40];


    for (int i = 0; i < 40; i++) cardStr[i] = 0;
    cardsToString(Ncards, cardStr, 13);

    int valread = 0;


    send(NS_client_socket, cardStr, strlen(cardStr), 0);
    //std::cout << "wysylanie\n";


    recv(NS_client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(buffer, "first package recived"))
    {
       // std::cout << "potwierdzono otrzymanie pakietu\n";
        for (int i = 0; i < 40; i++) cardStr[i] = 0;
        cardsToString(Scards, cardStr, 13);
        send(NS_client_socket, cardStr, strlen(cardStr), 0);
        //std::cout << "wysylanie drugiego pakietu\n";
    }

    recv(NS_client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(buffer, "second package recived"))
    {
       // std::cout << "potwierdzono otrzymanie drugiego pakietu\n";
    }




    for (int i = 0; i < 40; i++) cardStr[i] = 0;
    cardsToString(Ecards, cardStr, 13);


    send(EW_client_socket, cardStr, strlen(cardStr), 0);
    //std::cout << "wysylanie\n";

    clearBuffer(buffer, 1024);
    recv(EW_client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(buffer, "first package recived"))
    {
       // std::cout << "potwierdzono otrzymanie pakietu\n";
        for (int i = 0; i < 40; i++) cardStr[i] = 0;
        cardsToString(Wcards, cardStr, 13);
        send(EW_client_socket, cardStr, strlen(cardStr), 0);
       // std::cout << "wysylanie drugiego pakietu\n";
    }

    clearBuffer(buffer, 1024);
    recv(EW_client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(buffer, "second package recived"))
    {
       // std::cout << "potwierdzono otrzymanie drugiego pakietu\n";
    }


    COORD position = { 50,10 };
    SetConsoleCursorPosition(hConsole, position);

    std::cout << "Faza licytacji !";
    Sleep(2000);
    system("cls");


    char contract[3] = { 0,0,0 };


    position = { 55,9 };
    SetConsoleCursorPosition(hConsole, position);
    std::cout << 'N';

    position = { 45,13 };
    SetConsoleCursorPosition(hConsole, position);
    std::cout << 'W';

    position = { 65,13 };
    SetConsoleCursorPosition(hConsole, position);
    std::cout << 'E';

    position = { 55,17 };
    SetConsoleCursorPosition(hConsole, position);
    std::cout << 'S';


    bidingPhase('N', contract, NS_client_socket, EW_client_socket);

    position = { 50,10 };
    SetConsoleCursorPosition(hConsole, position);

    std::cout << "Faza akcji !";
    Sleep(2000);
    system("cls");

	position = { 5,1 };

	SetConsoleCursorPosition(hConsole, position);
	std::cout << "kontrakt gracza: " << contract[0] << " na " << contract[1] << "-" << contract[2];

	position = { 55,9 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << 'N';

	position = { 45,13 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << 'W';

	position = { 65,13 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << 'E';

	position = { 55,17 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << 'S';

	position = { 60,1 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << "N: 0";
	
	position = { 70,1 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << "E: 0";
	
	position = { 80,1 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << "S: 0";
	
	position = { 90,1 };
	SetConsoleCursorPosition(hConsole, position);
	std::cout << "W: 0";

	actionPhase(NS_client_socket, EW_client_socket, contract);




    // Cleanup
    closesocket(server_socket);
    closesocket(NS_client_socket);
    WSACleanup();

    return 0;
}