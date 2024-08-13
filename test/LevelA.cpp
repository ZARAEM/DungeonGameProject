#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 10

#define NUM_MAPS 2

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

//unsigned int LEVELA_OVERLAY[] =
//{
//1, 2, 2, 4, 2, 2, 2, 2, 2, 2, 5, 5, 2, 2, 2, 5, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 2, 6,
//            1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 36,
//            1, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 7, 8, 7, 8, 9, 10, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 36,
//            1, 27, 27, 27, 27, 27, 27, 27, 27, 7, 8, 9, 10, 7, 8, 9, 10, 7, 8, 9, 10, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 36,
//            1, 7, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 20, 17, 7, 7, 7, 7, 7, 8, 9, 7, 8, 7, 8, 9, 10, 10, 28, 29, 30, 36,
//            1, 7, 8, 9, 10, 20, 20, 20, 10, 20, 20, 20, 30, 27, 17, 17, 17, 17, 7, 7, 7, 17, 7, 17, 18, 19, 20, 20, 28, 29, 30, 36,
//            1, 7, 8, 9, 10, 30, 30, 30, 20, 30, 30, 30, 27, 27, 27, 27, 27, 27, 17, 17, 17, 27, 17, 27, 28, 29, 30, 30, 28, 29, 30, 36,
//            1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 27, 27, 27, 27, 27, 27, 28, 29, 30, 27, 28, 29, 30, 36,
//            1, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 27, 28, 29, 30, 36,
//            1, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 29, 30, 36,
//            41, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 46
//};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelA::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint player_texture_id = Utility::load_texture("assets/player.png");
    GLuint slime_texture_id = Utility::load_texture("assets/slime.png");
    GLuint dungeon_texture_id = Utility::load_texture("assets/tileset.png");

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

    m_game_state.player = new Entity(player_texture_id, 1.0f, acceleration, 0.0f, player_walking_animation, 0.0f, 4, 0, 4, 4, 0.6f, 0.6f, PLAYER);
    m_game_state.player->set_position(glm::vec3(5.0f, -2.0f, 0.0f));
    m_game_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.player->set_speed(3.0f);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    m_game_state.enemies[0] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.01f, 0.01f, ENEMY);
    m_game_state.enemies[0].set_ai_type(WALKER);
    m_game_state.enemies[0].set_ai_state(WALKING);
    m_game_state.enemies[0].set_position(glm::vec3(10.0f, -2.0f, 0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[1] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.01f, 0.01f, ENEMY);
    m_game_state.enemies[1].set_ai_type(WALKER);
    m_game_state.enemies[1].set_ai_state(WALKING);
    m_game_state.enemies[1].set_position(glm::vec3(15.0f, -2.0f, 0.0f));
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[2] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.01f, 0.01f, ENEMY);
    m_game_state.enemies[2].set_ai_type(WALKER);
    m_game_state.enemies[2].set_ai_state(WALKING);
    m_game_state.enemies[2].set_position(glm::vec3(20.0f, -2.0f, 0.0f));
    m_game_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    constexpr char BGM_FILEPATH[] = "assets/bgm.mp3";

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

void LevelA::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.enemies, 0, m_game_state.map);
    }

    glm::vec3 player_position = m_game_state.player->get_position();

    if (m_game_state.player->get_position().x >= 25.0f) {
        m_game_state.next_scene_id = 2;
    }
}

void LevelA::render(ShaderProgram* program)
{

    m_game_state.map->render(program);

    m_game_state.player->render(program);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].render(program);
    }
}