#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank corresponding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit corresponding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator< done
//   operator<= done
//   operator> done
//   operator>= done
//   operator== done
//   operator!= done

Card::Card() {
  rank = TWO;
  suit = SPADES;
}

Card::Card(Rank rank_in, Suit suit_in) {
  rank = rank_in;
  suit = suit_in;
}

Rank Card::get_rank() const {
  return rank;
}

 Suit Card::get_suit() const {
  return suit;
 }

Suit Card::get_suit(Suit trump) const {
  if (is_left_bower(trump)) {
        return trump; // Left Bower is also considered trump
    }
    return suit; // Otherwise, return the card's normal suit
}

bool Card::is_face_or_ace() const {
    return rank == JACK || rank == QUEEN | rank == KING || rank == ACE;
  }

  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(Suit trump) const {
    return (suit == trump && rank == JACK);
  }

  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(Suit trump) const {
    Suit next_suit = Suit_next(trump);
    return (suit == next_suit && rank == JACK);
  }

  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(Suit trump) const {
    return suit == trump || is_left_bower(trump);
  }

  Suit Suit_next(Suit suit) {
    if (suit == SPADES){
      suit = CLUBS;
    }
    else if (suit == CLUBS){
      suit = SPADES;
    }
    else if (suit == HEARTS){
      suit = DIAMONDS;
    }
    else{
      suit = HEARTS;
    }
    return suit;
}

bool Card_less(const Card &a, const Card &b, Suit trump) {
  //Suit suitA = a.get_suit();
  //Suit suitB = b.get_suit();
  //Rank rankA = a.get_rank();
  //Rank rankB = b.get_rank();
  if (b.is_trump(trump) && !a.is_trump(trump)) {
    return true;
  }
  else if (b.is_right_bower(trump)){
    return true;
  }
  else if (b.is_left_bower(trump) && !a.is_right_bower(trump)){
    return true;
  }
  else if (b.is_trump(trump) && a.is_trump(trump) && 
  !a.is_left_bower(trump) && a > b) {
      return true;
  }
  else if (!b.is_trump(trump) && !a.is_trump(trump)
   && a>b) {
    return true;
  }
  //else if ((!b.is_trump(trump) && !a.is_trump(trump) 
  //&& rankA == rankB && suitB > suitA)) {
  //  return true;
  //}
  else {
    return false;
  }
  
  /*else if (rankB > rankA && a.get_suit() != trump && !a.is_left_bower(trump)) {
    return true;
  }
  else if (rankA == rankB && suitB > suitA){
      return true;
  }
  else {
    return false;
  }*/
}

bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {
  Suit suitA = a.get_suit();
  Suit suitB = b.get_suit();
  Suit led_Suit = led_card.get_suit();
  //Rank rankA = a.get_rank();
  //Rank rankB = b.get_rank();
  if (b.is_trump(trump) && !a.is_trump(trump)) {
    return true;
  }
  else if (b.is_right_bower(trump)){
    return true;
  }
  else if (b.is_left_bower(trump) && !a.is_right_bower(trump)){
    return true;
  }
  else if (b.is_trump(trump) && a.is_trump(trump) && 
  !a.is_left_bower(trump) && a > b) {
      return true;
  }
  else if (!b.is_trump(trump) && !a.is_trump(trump) && suitB == led_Suit 
  && suitA != led_Suit) {
    return true;
  }
  else if (!b.is_trump(trump) && !a.is_trump(trump)
   && a>b) {
    return true;
  }
  //else if ((!b.is_trump(trump) && !a.is_trump(trump) 
  //&& rankA == rankB && suitB > suitA)) {
  //  return true;
  //}
  else {
    return false;
  }
  
  /*else if (rankB > rankA && a.get_suit() != trump && !a.is_left_bower(trump)) {
    return true;
  }
  else if (rankA == rankB && suitB > suitA){
      return true;
  }
  else {
    return false;
  }*/
}
std::istream & operator>>(std::istream &is, Card &card) {
  string rank_str, suit_str, of;
  is >> rank_str >> of >> suit_str;
  Rank rank = string_to_rank(rank_str);
  Suit suit = string_to_suit(suit_str);
  card = Card(rank, suit); 
  return is;
}


std::ostream & operator<<(std::ostream &os, const Card &card) {
  os << card.get_rank() << " of " << card.get_suit();
  return os;
}

bool operator<(const Card &lhs, const Card &rhs) {
  Suit suitA = lhs.get_suit();
  Suit suitB = rhs.get_suit();
  Rank rankA = lhs.get_rank();
  Rank rankB = rhs.get_rank();
  if (suitA < suitB) {
    return true;
  }
  else if (rankA < rankB) {
    return true;
  }
  else {
    return false;
  }
}

bool operator==(const Card &lhs, const Card &rhs) {
  Suit suitA = lhs.get_suit();
  Suit suitB = rhs.get_suit();
  Rank rankA = lhs.get_rank();
  Rank rankB = rhs.get_rank();
  if (suitA == suitB && rankA == rankB) {
    return true;
  }
  else {
    return false;
  }
}

bool operator<=(const Card &lhs, const Card &rhs) {
  return lhs < rhs || lhs == rhs;
}
bool operator>(const Card &lhs, const Card &rhs) {
  return !(lhs <= rhs);
}
bool operator>=(const Card &lhs, const Card &rhs) {
  return !(lhs < rhs);
}
bool operator!=(const Card &lhs, const Card &rhs) {
  return !(lhs == rhs);
}
