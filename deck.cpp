//
// Created by Christian's PC on 11/5/2019.
//
#include "deck.h"
using namespace std;

    Deck::Deck(){
        int indexCounter = 0;
        setMyIndex(0);
        for(int suitDeck = 0; suitDeck < 4; suitDeck++){
            //Changes Suit
            for(int rankDeck = 1; rankDeck < 14; rankDeck++){
                Card c1(rankDeck, (Card::Suit) suitDeck);
                myCards[indexCounter] = c1;
                indexCounter++;
            }
        }
    }

    void Deck::shuffle() {
        int arrayLength = sizeof(myCards);
        int oneArray = sizeof(myCards[0]);
        int length = arrayLength / oneArray;
        if(length < 2){
            return;
        }


        for(int iterations = 0; iterations < 50; iterations++) {

            int rand1 = getMyIndex() + (rand() % (51 - getMyIndex()));
            int rand2 = getMyIndex() + (rand() % (51 - getMyIndex()));
            Card temp1 = myCards[rand1];
            Card temp2 = myCards[rand2];
            //Swap them now
            myCards[rand1] = temp2;
            myCards[rand2] = temp1;
        }
    }
    void Deck::setMyIndex(int i) {
        myIndex = i;
    }


    Card Deck::dealCard() {
        int index = getMyIndex();
        if(index < 52) {
            Card c1 = myCards[index];
            setMyIndex(index + 1);
            return c1;
        }

    }

    int Deck::getMyIndex() {
        return myIndex;
    }
