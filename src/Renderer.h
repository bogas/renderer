#include "Vertex.h"
#include "tgaimage.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace Color {
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor black = TGAColor(0, 0, 0, 0);
const TGAColor blue = TGAColor(0, 0, 255, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
} // namespace Color

enum class Side { Front, Up, Side };

class Renderer {
public:
  Renderer(int height, int width, const string &outputFile = "output.tga")
      : baseHeight(height), baseWidth(width), midX(baseWidth / 2),
        midY(baseHeight / 2), outputFile(outputFile) {
    image.reset(new TGAImage{baseWidth, baseHeight, TGAImage::RGB});
  };
  void drawLine(int x1, int y1, int x2, int y2,
                TGAColor &color = const_cast<TGAColor &>(Color::black));

  void drawLine(Point p1, Point p2,
                TGAColor &color = const_cast<TGAColor &>(Color::black)) {
    drawLine(p1.x, p1.y, p2.x, p2.y, color);
  }

  void drawStar(int x, int y, int radius);

  ~Renderer() { image->write_tga_file(outputFile.c_str()); }

  void setColor(TGAColor color);

  void drawMeshGridFront(const vector<Vertex> &vertices,
                         const vector<Face> &faces, int scale, int centerX,
                         int centerY);

  void drawMeshGrid(const vector<Vertex> &vertices, const vector<Face> &faces,
                    int scale, Side side);
  void drawMeshGridUp(const vector<Vertex> &vertices, const vector<Face> &faces,
                      int scale, int centerX, int centerY);
  void drawMeshGridSide(const vector<Vertex> &vertices,
                        const vector<Face> &faces, int scale, int centerX,
                        int centerY);
  void drawMeshGrid3dProjections(const vector<Vertex> &vertices,
                                 const vector<Face> &faces, int scale);
  void drawTriangle(Point p0, Point p1, Point p2,
                    TGAColor &color = const_cast<TGAColor &>(Color::black));

private:
  string outputFile;
  unique_ptr<TGAImage> image;
  const unsigned int baseHeight;
  const unsigned baseWidth;
  const unsigned midY;
  const unsigned midX;
  std::pair<Point, Point> getShortestVertex(const Point &p1, const Point &p2,
                                            const Point &p3);
};