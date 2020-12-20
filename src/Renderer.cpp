#include "Renderer.h"
#include <algorithm>
#include <cmath>

using namespace std;

void Renderer::setColor(TGAColor color) {
  auto &localColor = color;
  auto imageHeight = image->get_height();
  auto imageWidth = image->get_width();
  for (auto x = 0; x < imageHeight; ++x) {
    for (auto y = 0; y < imageWidth; ++y) {
      image->set(x, y, localColor);
    }
  }
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, TGAColor &color) {
  auto &localColor = color;
  auto swaped = false;
  if (abs(x2 - x1) < abs(y2 - y1)) {
    swap(x1, y1);
    swap(x2, y2);
    swaped = true;
  }
  if (x2 < x1) {
    swap(x1, x2);
    swap(y1, y2);
  }

  auto dx = x2 - x1;
  auto dy = y2 - y1;
  auto coef = abs(dy) * 2;
  auto error = .0;
  auto y = y1;
  for (auto x = x1; x <= x2; x++) {
    if (!swaped) {
      image->set(x, y, localColor);
    } else {
      image->set(y, x, localColor);
    }
    error += coef;
    if (error > dx) {
      y += y2 > y1 ? 1 : -1;
      error -= 2 * dx;
    }
  }
}

void Renderer::drawStar(int x, int y, int radius) {
  for (double alpha = 0; alpha <= 3.14 * 2; alpha += 0.1) {
    drawLine(x, y, x + radius * sin(alpha), y + radius * cos(alpha));
  }
  auto localColor = Color::black;
  image->set(x, y, localColor);
}

void Renderer::drawMeshGrid(const vector<Vertex> &vertices,
                            const vector<Face> &faces, int scale, Side side) {
  switch (side) {
  case Side::Front:
    drawMeshGridFront(vertices, faces, scale, midX, midY);
    break;
  case Side::Up:
    drawMeshGridUp(vertices, faces, scale, midX, midY);
    break;
  case Side::Side:
    drawMeshGridSide(vertices, faces, scale, midX, midY);
    break;
  }
}

void Renderer::drawMeshGridFront(const vector<Vertex> &vertices,
                                 const vector<Face> &faces, int scale,
                                 int centerX, int centerY) {
  const auto factor = 2 * scale;
  for (const auto &f : faces) {
    auto currentVerticesSize = f.vertices.size();
    if (currentVerticesSize < 3) {
      cout << "Not enough vertices in a face " << endl;
      return;
    }

    for (auto i = 0; i < currentVerticesSize - 1; ++i) {
      drawLine(centerX + baseWidth * vertices.at(f.vertices[i]).x / factor,
               centerY - baseHeight * vertices.at(f.vertices[i]).y / factor,
               centerX + baseWidth * vertices.at(f.vertices[i + 1]).x / factor,
               centerY -
                   baseHeight * vertices.at(f.vertices[i + 1]).y / factor);
    }
    drawLine(centerX + baseWidth * vertices.begin()->x / factor,
             centerY - baseHeight * vertices.begin()->y / factor,
             centerX + baseWidth * (vertices.end() - 1)->x / factor,
             centerY - baseHeight * (vertices.end() - 1)->y / factor);
  }
}

void Renderer::drawMeshGridUp(const vector<Vertex> &vertices,
                              const vector<Face> &faces, int scale, int centerX,
                              int centerY) {
  const auto factor = 2 * scale;
  for (const auto &f : faces) {
    auto currentVerticesSize = f.vertices.size();
    if (currentVerticesSize < 3) {
      cout << "Not enough vertices in a face" << endl;
      return;
    }

    for (auto i = 0; i < currentVerticesSize - 1; ++i) {
      drawLine(centerX + baseWidth * vertices.at(f.vertices[i]).x / factor,
               centerY - baseHeight * vertices.at(f.vertices[i]).z / factor,
               centerX + baseWidth * vertices.at(f.vertices[i + 1]).x / factor,
               centerY -
                   baseHeight * vertices.at(f.vertices[i + 1]).z / factor);
    }
    drawLine(centerX + baseWidth * vertices.begin()->x / factor,
             centerY - baseHeight * vertices.begin()->z / factor,
             centerX + baseWidth * (vertices.end() - 1)->x / factor,
             centerY - baseHeight * (vertices.end() - 1)->z / factor);
  }
}

void Renderer::drawMeshGridSide(const vector<Vertex> &vertices,
                                const vector<Face> &faces, int scale,
                                int centerX, int centerY) {
  const auto factor = 2 * scale;
  for (const auto &f : faces) {
    auto currentVerticesSize = f.vertices.size();
    if (currentVerticesSize < 3) {
      cout << "Not enough vertices in a face" << endl;
      return;
    }

    for (auto i = 0; i < currentVerticesSize - 1; ++i) {
      drawLine(centerX + baseWidth * vertices.at(f.vertices[i]).z / factor,
               centerY - baseHeight * vertices.at(f.vertices[i]).y / factor,
               centerX + baseWidth * vertices.at(f.vertices[i + 1]).z / factor,
               centerY -
                   baseHeight * vertices.at(f.vertices[i + 1]).y / factor);
    }
    drawLine(centerX + baseWidth * vertices.begin()->z / factor,
             centerY - baseHeight * vertices.begin()->y / factor,
             centerX + baseWidth * (vertices.end() - 1)->z / factor,
             centerY - baseHeight * (vertices.end() - 1)->y / factor);
  }
}

void Renderer::drawMeshGrid3dProjections(const vector<Vertex> &vertices,
                                         const vector<Face> &faces, int scale) {
  image.reset(new TGAImage(2 * baseWidth, 2 * baseHeight, TGAImage::RGB));
  setColor(Color::white);
  drawMeshGridFront(vertices, faces, scale, midX, midY);
  drawMeshGridSide(vertices, faces, scale, 3 * midX, midY);
  drawMeshGridUp(vertices, faces, scale, midX, 3 * midY);
}

void Renderer::drawTriangle(
    Point p1, Point p2, Point p3,
    TGAColor &color = const_cast<TGAColor &>(Color::black)) {
  vector<Point> points;
  points.push_back(p1);
  points.push_back(p2);
  points.push_back(p3);
}

std::pair<Point, Point>
Renderer::getShortestVertex(const Point &p1, const Point &p2, const Point &p3) {
  auto maxLength = 0;
  using vertex = pair<Point, Point>;
  vector<vertex> allVertices{{p1, p2}, {p2, p3}, {p1, p3}};
  auto getLength = [](vertex p) {
    auto deltaX = abs(p.first.x - p.second.x);
    auto deltaY = abs(p.first.y - p.second.y);
    return deltaX * deltaX + deltaY * deltaY;
  };
  return *min_element(allVertices.begin(), allVertices.end(),
                      [getLength](const vertex &v1, const vertex &v2) -> bool {
                        return getLength(v1) > getLength(v2);
                      });
}
