#include <winsock2.h>
#include <ws2tcpip.h> 
#include<iostream>
#include <string>
#include <windows.h>
#include"Card.h"
#include"Deck.h"
#include"Hand.h"
#include"Player.h"

#pragma comment(lib, "ws2_32.lib")

void strToCards(std::string cards, Player& p)
{
    //int cardsCounter = 0;

    char cardRank[2] = { 0,0 };
    char cardSuit = 0;

    for(int i=0; i<cards.size();i++)
    {
        if (cards[i] <= 57) // jezeli znak jest cyfr¹
        {
            if(cardRank[0]==0)
                cardRank[0] = cards[i];
            else cardRank[1] = cards[i];
        }
        else // jezeli znak jest liter¹
        {
            cardSuit = cards[i];
            int Rank = atoi(cardRank);
            Card* card = new Card(Rank,cardSuit);
            p.getHand().addCard(*card);
            cardSuit = 0;
            cardRank[0] = 0;
            cardRank[1] = 0;
        }
    }

}

void clearBuffer(char* buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        buffer[i] = 0;
    }
}

int Bid(char* contract, Player& P)
{
	// 7, 8, 9, 10, 11, 12, 13
	// 1-7 
	// kolejnosc kolorow
	// trefl, karo, kier, pik, bez atu
	//  C      D     H     S      B

	//                      S H D C
	int SuitStrength[4] = { 0,0,0,0 };
	int SuitNumber[4] = { 0,0,0,0 };
	float totalStrength[4] = { 0,0,0,0 };
	int totalPower = P.getHand().ShowPower();


	SuitStrength[0] = P.getHand().ShowPower('s');
	SuitStrength[1] = P.getHand().ShowPower('h');
	SuitStrength[2] = P.getHand().ShowPower('d');
	SuitStrength[3] = P.getHand().ShowPower('c');


	SuitNumber[0] = P.getHand().findSuitCardNumber('s');
	SuitNumber[1] = P.getHand().findSuitCardNumber('h');
	SuitNumber[2] = P.getHand().findSuitCardNumber('d');
	SuitNumber[3] = P.getHand().findSuitCardNumber('c');


	totalStrength[0] = SuitStrength[0] + SuitNumber[0] * 0.5;
	totalStrength[1] = SuitStrength[1] + SuitNumber[1] * 0.5;
	totalStrength[2] = SuitStrength[2] + SuitNumber[2] * 0.5;
	totalStrength[3] = SuitStrength[3] + SuitNumber[3] * 0.5;

	int index = 0; // indeks w tablicy najlepszego koloru
	float max = 0;

	char suits[4] = { 's','h','d','c' };

	for (int i = 0; i < 4; i++)
	{
		if (max < totalStrength[i])
		{
			max = totalStrength[i];
			index = i;
		}
	}

	// contract[0] nazwa gracza;	[1] wartosc;	 [2] kolor

	// zaklad 3 lewy
	if (SuitNumber[index] >= 5 && SuitStrength[index] >= 6)
	{
		if (contract[0] == '\0' && contract[1] == '\0' && contract[2] == '\0') // jezeli nie bylo kontraktu
		{
			contract[0] = P.getName();
			contract[1] = '3';
			contract[2] = suits[index];

			return 1;
		}
		else if (contract[0] == P.getPartner()->getName()) // jezeli byl kontrakt od partnera
		{
			// kontrakt slabszy w innym kolorze (zmieniamy)
			if (contract[1] < '3' && contract[2] != suits[index])
			{
				contract[0] = P.getName();
				contract[1] = '3';
				contract[2] = suits[index];


				return 1;
			}
			// kontrakt w silnym kolorze (podbijamy)
			else if (contract[2] == suits[index])
			{
				contract[0] = P.getName();
				contract[1] += 3;
				contract[2] = suits[index];


				return 1;
			}
		}
		else if (contract[0] != P.getPartner()->getName() && contract[0] != P.getName()) // kontrakt od przeciwnika
		{
			// sparwdzamy czy mozemy podbic
			if (contract[1] < '3') // wartosc slabsza - mozemy podbic
			{
				contract[0] = P.getName();
				contract[1] = '3';
				contract[2] = suits[index];
		

				return 1;
			}
			else if (contract[1] == '3') // wartosc taka sama, patrzymy na kolor
			{
				if (index == 0 && (contract[3] == 'h' || contract[3] == 'd' || contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '3';
					contract[2] = suits[index];
				

					return 1;
				}
				else if (index == 1 && (contract[3] == 'd' || contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '3';
					contract[2] = suits[index];
					
					return 1;
				}
				else if (index == 2 && (contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '3';
					contract[2] = suits[index];
					

					return 1;
				}
			}
		}
	}




	// zaklad 2 lewy
	else if (SuitNumber[index] >= 4 && SuitStrength[index] >= 5)
	{
		if (contract[0] == '\0' && contract[1] == '\0' && contract[2] == '\0') // jezeli nie bylo kontraktu
		{
			contract[0] = P.getName();
			contract[1] = '2';
			contract[2] = suits[index];


			return 1;
		}
		else if (contract[0] == P.getPartner()->getName()) // jezeli byl kontrakt od partnera
		{
			// kontrakt slabszy w innym kolorze (zmieniamy)
			if (contract[1] < '2' && contract[2] != suits[index])
			{
				contract[0] = P.getName();
				contract[1] = '2';
				contract[2] = suits[index];

				return 1;
			}
			// kontrakt w silnym kolorze (podbijamy)
			else if (contract[2] == suits[index])
			{
				contract[0] = P.getName();
				contract[1] += 2;
				contract[2] = suits[index];

				return 1;
			}
		}
		else if (contract[0] != P.getPartner()->getName() && contract[0] != P.getName()) // kontrakt od przeciwnika
		{
			// sparwdzamy czy mozemy podbic
			if (contract[1] < '2') // wartosc slabsza - mozemy podbic
			{
				contract[0] = P.getName();
				contract[1] = '2';
				contract[2] = suits[index];

		
				return 1;
			}
			else if (contract[1] == '2') // wartosc taka sama, patrzymy na kolor
			{
				if (index == 0 && (contract[3] == 'h' || contract[3] == 'd' || contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '2';
					contract[2] = suits[index];

					return 1;
				}
				else if (index == 1 && (contract[3] == 'd' || contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '2';
					contract[2] = suits[index];

		
					return 1;
				}
				else if (index == 2 && (contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '2';
					contract[2] = suits[index];

					return 1;
				}
			}
		}
	}


	// zaklad 1 lew
	else if (SuitNumber[index] >= 4 && SuitStrength[index] >= 3)
	{
		if (contract[0] == '\0' && contract[1] == '\0' && contract[2] == '\0') // jezeli nie bylo kontraktu
		{
			contract[0] = P.getName();
			contract[1] = '1';
			contract[2] = suits[index];

			
			return 1;
		}
		else if (contract[0] == P.getPartner()->getName()) // jezeli byl kontrakt od partnera
		{
			// kontrakt slabszy w innym kolorze (zmieniamy)
			if (contract[1] < '1' && contract[2] != suits[index])
			{
				contract[0] = P.getName();
				contract[1] = '1';
				contract[2] = suits[index];

				
				return 1;
			}
			// kontrakt w silnym kolorze (podbijamy)
			else if (contract[2] == suits[index])
			{
				contract[0] = P.getName();
				contract[1] += 1;
				contract[2] = suits[index];

				
				return 1;
			}
		}
		else if (contract[0] != P.getPartner()->getName() && contract[0] != P.getName()) // kontrakt od przeciwnika
		{
			// sparwdzamy czy mozemy podbic
			if (contract[1] < '1') // wartosc slabsza - mozemy podbic
			{
				contract[0] = P.getName();
				contract[1] = '1';
				contract[2] = suits[index];

				
				return 1;
			}
			else if (contract[1] == '1') // wartosc taka sama, patrzymy na kolor
			{
				if (index == 0 && (contract[3] == 'h' || contract[3] == 'd' || contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '1';
					contract[2] = suits[index];

					
					return 1;
				}
				else if (index == 1 && (contract[3] == 'd' || contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '1';
					contract[2] = suits[index];

					
					return 1;
				}
				else if (index == 2 && (contract[3] == 'c'))
				{
					contract[0] = P.getName();
					contract[1] = '1';
					contract[2] = suits[index];

					
					return 1;
				}
			}
		}
	}

	return 0;
}

void strToCardsInformations(char* buffer, char* Contract, int* PlayedCard, char* Player)
{
	*Player = buffer[0];

	Contract[0] = buffer[1];
	Contract[1] = buffer[2];
	Contract[2] = buffer[3];

	int end = 0;
	int index = 4;
	int rank = 0;
	while (end < 8)
	{
		if (buffer[index] <= 57 && buffer[index] >= 48) // jezeli to cyfra
		{
			rank = rank * 10 + buffer[index] - 48;
			index++;
		}
		else if (buffer[index] == 0)
		{
			PlayedCard[end] = 0;
			index++;
			end++;
		}
		else
		{
			PlayedCard[end] = rank;
			end++;
			PlayedCard[end] = buffer[index];
			end++;
			index++;
			rank = 0;
		}
	}
}

void playCard(Player& P, char* Contract, int* PlayedCard)
{
	if (PlayedCard[0] == 0 && PlayedCard[1] == 0) // jezeli zagrywasz jako pierwszy daj najsilniejsza karte jaka posiadasz
	{
		int index = P.getHand().findHighestCard();
		PlayedCard[0] = P.getHand().getCards()[index].getRank();
		PlayedCard[1] = P.getHand().getCards()[index].getSuit();

		P.getHand().getCards().erase(P.getHand().getCards().begin() + index);
	}
	else
	{
		int index = 0; // indeks granej karty w tablicy PlayedCart
		while (PlayedCard[index] != 0)
		{
			index += 2;

		}
		char suit = PlayedCard[1]; // wymagany kolor
		int highestRankPlayed = 0;
		for (int i = 0; i < 3; i++)
		{
			if (PlayedCard[i * 2] > highestRankPlayed)
			{
				highestRankPlayed = PlayedCard[i * 2];
			}
		}
		// czy mam kolor
		if (P.getHand().isSuitInHand(suit)) // jezeli tak
		{
			// czy moge przebic
			if (P.getHand().getCards()[P.getHand().findHighestCard(suit)].getRank() > highestRankPlayed) // jezeli tak przebij
			{
				//index to index granej karty w tablicy PlayedCard
				PlayedCard[index] = P.getHand().getCards()[P.getHand().findHighestCard(suit)].getRank();
				PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findHighestCard(suit)].getSuit();
				P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findHighestCard(suit));
			}
			else // w przeciwnym razie
			{
				// najslabsza karta tego koloru
				PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard(suit)].getRank();
				PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard(suit)].getSuit();
				P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard(suit));
			}
		}
		else // jezeli nie mam koloru
		{
			//sprawdzam czy mam kolor atutowy
			char atutSuit = Contract[2];
			if (P.getHand().isSuitInHand(atutSuit)) // jezeli mam kolor atutowy na reku
			{
				bool atutPlayed = false;
				for (int i = 0; i < 3; i++) // sprawdzam czy ktos zagral kolor atutowy
				{
					if (PlayedCard[1 + (i * 2)] == (int)atutSuit)
					{
						atutPlayed = true;
						break;
					}
				}
				if (atutPlayed) // jezeli ktos zagral juz karte atutowa
				{
					int maxAtutPlayed = 0;
					for (int i = 0; i < 3; i++) // znajduje najwyzsza karte atutowa
					{
						if (PlayedCard[i * 2] > maxAtutPlayed && PlayedCard[1 + (i * 2)] == (int)atutSuit)
						{
							maxAtutPlayed = PlayedCard[i * 2];
						}
					}
					// czy moge go przebic
					if (P.getHand().getCards()[P.getHand().findHighestCard(atutSuit)].getRank() > maxAtutPlayed)
					{
						// jezeli tak przebij
						PlayedCard[index] = P.getHand().getCards()[P.getHand().findHighestCard(atutSuit)].getRank();
						PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findHighestCard(atutSuit)].getSuit();
						P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findHighestCard(atutSuit));
					}
					else // jezeli nie zagraj najslabsza karte
					{
						PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard()].getRank();
						PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard()].getSuit();
						P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard());
					}
				}
				else // jezeli karta atutowa nie zostala zagrana
				{
					//zagraj naslabszy atut
					PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard(atutSuit)].getRank();
					PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard(atutSuit)].getSuit();
					P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard(atutSuit));
				}
			}
			else // jezeli nie zagrywam najgorsza mozliwa karte
			{
				PlayedCard[index] = P.getHand().getCards()[P.getHand().findWorstCard()].getRank();
				PlayedCard[index + 1] = P.getHand().getCards()[P.getHand().findWorstCard()].getSuit();
				P.getHand().getCards().erase(P.getHand().getCards().begin() + P.getHand().findWorstCard());
			}
		}
	}
}

