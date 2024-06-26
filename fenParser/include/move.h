#include <iostream>
#include <string>

class Move {
private:
  int white;
  int draws;
  int black;
  std::string uci;
  std::string san;
  std::string game;
  int averageRating;
  int total;

public:
  Move() { total = 1; } // default constructor

  Move(std::string uci, std::string san, int white, int draws, int black,
       int averageRating)
      : uci(uci), san(san), white(white), draws(draws), black(black),
        averageRating(averageRating) {
    total = white + black + draws;
  }
  void update(std::string uci, std::string san, int white, int draws, int black,
              int averageRating) {
    this->uci = uci;
    this->san = san;
    this->white = white;
    this->draws = draws;
    this->black = black;
    this->averageRating = averageRating;
    this->total = this->white + this->draws + this->black;
  }

  // operator << overload
  friend std::ostream &operator<<(std::ostream &os, const Move &move) {
    os << "UCI: " << move.uci << "\nSAN: " << move.san
       << "\nWinning percentage\nWhite: "
       << (double)((double)move.white / (double)move.total) * 100
       << "%\nBlack: "
       << (double)((double)move.black / (double)move.total) * 100
       << "%\nDraws: "
       << (double)((double)move.draws / (double)move.total) * 100 << "%"
       << std::endl;
    return os;
  }

  std::string getUci() {
    std::cout << uci << std::endl;
    return uci;
  }
};
