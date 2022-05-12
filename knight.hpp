#pragma once
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

const int FIELD_SIZE = 8;

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
  int prevId;
  Position pos;
  int distance;
};

bool isInside(int x, int y) {
  if (x >= 0 && x < FIELD_SIZE && y >= 0 && y < FIELD_SIZE)
    return true;
  return false;
}

int knight(std::string start_pos, std::string end_pos) {
  const Position start_position = Position::fromAlgebraicNotation(start_pos);
  const Position end_position = Position::fromAlgebraicNotation(end_pos);

  const std::vector<int> dx = {-2, -1, 1, 2, -2, -1, 1, 2};
  const std::vector<int> dy = {-1, -2, -2, -1, 1, 2, 2, 1};

  std::queue<Cell> unchecked_cells;
  std::unordered_map<size_t, Cell> ids_nodes;
  size_t current_id = 0;

  // starting position of knight with 0 distance
  Cell current_cell(start_position, 0);

  current_cell.prevId = -1; // -1 means first cell
  current_cell.id = current_id;
  ids_nodes[current_id] = current_cell;

  current_id++;
  unchecked_cells.push(current_cell);

  int x, y;

  bool visit[FIELD_SIZE][FIELD_SIZE];

  for (int i = 0; i < FIELD_SIZE; i++)
    for (int j = 0; j < FIELD_SIZE; j++)
      visit[i][j] = false;

  visit[start_position.x][start_position.y] = true;

  while (!unchecked_cells.empty()) {
    current_cell = unchecked_cells.front();
    unchecked_cells.pop();

    if (current_cell.pos.x == end_position.x &&
        current_cell.pos.y == end_position.y) {
      return current_cell.distance;
    }

    for (int i = 0; i < FIELD_SIZE; i++) {
      x = current_cell.pos.x + dx[i];
      y = current_cell.pos.y + dy[i];

      if (isInside(x, y) && !visit[x][y]) {
        visit[x][y] = true;
        Cell next_cell(x, y, current_cell.distance + 1);
        next_cell.id = current_id;
        next_cell.prevId = current_cell.id;

        ids_nodes[current_id++] = next_cell;
        unchecked_cells.push(next_cell);
      }
    }
  }
  throw std::runtime_error("Failed to find minimum steps");
}