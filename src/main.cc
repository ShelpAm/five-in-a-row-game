//
// Created by small-sheep on 11/10/22.
//
#include "five_in_a_row_game/application.h"

int f1(const int i);
int f1(const int i) { return i; }

int main() {
  Application application;
  application.SetApplicationIsOn(true);
  application.MainLoop();

  return 0;
}
