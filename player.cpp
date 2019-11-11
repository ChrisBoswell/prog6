//
// Created by Christian's PC on 11/5/2019.
//



#include "player.h"
#include "card.h"
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
            for(int j = i+1; j < size; j++){
                comp2 = myHand[j];
                if(comp1.getRank() == comp2.getRank()){
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
        if(myHand.size()>1) {
            srand(time(nullptr)); //seed random gen
            int card = rand() % (myHand.size() - 1);
            return myHand[card];
        }
        else if(myHand.size() == 1){
            return myHand[0];
        }
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
        for(Card test : myHand){
            //cout << test.toString();
            //printf("\n");
            Hand += test.toString();
            Hand += " ";
        }
        return Hand;
    }

    string Player::showBooks() const {
        string book;
        for(Card test : myBook){
            //cout << test.toString();
            //printf("\n");
            book += test.toString();
            book += " ";
        }
        return book;
    }

    int Player::getHandSize() const {
            int size = myHand.size();
            return size;
    }

    int Player::getBookSize() const {
            int size = myBook.size();
            return size;
    }

    Card Player::returnRankCard(Card c) const {
        int targetRank = c.getRank();
        for(Card test : myHand){
            if(test.getRank() == targetRank){
                return test;
            }
        }
    }

    Card Player::returnIndexCard(int i) const {
        return myHand[i];
    }
