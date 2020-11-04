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
    flush_,
    full_house,
    four_of_a_kind,
    straight_flush,
    royal_flush
};

unordered_map<char, int> VAL_MAP = {
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};

card get_card(string & raw_card) {
    card c;

    char suit = raw_card[1];
    char value = raw_card[0];
    int value_int = isdigit(value) ? value - '0' : VAL_MAP[value];

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

bool same_value(const card cards[HAND_SIZE], unsigned i, unsigned j) {
    int value = cards[i].value;

    for (unsigned idx = i; idx <= j; idx++) {
        if (cards[idx].value != value) return false;
    }

    return true;
}

bool same_suit(const card cards[HAND_SIZE], unsigned i, unsigned j) {
    char suit = cards[i].suit;

    for (unsigned idx = i; idx <= j; idx++) {
        if (cards[idx].suit != suit) return false;
    }

    return true;
}

bool is_royal_flush(const card cards[HAND_SIZE]) {
    char suit = cards[0].suit;

    for (unsigned idx = 0; idx < HAND_SIZE; idx++) {
        int value = 10 + idx;

        if (cards[idx].suit != suit) return false;
        if (cards[idx].value != value) return false;
    }

    return true;
}

bool is_straight_flush(const card cards[HAND_SIZE]) {
    char suit = cards[0].suit;

    for (unsigned idx = 1; idx < HAND_SIZE; idx++) {
        if (cards[idx].value - cards[idx - 1].value != 1) return false;
        if (cards[idx].suit != suit) return false;
    }

    return true;
}

bool is_four_of_a_kind(const card cards[HAND_SIZE]) {
    return same_value(cards, 0, 3) || same_value(cards, 1, 4);
}

bool is_full_house(const card cards[HAND_SIZE]) {
    return  (same_value(cards, 0, 2) && same_value(cards, 3, 4)) || \
            (same_value(cards, 0, 1) && same_value(cards, 2, 4));
}

bool is_flush(const card cards[HAND_SIZE]) {
    return same_suit(cards, 0, 4);
}

bool is_straight(const card cards[HAND_SIZE]) {
    for (unsigned idx = 1; idx < HAND_SIZE; idx++) {
        if (cards[idx].value - cards[idx - 1].value != 1) return false;
    }

    return true;
}

bool is_three_of_a_kind(const card cards[HAND_SIZE]) {
    return (
        same_value(cards, 0, 2) || 
        same_value(cards, 1, 3) || 
        same_value(cards, 2, 4)
    );
}

bool is_two_pair(const card cards[HAND_SIZE]) {
    for (unsigned i = 0; i <= 1; i++) {
        for (unsigned j = i + 2; j + 1 < HAND_SIZE; j++) {
            if (same_value(cards, i, i + 1) && same_value(cards, j, j + 1)) return true;
        }
    }

    return false;
}

bool is_one_pair(const card cards[HAND_SIZE]) {
    for (unsigned idx = 1; idx < HAND_SIZE; idx++) {
        if (cards[idx - 1].value == cards[idx].value) return true;
    }

    return false;
}

Rank get_rank(hand & player) {
    sort(player.cards, player.cards + HAND_SIZE, card_lt);
    
    if (is_royal_flush(player.cards)) {
        return royal_flush;
    } else if (is_straight_flush(player.cards)) {
        return straight_flush;
    } else if (is_four_of_a_kind(player.cards)) {
        return four_of_a_kind;
    } else if (is_full_house(player.cards)) {
        return full_house;
    } else if (is_flush(player.cards)) {
        return flush_;
    } else if (is_straight(player.cards)) {
        return straight;
    } else if (is_three_of_a_kind(player.cards)) {
        return three_of_a_kind;
    } else if (is_two_pair(player.cards)) {
        return two_pair;
    } else if (is_one_pair(player.cards)) {
        return one_pair;
    } else {
        return high_card;
    }
}

bool high_card_tiebreaker(hand & p1, hand & p2) {
    for (int idx = HAND_SIZE - 1; idx >= 0; idx--) {
        if (p1.cards[idx].value == p2.cards[idx].value) continue;

        return p1.cards[idx].value > p2.cards[idx].value;
    }

    return false;
}

bool high_card_tiebreaker_vec(vector<card> & p1_cards, vector<card> & p2_cards) {
    for (unsigned idx = 0; idx < HAND_SIZE; idx++) {
        if (p1_cards[idx].value == p2_cards[idx].value) continue;

        return p1_cards[idx].value > p2_cards[idx].value;
    }

    return false;
}

vector<card> decomp_one_pair(const card cards[HAND_SIZE]) {
    int pair_value = 0;
    vector<card> remaining_cards;

    for (unsigned idx = 1; idx < HAND_SIZE; idx++) {
        if (cards[idx].value == cards[idx - 1].value) {
            pair_value = cards[idx].value;
            remaining_cards.push_back(cards[idx]);
            break;
        }
    }

    for (int idx = HAND_SIZE - 1; idx >= 0; idx--) {
        if (cards[idx].value == pair_value) continue;

        remaining_cards.push_back(cards[idx]);
    }

    return remaining_cards;
}

vector<card> decomp_two_pair(const card cards[HAND_SIZE]) {
    pair<int, int> pair_vals(0, 0);
    vector<card> remaining_cards;

    for (unsigned i = 0; i <= 1; i++) {
        for (unsigned j = i + 2; j + 1 < HAND_SIZE; j++) {
            if (same_value(cards, i, i + 1) && same_value(cards, j, j + 1)) {
                pair_vals.first = max(cards[i].value, cards[j].value);
                pair_vals.second = min(cards[i].value, cards[j].value);

                card first_card = pair_vals.first == cards[i].value ? cards[i] : cards[j];
                card second_card = first_card.value == cards[i].value ? cards[j] : cards[i];

                remaining_cards.push_back(first_card);
                remaining_cards.push_back(second_card);
                break;
            }
        }
    }

    for (int idx = HAND_SIZE - 1; idx >= 0; idx--) {
        if (cards[idx].value == pair_vals.first || \
            cards[idx].value == pair_vals.second) {
                continue;
        }

        remaining_cards.push_back(cards[idx]);
    }

    return remaining_cards;
}

vector<card> decomp_three_of_a_kind(const card cards[HAND_SIZE]) {
    int card_val;
    vector<card> remaining_cards;

    if (same_value(cards, 0, 2)) {
        card_val = cards[0].value;
        remaining_cards.push_back(cards[0]);
    } else if (same_value(cards, 1, 3)) {
        card_val = cards[1].value;
        remaining_cards.push_back(cards[1]);
    } else {
        card_val = cards[2].value;
        remaining_cards.push_back(cards[2]);
    }

    for (int idx = HAND_SIZE - 1; idx >= 0; idx--) {
        if (cards[idx].value == card_val) continue;

        remaining_cards.push_back(cards[idx]);
    }

    return remaining_cards;
}

vector<card> decomp_full_house(const card cards[HAND_SIZE]) {
    pair<int, int> full_house_vals(0, 0);
    vector<card> remaining_cards;

    if (same_value(cards, 0, 2) && same_value(cards, 3, 4)) {
        full_house_vals.first = cards[0].value;
        full_house_vals.second = cards[3].value;

        card first_card = cards[0];
        card second_card = cards[3];

        remaining_cards.push_back(first_card);
        remaining_cards.push_back(second_card);
    } else {
        full_house_vals.first = cards[2].value;
        full_house_vals.second = cards[0].value;

        card first_card = cards[2];
        card second_card = cards[0];

        remaining_cards.push_back(first_card);
        remaining_cards.push_back(second_card);
    }

    return remaining_cards;
}

vector<card> decomp_four_of_a_kind(const card cards[HAND_SIZE]) {
    int card_val;
    vector<card> remaining_cards;

    if (same_value(cards, 0, 4)) {
        card_val = cards[0].value;
        remaining_cards.push_back(cards[0]);
    } else {
        card_val = cards[1].value;
        remaining_cards.push_back(cards[1]);
    }

    for (int idx = HAND_SIZE - 1; idx >= 0; idx--) {
        if (cards[idx].value == card_val) continue;

        remaining_cards.push_back(cards[idx]);
    }

    return remaining_cards;
}

bool one_pair_tiebreaker(hand & p1, hand & p2) {
    vector<card> decomp_p1 = decomp_one_pair(p1.cards);
    vector<card> decomp_p2 = decomp_one_pair(p2.cards);

    return high_card_tiebreaker_vec(decomp_p1, decomp_p2);
}

bool two_pair_tiebreaker(hand & p1, hand & p2) {
    vector<card> decomp_p1 = decomp_two_pair(p1.cards);
    vector<card> decomp_p2 = decomp_two_pair(p2.cards);
    
    return high_card_tiebreaker_vec(decomp_p1, decomp_p2);
}

bool three_of_a_kind_tiebreaker(hand & p1, hand & p2) {
    vector<card> decomp_p1 = decomp_three_of_a_kind(p1.cards);
    vector<card> decomp_p2 = decomp_three_of_a_kind(p2.cards);

    return high_card_tiebreaker_vec(decomp_p1, decomp_p2);
}

bool full_house_tiebreaker(hand & p1, hand & p2) {
    vector<card> decomp_p1 = decomp_full_house(p1.cards);
    vector<card> decomp_p2 = decomp_full_house(p2.cards);

    return high_card_tiebreaker_vec(decomp_p1, decomp_p2);
}

bool four_of_a_kind_tiebreaker(hand & p1, hand & p2) {
    vector<card> decomp_p1 = decomp_four_of_a_kind(p1.cards);
    vector<card> decomp_p2 = decomp_four_of_a_kind(p2.cards);

    return high_card_tiebreaker_vec(decomp_p1, decomp_p2);
}

bool handle_tiebreaker(hand & p1, hand & p2, Rank rank) {
    switch (rank) {
        case high_card:
            return high_card_tiebreaker(p1, p2);
        case one_pair:
            return one_pair_tiebreaker(p1, p2);
        case two_pair:
            return two_pair_tiebreaker(p1, p2);
        case three_of_a_kind:
            return three_of_a_kind_tiebreaker(p1, p2);
        case straight:
            return high_card_tiebreaker(p1, p2);
        case flush_:
            return high_card_tiebreaker(p1, p2);
        case full_house:
            return full_house_tiebreaker(p1, p2);
        case four_of_a_kind:
            return four_of_a_kind_tiebreaker(p1, p2);
        case straight_flush:
            return high_card_tiebreaker(p1, p2);
        default: // royal_flush
            return true;
    }
}

bool p1_winner(hand & p1, hand & p2) {
    Rank rank_p1 = get_rank(p1);
    Rank rank_p2 = get_rank(p2);

    if (rank_p1 != rank_p2) {
        return rank_p1 > rank_p2;
    }

    return handle_tiebreaker(p1, p2, rank_p1);
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
