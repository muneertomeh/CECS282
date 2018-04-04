
#include <iostream>
#include <string>
using namespace std;


class Deck {
	private:
		Card pile[52]; //an array of cards that forms a 52 card deck
		int totalCardsLeft; // amount of remaining cards left in the deck
		int cardIndex; //an index (location) of a card used in the array of cards, pile[]

	public:
		Deck();
		void resetDeck();
		Card deal();
		void shuffle();
		int  cardsLeft();
		void displayDeck();
};
