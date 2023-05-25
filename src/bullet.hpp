#pragma once
#include "space.hpp"
#include "render.hpp"
#include "collission.hpp"

// if user hits space
// it generates new object
// that object is put in a vector
class BulletEngine : GameLogic {
private:
  Texture2D tex = LoadTexture("assets/bullet.png");
  std::vector<ObjectProperties> *total_bullets =
      new std::vector<ObjectProperties>;
  ObjectProperties *obj;

public:
  void add_bullet(ObjectProperties *spaceship_info);
  int render_bullet(Boulder b1, Boulder b2, Boulder b3, Boulder b4);
};

