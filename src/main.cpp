#include "ObjReader.h"
#include "Renderer.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  Renderer r(3000, 3000);
  ObjReader object;
  object.readFile("cessna.obj");
  r.drawMeshGrid3dProjections(object.getVertices(), object.getFaces(),
                              object.maxVerticeCoord);

  return 0;
}
