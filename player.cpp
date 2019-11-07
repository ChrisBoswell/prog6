//
// Created by Christian's PC on 11/5/2019.
//



#include "player.h"
#include <time.h>
#include <stdlib.h>

    void Player::addCard(Card c) {
        myHand.push_back(c);
    }

    void Player::bookCards(Card c1, Card c2) {
        myBook.push_back(c1);
        myBook.push_back(c2);
    }

    bool Player::checkHandForBook(Card &c1, Card &c2) {
        int size = myHand.size();
        Card comp1;
        Card comp2;
        for(int i = 0; i < size - 1; i++){
            comp1 = myHand[i];
            for(int j = i; j < size; j++){
                comp2 = myHand[j];
                if(comp1 == comp2){
                    c1 = comp1;
                    c2 = comp2;
                    return true;
                }
            }
        }
        return false;
    }

    bool Player::rankInHand(Card c) const {

    }

    Card Player::chooseCardFromHand() const {
        srand(time(NULL)); //seed random gen
        int card = rand() % myHand.size() -1;
        return myHand[card];
    }

    bool Player::cardInHand(Card c) const {
        for(Card test : myHand){
            if(test == c){
                return true;
            }
        }
        return false;
    }

    Card Player::removeCardFromHand(Card c) { //!!This function has no error checking!
        vector<Card>::iterator pos = myHand.begin();
        int i = 0;
        Card target;
        for(Card test : myHand){
            if(test == c){
                target = c;
                myHand.erase(pos);
                return target;
            }
            advance(pos, 1);
        }
    }

    string Player::showHand() const {
    
    }

    string Player::showBooks() const {
    
    }

    int Player::getHandSize() const {
    
    }

    int Player::getBookSize() const {
    
    }

    bool Player::checkHandForPair(Card &c1, Card &c2) {
    
    }

    bool Player::sameRankInHand(Card c) const {
    
    }
        
