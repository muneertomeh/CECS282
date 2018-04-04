#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//constructor for a new deck
Deck::Deck() {
	totalCardsLeft = 52;
	cardIndex = 51;

	char ranks[13] = { 'A', '2','3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };f
	char suits[4] = { 'H', 'S', 'D', 'C' };

	int k = 0;

	//forming a deck that will contain 52 cards
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			pile[k] =  Card(ranks[i], suits[j]);
			k++;
		}
	}
}

//This method resets a deck by starting with a fresh pile of cards
void Deck::resetDeck() {
	
	totalCardsLeft = 52;
	cardIndex = 51;
	//clearing the old set of cards and instantiating new cards without a suit or rank
	for (int i = 0; i < 52; i++){
		pile[i] = Card();
	}

	char ranks[13] = { 'A', '2','3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
	char suits[4] = { 'H', 'S', 'D', 'C' };

	//assigning a suit and rank to each card in the new pile
	int m = 0;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			pile[m].setCard(ranks[i], suits[j]);
				m++;
		}
	}
}

//This method deals a card from a deck and gives it to a player
Card Deck::deal() {
	Card temp = pile[cardIndex];
	totalCardsLeft--;
	cardIndex--;
	return temp;
}

//This method randomly shuffles a 52 card deck ONLY, not a partial one
void Deck::shuffle() {

	if (totalCardsLeft != 52) {
		cout << "Cannot shuffle a partial deck" << endl;
		cout << " " << endl;
	}
	else {
		cout << "Cards have been shuffled" << endl;
		srand(time(0));
		for (int i = 0; i < 52; i++) {
			//an arbitrary index of the deck is generated in which the card at that location with be swapped
			//with a card at an incrementing index, i
			int randyIndex = rand() % 52;
			Card auxiliary = pile[i];
			pile[i] = pile[randyIndex];
			pile[randyIndex] = auxiliary;
		}
	}
}

//This method returns the amount of cards left in a deck
int Deck::cardsLeft() {
	return totalCardsLeft;

}

//This method displays the total amount of cards left in the deck
void Deck::displayDeck() {
	//tests if the deck doesn't contain any cards
	if (totalCardsLeft == 0) {
		cout << "Cannot show any cards in the deck, as the deck is EMPTY" << endl;
	}
	//else, show all remaining cards left in the deck
	else {
		for (int i = 0; i < totalCardsLeft; i++) {
			pile[i].displayCardInfo();
		}

	}
	cout << "" << endl;
	
}
