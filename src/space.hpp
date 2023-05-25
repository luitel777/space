#pragma once
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <string>
#include <thread>
#include <vector>

static int score = 0;

// Just TRUE or FALSE instead of
// conventional 0 or !0
enum STATUS {
  FALSE = 0,
  TRUE,
};

class StaticInformation {
private:
  int width;
  int height;

public:
  void set_window_status();
  void get_monitor_height();
  int get_width();
  int get_height();
};

class MusicAnarchy;

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



#define spaceship_width 20
#define spaceship_height 20
#define boulder_width 40
#define boulder_height 40
