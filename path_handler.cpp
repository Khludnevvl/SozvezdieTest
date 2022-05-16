#include "path_handler.h"

#include <algorithm>

PathHandler::PathHandler(int field_size) {
  visited_cells_.resize(field_size);

  for (int i = 0; i < field_size; i++) {
    visited_cells_[i].resize(field_size);
    for (int j = 0; j < field_size; j++)
      visited_cells_[i][j] = false;
  }
}

void PathHandler::visitCell(Position pos) {
  visitCell(pos.x, pos.y);
}
void PathHandler::visitCell(int x, int y) {
  visited_cells_[x][y] = true;
}

bool PathHandler::isVisitedCell(int x, int y) const {
  return visited_cells_[x][y];
}

void PathHandler::addCell(Cell cell) {
  ids_cells_[cell.id] = cell;
  visitCell(cell.pos);
}

Cell PathHandler::getCell(size_t id) const {
  return ids_cells_.at(id);
}

std::vector<Position> PathHandler::printPath(size_t path_to_id) const {
  std::vector<Position> result;
  int id = path_to_id;
  while (id != -1) {
    Cell tmp_cell = getCell(id);
    result.push_back(tmp_cell.pos);
    id = tmp_cell.prevId;
  }
  std::reverse(result.begin(), result.end());
  return result;
}
