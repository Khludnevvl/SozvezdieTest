#pragma once

#include "cell.h"
#include "path_handler.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

const int FIELD_SIZE = 8;

bool isInside(int x, int y) {
  if (x >= 0 && x < FIELD_SIZE && y >= 0 && y < FIELD_SIZE)
    return true;
  return false;
}

std::vector<Position> knight(std::string start_pos, std::string end_pos) {

  const Position start_position = Position::fromAlgebraicNotation(start_pos);
  const Position end_position = Position::fromAlgebraicNotation(end_pos);

  const std::vector<int> dx = {-2, -1, 1, 2, -2, -1, 1, 2};
  const std::vector<int> dy = {-1, -2, -2, -1, 1, 2, 2, 1};

  PathHandler path_handler(FIELD_SIZE);

  std::queue<Cell> unchecked_cells;
  size_t current_id = 0;

  // starting position of knight with 0 distance
  Cell current_cell(start_position, 0);

  current_cell.prevId = -1; // -1 means first cell
  current_cell.id = current_id;

  path_handler.addCell(current_cell);

  current_id++;
  unchecked_cells.push(current_cell);

  int x, y;

  while (!unchecked_cells.empty()) {
    current_cell = unchecked_cells.front();
    unchecked_cells.pop();

    if (current_cell.pos.x == end_position.x &&
        current_cell.pos.y == end_position.y) {
      return path_handler.printPath(current_cell.id);
    }

    for (int i = 0; i < FIELD_SIZE; i++) {
      x = current_cell.pos.x + dx[i];
      y = current_cell.pos.y + dy[i];

      if (isInside(x, y) && !path_handler.isVisitedCell(x, y)) {

        Cell next_cell(x, y, current_cell.distance + 1);
        next_cell.id = current_id++;
        next_cell.prevId = current_cell.id;

        path_handler.addCell(next_cell);
        unchecked_cells.push(next_cell);
      }
    }
  }
  throw std::runtime_error("Failed to find minimum steps");
}