void informationToStr(int* PlayedCard, char* buffer)
{
	clearBuffer(buffer, 1024);
	int rank;
	int index = 0;
	int bufferIndex = 0;
	while (index < 8)
	{
		if (PlayedCard[index] >= 10 && PlayedCard[index] <= 14)
		{
			buffer[bufferIndex] = '1';
			bufferIndex++;
			buffer[bufferIndex] = PlayedCard[index] % 10 + 48;
			bufferIndex++;
			index++;
		}
		else if (PlayedCard[index] >= 2 && PlayedCard[index] <= 9)
		{
			buffer[bufferIndex] = PlayedCard[index] + 48;
			bufferIndex++;
			index++;
		}
		else if(PlayedCard[index] >= 97)
		{
			buffer[bufferIndex] = PlayedCard[index];
			bufferIndex++;
			index++;
		}
		else
		{
			buffer[bufferIndex] = 0;
			bufferIndex++;
			index++;
		}
	}
}


int main()
{
    Hand N_Hand;
    Hand S_Hand;

    Player S_Player('S', S_Hand);
    Player N_Player('N', N_Hand);

    N_Player.SetPartner(&S_Player);
    S_Player.SetPartner(&N_Player);

    WSADATA wsaData;
    SOCKET NS_client_socket;
    struct sockaddr_in server_address;
    const int PORT = 65432;
    const char* message = "Hello, world";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "WSAStartup failed" << std::endl;
        return -1;
    }

    // Create socket
    if ((NS_client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
    {
        std::cerr << "Socket creation failed" << std::endl;
        WSACleanup();
        return -1;
    }

    // Prepare the server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) 
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(NS_client_socket);
        WSACleanup();
        return -1;
    }

    // Connect to the server
    if (connect(NS_client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == SOCKET_ERROR) 
    {
        std::cerr << "Connection failed" << std::endl;
        closesocket(NS_client_socket);
        WSACleanup();
        return -1;
    }
    std::cout << "NS Players connected to server\n";



    char buffer[1024] = { 0 };
    std::string cards = "";
    int valread;

    recv(NS_client_socket, buffer, sizeof(buffer), 0);
    std::cout<<"odbieranie\n";
    cards += buffer;


    strToCards(cards, N_Player);
    send(NS_client_socket, "first package recived", strlen("first package recived"), 0);

    cards = "";
    recv(NS_client_socket, buffer, sizeof(buffer), 0);
    std::cout << "odbieranie\n";
    cards += buffer;

    strToCards(cards, S_Player);
    send(NS_client_socket, "second package recived", strlen("second package recived"), 0);



    //faza licytacji
	char contract[3];
	while (1)
	{
		clearBuffer(buffer, 1024);
		recv(NS_client_socket, buffer, sizeof(buffer), 0); // buffer[0] nazwa gracza buffer[1] wartosc [2] kolor [3] bidujacy aktualnie gracz
		if (!strcmp(buffer, "done"))
		{
			break;
		}

		contract[0] = buffer[1];
		contract[1] = buffer[2];
		contract[2] = buffer[3];

		if (buffer[0] == 'N') // biduje gracz N
		{
			if (Bid(contract, N_Player))
			{
				buffer[0] = 'N';
				buffer[1] = contract[0];
				buffer[2] = contract[1];
				buffer[3] = contract[2];
				send(NS_client_socket, buffer, sizeof(buffer), 0);
			}
			else
			{
				send(NS_client_socket, "pass", strlen("pass"), 0);
			}
		}
		else if (buffer[0] == 'S') // biduje gracz S
		{
			if (Bid(contract, S_Player))
			{
				buffer[0] = 'S';
				buffer[1] = contract[0];
				buffer[2] = contract[1];
				buffer[3] = contract[2];
				send(NS_client_socket, buffer, sizeof(buffer), 0);
			}
			else
			{
				send(NS_client_socket, "pass", sizeof("pass"), 0);
			}
		}

	}


	//faza gry
	int PlayedCard[8];
	while (1)
	{
		char PlayerName;
		clearBuffer(buffer, 1024);
		int val = recv(NS_client_socket, buffer, sizeof(buffer), 0); 
		
		if (!strcmp(buffer, "done"))
		{
			break;
		}

		strToCardsInformations(buffer, contract, PlayedCard, &PlayerName);
		
		if (PlayerName == 'N')
		{
			playCard(N_Player, contract, PlayedCard);
			informationToStr(PlayedCard, buffer);
			send(NS_client_socket, buffer, strlen(buffer), 0);
		}
		else if (PlayerName == 'S')
		{
			playCard(S_Player, contract, PlayedCard);
			informationToStr(PlayedCard, buffer);
			send(NS_client_socket, buffer, strlen(buffer), 0);
		}
	}



    // Cleanup
    closesocket(NS_client_socket);
    WSACleanup();
    
	return 0;
}