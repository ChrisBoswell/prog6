//
// Created by Christian's PC on 11/5/2019.
//
#import "card.h"

    Card::Card(){
        setSuit(spades);
        setRank(1);
    }
    Card::Card(int rank, Suit s){
        setSuit(s);
        setRank(rank);
    }
    string Card::toString() const {
        return rankConversion(getRank()) + suitString(this->mySuit);

    }
    bool Card::sameSuitAs(const Card &c) const {

    }
    int Card::getRank() const {
        return myRank;
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

    }
    bool Card::operator!=(const Card &rhs) const {

    }
    bool Card::operator==(const Card &rhs) const {
            if(myRank == rhs.getRank() && mySuit == rhs.suitString())
    }

    void Card::setRank(int r){
        this -> myRank = r;
    }

    void Card::setSuit(Card::Suit s) {
        this -> mySuit = s;
    }

    string Card::rankConversion(int rank) const {
        switch(rank){
            case 1:
                return "A";
            case 11:
                return "J";
            case 12:
                return "Q";
            case 13:
                return "K";
        }
        return to_string(rank);
    }






