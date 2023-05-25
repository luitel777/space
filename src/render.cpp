#include "space.hpp"
#include "render.hpp"

// self explanatory
// every object has height and width called obj_h and obj_w
// and has x and y coordinates called width and height
void RenderObjects::render(ObjectProperties obj) {
  // size of spaceship rectangle is 20x20
  object_width = obj.obj_w;
  object_height = obj.obj_h;

  // x axis
  // width of window divide by 2 puts the spaceship at middle
  //    |
  //    |
  // ___|[]____
  // kinda like this
  // from its left so its slightly right

  width = obj.w;
  width = obj.w;
  // y axis
  // in computer graphics axis start from top of screen
  // so y axis is inverted so adding on y axis
  // will move object downwards
  // _________
  // |
  // |
  // |
  // |
  // |
  height = obj.h;
}

// updates the rendered object
void RenderObjects::update(ObjectProperties obj, Texture2D tex) {
  Color transparent;
  transparent.a = 255;

  Rectangle r;
  r.height = obj.h;
  r.width = obj.w;
  r.x = obj.w;
  r.y = obj.h;

  Vector2 v;
  v.x = obj.w;
  v.y = obj.h;

  DrawRectangle(obj.w, obj.h, obj.obj_w, obj.obj_h, BLANK);
  DrawTextureV(tex, v, WHITE);

  //DrawTextureEx(tex, v, 0,  1.5f, WHITE);
}
