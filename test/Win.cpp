#include "Win.h"

void Win::initialise() {
	m_game_state.next_scene_id = -1;

	m_number_of_enemies = 0;

	m_game_state.player = new Entity();

	m_game_state.enemies = new Entity();

	Mix_HaltMusic();

	win_sfx = Mix_LoadWAV("assets/win.wav");

	Mix_VolumeChunk(win_sfx, MIX_MAX_VOLUME / 4);

	Mix_PlayChannel(-1, win_sfx, 0);
}

void Win::update(float delta_time) {}

void Win::render(ShaderProgram* program) {
	GLuint texture_id = Utility::load_texture("assets/font1.png");

	Utility::draw_text(program, texture_id, "YOU WON", 0.4f, 0.0f, glm::vec3(1.0f, -3.0f, 0.0f));

	Utility::draw_text(program, texture_id, "Press q to exit", 0.4f, 0.0f, glm::vec3(1.0f, -3.0f, 0.0f));
}