#include "BetweenScreen.h"

void BetweenScreen::initialise() {
	m_game_state.next_scene_id = -1;
	m_number_of_enemies = 0;

	m_game_state.player = new Entity();

	m_game_state.enemies = new Entity();
}

void BetweenScreen::update(float delta_time) {}

void BetweenScreen::render(ShaderProgram* program) {
	GLuint texture_id = Utility::load_texture("assets/font1.png");

	Utility::draw_text(program, texture_id, "You found armor while climbing down.", 0.4f, 0.0f, glm::vec3(1.0f, -3.0f, 0.0f));

	Utility::draw_text(program, texture_id, "Continue on to escape!", 0.4f, 0.0f, glm::vec3(1.0f, -3.0f, 0.0f));

	Utility::draw_text(program, texture_id, "Press enter to continue your journey!", 0.4f, 0.0f, glm::vec3(1.0f, -3.0f, 0.0f));
}