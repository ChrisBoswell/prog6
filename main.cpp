// FILE: card_demo.cpp
// This is a small demonstration program showing how the Card and Deck classes are used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
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
    ofstream output;
    output.open("gofish_results.txt");
    output << "Output file created succesfully \n";

    vector <Player> players;
    Player eric("Eric");
    Player christian("Christian");
    Player priebe ("priebe");

    players.push_back(eric);
    players.push_back(christian);
    players.push_back(priebe);
    int numPlayers = players.size();

    if(numPlayers <= 1){
        output << "Illegal Player Count. Exiting with code" << EXIT_FAILURE;
        return EXIT_FAILURE;
    }

    int initNumCards = MORE_PLAYERS;
    if(numPlayers == 2) initNumCards = TWO_PLAYERS;


    //INITIALIZE A DECK OF CARDS AND DISTRIBUTE THEM TO PLAYERS
    Deck d;
    d.shuffle();
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

    /* OLD DEBUG STUFF FOR TIE TESTING
    Card::Suit s = Card::spades;
    Card x1(4, s);
    Card x2(6, s);
    Card x3(8, s);
    players[0].addCard(x1);
    players[1].addCard(x2);
    players[2].addCard(x3); */

    output << "The starting card configurations: \n";
    cout << "The starting card configurations: \n";
    for(Player p : players){
        output << p.getName() << " has " << p.showHand() << " and " << p.showBooks() << "\n";
        cout << p.getName() << " has " << p.showHand() << " and " << p.showBooks() << "\n";
    }
    output << "\n\n";
    bool tie = false;
    int currentPlayer = 0;
    int counterParty = 0;
    bool gameStatus = true;
    Card newCard;
    //stop playing when the cards run out
    while(gameStatus && !tie){

        counterParty = (currentPlayer + 1) % numPlayers; //establish the player you are playing against

        //IF NO CARDS IN THE CURRENT HAND, DRAW A NEW ONE IF POSSIBLE
        if(players[currentPlayer].getHandSize() == 0){
            if(d.getMyIndex() < 52){ //ensure in bounds
                newCard = d.dealCard();
                players[currentPlayer].addCard(newCard); //add the new card
                cout << "\n" << players[currentPlayer].getName() << " draws " << newCard.toString();
                output << players[currentPlayer].getName() << " draws " << newCard.toString() << "\n";
            }
        }

        //IF THERE ARE CARDS IN THE HAND, PLAY GOFISH
        if(players[currentPlayer].getHandSize()!=0){
            Card target = players[currentPlayer].chooseCardFromHand();
            cout << "\n" << players[currentPlayer].getName() << " requests card with rank " << target.toString();
            output << players[currentPlayer].getName() << " requests card with same rank as " << target.toString() << "\n";

            bool turnOver = false;
            //ARE THERE CARDS IN THE COUNTERPARTY'S HAND WITH SAME RANK? IF YES TURN THEM OVER
            while(players[counterParty].rankInHand(target)){
                Card given = players[counterParty].returnRankCard(target);
                players[counterParty].removeCardFromHand(given);
                players[currentPlayer].addCard(given);

                cout <<" \n" << players[counterParty].getName() << " gives " << players[currentPlayer].getName() << " " << given.toString();
                output<< players[counterParty].getName() << " gives " << players[currentPlayer].getName() << " " << given.toString() << "\n";

                Card bookTest1, bookTest2;
                bookWin(players[currentPlayer], bookTest1, bookTest2);
                turnOver = true;
            }

            //IF NOT, DRAW NEW FROM THE PILE IF POSSIBLE
            if(!players[counterParty].rankInHand(target) && !turnOver){ //if not, the requester must draw
                cout<< "\n" << players[counterParty].getName() << ": Go Fish";
                output << players[counterParty].getName() << ": Go Fish\n";
                if(d.getMyIndex()<52) {
                    Card newCard = d.dealCard();
                    cout << "\n" << players[currentPlayer].getName() << " draws " << newCard.toString();
                    output << players[currentPlayer].getName() << " draws " << newCard.toString() << "\n";

                    players[currentPlayer].addCard(newCard);
                    Card goFish1, goFish2;

                    while(players[currentPlayer].checkHandForBook(goFish1, goFish2)){
                        players[currentPlayer].bookCards(goFish1, goFish2);
                        players[currentPlayer].removeCardFromHand(goFish1);
                        players[currentPlayer].removeCardFromHand(goFish2);
                    }
                }
                else cout << "\nnothing left to draw";
            }
        }

        currentPlayer = (currentPlayer + 1) % numPlayers;
        cout << "\n";
        output << "\n"; //THE TURN ENDS HERE

        //DEBUG OUTPUT
        string debug0 = players[0].showHand();
        string debug1 = players[1].showHand();
        string debug2 = players[2].showHand();
        cout << "\ndebug0:"<< debug0 << "\ndebug1:";
        cout << debug1 << "\ndebug2:";
        cout << debug2 << "\n";

        //CHECK IF WE'VE REACHED AN INFINITE LOOP
        tie = true;
        if(d.getMyIndex() >= 52){
            for(int i = 0; i < numPlayers; i++){
                int nextPlayer = (i + 1) % numPlayers;
                for(int j = 0; j < players[i].getHandSize(); j++){
                    if(players[nextPlayer].rankInHand(players[i].returnIndexCard(j))) tie = false;
                }
            }
        }

        //IF STILL CARDS LEFT, IGNORE THE INFINITE CONDITION BC IT CAN CHANGE
        if(d.getMyIndex()<52){
            tie = false;
        }

        //IF THE CARD STACK IS OVERDRAWN, PRESUME GAME TO BE OVER
        if(d.getMyIndex()>=52) gameStatus = false;
        //BUT IF THERE'S STILL CARDS LEFT IN THE PLAYER'S HAND, KEEP GOING
        if(d.getMyIndex()>=52) {
            int cardsInHand = 0;
            for (Player p : players) {
                cardsInHand += p.getHandSize();
            }
            if (cardsInHand > 0) gameStatus = true;
            else if (cardsInHand <= 0) gameStatus = false;
        }
    }
    //CORE GAME LOGIC ENDS HERE WHEN THE GAME ENDS. NEXT TO DECIDE WINNER

    //DEBUG OUTPUT
    for(Player p : players){
        cout << p.getName() << " hand: " << p.showHand() << "\n";
        cout << p.getName() << " book " << p.showBooks() << "\n \n";
    }

    //WINNER DETERMINATION
    int maxBookSize = players[0].getBookSize();
    int winnerIndex = 0;
    for(int i = 1; i < numPlayers; i++){
        if(players[i].getBookSize()>maxBookSize){
            maxBookSize = players[i].getBookSize();
            winnerIndex = i;
        }
    }

    //HOW MANY TOP SCORES ARE THERE?
    int maxCount = 0;
    for(Player p : players){
        if(p.getBookSize() == maxBookSize){
            maxCount++;
        }
    }

    //BUILD OUTPUT DEPENDING ON GAME CONDITION
    if(maxCount == numPlayers){
        cout << "All players have tied";
        output << "All players have tied";
    }
    else if(maxCount == 1){
        cout << "The winner is " << players[winnerIndex].getName();
        output << "The winner is " << players[winnerIndex].getName();
    }
    else{
        string winnerList;
        for(Player p : players){
            if(p.getBookSize() == maxBookSize){
                winnerList = winnerList + p.getName() + ", ";
            }
        }
        cout << "The winners are " << winnerList;
        output << "The winners are " << winnerList;
    }

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

