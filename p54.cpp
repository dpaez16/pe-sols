#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p054_poker.txt"
#define HAND_SIZE 5

typedef struct {
    char suit;
    int value;
} card;

typedef struct {
    card cards[HAND_SIZE];
} hand;

enum Rank {    
    high_card,
    one_pair,
    two_pair,
    three_of_a_kind,
    straight,
    flush,
    full_house,
    four_of_a_kind,
    straight_flush,
    royal_flush
};

unordered_map<string, int> VAL_MAP = {
    {"T", 10},
    {"J", 11},
    {"Q", 12},
    {"K", 13},
    {"A", 14}
};

card get_card(string & raw_card) {
    int size = raw_card.size();
    card c;

    char suit = raw_card[size - 1];
    string value = raw_card.substr(0, size - 1);
    int value_int = all_of(value.begin(), value.end(), ::isdigit) ? stoi(value) : VAL_MAP[value];

    c.suit = suit;
    c.value = value_int;

    return c;
}

pair<hand, hand> process_line(string & line) {
    hand p1, p2;

    stringstream ss(line);
    string raw_card;
    

    for (unsigned idx = 0; idx < HAND_SIZE; idx++) {
        getline(ss, raw_card, ' ');
        p1.cards[idx] = get_card(raw_card);
    }

    for (unsigned idx = 0; idx < HAND_SIZE; idx++) {
        getline(ss, raw_card, ' ');
        p2.cards[idx] = get_card(raw_card);
    }

    pair<hand, hand> game(p1, p2);
    return game;
}

vector<pair<hand, hand>> process_file() {
	string line;
	ifstream file;
	file.open(FILE_PATH);
	vector<pair<hand, hand>> games;

    while (getline(file, line)) {
	    pair<hand, hand> game = process_line(line);
        games.push_back(game);
    }

	file.close();
	return games;
}

bool card_lt(const card & left, const card & right) {
    if (left.value == right.value) {
        return left.suit < right.suit;
    }

    return left.value < right.value;
}

void print_cards(const card cards[HAND_SIZE]) {
    for (unsigned idx = 0; idx < HAND_SIZE; idx++) {
        cout << cards[idx].value << cards[idx].suit << ' ';
    }

    cout << endl;
}

Rank get_rank(hand & player) {
    // TODO
    sort(player.cards, player.cards + HAND_SIZE, card_lt);
    return royal_flush;
}

bool p1_winner(hand & p1, hand & p2) {
    Rank rank_p1 = get_rank(p1);
    Rank rank_p2 = get_rank(p2);

    if (rank_p1 != rank_p2) {
        return rank_p1 > rank_p2;
    }

    // TODO - tiebreaker
    return true;
}

int main() {
	vector<pair<hand, hand>> games = process_file();
    int count = 0;

    for (auto game : games) {
        hand p1 = game.first;
        hand p2 = game.second;

        if (p1_winner(p1, p2)) count++;
        break;
    }

    cout << count << endl;
	return 0;
}
