#include "ObjReader.h"
#include "Renderer.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  Renderer r(500, 500);
  ObjReader object;
  object.readFile("cessna.obj");
  r.setColor(Color::white);
  r.drawTriangle(Point{100, 100}, Point{120, 300}, Point{350, 150});
  return 0;
}
