#include "collission.hpp"
// TODO: move game logic here

int GameLogic::collission(ObjectProperties obj_1, ObjectProperties *obj_2,
                          int collission_height_up, int collission_width_up){
  if (abs(obj_1.h - obj_2->h) < collission_height_up &&
      abs(obj_1.w - obj_2->w) < collission_width_up) {
    obj_2->obj_h = 0;
    std::cout << "collission\n";
    return 1;
  }
  return 0;
}
int GameLogic::collission_boulder(ObjectProperties spaceship_property,
                                  Boulder b1, Boulder b2, Boulder b3,
                                  Boulder b4, bool &pause) {
  if (collission(spaceship_property, b1.return_property(), 20, 30) ||
      collission(spaceship_property, b2.return_property(), 20, 30) ||
      collission(spaceship_property, b3.return_property(), 20, 30) ||
      collission(spaceship_property, b4.return_property(), 20, 30)) {
    std::cout << "collission detection spaceship ded\n";
    std::cout << "spaceship: " << spaceship_property.w << " "
              << spaceship_property.h << std::endl;
    std::cout << "boulder 1: " << b1.return_property()->w << " "
              << b1.return_property()->h << std::endl;
    std::cout << "boulder 2: " << b2.return_property()->w << " "
              << b2.return_property()->h << std::endl;
    std::cout << "boulder 3: " << b3.return_property()->w << " "
              << b3.return_property()->h << std::endl;
    std::cout << "boulder 4: " << b4.return_property()->w << " "
              << b4.return_property()->h << std::endl;
    pause = TRUE;
    return 1;
  }
  return 0;
}


void GameLogic::set_object_size(ObjectProperties *obj, int size) {
  obj->obj_h = size;
  obj->obj_w = size;
}
