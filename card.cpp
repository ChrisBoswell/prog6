//
// Created by Christian's PC on 11/5/2019.
//
#include "card.h"
using namespace std;
    Card::Card(){
        setSuit(spades);
        setRank(1);
    }

    Card::Card(int rank, Suit s){
        setSuit(s);
        setRank(rank);
    }
    string Card::toString() const {
        return rankString(getRank()) + suitString(getSuit());
    }

    bool Card::sameSuitAs(const Card &c) const {
        return (getSuit() == c.getSuit());
    }

    int Card::getRank() const {
        return myRank;
    }

    Card::Suit Card::getSuit() const {
        return mySuit;
    }

    string Card::suitString(Card::Suit s) const {
        Suit cases;
        cases = s;
        switch(cases){
            case spades:
                return "s";
            case hearts:
                return "h";
            case diamonds:
                return "d";
            case clubs:
                return "c";
        }
    }

    string Card::rankString(int r) const {
        switch(r){
            case 1:
                return "A";
            case 11:
                return "J";
            case 12:
                return "Q";
            case 13:
                return "K";
        }
        return to_string(r);
    }

    bool Card::operator!=(const Card &rhs) const {
        return !(myRank == rhs.getRank() && mySuit == rhs.getSuit());
    }

    bool Card::operator==(const Card &rhs) const {
        return (myRank == rhs.getRank() && mySuit == rhs.getSuit());
    }

    void Card::setRank(int r){
        this -> myRank = r;
    }

    void Card::setSuit(Card::Suit s) {
        this -> mySuit = s;
    }






