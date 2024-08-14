#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 10
#define LEVEL_HEIGHT 10

unsigned int LEVELC_DATA[] =
{
            1, 4, 3, 4, 3, 4, 2, 2, 4, 6,
            11, 7, 7, 7, 7, 7, 8, 9, 10, 16,
            11, 17, 17, 17, 17, 7, 8, 9, 10, 16,
            21, 7, 8, 9, 10, 7, 8, 9, 10, 26,
            21, 7, 8, 9, 10, 10, 8, 9, 10, 26,
            21, 7, 8, 9, 10, 20, 8, 9, 10, 26,
            21, 7, 8, 9, 10, 30, 10, 10, 10, 26,
            31, 17, 18, 19, 20, 30, 20, 20, 20, 16,
            31, 27, 28, 29, 30, 30, 30, 30, 30, 16,
            41, 42, 42, 43, 43, 44, 44, 45, 45, 46
};

LevelC::~LevelC()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete[]    m_game_state.crystals;
    Mix_FreeMusic(m_game_state.bgm);
    Mix_FreeChunk(m_game_state.walk_sfx);
    Mix_FreeChunk(m_game_state.coin_sfx);
}

void LevelC::initialise() {

    m_game_state.next_scene_id = -1;
    m_game_state.count = 0;

    GLuint player_texture_id = Utility::load_texture("assets/player.png");
    GLuint slime_texture_id = Utility::load_texture("assets/slime.png");
    GLuint dungeon_texture_id = Utility::load_texture("assets/tileset.png");
    GLuint crystal_texture_id = Utility::load_texture("assets/crystal.png");

    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, dungeon_texture_id, 0.8f, 10, 10);

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
    m_game_state.player->set_position(glm::vec3(1.0f, -0.8f, 0.0f));
    m_game_state.player->set_acceleration(acceleration);
    m_game_state.player->set_speed(2.0f);

    m_game_state.enemies = new Entity[32];

    m_game_state.enemies[0] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[0].set_speed(0.0f);
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    m_game_state.enemies[0].set_position(glm::vec3(1.5f, -1.0f, 0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[1] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[1].set_speed(0.0f);
    m_game_state.enemies[1].set_ai_type(GUARD);
    m_game_state.enemies[1].set_ai_state(IDLE);
    m_game_state.enemies[1].set_position(glm::vec3(1.5f, -0.5f, 0.0f));
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[2] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[2].set_speed(0.0f);
    m_game_state.enemies[2].set_ai_type(GUARD);
    m_game_state.enemies[2].set_ai_state(IDLE);
    m_game_state.enemies[2].set_position(glm::vec3(1.0f, -0.5f, 0.0f));
    m_game_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[3] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[3].set_speed(0.0f);
    m_game_state.enemies[3].set_ai_type(GUARD);
    m_game_state.enemies[3].set_ai_state(IDLE);
    m_game_state.enemies[3].set_position(glm::vec3(0.5f, -0.5f, 0.0f));
    m_game_state.enemies[3].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[4] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[4].set_speed(0.0f);
    m_game_state.enemies[4].set_ai_type(GUARD);
    m_game_state.enemies[4].set_ai_state(IDLE);
    m_game_state.enemies[4].set_position(glm::vec3(0.5f, -1.0f, 0.0f));
    m_game_state.enemies[4].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[5] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[5].set_speed(0.0f);
    m_game_state.enemies[5].set_ai_type(GUARD);
    m_game_state.enemies[5].set_ai_state(IDLE);
    m_game_state.enemies[5].set_position(glm::vec3(0.5f, -1.5f, 0.0f));
    m_game_state.enemies[5].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[6] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[6].set_speed(0.0f);
    m_game_state.enemies[6].set_ai_type(GUARD);
    m_game_state.enemies[6].set_ai_state(IDLE);
    m_game_state.enemies[6].set_position(glm::vec3(0.5f, -2.0f, 0.0f));
    m_game_state.enemies[6].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[7] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[7].set_speed(0.0f);
    m_game_state.enemies[7].set_ai_type(GUARD);
    m_game_state.enemies[7].set_ai_state(IDLE);
    m_game_state.enemies[7].set_position(glm::vec3(0.5f, -2.5f, 0.0f));
    m_game_state.enemies[7].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[8] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[8].set_speed(0.0f);
    m_game_state.enemies[8].set_ai_type(GUARD);
    m_game_state.enemies[8].set_ai_state(IDLE);
    m_game_state.enemies[8].set_position(glm::vec3(0.5f, -3.0f, 0.0f));
    m_game_state.enemies[8].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[9] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[9].set_speed(0.0f);
    m_game_state.enemies[9].set_ai_type(GUARD);
    m_game_state.enemies[9].set_ai_state(IDLE);
    m_game_state.enemies[9].set_position(glm::vec3(0.5f, -3.5f, 0.0f));
    m_game_state.enemies[9].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[10] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[10].set_speed(0.0f);
    m_game_state.enemies[10].set_ai_type(GUARD);
    m_game_state.enemies[10].set_ai_state(IDLE);
    m_game_state.enemies[10].set_position(glm::vec3(0.5f, -4.0f, 0.0f));
    m_game_state.enemies[10].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[11] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[11].set_speed(0.0f);
    m_game_state.enemies[11].set_ai_type(GUARD);
    m_game_state.enemies[11].set_ai_state(IDLE);
    m_game_state.enemies[11].set_position(glm::vec3(1.5f, -4.0f, 0.0f));
    m_game_state.enemies[11].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[12] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[12].set_speed(0.0f);
    m_game_state.enemies[12].set_ai_type(GUARD);
    m_game_state.enemies[12].set_ai_state(IDLE);
    m_game_state.enemies[12].set_position(glm::vec3(1.5f, -3.5f, 0.0f));
    m_game_state.enemies[12].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[13] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[13].set_speed(0.0f);
    m_game_state.enemies[13].set_ai_type(GUARD);
    m_game_state.enemies[13].set_ai_state(IDLE);
    m_game_state.enemies[13].set_position(glm::vec3(1.5f, -3.0f, 0.0f));
    m_game_state.enemies[13].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[14] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[14].set_speed(0.0f);
    m_game_state.enemies[14].set_ai_type(GUARD);
    m_game_state.enemies[14].set_ai_state(IDLE);
    m_game_state.enemies[14].set_position(glm::vec3(1.5f, -2.5f, 0.0f));
    m_game_state.enemies[14].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[15] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[15].set_speed(0.0f);
    m_game_state.enemies[15].set_ai_type(GUARD);
    m_game_state.enemies[15].set_ai_state(IDLE);
    m_game_state.enemies[15].set_position(glm::vec3(1.5f, -2.0f, 0.0f));
    m_game_state.enemies[15].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[16] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[16].set_speed(0.0f);
    m_game_state.enemies[16].set_ai_type(GUARD);
    m_game_state.enemies[16].set_ai_state(IDLE);
    m_game_state.enemies[16].set_position(glm::vec3(1.5f, -1.5f, 0.0f));
    m_game_state.enemies[16].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[17] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[17].set_speed(0.0f);
    m_game_state.enemies[17].set_ai_type(GUARD);
    m_game_state.enemies[17].set_ai_state(IDLE);
    m_game_state.enemies[17].set_position(glm::vec3(0.5f, -4.5f, 0.0f));
    m_game_state.enemies[17].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[18] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[18].set_speed(0.0f);
    m_game_state.enemies[18].set_ai_type(GUARD);
    m_game_state.enemies[18].set_ai_state(IDLE);
    m_game_state.enemies[18].set_position(glm::vec3(0.5f, -5.0f, 0.0f));
    m_game_state.enemies[18].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[19] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[19].set_speed(0.0f);
    m_game_state.enemies[19].set_ai_type(GUARD);
    m_game_state.enemies[19].set_ai_state(IDLE);
    m_game_state.enemies[19].set_position(glm::vec3(1.0f, -5.0f, 0.0f));
    m_game_state.enemies[19].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[20] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[20].set_speed(0.0f);
    m_game_state.enemies[20].set_ai_type(GUARD);
    m_game_state.enemies[20].set_ai_state(IDLE);
    m_game_state.enemies[20].set_position(glm::vec3(1.5f, -5.0f, 0.0f));
    m_game_state.enemies[20].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[21] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[21].set_speed(0.0f);
    m_game_state.enemies[21].set_ai_type(GUARD);
    m_game_state.enemies[21].set_ai_state(IDLE);
    m_game_state.enemies[21].set_position(glm::vec3(2.0f, -5.0f, 0.0f));
    m_game_state.enemies[21].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[22] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[22].set_speed(0.0f);
    m_game_state.enemies[22].set_ai_type(GUARD);
    m_game_state.enemies[22].set_ai_state(IDLE);
    m_game_state.enemies[22].set_position(glm::vec3(2.5f, -5.0f, 0.0f));
    m_game_state.enemies[22].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[23] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[23].set_speed(0.0f);
    m_game_state.enemies[23].set_ai_type(GUARD);
    m_game_state.enemies[23].set_ai_state(IDLE);
    m_game_state.enemies[23].set_position(glm::vec3(2.5f, -4.0f, 0.0f));
    m_game_state.enemies[23].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[24] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[24].set_speed(0.0f);
    m_game_state.enemies[24].set_ai_type(GUARD);
    m_game_state.enemies[24].set_ai_state(IDLE);
    m_game_state.enemies[24].set_position(glm::vec3(2.0f, -4.0f, 0.0f));
    m_game_state.enemies[24].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[25] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[25].set_speed(0.0f);
    m_game_state.enemies[25].set_ai_type(GUARD);
    m_game_state.enemies[25].set_ai_state(IDLE);
    m_game_state.enemies[25].set_position(glm::vec3(3.0f, -3.5f, 0.0f));
    m_game_state.enemies[25].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[26] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[26].set_speed(0.0f);
    m_game_state.enemies[26].set_ai_type(GUARD);
    m_game_state.enemies[26].set_ai_state(IDLE);
    m_game_state.enemies[26].set_position(glm::vec3(3.0f, -5.5f, 0.0f));
    m_game_state.enemies[26].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[27] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[27].set_speed(0.0f);
    m_game_state.enemies[27].set_ai_type(GUARD);
    m_game_state.enemies[27].set_ai_state(IDLE);
    m_game_state.enemies[27].set_position(glm::vec3(3.5f, -5.5f, 0.0f));
    m_game_state.enemies[27].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[28] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[28].set_speed(0.0f);
    m_game_state.enemies[28].set_ai_type(GUARD);
    m_game_state.enemies[28].set_ai_state(IDLE);
    m_game_state.enemies[28].set_position(glm::vec3(3.5f, -3.5f, 0.0f));
    m_game_state.enemies[28].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[29] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[29].set_speed(0.0f);
    m_game_state.enemies[29].set_ai_type(GUARD);
    m_game_state.enemies[29].set_ai_state(IDLE);
    m_game_state.enemies[29].set_position(glm::vec3(4.0f, -4.0f, 0.0f));
    m_game_state.enemies[29].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[30] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[30].set_speed(0.0f);
    m_game_state.enemies[30].set_ai_type(GUARD);
    m_game_state.enemies[30].set_ai_state(IDLE);
    m_game_state.enemies[30].set_position(glm::vec3(4.0f, -4.5f, 0.0f));
    m_game_state.enemies[30].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[31] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.1f, 0.1f, ENEMY);
    m_game_state.enemies[31].set_speed(0.0f);
    m_game_state.enemies[31].set_ai_type(GUARD);
    m_game_state.enemies[31].set_ai_state(IDLE);
    m_game_state.enemies[31].set_position(glm::vec3(4.0f, -5.0f, 0.0f));
    m_game_state.enemies[31].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));


    //m_game_state.chests = new Entity[0];

    m_game_state.crystals = new Entity[10];

    m_game_state.crystals[0] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[0].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[0].set_speed(0.0f);
    m_game_state.crystals[0].set_position(glm::vec3(1.0f, -1.5f, 0.0f));
    m_game_state.crystals[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[1] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[1].set_speed(0.0f);
    m_game_state.crystals[1].set_position(glm::vec3(1.0f, -2.0f, 0.0f));
    m_game_state.crystals[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[2] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[2].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[2].set_speed(0.0f);
    m_game_state.crystals[2].set_position(glm::vec3(1.0f, -2.5f, 0.0f));
    m_game_state.crystals[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[3] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[3].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[3].set_speed(0.0f);
    m_game_state.crystals[3].set_position(glm::vec3(1.0f, -3.0f, 0.0f));
    m_game_state.crystals[3].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[4] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[4].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[4].set_speed(0.0f);
    m_game_state.crystals[4].set_position(glm::vec3(1.0f, -3.5f, 0.0f));
    m_game_state.crystals[4].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[5] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[5].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[5].set_speed(0.0f);
    m_game_state.crystals[5].set_position(glm::vec3(1.0f, -4.0f, 0.0f));
    m_game_state.crystals[5].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[6] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[6].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[6].set_speed(0.0f);
    m_game_state.crystals[6].set_position(glm::vec3(1.0f, -4.5f, 0.0f));
    m_game_state.crystals[6].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[7] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[7].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[7].set_speed(0.0f);
    m_game_state.crystals[7].set_position(glm::vec3(1.5f, -4.5f, 0.0f));
    m_game_state.crystals[7].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[8] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[8].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[8].set_speed(0.0f);
    m_game_state.crystals[8].set_position(glm::vec3(2.0f, -4.5f, 0.0f));
    m_game_state.crystals[8].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[9] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[9].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[9].set_speed(0.0f);
    m_game_state.crystals[9].set_position(glm::vec3(3.0f, -4.5f, 0.0f));
    m_game_state.crystals[9].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

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

void LevelC::update(float delta_time)
{
    if (m_game_state.player->get_movement() != glm::vec3(0.0f, 0.0f, 0.0f)) {
        Mix_PlayChannel(1, m_game_state.walk_sfx, 0);
    }

    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, 3, m_game_state.map);

    for (int i = 0; i < 32; i++) {
        if (m_game_state.player->check_collision(&m_game_state.enemies[i]) && (m_game_state.enemies[i].get_entity_type() == ENEMY)) {
            m_game_state.next_scene_id = 4;
        }
        else {
            m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.enemies, 0, m_game_state.map);
        }
    }

    for (int i = 0; i < 10; i++) {
        m_game_state.crystals[i].update(delta_time, m_game_state.player, m_game_state.crystals, 0, m_game_state.map);

        if (m_game_state.player->check_collision(&m_game_state.crystals[i])) {
            m_game_state.crystals[i].deactivate();

            Mix_PlayChannel(-1, m_game_state.coin_sfx, 0);
            m_game_state.count += 1;
        }
    }

    glm::vec3 player_position = m_game_state.player->get_position();

    if (m_game_state.count == 10) {
        m_game_state.next_scene_id = 5;
    }
}

void LevelC::render(ShaderProgram* program)
{
    GLuint texture_id = Utility::load_texture("assets/font1.png");

    m_game_state.map->render(program);

    m_game_state.player->render(program);

    for (int i = 0; i < 32; i++) {
        m_game_state.enemies[i].render(program);
    }

    for (int i = 0; i < 10; i++) {
        if (m_game_state.crystals[i].get_active()) {
            m_game_state.crystals[i].render(program);
        }
    }

    Utility::draw_text(program, texture_id, std::to_string(m_game_state.count) + "/10", 0.4f, 0.0f, glm::vec3(5.0f, -2.0f, 0.0f));
}