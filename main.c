#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// card game - game of war

// define card states
#define NOT_DEALT 0
#define DEALT 1
#define EMPTY 2

// define deck parameters
#define DECK_SIZE 52

typedef struct{
    char suit[10];
    int value;          // stores the card's value: A, 2, 3, ...
    int actual_value;   // stores the card's actual value: 1, 2, 3, ...
    int state;          // 0 -> not dealt, 1 -> dealt, 2 -> empty
} Card;

#define EMPTY_CARD (Card){ .suit = "empty", .value = 0, .state = EMPTY }

typedef struct{
    int current_number_of_cards;
    Card cards[DECK_SIZE];
} Deck;

typedef struct{
    int num_of_cards;
    Card cards_played[];
} Table;

Table* dynamic_cards_arr(int number_of_cards){
    Table* table = malloc(sizeof(Table) + (sizeof(Card) * number_of_cards));
    if(table == NULL){
        fprintf(stderr, "Failed to allocate memory for array\n");
        return NULL;
    }
    table->num_of_cards = number_of_cards;
    return table;
}

void free_table(Table* table){
    free(table);
}

void populate_cards_in_deck(Deck *deck);

void shuffle_deck(Deck *deck);

void split_deck(Deck *deck, Deck *deck_player, Deck *deck_bot);

void play_card(Deck *deck, Table** table);     // TODO ADD TABLE TO ENABLE STORAGE FOR CARDS IN EACH PLAY

void print_deck(Deck *deck);


int main(){
    Deck deck;  // the initial deck
    Deck deck_player, deck_bot;

    int initial_cards_played = 2;
    Table *table = dynamic_cards_arr(initial_cards_played);
    if(table == NULL){
        fprintf(stderr, "Failed to create array in main\n");
        return 1;
    }

    // seed random generator for shuffling
    srand(time(NULL));

    // populate main deck
    populate_cards_in_deck(&deck);

    // shuffle deck
    //shuffle_deck(&deck);

    // split deck between players
    //split_deck(&deck, &deck_player, &deck_bot);

    // for testing
    print_deck(&deck);
    //print_deck(&deck_player);
    //print_deck(&deck_bot);

    
    // GAME LOOP


    return 0;
}


void populate_cards_in_deck(Deck *deck){

    int card_values = 13;
    const char* suits[] = {"hearts", "spades", "diamonds", "clubs"};
    for (int i = 0; i < DECK_SIZE; i++) {
        strcpy(deck->cards[i].suit, suits[i / card_values]);
        deck->cards[i].value = (i % card_values) + 1; // 1-13
        deck->cards[i].actual_value = (i % card_values) + 1;
        deck->cards[i].state = NOT_DEALT;
    }

    // account for special card values: 1->A, 11->J, 12->Q, 13->K
    int ascii_A = 65;
    int ascii_J = 74;
    int ascii_Q = 81;
    int ascii_K = 75;

    for(int i = 0; i < DECK_SIZE; i++){
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
        deck_player->cards[i] = EMPTY_CARD;
        deck_bot->cards[i] = EMPTY_CARD;
    }
    
    // add coresponding cards to players
    const int split_offset = DECK_SIZE / 2;
    for(int j = 0; j < (DECK_SIZE / 2); j++){
        deck_player->cards[j] = deck->cards[j];
        deck_bot->cards[j] = deck->cards[j + split_offset];
    }
}

void play_card(Deck *deck, Table** table){}


// for testing
void print_deck(Deck *deck){
    for(int i = 0; i < DECK_SIZE; i++){
        if(deck->cards[i].actual_value < 11 && !(deck->cards[i].actual_value == 1)){
            printf("Card %d actual-value/value/suit: %d / %d / %s\n", i + 1, deck->cards[i].actual_value, deck->cards[i].value, deck->cards[i].suit);
        } else {
            printf("Card %d actual-value/value/suit: %d / %c / %s\n", i + 1, deck->cards[i].actual_value, deck->cards[i].value, deck->cards[i].suit);
        }
        //printf("Card state: %d\n", deck->cards[i].state);
    }
}