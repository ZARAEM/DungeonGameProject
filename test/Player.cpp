#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Player.h"

Player::Player(GLuint texture_id, float speed, glm::vec3 acceleration, int walking[2], float animation_time,
    int animation_frames, int animation_index, int animation_cols, int animation_rows, float width, float height)
    : position(0.0f), movement(0.0f), scale(1.0f, 1.0f, 0.0f), model_matrix(1.0f),
    speed(speed), animation_cols(0), animation_frames(0), animation_index(0),
    animation_rows(0), animation_indices(nullptr), animation_time(0.0f),
    texture_id(texture_id), velocity(0.0f), acceleration(0.0f), width(width), height(height)
{
    for (int i = 0; i < 2; ++i) {
        walking[i] = walking[i];
    }
};

void Player::update(float delta_time, Entity* enemies, int enemy_count, Map* map) {
    static float animation_timer = 0.0f;
    animation_timer += delta_time;
    if (animation_timer > 0.2f) {
        animation_index = (animation_index + 1) % 2;
        animation_timer = 0.0f;
    }
}

void Player::render(ShaderProgram* program) {
    draw_sprite_from_texture_atlas(program, texture_id, walking[animation_index]);
}

void Player::draw_sprite_from_texture_atlas(ShaderProgram* program, GLuint texture_id, int index) {
    float u_coord = (float)(index % animation_cols) / (float)animation_cols;
    float v_coord = (float)(index / animation_cols) / (float)animation_rows;

    // Calculate UV size
    float width = 1.0f / (float)animation_cols;
    float height = 1.0f / (float)animation_rows;

    // Texture coordinates for the sprite
    float tex_coords[] = {
        u_coord, v_coord + height, u_coord + width, v_coord + height, u_coord + width, v_coord,
        u_coord, v_coord + height, u_coord + width, v_coord, u_coord, v_coord
    };

    // Vertex coordinates
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f
    };

    // Bind texture and set vertex attributes
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glVertexAttribPointer(program->get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->get_position_attribute());

    glVertexAttribPointer(program->get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, tex_coords);
    glEnableVertexAttribArray(program->get_tex_coordinate_attribute());

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program->get_position_attribute());
    glDisableVertexAttribArray(program->get_tex_coordinate_attribute());
}

void Player::move_up() {
    velocity.y += speed;
}

void Player::move_down() {
    velocity.y -= speed;
}

void Player::move_left() {
    velocity.x -= speed;
}

void Player::move_right() {
    velocity.x += speed;
}