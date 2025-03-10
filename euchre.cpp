#include <iostream>
#include <Pack.hpp>
#include <Card.hpp>
#include <Player.hpp>
#include <string>
using namespace std;

class Game {
        public:
            Game(char **argv) { //take in players, points to win, etc...
                pointsA = 0;
                pointsB = 0;
                int index = 0;
                dealer = 0;
                for (int i = 4; i > 12; i + 2) {
                    players[index] = Player_factory(argv[i], argv[i + 1]);
                    index++;
                }
                POINTS_TO_WIN = atoi(argv[3]);
                if (argv[2] == "shuffle") {
                    shuffle_or = true;
                }
                
                char *pack_filename = argv[1];
                Pack pack(std::ifstream *pack_filename);
            }

            void play() {
                while (pointsA != POINTS_TO_WIN && pointsB != POINTS_TO_WIN) {
                    if (shuffle_or == true) {
                        shuffle();
                    }
                    deal(dealer);
                    make_trump();
                    while (tricksA + tricksB < 5) {
                        play_hand();
                    }

                }
                if (pointsA >= 100) {
                    cout << players[0]->get_name() << " and " << players[2]->get_name() << " win!" << endl;
                }
                else {
                    cout << players[1]->get_name() << " and " << players[3]->get_name() << " win!" << endl;
                }
                for (size_t i = 0; i < players.size(); ++i) {
                    delete players[i];
                }
            }

        private:
            std::vector<Player*> players;
            Pack pack;
            int POINTS_TO_WIN;
            int dealer;
            int order_up_team;
            int pointsA;
            int pointsB;
            int tricksA;
            int tricksB;
            bool shuffle_or = false;
            bool trump = false;
            Suit suit_trump;

            void shuffle() {
                pack.shuffle();
            }
            void deal(int dealer) {
                //3
                players[(dealer + 1)%4]->add_card(pack.deal_one());
                players[(dealer + 1)%4]->add_card(pack.deal_one());
                players[(dealer + 1)%4]->add_card(pack.deal_one());
                //2
                players[(dealer + 2)%4]->add_card(pack.deal_one());
                players[(dealer + 2)%4]->add_card(pack.deal_one());
                //3
                players[(dealer + 3)%4]->add_card(pack.deal_one());
                players[(dealer + 3)%4]->add_card(pack.deal_one());
                players[(dealer + 3)%4]->add_card(pack.deal_one());
                //2
                players[dealer]->add_card(pack.deal_one());
                players[dealer]->add_card(pack.deal_one());
                //2
                players[(dealer + 1)%4]->add_card(pack.deal_one());
                players[(dealer + 1)%4]->add_card(pack.deal_one());
                //3
                players[(dealer + 2)%4]->add_card(pack.deal_one());
                players[(dealer + 2)%4]->add_card(pack.deal_one());
                players[(dealer + 2)%4]->add_card(pack.deal_one());
                //2
                players[(dealer + 3)%4]->add_card(pack.deal_one());
                players[(dealer + 3)%4]->add_card(pack.deal_one());
                //3
                players[dealer]->add_card(pack.deal_one());
                players[dealer]->add_card(pack.deal_one());
                players[dealer]->add_card(pack.deal_one());
            }
            void make_trump(/* ... */) {
                cout << "Hand 0" << endl;
                cout << players[dealer]->get_name() << " deals" << endl;
                Card upcard = pack.deal_one();
                cout << upcard.get_rank() << " of " << upcard.get_suit() << " turned up";
                for (int i = 1; i < 5; i++) {
                    if (i != 4) {
                        trump = players[(dealer + i)%4]->make_trump(upcard, false, 1, suit_trump);
                        if (trump) {
                            if ((dealer + i)%2) {
                                order_up_team = 1;
                            }
                            else {
                                order_up_team = 2;
                            }
                            cout << players[(dealer + i)%4]->get_name() << " orders up " << upcard.get_suit() << endl;
                            players[dealer]->add_and_discard(upcard);
                            return;
                        }
                        else {
                            cout << players[(dealer + i)%4]->get_name() << " passes" << endl;
                        }
                    }
                    else {
                        trump = players[dealer]->make_trump(upcard, true, 1, suit_trump);
                        if (trump) {
                            if (dealer%2) {
                                order_up_team = 1;
                            }
                            else {
                                order_up_team = 2;
                            }
                            cout << players[dealer]->get_name() << " orders up " << upcard.get_suit() << endl;
                            players[dealer]->add_and_discard(upcard);
                            return;
                        }
                        else {
                            cout << players[dealer]->get_name() << " passes" << endl;
                        }
                    }
                }
                for (int i = 1; i < 5; i++) {
                    if (i != 4) {
                        trump = players[(dealer + i)%4]->make_trump(upcard, false, 2, suit_trump);
                        if (trump) {
                            if ((dealer + i)%2) {
                                order_up_team = 1;
                            }
                            else {
                                order_up_team = 2;
                            }
                            cout << players[(dealer + i)%4]->get_name() << " orders up " << Suit_next(upcard.get_suit())<< endl;
                            return;
                        }
                        else {
                            cout << players[(dealer + i)%4]->get_name() << " passes" << endl;
                        }
                    }
                    else {
                        trump = players[dealer]->make_trump(upcard, true, 2, suit_trump);
                        if (dealer%2) {
                                order_up_team = 1;
                            }
                        else {
                                order_up_team = 2;
                            }
                        cout << players[dealer]->get_name() << " orders up " << Suit_next(upcard.get_suit()) << endl;
                        players[dealer]->add_and_discard(upcard);
                        return;
                    }
                }
            }

