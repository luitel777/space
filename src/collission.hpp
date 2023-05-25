#pragma once
#include "space.hpp"
#include "boulder.hpp"

// TODO: move game logic here
class GameLogic : public Boulder {
public:
  void game_loop();
  void set_object_size(ObjectProperties *obj, int size);
  void init_spaceship();
  int collission_boulder(ObjectProperties spaceship_property, Boulder b1,
                         Boulder b2, Boulder b3, Boulder b4, bool &pause);
  int collission(ObjectProperties obj_1, ObjectProperties *obj_2,
                 int collission_height_up, int collission_width_up);
};

