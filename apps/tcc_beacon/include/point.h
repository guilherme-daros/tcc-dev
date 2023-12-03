#pragma once
#include <array>

struct point {
  int x_acc;
  int y_acc;
  int z_acc;

  constexpr point(double x_acc, double y_acc, double z_acc)
      : x_acc(x_acc), y_acc(y_acc), z_acc(z_acc) {}
};