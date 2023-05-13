#include <chrono>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <string>
#include <thread>
#include <vector>

#define spaceship_width 20
#define spaceship_height 20
#define boulder_width 40
#define boulder_height 40

class Boulder;
class Controller;
class BulletEngine;
class RenderObjects;
class StaticInformation;
class GameLogic;

// window layout since all the objects
// are relative to the window frame
struct layout {
  int width;
  int height;
  std::string title;
};

// Just TRUE or FALSE instead of
// conventional 0 or !0
enum STATUS {
  FALSE = 0,
  TRUE,
};

// every object we make have its properties
// made this another so called `public class`
// since it would be easier to get fine grain
// control of all the objects
struct ObjectProperties {
  int w;
  int h;
  int obj_w;
  int obj_h;
  STATUS shoot_bullet;
};

// static information of the window
// similar to struct layout
class StaticInformation {
private:
  int width;
  int height;

public:
  void set_window_status();
  void get_monitor_height();
  int get_width() { return width; }
  int get_height() { return height; }
};

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
  void update(ObjectProperties obj, Color COLOR, Texture2D text);
};

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
void RenderObjects::update(ObjectProperties obj, Color COLOR, Texture2D tex) {
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
  DrawTextureV(tex, v, COLOR);
}

class Boulder : public RenderObjects {
private:
  RenderObjects *boulder = new RenderObjects;
  ObjectProperties *boulder_property = new ObjectProperties;

public:
  void add_unique_boulder(int a) {
    boulder_property->h = a % 650;
    boulder_property->obj_h = boulder_height;
    boulder_property->w = 0 - 100;
    boulder_property->obj_w = boulder_width;
  };
  ObjectProperties *return_property() { return boulder_property; }
  void set_speed() { boulder_property->w += (int)(rand() % 3 + 2); }
  void reset_property() {
    boulder_property->w = 900;
    boulder_property->h = 900;
    boulder_property->obj_w = 0;
    boulder_property->obj_h = 0;
  }
  void render_boulder() { boulder->render(*boulder_property); }
  void update_boulder(Color color) {
    Texture2D tex = LoadTexture("boulder.png");
    boulder->update(*boulder_property, color, tex);
  }
};

Boulder b1, b2, b3, b4;

// TODO: move game logic here
class GameLogic : public Boulder {
public:
  void game_loop();
  void set_object_size(ObjectProperties *obj, int size);
  void init_spaceship();
  int collission_boulder(ObjectProperties spaceship_property, Boulder b1,
                         Boulder b2, Boulder b3, Boulder b4, bool &pause);
  int collission(ObjectProperties obj_1, ObjectProperties *obj_2,
                 int collission_height_up, int collission_width_up,
                 int collission_height_down, int collission_width_down);
};

