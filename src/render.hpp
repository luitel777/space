#pragma once
#include "space.hpp"
// every object is essentially rendered through this class
// this class uses struct called ObjectProperties we defined
// earlier
class RenderObjects {
private:
  int width;
  int height;
  int object_width;
  int object_height;

public:
  // location of object is respective to the window width
  void render(ObjectProperties obj);
  void update(ObjectProperties obj, Texture2D text);
};
