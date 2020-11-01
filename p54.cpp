#include <bits/stdc++.h>

using namespace std;

#define FILE_PATH "files/p054_poker.txt"

typedef struct {
    char suit;
    char value;
} card;

typedef struct {
    card cards[5];
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

pair<hand, hand> process_line(string & line) {
    hand p1, p2;

    stringstream ss(line);
    string raw_card;
    

    for (unsigned idx = 0; idx < 5; idx++) {
        getline(ss, raw_card, ' ');

        char value = raw_card[0];
        char suit = raw_card[1];

        p1.cards[idx].value = value;
        p1.cards[idx].suit = suit;
    }

    for (unsigned idx = 0; idx < 5; idx++) {
        getline(ss, raw_card, ' ');

        char value = raw_card[0];
        char suit = raw_card[1];

        p2.cards[idx].value = value;
        p2.cards[idx].suit = suit;
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

Rank get_rank(hand & player) {
    // TODO
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
    }

    cout << count << endl;
	return 0;
}
