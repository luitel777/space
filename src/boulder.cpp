#include "boulder.hpp"
#include "space.hpp"

void Boulder::add_unique_boulder(int a) {
	boulder_property->h = a % 650;
	boulder_property->obj_h = boulder_height;
	boulder_property->w = 0 - 100;
	boulder_property->obj_w = boulder_width;
};

ObjectProperties *Boulder::return_property() { return boulder_property; }

void Boulder::set_speed(int score) { 
	boulder_property->w += (int)(rand() % 3 + 3 + float(score / 10.0));
}
void Boulder::reset_property() {
	boulder_property->w = 900;
	boulder_property->h = 900;
	boulder_property->obj_w = 0;
	boulder_property->obj_h = 0;
}
void Boulder::render_boulder() { boulder->render(*boulder_property); }
void Boulder::update_boulder() {
	Texture2D tex = LoadTexture("assets/boulder.png");
	boulder->update(*boulder_property, tex);
}


