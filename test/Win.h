#pragma once

#include "Scene.h"

class Win : public Scene {
private:
	Mix_Chunk* win_sfx;
public:
	void initialise() override;
	void update(float delta_time) override;
	void render(ShaderProgram* program) override;
};