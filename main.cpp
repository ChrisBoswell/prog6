// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include "card.h"
#include "player.h"
#include "deck.h"
using namespace std;
// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);
void bookWin(Player &p, Card c1, Card c2);
#define TWO_PLAYERS 7
#define MORE_PLAYERS 5

int main() {
    vector <Player> players;
    Player eric("Eric");
    Player christian("Christian");
    Player priebe ("priebe");

    players.push_back(eric);
    players.push_back(christian);
    //players.push_back(priebe);
    int numPlayers = players.size();

    int initNumCards = MORE_PLAYERS;
    if(numPlayers == 2) initNumCards = TWO_PLAYERS;

    bool tie = false;
    Deck d;
    d.shuffle();
    //initialize the hand

    for(int i = 0; i < numPlayers; i++){
        dealHand(d, players[i], initNumCards);
        cout << players[i].showHand() << "\n";
        Card test1, test2;
        while(players[i].checkHandForBook(test1, test2)){
            players[i].bookCards(test1, test2);
            players[i].removeCardFromHand(test1);
            players[i].removeCardFromHand(test2);
        }
    }

    for(Player p : players){
        cout << p.showHand() << "\n";
    }

    int currentPlayer = 0;
    int counterParty;
    bool gameStatus = true;

    //stop playing when the cards run out
    while(gameStatus && !tie){

        counterParty = (currentPlayer + 1) % numPlayers; //establish the player you are playing against

        if(players[currentPlayer].getHandSize() == 0){ //if no cards in hand, get a new card
            if(d.getMyIndex() < 52){ //ensure in bounds
                players[currentPlayer].addCard(d.dealCard()); //add the new card
                cout << "\n" << players[currentPlayer].getName() << " draws";
            }
        }

        if(players[currentPlayer].getHandSize()!=0){
            //choose card from hand, then ask the other player if they have it
            Card target = players[currentPlayer].chooseCardFromHand();
            cout << "\n" << players[currentPlayer].getName() << " requests card with rank " << target.toString();
            bool turnOver = false;
            while(players[counterParty].rankInHand(target)){ //if the ask is successful, hand over all cards of the same rank

                Card given = players[counterParty].returnRankCard(target);
                players[counterParty].removeCardFromHand(given);
                players[currentPlayer].addCard(given);
                cout <<" \n" << players[counterParty].getName() << " gives " << players[currentPlayer].getName() << " " << given.toString();

                Card bookTest1, bookTest2;
                bookWin(players[currentPlayer], bookTest1, bookTest2);
                turnOver = true;
            }

            if(!players[counterParty].rankInHand(target) && !turnOver){ //if not, the requester must draw
                cout<< "\n" << players[counterParty].getName() << ": Go Fish";
                if(d.getMyIndex()<52) {
                    Card newCard = d.dealCard();
                    cout << "\n" << players[currentPlayer].getName() << " draws " << newCard.toString();
                    players[currentPlayer].addCard(newCard);
                    Card goFish1, goFish2;
                    while(players[currentPlayer].checkHandForBook(goFish1, goFish2)){
                        players[currentPlayer].bookCards(goFish1, goFish2);
                        players[currentPlayer].removeCardFromHand(goFish1);
                        players[currentPlayer].removeCardFromHand(goFish2);
                    }
                }
            }
        }

        cout << "\n";
        //check for tie scenario
        tie = true;
        if(d.getMyIndex() >= 52){
            for(int i = 0; i < numPlayers; i++){
                int nextPlayer = (i + 1) % numPlayers;
                for(int j = 0; j < players[i].getHandSize(); j++){
                    if(players[nextPlayer].rankInHand(players[i].returnIndexCard(j))) tie = false;

                }
            }
        }

        if(d.getMyIndex()<52){
            tie = false;
        }
        currentPlayer = (currentPlayer + 1) % numPlayers;
        if(d.getMyIndex()>=52) gameStatus = false;

        int cardsInHand = 0;
        for(Player p : players){
            cardsInHand+=p.getHandSize();
        }
        if(cardsInHand>0) gameStatus = true;
        else if(cardsInHand <= 0) gameStatus = false;


    }

    for(Player p : players){
        cout << p.getName() << " hand: " << p.showHand() << "\n";
        cout << p.getName() << " book " << p.showBooks() << "\n \n";
    }

    int maxBookSize = players[0].getBookSize();
    int winnerIndex;
    /*
    for(int i = 0; i < numPlayers; i++){
        if(players[i].getBookSize()>maxBookSize){
            maxBookSize = players[i].getBookSize();
            winnerIndex = i;
        }
    }

    cout << "\n Winner is " << players[winnerIndex].getName(); */


    return EXIT_SUCCESS;
}


void dealHand(Deck &d, Player &p, int numCards)
{
    for (int i=0; i < numCards; i++)
        p.addCard(d.dealCard());
}

void bookWin(Player &p, Card c1, Card c2){
    p.checkHandForBook(c1, c2);
    p.bookCards(c1, c2);
    p.removeCardFromHand(c1);
    p.removeCardFromHand(c2);
}

