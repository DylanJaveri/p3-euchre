#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include "Pack.hpp"
#include <sstream>

Pack::Pack() {
    next = 0;
    int index = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        Suit suit = static_cast<Suit>(s);
        for (int r = 7; r < 13; ++r) {
            Rank rank = static_cast<Rank>(r);
            cards[index] = Card(rank, suit);
            index++;
        }
    }
}

  Pack::Pack(std::istream& pack_input) {
    next = 0;
    int index = 0;
    std::string line;
    while (getline(pack_input, line)) {
        std::istringstream iss(line);
        Card c; 
        iss >> c;
        cards[index] = c;
        index ++;
    }
  }

 Card Pack::deal_one() {
     Card dealt = cards[next];
     next++;
     return dealt;
 }

void Pack::shuffle() {
    std::array<Card, PACK_SIZE> news;
    for (int times = 0; times < 7; times++) {
        int half = PACK_SIZE / 2;
        int j = 0;
        for (int i = 0; i < half; i++) {
            news[j] = cards[i + half];
            news[j + 1] = cards[i];
            j+= 2;
        }
    cards = news;
    }
    reset();
}

void Pack::reset() {
    next = 0;
}

bool Pack::empty() const {
    return(next == PACK_SIZE);
}
