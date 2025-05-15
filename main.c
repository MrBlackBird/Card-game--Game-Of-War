#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// war card game

#define DEALT 1
#define NOT_DEALT 0
#define EMPTY 2

typedef struct{
    char suit[10];
    int value;
    int state;      // 0 -> not dealt, 1 -> dealt
} Card;

typedef struct{
    int current_number_of_cards;
    Card cards[52];
} Deck;

typedef struct{
    int num_of_cards;
    Card cards[];
} Table;

void populate_cards_in_deck(Deck *deck);

void shuffle_deck(Deck *deck);

void split_deck(Deck *deck, Deck *deck_player, Deck *deck_bot);

void play_card(Deck *deck);

void print_deck(Deck *deck);


int main(){
    Deck deck;  // the initial deck
    Deck deck_player, deck_bot;


    // seed random generator for shuffling
    srand(time(NULL));

    // populate main deck
    populate_cards_in_deck(&deck);

    // shuffle deck
    shuffle_deck(&deck);

    // split deck between players
    split_deck(&deck, &deck_player, &deck_bot);

    // for testing
    //print_deck(&deck);
    //print_deck(&deck_player);
    //print_deck(&deck_bot);

    
    // GAME LOOP


    return 0;
}


void populate_cards_in_deck(Deck *deck){
    int hearts = 13;            // splits cards into correct suits
    int hearts_offset = 1;      // append the shifted value as card value
    int spades = 26;
    int spades_offset = 12;
    int diamonds = 39;
    int diamonds_offset = 25;
    int clubs_offset = 38;

    for(int i = 0; i < 52; i++){
        if(i < hearts){
            strcpy(deck->cards[i].suit, "hearts");
            deck->cards[i].value = i + hearts_offset;
        }
        else if(i < spades){
            strcpy(deck->cards[i].suit, "spades");
            deck->cards[i].value = i - spades_offset;
        }
        else if(i < diamonds){
            strcpy(deck->cards[i].suit, "diamonds");
            deck->cards[i].value = i - diamonds_offset;
        } else {
            strcpy(deck->cards[i].suit, "clubs");
            deck->cards[i].value = i - clubs_offset;
        }
    }

    // account for special card values: 1->A, 11->J, 12->Q, 13->K
    int ascii_A = 65;
    int ascii_J = 74;
    int ascii_Q = 81;
    int ascii_K = 75;

    for(int i = 0; i < 52; i++){
        if(deck->cards[i].value == 1){
            // set A
            deck->cards[i].value = ascii_A;
        }
        else if(deck->cards[i].value == 11){
            // set J
            deck->cards[i].value = ascii_J;
        }
        else if(deck->cards[i].value == 12){
            // set Q
            deck->cards[i].value = ascii_Q;
        }
        else if(deck->cards[i].value == 13){
            // set K
            deck->cards[i].value = ascii_K;
        }

        // define card state
        deck->cards[i].state = NOT_DEALT;
    }
}

void shuffle_deck(Deck *deck){
    int rand_card_idx1 = 0;
    int rand_card_idx2 = 0;
    Card temp_card;

    for(int i = 0; i < 100; i++){
        do {
            rand_card_idx1 = rand() % 52;        // gen random indexes for mixing, make sure they're not the same !!!
            rand_card_idx2 = rand() % 52;
        } while (rand_card_idx1 == rand_card_idx2);

        // swap cards in pairs
        temp_card = deck->cards[rand_card_idx1];
        deck->cards[rand_card_idx1] = deck->cards[rand_card_idx2];
        deck->cards[rand_card_idx2] = temp_card;
    }

    //printf("Deck shuffled (random nums: %d, %d\n)", rand_card_idx1 + 1, rand_card_idx2 + 1);
}

void split_deck(Deck *deck, Deck *deck_player, Deck *deck_bot){
    // don't allow empty cells in each player's deck
    for(int i = 0; i < 52; i++){
        deck_player->cards[i].value = 0;
        strcpy(deck_player->cards[i].suit, "empty");
        deck_player->cards[i].state = EMPTY;

        deck_bot->cards[i].value = 0;
        strcpy(deck_bot->cards[i].suit, "empty");
        deck_bot->cards[i].state = EMPTY;
    }
    
    // add coresponding cards to players
    const int split_offset = 26;
    for(int j = 0; j < 26; j++){
        deck_player->cards[j] = deck->cards[j];
        deck_bot->cards[j] = deck->cards[j + split_offset];
    }
}

void play_card(Deck *deck){}


// for testing
void print_deck(Deck *deck){
    for(int i = 0; i < 52; i++){
        if(deck->cards[i].value < 11){
            printf("Card %d value/suit: %d / %s\n", i + 1, deck->cards[i].value, deck->cards[i].suit);
        } else {
            printf("Card %d value/suit: %c / %s\n", i + 1, deck->cards[i].value, deck->cards[i].suit);
        }
        //printf("Card state: %d\n", deck->cards[i].state);
    }
}