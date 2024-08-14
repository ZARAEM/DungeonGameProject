#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 10

unsigned int LEVELA_DATA[] =
{
            11, 2, 2, 4, 2, 2, 2, 2, 2, 2, 5, 5, 2, 2, 2, 5, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 6,
            11, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 36,
            11, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 7, 8, 7, 8, 9, 10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 36,
            11, 27, 27, 27, 27, 27, 27, 27, 27, 7, 8, 9, 10, 7, 8, 9, 10, 7, 8, 9, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 36,
            11, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 20, 17, 7, 7, 7, 7, 7, 8, 9, 7, 8, 7, 8, 9, 10, 10, 28, 29, 30, 40,
            11, 7, 8, 9, 10, 20, 20, 20, 10, 20, 20, 20, 30, 27, 17, 17, 17, 17, 7, 7, 7, 17, 7, 17, 18, 19, 20, 20, 28, 29, 30, 40,
            11, 7, 8, 9, 10, 30, 30, 30, 20, 30, 30, 30, 27, 27, 27, 27, 27, 27, 17, 17, 17, 27, 17, 27, 28, 29, 30, 30, 28, 29, 30, 36,
            11, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 27, 27, 27, 27, 27, 27, 28, 29, 30, 27, 28, 29, 30, 36,
            11, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 27, 28, 29, 30, 36,
            41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 46,
            41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 46
};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete[]    m_game_state.crystals;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.walk_sfx);
    Mix_FreeChunk(m_game_state.coin_sfx);
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;
    m_game_state.count = 0;

    GLuint player_texture_id = Utility::load_texture("assets/player.png");
    GLuint slime_texture_id = Utility::load_texture("assets/slime.png");
    GLuint dungeon_texture_id = Utility::load_texture("assets/tileset.png");
    GLuint crystal_texture_id = Utility::load_texture("assets/crystal.png");

    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, dungeon_texture_id, 0.8f, 10, 10);

    int player_walking_animation[4][4] =
    {
        { 0, 1, 2, 3 }, // left
        { 4, 5, 6, 7 }, // right
        { 8, 9, 10, 11 }, // up
        { 12, 13, 14, 15 } // down
    };

    int slime_walking_animation[4][4] =
    {
        { 0, 1, 2, 3 }, // left
        { 4, 5, 6, 7 }, // right
        { 8, 9, 10, 11 }, // up
        { 12, 13, 14, 15 } // down
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    m_game_state.player = new Entity(player_texture_id, 1.0f, acceleration, 0.0f, player_walking_animation, 0.0f, 4, 0, 4, 4, 0.3f, 0.3f, PLAYER);
    m_game_state.player->set_position(glm::vec3(5.0f, -2.0f, 0.0f));
    m_game_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.player->set_speed(2.0f);

    m_game_state.enemies = new Entity[3];

    m_game_state.enemies[0] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[0].set_speed(1.0f);
    m_game_state.enemies[0].set_ai_type(WALKER);
    m_game_state.enemies[0].set_ai_state(WALKING);
    m_game_state.enemies[0].set_position(glm::vec3(10.0f, -1.0f, 0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[1] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[1].set_speed(1.0f);
    m_game_state.enemies[1].set_ai_type(GUARD);
    m_game_state.enemies[1].set_ai_state(WALKING);
    m_game_state.enemies[1].set_position(glm::vec3(15.0f, -3.0f, 0.0f));
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[2] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[2].set_speed(1.0f);
    m_game_state.enemies[2].set_ai_type(GUARD);
    m_game_state.enemies[2].set_ai_state(WALKING);
    m_game_state.enemies[2].set_position(glm::vec3(20.0f, -2.0f, 0.0f));
    m_game_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    //m_game_state.chests = new Entity[0];

    m_game_state.crystals = new Entity[4];

    m_game_state.crystals[0] = Entity(crystal_texture_id, 0.0f, 0.01f, 0.01f, CRYSTAL);
    m_game_state.crystals[0].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[0].set_speed(0.0f);
    m_game_state.crystals[0].set_position(glm::vec3(10.0f, -5.0f, 0.0f));
    m_game_state.crystals[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[1] = Entity(crystal_texture_id, 0.0f, 0.01f, 0.01f, CRYSTAL);
    m_game_state.crystals[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[1].set_speed(0.0f);
    m_game_state.crystals[1].set_position(glm::vec3(10.0f, -1.0f, 0.0f));
    m_game_state.crystals[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[2] = Entity(crystal_texture_id, 0.0f, 0.01f, 0.01f, CRYSTAL);
    m_game_state.crystals[2].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[2].set_speed(0.0f);
    m_game_state.crystals[2].set_position(glm::vec3(15.0f, -1.0f, 0.0f));
    m_game_state.crystals[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[3] = Entity(crystal_texture_id, 0.0f, 0.01f, 0.01f, CRYSTAL);
    m_game_state.crystals[3].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[3].set_speed(0.0f);
    m_game_state.crystals[3].set_position(glm::vec3(20.0f, -1.0f, 0.0f));
    m_game_state.crystals[3].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    constexpr char BGM_FILEPATH[] = "assets/bgm.mp3";

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 10);

    m_game_state.coin_sfx = Mix_LoadWAV("assets/coin.wav");
    m_game_state.walk_sfx = Mix_LoadWAV("assets/walk.wav");

    Mix_VolumeChunk(m_game_state.coin_sfx, MIX_MAX_VOLUME / 2);
    Mix_VolumeChunk(m_game_state.walk_sfx, MIX_MAX_VOLUME / 32);
}

void LevelA::update(float delta_time)
{
    if (m_game_state.player->get_movement() != glm::vec3(0.0f,0.0f,0.0f)) {
        Mix_PlayChannel(1, m_game_state.walk_sfx, 0);
    }
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, 3, m_game_state.map);

    for (int i = 0; i < 3; i++) {
        if (m_game_state.player->check_collision(&m_game_state.enemies[i]) && (m_game_state.enemies[i].get_entity_type() == ENEMY)) {
            m_game_state.next_scene_id = 4;
        }
        else {
            m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.enemies, 0, m_game_state.map);
        }
    }

    for (int i = 0; i < 4; i++) {
        m_game_state.crystals[i].update(delta_time, m_game_state.player, m_game_state.crystals, 0, m_game_state.map);

        if (m_game_state.player->check_collision(&m_game_state.crystals[i])) {
            m_game_state.crystals[i].deactivate();

            Mix_PlayChannel(2, m_game_state.coin_sfx, 0);
            m_game_state.count += 1;
        }
    }

    glm::vec3 player_position = m_game_state.player->get_position();

    if (m_game_state.player->get_position().x >= 25.0f) {
        if (m_game_state.count == 4) {
            m_game_state.next_scene_id = 2;
        }
        else {
            m_game_state.next_scene_id = 4;
        }
    }
}

void LevelA::render(ShaderProgram* program)
{
    GLuint texture_id = Utility::load_texture("assets/font1.png");

    m_game_state.map->render(program);

    m_game_state.player->render(program);

    for (int i = 0; i < 3; i++) {
        m_game_state.enemies[i].render(program);
    }
    for (int i = 0; i < 4; i++) {
        if (m_game_state.crystals[i].get_active()) {
            m_game_state.crystals[i].render(program);
        }
    }

    Utility::draw_text(program, texture_id, std::to_string(m_game_state.count) + "/4", 0.4f, 0.0f, glm::vec3(5.0f, -1.5f, 0.0f));

}