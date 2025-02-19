#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include "Pack.hpp"

Pack::Pack() {
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
    int index = 0;
    std::string line;
    while (getline(pack_input, line)) {
        std::istringstream iss(line); //error here
        Card c; 
        iss >> c; //error here
        cards[index] = c;
        index ++ 
    }
  }

bool Pack::empty() const {
    array<Card, 24> empty;
    fill(empty, empty + n, 0);
    if (cards == empty) { //error may have been fixed
        return true;
    };
}
