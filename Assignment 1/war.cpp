

#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	//a new deck is created automatically once the program starts
	Deck myDeck;
	
	//showing the main menu for the War program
	int menuSelection=0;
	do {
		if(menuSelection !=4){
			cout << "1) Get a new card deck" << endl;
			cout << "2) Show all remaining cards in deck" << endl;
			cout << "3) Shuffle the deck" << endl;
			cout << "4) Play WAR!" << endl;
			cout << "5) Exit program" << endl;

			cin >> menuSelection;
		}

		Card c1;
		Card c2;

		switch (menuSelection) {
			cout << menuSelection << endl;
			case 1:
			//this option resets the card pile inside the deck
				myDeck.resetDeck();
				cout << "Deck has been reset" << endl;
				break;
			//this option allows the user to peek at the deck's remanining cards
			case 2:
				myDeck.displayDeck();
				break;
			//this choice shuffles a full deck, but if the deck is partial, shuffling will not occur
			case 3:
				myDeck.shuffle();
				break;
			//this option initiates the game of War
			case 4:
				if (myDeck.cardsLeft() == 0) {
					cout << "Cannot play War with nothing inside the deck" << endl;
					menuSelection = 0;
					break;
				}
				cout << "GET READY TO PLAY WAR!!!" << endl;
				cout << " " << endl;
				cout << "Total amount of cards in deck: "<< myDeck.cardsLeft() <<endl;
				cout << " ....dealing" << endl;
				//dealing a card for the user and displaying it
				cout << "One for you" << endl;
				c1 = myDeck.deal(); 
				c1.displayCardInfo();
				c1.displayCard();
				cout << "" << endl;
				//dealing a card for the AI and displaying it
				cout << "One for me" << endl;
				c2 = myDeck.deal();
				c2.displayCardInfo();
				c2.displayCard();
				cout << "" << endl;

				//if the player's card value is higher than the AI's card value, then the player wins
				if (c1.getValue() > c2.getValue()) {
					cout << "You win!" << endl;
					cout << " " << endl;
				}
				//if both card values are the same, then it is automatically a draw
				else if (c1.getValue() == c2.getValue()){
					cout << "It's a tie folks!" << endl;
					cout << " " << endl;
				}
				//the human player loses if his card value is less than the AI's card value
				else {
					cout << "You lose!" << endl;
					cout << " " << endl;
				}
				char answer;

				//inquiring if user wants to play again
				if (myDeck.cardsLeft() == 0) { // however if there aren't any cards left, the user will be directed to the main menu
					cout << "Cannot play WAR since there are no cards left, REDIRECTING TO MAIN MENU" << endl;
					menuSelection = 0;
					break;
				}
				cout << "Would you like to play again?, Y/y for Yes, N/n for No" << endl;
				cin >> answer;
				
				if (answer == 'Y' || answer == 'y') { //if the user selects yes, then he is directed to the war game(selection 4)
					menuSelection = 4;
					
				} //else, the user will be directed to the War program main menu
				else {
					menuSelection = 0;
				}
				break;

			case 5://exits program
				break;
		}
	} while (menuSelection !=5);

	return 0;
}
