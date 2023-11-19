#pragma once
#include "log.h"

#include <array>
#include <functional>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

template <class T, int size = 54> struct data_window {
  data_window() : count{0} {}

  void add(T x, T y, T z) {
    x_[count] = x;
    y_[count] = y;
    z_[count] = z;

    count++;
  }

  bool is_ready() { return count >= size - 1; }

  void reset() {
    std::fill(x_.begin(), x_.end(), 0);
    std::fill(y_.begin(), y_.end(), 0);
    std::fill(z_.begin(), z_.end(), 0);
    count = 0;
  }

  std::array<T, size> x_;
  std::array<T, size> y_;
  std::array<T, size> z_;
  int count;
};

template <class T, int size = 54, int n_feats = 5, int n_axis = 3>
std::array<float, n_feats * n_axis>
get_features(const data_window<int, size> &data) {

  static std::unordered_map<std::string,
                            std::function<float(std::array<T, size>)>>
      feature_funcs = {{"sum",
                        [](std::array<T, size> p) {
                          return std::accumulate(p.begin(), p.end(), 0);
                        }},
                       {"mean",
                        [](std::array<T, size> p) {
                          return std::accumulate(p.begin(), p.end(), 0);
                        }},
                       {"max",
                        [](std::array<T, size> p) {
                          return std::accumulate(p.begin(), p.end(), 0);
                        }},
                       {"min",
                        [](std::array<T, size> p) {
                          return std::accumulate(p.begin(), p.end(), 0);
                        }},
                       {"std", [](std::array<T, size> p) {
                          return std::accumulate(p.begin(), p.end(), 0);
                        }}};

  std::array<float, n_feats *n_axis> ret = {};

  auto i = 0;

  for (auto [name, func] : feature_funcs) {
    ret[i++] = func(data.x_);
    ret[i++] = func(data.y_);
    ret[i++] = func(data.z_);
  }

  return ret;
}