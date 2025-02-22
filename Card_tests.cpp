#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST (test_default){
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST (test_cards_with_2ctors){
    Card c1(ACE, CLUBS);
    Card c2(SEVEN, HEARTS);
    ASSERT_EQUAL(ACE, c1.get_rank());
    ASSERT_EQUAL(SEVEN, c2.get_suit());
    ASSERT_EQUAL(CLUBS, c1.get_suit());
    ASSERT_EQUAL(HEARTS, c2.get_suit());
}

TEST (test_is_face_or_ace){
    Card c1(ACE, DIAMONDS);
    Card c2(JACK, HEARTS);
    Card c3(KING, SPADES);
    Card c4(QUEEN, CLUBS);
    Card c5(EIGHT, HEARTS);
    ASSERT_EQUAL(true, c1.is_face_or_ace());
    ASSERT_EQUAL(true, c2.is_face_or_ace());
    ASSERT_EQUAL(true, c3.is_face_or_ace());
    ASSERT_EQUAL(true, c4.is_face_or_ace());
    ASSERT_EQUAL(false, c5.is_face_or_ace());
}

TEST(test_is_right_bower){
    Card c1(JACK, DIAMONDS);
    Card c2(EIGHT, DIAMONDS);
    Card c3(TWO, SPADES);
    Card c4(JACK, HEARTS);
    ASSERT_EQUAL(true, c1.is_right_bower(DIAMONDS));
    ASSERT_EQUAL(false, c2.is_right_bower(DIAMONDS));
    ASSERT_EQUAL(false, c3.is_right_bower(DIAMONDS));
    ASSERT_EQUAL(false, c4.is_right_bower(DIAMONDS));
}

TEST(test_is_left_bower){
    Card c1(JACK, DIAMONDS);
    Card c2(EIGHT, DIAMONDS);
    Card c3(TWO, HEARTS);
    Card c4(JACK, HEARTS);
    ASSERT_EQUAL(false, c1.is_left_bower(DIAMONDS));
    ASSERT_EQUAL(false, c2.is_left_bower(DIAMONDS));
    ASSERT_EQUAL(false, c3.is_left_bower(DIAMONDS));
    ASSERT_EQUAL(true, c4.is_left_bower(DIAMONDS));
}

TEST(test_is_trump){
    Card c1(ACE, CLUBS);
    Card c2(SEVEN, HEARTS);
    Card c3(JACK, SPADES);
    ASSERT_EQUAL(false, c1.is_trump(DIAMONDS));
    ASSERT_EQUAL(true, c2.is_trump(HEARTS));
    ASSERT_EQUAL(true, c3.is_trump(CLUBS));
}

TEST(test_Suit_next){
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
}

TEST(test_Card_less){
    Card c1(QUEEN, DIAMONDS);
    Card c2(EIGHT, HEARTS);
    Card c3(JACK, CLUBS);
    Card c4(JACK, SPADES);
    Card c5(JACK, HEARTS);
    Card c6(ACE, DIAMONDS);
    Card c7(FOUR, HEARTS);
    Card c8(QUEEN, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c2, c1, SPADES));
    ASSERT_EQUAL(true, Card_less(c4, c3, CLUBS));
    ASSERT_EQUAL(true, Card_less(c6, c5, DIAMONDS));
    ASSERT_EQUAL(true, Card_less(c8, c7, HEARTS));
}

TEST(test_CARD_less_2){
    Card c1(EIGHT, HEARTS);
    Card c2(JACK, DIAMONDS);
    Card led_card(FOUR, HEARTS);
    ASSERT_EQUAL(false, Card_less(c1, c2, led_card, CLUBS));
    ASSERT_EQUAL(true, Card_less(c1, c2, led_card, DIAMONDS));
    ASSERT_EQUAL(true, Card_less(c1, c2, led_card, HEARTS));
}

TEST(test_operators){
    Card c1(ACE, SPADES);
    Card c2(QUEEN, HEARTS);
    Card c3(QUEEN, DIAMONDS);
    ASSERT_EQUAL(true, c2 < c1);
    ASSERT_EQUAL(true, c1 > c2);
    ASSERT_EQUAL(true, c2 >= c3);
    ASSERT_EQUAL(true, c2 == c3);
    ASSERT_EQUAL(true, c1 != c2);
}

TEST_MAIN()
