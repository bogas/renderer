#include "ObjReader.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

namespace EntryType {
const string Vertex = "v";
const string Face = "f";
} // namespace EntryType
const vector<Vertex> &ObjReader::getVertices() { return vertices; }
const vector<Face> &ObjReader::getFaces() { return faces; }

void ObjReader::readFile(const string &fileName) {
  ifstream objFile;
  objFile.open(fileName);
  if (!objFile.is_open()) {
    cout << "File " << fileName << " could not be opened" << endl;
  }
  string currentLine;
  string entryType;
  while (getline(objFile, currentLine)) {
    stringstream lineStream(currentLine);
    lineStream >> entryType;

    if (entryType == EntryType::Vertex) {
      double x, y, z;
      lineStream >> x >> y >> z;
      maxVerticeCoord =
          maxVerticeCoord < ceil(abs(x)) ? ceil(abs(x)) : maxVerticeCoord;
      maxVerticeCoord =
          maxVerticeCoord < ceil(abs(y)) ? ceil(abs(y)) : maxVerticeCoord;
      maxVerticeCoord =
          maxVerticeCoord < ceil(abs(z)) ? ceil(abs(z)) : maxVerticeCoord;
      vertices.push_back(Vertex{x, y, z});
    } else if (entryType == EntryType::Face) {
      size_t rawIndex;
      Face currentFace;

      while (!lineStream.eof()) {
        lineStream >> rawIndex;
        rawIndex--;
        currentFace.addVertex(rawIndex);
      }
      faces.push_back(currentFace);
    }
  }
}