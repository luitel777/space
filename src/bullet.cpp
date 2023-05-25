#include "bullet.hpp"

void BulletEngine::add_bullet(ObjectProperties *spaceship_info) {
  obj = new ObjectProperties;
  obj->h = spaceship_info->h + 7;
  obj->w = spaceship_info->w;
  obj->obj_h = 5;
  obj->obj_w = 10;
  total_bullets->push_back(*obj);
}

// this takes total_bullets and loops it
int BulletEngine::render_bullet(Boulder b1, Boulder b2, Boulder b3,
		Boulder b4) {
  std::vector<ObjectProperties>::iterator it;
  for (it = total_bullets->begin(); it < total_bullets->end(); it++) {
    update(*it, tex);
    it->w += -4;
    render(*it);

    if ((collission(*it, b1.return_property(), 30, 30))) {
      b1.reset_property();
      return 1;
    }
    if ((collission(*it, b2.return_property(), 30, 30))) {
      b2.reset_property();
      return 1;
    }
    if ((collission(*it, b3.return_property(), 30, 30))) {
      b3.reset_property();
      return 1;
    }
    if ((collission(*it, b4.return_property(), 30, 30))) {
			b4.reset_property();
      return 1;
    }

    // delete bullets that go out of frame
    // 0 is leftmost side of frame
    // -20 means its obviously rendering out of frame
    // std::cout << it->w << std::endl;
    if (it->w < -20) {
      // for some reason this crashes on windows
      // but works perfectly fine on linux
      // maybe something to do with vector reallocation
      total_bullets->erase(total_bullets->begin());
    }
  }
  return 0;
}
