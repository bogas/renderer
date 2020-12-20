#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
  double x, y, z;
  friend std::ostream &operator<<(std::ostream &stream, const Vertex &v) {
    cout << v.x << " " << v.y << " " << v.z << endl;
  }
};

struct Face {
  void addVertex(size_t v) { vertices.push_back(v); }
  vector<size_t> vertices;
  friend std::ostream &operator<<(std::ostream &stream, const Face &face) {
    for (const auto &v : face.vertices) {
      cout << v << " ";
    }
    cout << endl;
  }
};

struct Point {
  int x, y;
  Point(const int &a, const int &b) : x(a), y(b) {}
  bool operator<(const Point &rhs) { return this->y < rhs.y; }
};
