//
// Created by Christian's PC on 11/5/2019.
//
#include "deck.h"
using namespace std;

    Deck::Deck(){
        int indexCounter = 0;
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
            int rand1 = rand() % length;
            int rand2 = rand() % length;
            Card temp1 = myCards[rand1];
            Card temp2 = myCards[rand2];
            //Swap them now
            myCards[rand1] = temp2;
            myCards[rand2] = temp1;
        }
    }
    int Deck::setMyIndex() {
        int index = 0;
        return index;
    }

    Card Deck::dealCard() {
        int index = getMyIndex();
        Card c1 = myCards[index];
        setMyIndex(index);
        return c1;
    }
