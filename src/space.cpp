#include "space.hpp"
#include "music.hpp"
#include "render.hpp"
#include "collission.hpp"
#include "bullet.hpp"
#include "controller.hpp"

// window layout since all the objects
// are relative to the window frame
struct layout {
  int width;
  int height;
  std::string title;
};


// static information of the window
// similar to struct layout


void StaticInformation::set_window_status() {
  width = 400 * 2;
  height = 650;
  std::string title = "space shooter";

  InitWindow(width, height, title.c_str());
};

int StaticInformation::get_width(){
	return width;
}
int StaticInformation::get_height(){
	return height;
}
// every boulder gets random spawn interval
void unique_boulder() {
  while (1) {
    std::chrono::milliseconds timespan_1(2000);
    std::this_thread::sleep_for(timespan_1);
    int a = rand();
    { b1->add_unique_boulder(a); }

    std::chrono::milliseconds timespan_2((rand() % 3000));
    std::this_thread::sleep_for(timespan_2);
    int b = rand();
    { b2->add_unique_boulder(b); }
    std::chrono::milliseconds timespan_3((rand() % 2000));
    std::this_thread::sleep_for(timespan_3);
    int c = rand();
    { b3->add_unique_boulder(c); }

    std::chrono::milliseconds timespan_4((rand() % 3000));
    std::this_thread::sleep_for(timespan_4);
    int d = rand();
    { b4->add_unique_boulder(d); }
  }
}



int main() {
  STATUS game_loop = TRUE;
  bool pause = FALSE;
  GameLogic space;
  SetTraceLogLevel(LOG_ERROR);
  SetTargetFPS(60);

  MusicAnarchy music;
  music.init_music("assets/Anarchy.mp3");

  StaticInformation properties;
  Controller controller;
  RenderObjects spaceship;
  properties.set_window_status();

  Image image = LoadImage("assets/space.png");
  Texture2D background = LoadTextureFromImage(image);
  Texture2D pause_menu = LoadTexture("assets/menu.png");

  ObjectProperties spaceship_property;
  spaceship_property.w = properties.get_width() / 2 + 10;
  spaceship_property.h = properties.get_height() / 2 + 200;

  spaceship_property.obj_w = spaceship_width;
  spaceship_property.obj_h = spaceship_height;

  // runs this shit in another thread
  // non blocking cood
  std::thread boulder_thread(&unique_boulder);

  BulletEngine bullet_engine;
  Texture2D tex = LoadTexture("assets/shooter.png");

  while (game_loop) {
    controller.initcontroller(&spaceship_property, &properties, &pause,
                              &game_loop);

    ClearBackground(RAYWHITE);
    if (pause) {
      music.set_position(0);
      DrawTexture(pause_menu, 0, 0, WHITE);
      space.return_property()->h = 0;
      space.return_property()->w = 0;
      DrawText("GAME\nOVER", 40, 200, 120, WHITE);
    } else {
      music.play_music();
      // std::cout << GetMusicTimePlayed(music) << std::endl;
      if (music.get_current_timestamp() > 140) {
        music.set_position(2);
      }
      DrawTexture(background, -6, 1, WHITE);
      spaceship.render(spaceship_property);

      if (spaceship_property.shoot_bullet == TRUE) {
        std::cout << "bullet fired\n";
        spaceship_property.shoot_bullet = FALSE;
        bullet_engine.add_bullet(&spaceship_property);
      }

      DrawText("Score", 260, 20, 20, RED);
      DrawText(std::to_string(score).c_str(), 360, 20, 20, RED);
      DrawText("Level", 560, 20, 20, RED);
      DrawText(std::to_string(score/10).c_str(), 660, 20, 20, RED);

      spaceship.update(spaceship_property, tex);

      // speed of each boulder
      b1->set_speed(score);
      b2->set_speed(score);
      b3->set_speed(score);
      b4->set_speed(score);

      score += bullet_engine.render_bullet(*b1, *b2, *b3, *b4);

      // bolder starting position
      b1->render_boulder();
      b2->render_boulder();
      b3->render_boulder();
      b4->render_boulder();

      // display boulder
      b1->update_boulder();
      b2->update_boulder();
      b3->update_boulder();
      b4->update_boulder();

      if (space.collission_boulder(spaceship_property, *b1, *b2, *b3, *b4, pause)) {
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
