#include <bits/stdc++.h>

using namespace std;

#define DICE_ORDER 4
#define N_ITERS 100
#define TOP_N 3

class Board {
public:
    Board() {
        this->squares = {
            "GO",
            "A1",
            "CC1",
            "A2",
            "T1",
            "R1",
            "B1",
            "CH1",
            "B2",
            "B3",
            "JAIL",
            "C1",
            "U1",
            "C2",
            "C3",
            "R2",
            "D1",
            "CC2",
            "D2",
            "D3",
            "FP",
            "E1",
            "CH2",
            "E2",
            "E3",
            "R3",
            "F1",
            "F2",
            "U2",
            "F3",
            "G2J",
            "G1",
            "G2",
            "CC3",
            "G3",
            "R4",
            "CH3",
            "H1",
            "T2",
            "H2"
        };
    }

    unsigned size() {
        return this->squares.size();
    }

    string operator[](unsigned idx) {
        return this->squares[idx];
    }

    unsigned operator[](string key) {
        for (unsigned i = 0; i < this->size(); i++) {
            if (this->operator[](i) == key) return i;
        }

        return this->size();
    }

    bool is_chance(unsigned idx) {
        return this->operator[](idx).substr(0, 2) == "CH";
    }

    bool is_community_chest(unsigned idx) {
        return this->operator[](idx).substr(0, 2) == "CC";
    }

    bool is_go_to_jail(unsigned idx) {
        return this->operator[](idx) == "G2J";
    }

    bool is_special_spot(unsigned idx) {
        return this->is_chance(idx) || this->is_community_chest(idx);
    }

    unsigned go_to_next_r(unsigned idx) {
        while (this->operator[](idx).substr(0, 1) != "R") {
            idx = (idx + 1) % this->size();
        }

        return idx;
    }

    unsigned go_to_next_u(unsigned idx) {
        while (this->operator[](idx).substr(0, 1) != "U") {
            idx = (idx + 1) % this->size();
        }

        return idx;
    }

    vector<pair<unsigned, double>> get_community_chest_cards(unsigned idx) {
        vector<unsigned> additional_cards(14, idx);
        vector<unsigned> initial_cards = {
            this->operator[]("GO"),
            this->operator[]("JAIL")
        };

        vector<pair<unsigned, double>> cards;
        double n = additional_cards.size() + initial_cards.size();
        double p = 1.0 / n;
        
        for (auto card : initial_cards) {
            cards.push_back({card, p});
        }

        for (auto card : additional_cards) {
            cards.push_back({card, p});
        }

        return cards;
    }

    vector<pair<unsigned, double>> get_chance_cards(unsigned idx) {
        unsigned next_r = this->go_to_next_r(idx);
        unsigned next_u = this->go_to_next_u(idx);
        vector<unsigned> additional_cards(6, idx);
        vector<unsigned> initial_cards = {
            this->operator[]("GO"),
            this->operator[]("JAIL"),
            this->operator[]("C1"),
            this->operator[]("E3"),
            this->operator[]("H2"),
            this->operator[]("R1"),
            next_r,
            next_r,
            next_u
        };

        double n = initial_cards.size() + additional_cards.size() + 1;
        double p = 1.0 / n;
        vector<pair<unsigned, double>> cards;

        for (auto card : initial_cards) {
            cards.push_back({card, p});
        }

        for (auto card : additional_cards) {
            cards.push_back({card, p});
        }

        idx = idx >= 3 ? idx - 3 : this->size() - (3 - idx);
        if (this->is_community_chest(idx)) {
            vector<pair<unsigned, double>> cc_cards = this->get_community_chest_cards(idx);
            for (auto cardProbPair : cc_cards) {
                cards.push_back({cardProbPair.first, p * cardProbPair.second});
            }
        } else {
            cards.push_back({idx, p});
        }

        return cards;
    }

private:
    vector<string> squares;
};

vector<double> get_dice_prob_dist(unsigned dice_order, unsigned n) {
    vector<double> prob_dist(n, 0);

    for (unsigned d1 = 1; d1 <= dice_order; d1++) {
        for (unsigned d2 = 1; d2 <= dice_order; d2++) {
            prob_dist[d1 + d2] += 1;
        }
    }

    double total_n = dice_order * dice_order;

    for (unsigned i = 0; i < prob_dist.size(); i++) {
        prob_dist[i] /= total_n;
    }

    return prob_dist;
}

