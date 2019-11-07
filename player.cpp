//
// Created by Christian's PC on 11/5/2019.
//



#include "player.h"
#include <ctime>
#include <cstdlib>

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
        for(Card test : myHand){
            if(c.getRank() == test.getRank()){
                return true;
            }
        }
        return false;
    }

    Card Player::chooseCardFromHand() const {
        srand(time(nullptr)); //seed random gen
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
        auto pos = myHand.begin();
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
        string Hand;
        for(std::vector<Card>::const_iterator i = myHand.begin(); i != myHand.end(); ++i){
                ;
            }
            return "";
    }

    string Player::showBooks() const {
        for(std::vector<Card>::const_iterator i = myBook.begin(); i != myBook.end(); ++i){
                std::cout << *i << "";
            }
    }

    int Player::getHandSize() const {
            int size = myHand.size();
            return size;
    }

    int Player::getBookSize() const {
            int size = myBook.size();
            return size;
    }
    