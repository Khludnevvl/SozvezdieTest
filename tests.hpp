#pragma once
#include <cassert>

#include "knight.hpp"

void TestWrongPosition() {
  try {
    assert(knight("a9", "a1") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }

  try {
    assert(knight("a1", "i1") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }
  try {
    assert(knight("a8", "a9") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }
  try {
    assert(knight("a0", "a0") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }
  try {
    assert(knight("a1", "##") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }
  try {
    assert(knight("", "") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }
  try {
    assert(knight("@_@", "a1") == 0);
    assert(false);

  } catch (WrongPosition &e) {

  } catch (std::exception &) {
    assert(false);
  }
  std::cout << "TestWrongPosition: OK!" << std::endl;
}

void TestCorrectPos() {
  assert(knight("a3", "b5") == 1);
  assert(knight("a1", "a1") == 0);
  assert(knight("a1", "h8") == 6);
  assert(knight("a1", "h7") == 5);
  assert(knight("a1", "h7") == 5);

  assert(knight("e6", "f6") == 3);
  assert(knight("e6", "e5") == 3);
  assert(knight("e6", "d6") == 3);
  assert(knight("e6", "e7") == 3);

  assert(knight("e6", "f7") == 2);
  assert(knight("e6", "f5") == 2);
  assert(knight("e6", "d5") == 2);
  assert(knight("e6", "d7") == 2);

  assert(knight("h8", "h7") == 3);
  assert(knight("h8", "g8") == 3);

  assert(knight("h8", "g7") == 4);
  assert(knight("h8", "f6") == 4);
  assert(knight("h8", "e5") == 2);
  assert(knight("h8", "d4") == 4);
  assert(knight("h8", "c3") == 4);
  assert(knight("h8", "b2") == 4);

  std::cout << "TestCorrectPos: OK!" << std::endl;
}

void Test() {
  TestCorrectPos();
  TestWrongPosition();
}