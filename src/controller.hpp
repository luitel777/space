#include "space.hpp"
// all keyboard controller goes here
class Controller {
private:
  int times = 0;

public:
  void initcontroller(ObjectProperties *spaceship,
                      StaticInformation *window_properties, bool *pause_menu,
                      STATUS *game_loop);
};

