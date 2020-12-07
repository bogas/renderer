#include "Vertex.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class ObjReader {
public:
  void readFile(const string &file);
  const vector<Vertex> &getVertices();
  const vector<Face> &getFaces();

  int maxVerticeCoord = 0;

private:
  vector<Vertex> vertices;
  vector<Face> faces;
};