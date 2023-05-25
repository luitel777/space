#include "controller.hpp"

// all keyboard controller goes here
void Controller::initcontroller(ObjectProperties *spaceship,
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
		spaceship->h -= 7;
		// std::cout << "R Y: " << spaceship->h << std::endl;
		if (spaceship->h < 0) {
			spaceship->h = 0;
		}
	} else if (IsKeyDown(KEY_DOWN)) {
		// std::cout << "R Y: " << spaceship->h << std::endl;
		if (spaceship->h < window_properties->get_height() - 10) {
			spaceship->w += 0;
			spaceship->h += 7;
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