unordered_map<unsigned, vector<double>> get_pr_special_to_spot(Board & board) {
    unordered_map<unsigned, vector<double>> prob_dist;

    for (unsigned idx = 0; idx < board.size(); idx++) {
        if (board.is_go_to_jail(idx)) {
            prob_dist[idx] = vector<double>(board.size(), 0);
            prob_dist[idx][board["JAIL"]] = 1;
            continue;
        }

        if (!board.is_special_spot(idx)) continue;

        prob_dist[idx] = vector<double>(board.size(), 0);
        vector<pair<unsigned, double>> cards = board.is_chance(idx) ? board.get_chance_cards(idx) : board.get_community_chest_cards(idx);

        for (auto cardProbPair : cards) {
            unsigned card = cardProbPair.first;
            double p = cardProbPair.second;
            
            prob_dist[idx][card] += p;
        }
    }

    return prob_dist;
}

void transpose(double ** M, unsigned n) {
    double ** M_copy = (double **)calloc(n, sizeof(double *));

    for (unsigned i = 0; i < n; i++) {
        M_copy[i] = (double *)calloc(n, sizeof(double));

        for (unsigned j = 0; j < n; j++) {
            M_copy[i][j] = M[i][j];
        }
    }

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            M[j][i] = M_copy[i][j];
        }
    }

    for (unsigned i = 0; i < n; i++) {
        free(M_copy[i]);
    }

    free(M_copy);
}

void iterate_power_iteration(double ** M, double * x, unsigned n) {
    double * x_next = (double *)calloc(n, sizeof(double));
    double norm = 0;

    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            x_next[i] += x[j] * M[i][j];
        }

        norm += abs(x_next[i]);
    }

    for (unsigned i = 0; i < n; i++) {
        x[i] = x_next[i] / norm;
    }

    free(x_next);
}

unsigned get_dice_roll(unsigned src, unsigned dst, unsigned n) {
    return dst >= src ? (dst - src) % n : n - (src - dst);
}

string get_ans(vector<unsigned> & spots, unsigned top_n) {
    string ans = "";

    for (unsigned i = 0; i < top_n; i++) {
        if (spots[i] < 10) {
            ans += "0";
        }

        ans += to_string(spots[i]);
    }

    return ans;
}

int main() {
    Board board;

    unsigned n = board.size();
    vector<double> pr_dice_roll = get_dice_prob_dist(DICE_ORDER, board.size());
    unordered_map<unsigned, vector<double>> pr_special_to_spot = get_pr_special_to_spot(board);

    // construct markov matrix
    double ** M = (double **)calloc(n, sizeof(double *));
    for (unsigned i = 0; i < n; i++) {
        M[i] = (double *)calloc(n, sizeof(double));

        for (unsigned j = 0; j < n; j++) {
            unsigned dice_roll = get_dice_roll(i, j, n);
            M[i][j] = pr_dice_roll[dice_roll];

            for (auto pair : pr_special_to_spot) {
                unsigned s = pair.first;
                M[i][j] += pr_dice_roll[get_dice_roll(i, s, n)] * pair.second[j];
            }

            if (pr_special_to_spot.find(j) != pr_special_to_spot.end()) {
                M[i][j] -= pr_dice_roll[dice_roll];
            }
        }
    }

    transpose(M, n);
    double * x = (double *)calloc(n, sizeof(double));
    x[0] = 1;

    // power iteration to get steady state
    for (unsigned it = 0; it < N_ITERS; it++) {
        iterate_power_iteration(M, x, n);
    }

    vector<unsigned> spots(n);
    for (unsigned i = 0; i < n; i++) {
        spots[i] = i;
    }

    sort(spots.begin(), spots.end(), [&](unsigned const & i, unsigned const & j) {
        return x[i] > x[j];
    });

    string ans = get_ans(spots, TOP_N);
    cout << ans << endl;

    for (unsigned i = 0; i < n; i++) {
        free(M[i]);
    }

    free(M);
    free(x);
    return 0;
}