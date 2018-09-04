#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h> // rand
#include <time.h> // time

#include "da/da.h"
#include "da/da_util.h"

typedef enum {SUIT_SPADES, SUIT_DIAMONDS, SUIT_CLUBS, SUIT_HEARTS} suit_t;

typedef enum {
    FACE_A, FACE_2, FACE_3, FACE_4, FACE_5, FACE_6, FACE_7, FACE_8, FACE_9,
    FACE_10, FACE_J, FACE_Q, FACE_K,
} face_t;

typedef struct {
    face_t face;
    suit_t suit;
} card_t;

typedef struct {
    int pts;
    int aces;
} value_t;

typedef struct {
    da_t *hand;
    int bank;
    int bet;
    value_t val;
} player_t;

static const int NUM_COLORS = 2;
static const int NUM_FACES = FACE_K + 1;
static const int NUM_SUITS = SUIT_HEARTS + 1;
static const int NUM_PLAYERS = 2;

static const char *const COLOR_STRS[NUM_COLORS] = {"\e[0;2m", "\e[0;31m"};
static const char *const FACE_STRS[NUM_FACES] = {
    "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K",
};
static const char *const SUIT_STRS[NUM_SUITS] = {"♤", "♢", "♧", "♡"};

DA_DEF_HELPERS(card, card_t);

static da_t *deck = NULL;

static player_t players[NUM_PLAYERS] = {};
static player_t *dealer = &players[NUM_PLAYERS - 1];

da_t *new_deck(void)
{
    da_t *deck = da_new_card();
    da_setcap(deck, 52);
    for (face_t face = 0; face < NUM_FACES; ++face) {
        for (suit_t suit = 0; suit < NUM_SUITS; ++suit) {
            card_t card = {.face = face, .suit = suit};
            da_append_card(deck, card);
        }
    }
    return deck;
}

void print_card(card_t card)
{
    printf("%s%2s%s\e[0m", COLOR_STRS[card.suit % 2], FACE_STRS[card.face],
            SUIT_STRS[card.suit]);
}

void shuffle_cards(da_t *cards)
{
    for (int i = 0; i < da_len(cards); ++i) {
        int j = i + (rand() % da_len(cards) - i);
        card_t card_i = da_get_card(cards, i);
        da_set_card(cards, i, da_get_card(cards, j));
        da_set_card(cards, j, card_i);
    }
}

void print_cards(da_t *cards)
{
    for (int i = 0; i < da_len(cards); ++i) {
        print_card(da_get_card(cards, i));
        printf("  ");
    }
}

value_t get_value(da_t *hand)
{
    value_t value = {.pts = 0, .aces = 0};
    for (int i = 0; i < da_len(hand); ++i) {
        face_t face = da_get_card(hand, i).face;
        switch (face) {
        case FACE_A:
            value.pts += 11;
            value.aces++;
            break;
        case FACE_J:
        case FACE_Q:
        case FACE_K:
            value.pts += 10;
            break;
        default:
            value.pts += face + 1;
            break;
        }
    }
    while (value.pts > 21 && value.aces) {
        value.pts -= 10;
        value.aces--;
    }
    return value;
}

void print_player(const player_t *player)
{
    if (player == dealer) {
        printf("dealer:   ");
    } else {
        printf("player %d: ", (int)(player - players));
    }
    print_cards(player->hand);
    printf("[%d%s]", player->val.pts,
            player->val.aces && player->val.pts != 21 ? "s" : "");
    printf("\n");
}

void print_table(void)
{
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        print_player(&players[i]);
    }
}

void return_hand_to_deck(da_t *b)
{
    while (da_len(b)) {
        da_append_card(deck, da_pop_card(b));
    }
}

void deal_card(player_t *player)
{
    da_append_card(player->hand, da_pop_card(deck));
    player->val = get_value(player->hand);
    print_table();
}

#define busted(p) ((p)->val.pts > 21)
#define beats(p, q) (!busted(p) && (p)->val.pts > (q)->val.pts)

void play(void)
{
    while (1) {
        assert(da_len(deck) == 52);
        shuffle_cards(deck);
        for (int i = 0; i < NUM_PLAYERS - 1; ++i) {
            unsigned int bet = 0;
            int ret = 0;
            while (!ret || !bet || bet > players[i].bank) {
                bet = 0;
                printf("Bet [$%d]: ", players[i].bank);
                fpurge(stdin);
                if ((ret = scanf("%u", &bet)) == EOF) {
                    exit(0);
                }
            }
            players[i].bet = bet;
            players[i].bank -= bet;
            printf("Bet $%d\n", bet);
        }
        // deal
        for (int n = 0; n < 2; ++n) {
            for (int i = 0; i < NUM_PLAYERS; ++i) {
                deal_card(&players[i]);
            }
        }
        int stand = 0;
        for (int i = 0; i < NUM_PLAYERS - 1; ++i) {
            while (!stand && players[i].val.pts < 21) {
                char c;
                printf("Choice [s/h/q]: ");
                fpurge(stdin);
                scanf("%c", &c);
                switch (c) {
                case 's':
                    printf("You stand\n");
                    stand = 1;
                    break;
                case 'h':
                    printf("You hit\n");
                    deal_card(&players[i]);
                    break;
                case 'q':
                    exit(0);
                    break;
                }
            }
        }
        while (dealer->val.pts < 17) {
            deal_card(dealer);
        }
        for (int i = 0; i < NUM_PLAYERS - 1; ++i) {
            if (busted(&players[i]) || beats(dealer, &players[i])) {
                printf("player %d loses\n", i + 1);
            } else if (busted(dealer) || beats(&players[i], dealer)) {
                printf("player %d wins\n", i + 1);
                players[i].bank += players[i].bet * 2;
            } else {
                printf("player %d pushes\n", i + 1);
                players[i].bank += players[i].bet;
            }
        }
        for (int i = 0; i < NUM_PLAYERS; ++i) {
            return_hand_to_deck(players[i].hand);
        }
    }
}

void cleanup(void)
{
    if (deck) {
        da_free(deck);
    }
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        if (players[i].hand) {
            da_free(players[i].hand);
        }
    }
}

int main()
{
    atexit(cleanup);
    srand(time(NULL));
    deck = new_deck();
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        players[i].hand = da_new_card();
        players[i].bank = &players[i] == dealer ? INT_MAX : 300;
    }
    play();
    return 0;
}
