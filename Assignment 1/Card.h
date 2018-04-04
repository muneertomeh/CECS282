#ifndef CARD_H
#define CARD_H

class Card {

	private:
		char rank; //placement level from best to worst
		char suit; //category of a card; hearts, spades, diamonds, clubs

	public:
		Card();
		Card(char r, char s);
		void setCard(char r, char s);
		void displayCard();
		void displayCardInfo();
		int getValue();


};
#endif;
