#include "Lose.h"

void Lose::initialise() {
	m_game_state.next_scene_id = -1;

	m_number_of_enemies = 0;

	m_game_state.player = new Entity();

	m_game_state.enemies = new Entity();

	Mix_HaltMusic();

	lose_sfx = Mix_LoadWAV("assets/death.wav");

	Mix_VolumeChunk(lose_sfx, MIX_MAX_VOLUME / 4);

	Mix_PlayChannel(-1, lose_sfx, 0);
}

void Lose::update(float delta_time) {}

void Lose::render(ShaderProgram* program) {
	GLuint texture_id = Utility::load_texture("assets/font1.png");

	Utility::draw_text(program, texture_id, "YOU LOST", 0.4f, 0.0f, glm::vec3(3.5f, -1.0f, 0.0f));

	Utility::draw_text(program, texture_id, "Press q to exit", 0.4f, 0.0f, glm::vec3(2.0f, -6.0f, 0.0f));
}