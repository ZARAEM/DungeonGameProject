#pragma once

#include "Scene.h"

class Lose : public Scene {
private:
	Mix_Chunk* lose_sfx;
public:
	void initialise() override;
	void update(float delta_time) override;
	void render(ShaderProgram* program) override;
};