int GameLogic::collission(ObjectProperties obj_1, ObjectProperties *obj_2,
                          int collission_height_up, int collission_width_up,
                          int collission_height_down,
                          int collission_width_down) {
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
  if (collission(spaceship_property, b1.return_property(), 20, 30, 10, 10) ||
      collission(spaceship_property, b2.return_property(), 20, 30, 10, 10) ||
      collission(spaceship_property, b3.return_property(), 20, 30, 10, 10) ||
      collission(spaceship_property, b4.return_property(), 20, 30, 10, 10)) {
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

void GameLogic::init_spaceship() { ObjectProperties spaceship_property; }

void GameLogic::set_object_size(ObjectProperties *obj, int size) {
  obj->obj_h = size;
  obj->obj_w = size;
}

void StaticInformation::set_window_status() {
  width = 400;
  height = 650;
  std::string title = "space shooter";

  InitWindow(width, height, title.c_str());
};

// all keyboard controller goes here
class Controller {
private:
  int times = 0;

public:
  void initcontroller(ObjectProperties *spaceship,
                      StaticInformation *window_properties, bool *pause_menu,
                      STATUS *game_loop) {
    if (IsKeyDown(KEY_RIGHT)) {
      spaceship->w += 5;
      spaceship->h += 0;
      // std::cout << "R X: " << spaceship->w << std::endl;
      if (spaceship->w > window_properties->get_width()) {
        spaceship->w = 0;
      }
    } else if (IsKeyDown(KEY_UP)) {
      spaceship->w += 0;
      spaceship->h -= 5;
      // std::cout << "R Y: " << spaceship->h << std::endl;
      if (spaceship->h < 0) {
        spaceship->h = 0;
      }
    } else if (IsKeyDown(KEY_DOWN)) {
      // std::cout << "R Y: " << spaceship->h << std::endl;
      if (spaceship->h < window_properties->get_height() - 10) {
        spaceship->w += 0;
        spaceship->h += 5;
      } else {
        // spaceship->h = properties->get_height() - 2;
      }
    } else if (IsKeyDown(KEY_LEFT)) {
      spaceship->w -= 5;
      spaceship->h += 0;
      // std::cout << "R X: "  << spaceship->w << std::endl;
      if (spaceship->w < 0) {
        spaceship->w = window_properties->get_width();
      }
    } else if (IsKeyPressed(KEY_P)) {
      *pause_menu = !*pause_menu;
      times++;
      // std::cout << "SPACE\n" << *pause_menu << '\n' << times << std::endl;
    } else if (IsKeyPressed(KEY_SPACE)) {
      spaceship->shoot_bullet = TRUE;
    } else if (IsKeyPressed(KEY_ESCAPE)) {
      *game_loop = FALSE;
    }
  }
};

// every boulder gets random spawn interval
void unique_boulder() {
  while (1) {
    std::chrono::milliseconds timespan_1(2000);
    std::this_thread::sleep_for(timespan_1);
    int a = rand();
    { b1.add_unique_boulder(a); }

    std::chrono::milliseconds timespan_2((rand() % 3000));
    std::this_thread::sleep_for(timespan_2);
    int b = rand();
    { b2.add_unique_boulder(b); }
    std::chrono::milliseconds timespan_3((rand() % 2000));
    std::this_thread::sleep_for(timespan_3);
    int c = rand();
    { b3.add_unique_boulder(c); }

    std::chrono::milliseconds timespan_4((rand() % 3000));
    std::this_thread::sleep_for(timespan_4);
    int d = rand();
    { b4.add_unique_boulder(d); }
  }
}

// if user hits space
// it generates new object
// that object is put in a vector
class BulletEngine : GameLogic {
private:
  Texture2D tex = LoadTexture("bullet.png");
  std::vector<ObjectProperties> *total_bullets =
      new std::vector<ObjectProperties>;
  ObjectProperties *obj;
  RenderObjects bullet;

public:
  void add_bullet(ObjectProperties *spaceship_info);
  int render_bullet();
};

void BulletEngine::add_bullet(ObjectProperties *spaceship_info) {
  obj = new ObjectProperties;
  obj->h = spaceship_info->h + 7;
  obj->w = spaceship_info->w;
  obj->obj_h = 5;
  obj->obj_w = 10;
  total_bullets->push_back(*obj);
}

// this takes total_bullets and loops it
int BulletEngine::render_bullet() {
  std::vector<ObjectProperties>::iterator it;
  for (it = total_bullets->begin(); it < total_bullets->end(); it++) {
    update(*it, WHITE, tex);
    it->w += -2;
    render(*it);

    // COLLISSION
    if ((collission(*it, b1.return_property(), 30, 30, 0, 0))) {
      b1.reset_property();
      return 1;
    }
    if ((collission(*it, b2.return_property(), 30, 30, 0, 0))) {
      b2.reset_property();
      return 1;
    }
    if ((collission(*it, b3.return_property(), 30, 30, 0, 0))) {
      b3.reset_property();
      return 1;
    }
    if ((collission(*it, b4.return_property(), 30, 30, 0, 0))) {
      // std::cout << "collission\n";
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

int main() {
  STATUS game_loop = TRUE;
  bool pause = FALSE;
  GameLogic space;

  // toggle true means beam is thrown
  STATUS toggle;
  SetTraceLogLevel(LOG_ERROR);
  SetTargetFPS(60);

  StaticInformation properties;
  Controller controller;
  RenderObjects spaceship;
  RenderObjects spaceship2;

  properties.set_window_status();

  Image image = LoadImage("space.png");
  Texture2D background = LoadTextureFromImage(image);
  Texture2D pause_menu = LoadTexture("menu.png");

  float scrollingBack = 0.0f;

  ObjectProperties spaceship_property;
  spaceship_property.w = properties.get_width() / 2 + 10;
  spaceship_property.h = properties.get_height() / 2 + 200;

  spaceship_property.obj_w = spaceship_width;
  spaceship_property.obj_h = spaceship_height;

  // runs this shit in another thread
  // non blocking cood
  std::thread boulder_thread(&unique_boulder);

  BulletEngine bullet_engine;
  Texture2D tex = LoadTexture("shooter.png");

  int score = 0;
  while (game_loop) {
    controller.initcontroller(&spaceship_property, &properties, &pause,
                              &game_loop);

    scrollingBack -= 9.0f;
    BeginDrawing();

    ClearBackground(RAYWHITE);
    if (pause) {
      DrawTexture(pause_menu, 0, 0, WHITE);
      space.set_object_size(b1.return_property(), 0);
      space.set_object_size(b2.return_property(), 0);
      space.set_object_size(b3.return_property(), 0);
      space.set_object_size(b4.return_property(), 0);
      DrawText("GAME\nOVER", 40, 200, 120, WHITE);
    } else {
      DrawTexture(background, -6, 1, WHITE);
      spaceship.render(spaceship_property);

      if (spaceship_property.shoot_bullet == TRUE) {
        std::cout << "bullet fired\n";
        spaceship_property.shoot_bullet = FALSE;
        bullet_engine.add_bullet(&spaceship_property);
      }

      DrawText("Score", 260, 20, 20, RED);
      DrawText(std::to_string(score).c_str(), 360, 20, 20, RED);

      spaceship.update(spaceship_property, RED, tex);

      // speed of each boulder
      b1.set_speed();
      b2.set_speed();
      b3.set_speed();
      b4.set_speed();

      score += bullet_engine.render_bullet();

      // bolder starting position
      b1.render_boulder();
      b2.render_boulder();
      b3.render_boulder();
      b4.render_boulder();

      // display boulder
      b1.update_boulder(VIOLET);
      b2.update_boulder(VIOLET);
      b3.update_boulder(VIOLET);
      b4.update_boulder(VIOLET);

      if (space.collission_boulder(spaceship_property, b1, b2, b3, b4, pause)) {
        score = 0;
      }
    }
    EndDrawing();
  }
  CloseWindow();

  // I have no idea how to terminate a thread so I just exit the
  // whole process
  // boulder_thread.join(); 
  exit(0);
  return 0;
}
