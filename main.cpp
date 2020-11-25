#include "tgaimage.h"
#include <iostream>

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor black = TGAColor(0, 0, 0, 0);

void setColor(TGAImage &image, TGAColor color) {
  for (auto x = 0; x < image.get_height(); ++x) {
    for (auto y = 0; y < image.get_width(); ++y) {
      image.set(x, y, color);
    }
  }
}

void drawLine(int x1, int y1, int x2, int y2, TGAImage &image,
              const TGAColor &color) {
  auto delta = 0.01;
  for (auto i = 0.0; i < 1.0; i += delta) {
    auto x = x1 + (x2 - x1) * i;
    auto y = y1 + (y2 - y1) * i;
    cout << "Debug: x = " << x << " " << i << x2 - x1 << "endl" << endl;
    image.set(x, y, color);
  }
}

void drawLine2(int x1, int y1, int x2, int y2, TGAImage &image,
               const TGAColor &color) {
  if (x2 - x1 < y2 - y1) {
    swap(x1, y1);
    swap(x2, y2);
  }
  for (auto x = x1; x < x2; x++) {
    auto y = y1 + x * (x2 - x1) / (float)(y2 - y1);
    image.set(x, y, color);
  }
}

int main(int argc, char **argv) {
  TGAImage image(1000, 1000, TGAImage::RGB);
  setColor(image, white);
  //   drawLine(10, 20, 700, 930, image, red);
  //   drawLine2(200, 20, 900, 500, image, red);
  drawLine2(0, 0, 1000, 1000, image, red);
  drawLine2(0, 0, 650, 1000, image, black);
  image.write_tga_file("output.tga");
  return 0;
}
