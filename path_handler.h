#pragma once
#include "cell.h"

#include <unordered_map>
#include <vector>

class PathHandler {
public:
  PathHandler(int field_size);

  void visitCell(int x, int y);
  void visitCell(Position pos);

  bool isVisitedCell(int x, int y) const;
  void addCell(Cell cell);

  Cell getCell(size_t id) const;

  std::vector<Position> printPath(size_t id) const;

private:
  std::unordered_map<size_t, Cell> ids_cells_;
  std::vector<std::vector<bool>> visited_cells_;
};
