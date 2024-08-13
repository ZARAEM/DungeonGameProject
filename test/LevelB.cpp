#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 20

constexpr char SPRITESHEET_FILEPATH[] = "assets/characters.png";

unsigned int LEVELB_DATA[] =
{
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
    6,7,8,9,16,17,18,19,26,27,28,29,6,7,8,9,16,17,18,19,26,27,28,29,6,7,6,7,8,9,16,17,
};

LevelB::~LevelB()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelB::initialise()
{
    m_game_state.next_scene_id = -1;

    GLuint dungeon_texture_id = Utility::load_texture("assets/tileset.png");

    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, dungeon_texture_id, 0.8f, 10, 10);

    int player_walking_animation[4][4] =
    {
        { 0, 1, 0, 1 },
        { 0, 1, 0, 1 },
        { 0, 1, 0, 1 },
        { 0, 1, 0, 1 }
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    m_game_state.player = new Entity(player_texture_id, 1.0f, acceleration, 0.0f, player_walking_animation, 0.25f, 2, 0, 7, 2, 1.0f, 1.0f, PLAYER);

    m_game_state.enemies = new Entity[ENEMY_COUNT];

    m_game_state.enemies[0] = Entity(dungeon_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, WALKER, WALKING);
    m_game_state.enemies[0].set_position(glm::vec3(10.0f, -2.0f, 0.0f));

    m_game_state.enemies[1] = Entity(dungeon_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
    m_game_state.enemies[1].set_position(glm::vec3(15.0f, -2.0f, 0.0f));

    m_game_state.enemies[2] = Entity(dungeon_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, WALKER, WALKING);
    m_game_state.enemies[2].set_position(glm::vec3(20.0f, -2.0f, 0.0f));

    m_game_state.enemies[3] = Entity(dungeon_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
    m_game_state.enemies[3].set_position(glm::vec3(15.0f, -2.0f, 0.0f));

    m_game_state.enemies[4] = Entity(dungeon_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, WALKER, WALKING);
    m_game_state.enemies[4].set_position(glm::vec3(20.0f, -2.0f, 0.0f));

    m_game_state.player->set_position(glm::vec3(5.0f, -2.0f, 0.0f));
    m_game_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    constexpr char BGM_FILEPATH[] = "assets/bgm.mp3";

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

void LevelB::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, ENEMY_COUNT, m_game_state.map);

    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.enemies, 3, m_game_state.map);
    }

    glm::vec3 player_position = m_game_state.player->get_position();

    if (m_game_state.player->get_position().y > 10.0f) {
        player_position.y = 10.0f;
        m_game_state.player->set_position(player_position);
        m_game_state.player->set_velocity(glm::vec3(m_game_state.player->get_velocity().x, 0.0f, 0.0f));
    }
    else if (m_game_state.player->get_position().y < -10.0f) {
        player_position.y = -10.0f;
        m_game_state.player->set_position(player_position);
        m_game_state.player->set_velocity(glm::vec3(m_game_state.player->get_velocity().x, 0.0f, 0.0f));
    }

    //if (m_game_state.player->get_position().y < -10.0f) m_game_state.next_scene_id = 1;
}

void LevelB::render(ShaderProgram* program)
{
    m_game_state.map->render(program);
    m_game_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++) {
        m_game_state.enemies[i].render(program);
    }
}