            void play_hand(/* ... */);
            void scoring(int order_up_team) {
                if (order_up_team == 1) {
                    if (tricksA == 5) {
                        cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
                        cout << "march!" << endl;
                        pointsA += 2;
                    }
                    else if (tricksA == 3 || tricksA == 4) {
                        cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
                        pointsA += 1;
                    }
                    else {
                        cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
                        cout << "euchred!" << endl;
                        pointsB += 2;
                    }
                }
                if (order_up_team == 2) {
                    if (tricksB == 5) {
                        cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
                        cout << "march!" << endl;
                        pointsB += 2;
                    }
                    else if (tricksB == 3 || tricksB == 4) {
                        cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
                        pointsB += 1;
                    }
                    else {
                        cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
                        cout << "euchred!" << endl;
                        pointsA += 2;
                    }
                }
            }
    };

int main (int argc, char **argv) {
  cout << "Hello World!\n";
  if (!(argc == 12 || argv[3] < "100" || argv[3] > "1" || argv[2] == "shuffle" || argv[2] == "shuffle")) {
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
     return 1;
  }
  
  for (int i = 6; i = 12; i+2) {
    if (argv[i] != "simple" && argv[i] != "human") {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
  }
    
    string file_in = argv[1];
    ifstream pack_file(file_in);
    if (! pack_file.open()) {
        cout << "Error opening " << file_in << endl; 
    }
    //need to fix error line

    Game game(argv);
    game.play();
}

void Game::play_hand() {
    // Determine the leader for this trick (player after dealer for first trick)
    int leader = (dealer + 1) % 4;
    
    // Initialize variables for the trick
    Card led_card;
    Card winning_card;
    int winner = leader;
    
    cout << endl << leader << " leads" << endl;
    
    // First player leads
    led_card = players[leader]->lead_card(suit_trump);
    cout << players[leader]->get_name() << " leads " << led_card << endl;
    winning_card = led_card;
    
    // Subsequent players play cards
    for (int i = 1; i < 4; i++) {
        int current_player = (leader + i) % 4;
        Card played_card = players[current_player]->play_card(led_card, suit_trump);
        cout << players[current_player]->get_name() << " plays " << played_card << endl;
        
        // Determine if this card beats the current winning card
        if (Card_less(winning_card, played_card, led_card, suit_trump)) {
            winning_card = played_card;
            winner = current_player;
        }
    }
    
    // Announce winner and update trick count
    cout << players[winner]->get_name() << " takes the trick" << endl;
    
    // Update trick counts for the appropriate team
    if (winner % 2 == 0) {
        tricksA++;
    } else {
        tricksB++;
    }
    
    // Set the leader for the next trick to be the winner of this trick
    leader = winner;
}