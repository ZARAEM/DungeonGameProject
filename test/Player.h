#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"
#include "glm/glm.hpp"
#include "ShaderProgram.h"
#include "Entity.h"

class Player {
private:
	bool is_active = true;

	int walking[2];

    // ————— TRANSFORMATIONS ————— //
    glm::vec3 movement;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    glm::mat4 model_matrix;

    float     speed;

    // ————— TEXTURES ————— //
    GLuint    texture_id;

    // ————— ANIMATION ————— //
    int animation_cols;
    int animation_frames,
        animation_index,
        animation_rows;

    int* animation_indices = nullptr;
    float animation_time = 0.0f;

    float width = 1.0f,
        height = 1.0f;
    // ————— COLLISIONS ————— //
    bool collided_top = false;
    bool collided_bottom = false;
    bool collided_left = false;
    bool collided_right = false;

    // ————— COLLISIONS ————— //
    bool m_collided_top = false;
    bool m_collided_bottom = false;
    bool m_collided_left = false;
    bool m_collided_right = false;

public:
	Player(GLuint texture_id, float speed, glm::vec3 acceleration, int walking[2], float animation_time,
		int animation_frames, int animation_index, int animation_cols, int animation_rows, float width, float height);

	void update(float delta_time, Entity* enemies, int enemy_count, Map* map);

	void render(ShaderProgram* program);

    void draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index);

    glm::vec3 const get_position()     const { return position; }
    glm::vec3 const get_velocity()     const { return velocity; }
    glm::vec3 const get_acceleration() const { return acceleration; }
    glm::vec3 const get_movement()     const { return movement; }
    glm::vec3 const get_scale()        const { return scale; }
    GLuint    const get_texture_id()   const { return texture_id; }
    float     const get_speed()        const { return speed; }
    bool      const get_collided_top() const { return collided_top; }
    bool      const get_collided_bottom() const { return collided_bottom; }
    bool      const get_collided_right() const { return collided_right; }
    bool      const get_collided_left() const { return collided_left; }

    void const set_position(glm::vec3 new_position) { position = new_position; }
    void const set_velocity(glm::vec3 new_velocity) { velocity = new_velocity; }
    void const set_acceleration(glm::vec3 new_acceleration) { acceleration = new_acceleration; }
    void const set_movement(glm::vec3 new_movement) { movement = new_movement; }
    void const set_scale(glm::vec3 new_scale) { scale = new_scale; }
    void const set_texture_id(GLuint new_texture_id) { texture_id = new_texture_id; }
    void const set_speed(float new_speed) { speed = new_speed; }
    void const set_animation_cols(int new_cols) { animation_cols = new_cols; }
    void const set_animation_rows(int new_rows) { animation_rows = new_rows; }
    void const set_animation_frames(int new_frames) { animation_frames = new_frames; }
    void const set_animation_index(int new_index) { animation_index = new_index; }
    void const set_animation_time(float new_time) { animation_time = new_time; }
    void const set_width(float new_width) { width = new_width; }
    void const set_height(float new_height) { height = new_height; }

    void move_up();
    void move_down();
    void move_left();
    void move_right();
};

#endif