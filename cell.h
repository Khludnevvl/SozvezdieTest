#pragma once
#include <stdexcept>

struct WrongPosition : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class Position {
public:
  Position() {}
  Position(int _x, int _y) : x(_x), y(_y) {}

  static Position fromAlgebraicNotation(const std::string &pos) {
    if (pos.size() != 2) {
      throw WrongPosition("Uncorrect algebraic notation. Use: [a-h][1-8]");
    }
    int x = pos[0] - 97; // lower letters starts from 97 in ASCII
    int y = pos[1] - 49; // numbers starts from 48 in ASCII
    if (x < 0 || x >= 8 || y < 0 || y >= 8) {
      throw WrongPosition("Uncorrect algebraic notation. Use: [a-h][1-8]");
    }
    return Position{x, y};
  }

  int x = -1;
  int y = -1;
};

class Cell {
public:
  Cell() {}
  Cell(Position _pos, int dis) : pos(_pos), distance(dis) {}
  Cell(int x, int y, int dis) : pos(x, y), distance(dis) {}

  int id;
  int prevId = -1;
  Position pos;
  int distance = 0;
};
