#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 32
#define LEVEL_HEIGHT 10

#define NUM_MAPS 2

constexpr int PLAY_ONCE = 0,
NEXT_CHNL = -1,
MUTE_VOL = 0,
MILS_IN_SEC = 1000,
ALL_SFX_CHN = -1;

unsigned int LEVELB_DATA[] =
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

//unsigned int LEVELB_OVERLAY[] =
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

LevelB::~LevelB()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelB::initialise()
{
    m_game_state.count = 0;
    m_game_state.next_scene_id = -1;

    GLuint player_texture_id = Utility::load_texture("assets/player.png");
    GLuint slime_texture_id = Utility::load_texture("assets/slime.png");
    GLuint dungeon_texture_id = Utility::load_texture("assets/tileset.png");
    GLuint chest_texture_id = Utility::load_texture("assets/chest.png");
    GLuint crystal_texture_id = Utility::load_texture("assets/crystal.png");

    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, dungeon_texture_id, 0.8f, 10, 10);

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

    //int chest_animation[4][4] =
    //{
    //    { 1,1,1,1 }, // left
    //    { 1,1,1,1 }, // right
    //    { 1,1,1,1 }, // up
    //    { 1,1,1,1 } // down
    //};

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    m_game_state.walk_sfx = Mix_LoadWAV("assets/walk.wav");

    m_game_state.player = new Entity(player_texture_id, 1.0f, acceleration, 0.0f, player_walking_animation, 0.0f, 4, 0, 4, 4, 0.3f, 0.3f, PLAYER);
    m_game_state.player->set_walk_sfx(m_game_state.walk_sfx);
    m_game_state.player->set_position(glm::vec3(1.0f, -1.0f, 0.0f));
    m_game_state.player->set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.player->set_speed(2.0f);

    m_game_state.enemies = new Entity[5];

    m_game_state.enemies[0] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.2f, 0.2f, ENEMY);
    m_game_state.enemies[0].set_speed(1.1f);
    m_game_state.enemies[0].set_ai_type(GUARD);
    m_game_state.enemies[0].set_ai_state(IDLE);
    m_game_state.enemies[0].set_position(glm::vec3(10.0f, -1.0f, 0.0f));
    m_game_state.enemies[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[1] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.2f, 0.2f, ENEMY);
    m_game_state.enemies[1].set_speed(1.1f);
    m_game_state.enemies[1].set_ai_type(GUARD);
    m_game_state.enemies[1].set_ai_state(IDLE);
    m_game_state.enemies[1].set_position(glm::vec3(10.0f, -5.0f, 0.0f));
    m_game_state.enemies[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[2] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.2f, 0.2f, ENEMY);
    m_game_state.enemies[2].set_speed(1.1f);
    m_game_state.enemies[2].set_ai_type(GUARD);
    m_game_state.enemies[2].set_ai_state(IDLE);
    m_game_state.enemies[2].set_position(glm::vec3(9.0f, -1.0f, 0.0f));
    m_game_state.enemies[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[3] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.2f, 0.2f, ENEMY);
    m_game_state.enemies[3].set_speed(1.1f);
    m_game_state.enemies[3].set_ai_type(GUARD);
    m_game_state.enemies[3].set_ai_state(IDLE);
    m_game_state.enemies[3].set_position(glm::vec3(9.0f, -1.0f, 0.0f));
    m_game_state.enemies[3].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.enemies[4] = Entity(slime_texture_id, 1.0f, acceleration, 0.0f, slime_walking_animation, 0.0f, 4, 0, 4, 4, 0.2f, 0.2f, ENEMY);
    m_game_state.enemies[4].set_speed(1.1f);
    m_game_state.enemies[4].set_ai_type(GUARD);
    m_game_state.enemies[4].set_ai_state(IDLE);
    m_game_state.enemies[4].set_position(glm::vec3(9.0f, -1.0f, 0.0f));
    m_game_state.enemies[4].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.chests = new Entity[2];

    m_game_state.chests[0] = Entity(chest_texture_id, 0.0f, 0.3f, 0.3f, CHEST);
    m_game_state.chests[0].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.chests[0].set_speed(0.0f);
    m_game_state.chests[0].set_position(glm::vec3(4.0f, -1.0f, 0.0f));
    m_game_state.chests[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.chests[1] = Entity(chest_texture_id, 0.0f, 0.3f, 0.3f, CHEST);
    m_game_state.chests[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.chests[1].set_speed(0.0f);
    m_game_state.chests[1].set_position(glm::vec3(6.0f, -1.0f, 0.0f));
    m_game_state.chests[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals = new Entity[10];

    m_game_state.crystals[0] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[0].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[0].set_speed(0.0f);
    m_game_state.crystals[0].set_position(glm::vec3(5.0f, -1.0f, 0.0f));
    m_game_state.crystals[0].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[1] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[1].set_speed(0.0f);
    m_game_state.crystals[1].set_position(glm::vec3(5.0f, -3.0f, 0.0f));
    m_game_state.crystals[1].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[2] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[2].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[2].set_speed(0.0f);
    m_game_state.crystals[2].set_position(glm::vec3(5.0f, -5.0f, 0.0f));
    m_game_state.crystals[2].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[3] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[3].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[3].set_speed(0.0f);
    m_game_state.crystals[3].set_position(glm::vec3(10.0f, -1.0f, 0.0f));
    m_game_state.crystals[3].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[4] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[4].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[4].set_speed(0.0f);
    m_game_state.crystals[4].set_position(glm::vec3(10.0f, -3.0f, 0.0f));
    m_game_state.crystals[4].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[5] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[5].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[5].set_speed(0.0f);
    m_game_state.crystals[5].set_position(glm::vec3(10.0f, -4.0f, 0.0f));
    m_game_state.crystals[5].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[6] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[6].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[6].set_speed(0.0f);
    m_game_state.crystals[6].set_position(glm::vec3(10.0f, -5.0f, 0.0f));
    m_game_state.crystals[6].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[7] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[7].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[7].set_speed(0.0f);
    m_game_state.crystals[7].set_position(glm::vec3(15.0f, -1.0f, 0.0f));
    m_game_state.crystals[7].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[8] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[8].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[8].set_speed(0.0f);
    m_game_state.crystals[8].set_position(glm::vec3(15.0f, -3.0f, 0.0f));
    m_game_state.crystals[8].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    m_game_state.crystals[9] = Entity(crystal_texture_id, 0.0f, 0.3f, 0.3f, CRYSTAL);
    m_game_state.crystals[9].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.crystals[9].set_speed(0.0f);
    m_game_state.crystals[9].set_position(glm::vec3(20.0f, -2.0f, 0.0f));
    m_game_state.crystals[9].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));

    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    constexpr char BGM_FILEPATH[] = "assets/bgm.mp3";

    m_game_state.bgm = Mix_LoadMUS(BGM_FILEPATH);
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

    m_game_state.coin_sfx = Mix_LoadWAV("assets/coin.wav");

    Mix_VolumeChunk(m_game_state.coin_sfx, MIX_MAX_VOLUME / 4);
}

void LevelB::update(float delta_time)
{
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.enemies, 5, m_game_state.map);

    m_game_state.player->update(0, m_game_state.player, m_game_state.chests, 2, m_game_state.map);

    for (int i = 0; i < 5; i++) {
        if (m_game_state.player->check_collision(&m_game_state.enemies[i]) && (m_game_state.enemies[i].get_entity_type() == ENEMY)) {
            m_game_state.next_scene_id = 4;
        }
        else {
            m_game_state.enemies[i].update(delta_time, m_game_state.player, m_game_state.enemies, 0, m_game_state.map);
        }
    }

    for (int i = 0; i < 2; i++) {
        m_game_state.chests[i].update(delta_time, m_game_state.player, m_game_state.chests, 0, m_game_state.map);
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

    if (m_game_state.player->get_position().x >= 25.0f) {
        if (m_game_state.count == 10) {
            m_game_state.next_scene_id = 3;
        }
        else {
            m_game_state.next_scene_id = 4;
        }
    }

    if (near_chest_bad()) {
        BAD_CHEST = true;
    }

    if (near_chest_good()) {
        GOOD_CHEST = true;
    }
}

void LevelB::render(ShaderProgram* program)
{
    GLuint texture_id = Utility::load_texture("assets/font1.png");

    m_game_state.map->render(program);

    m_game_state.player->render(program);

    for (int i = 0; i < 5; i++) {
        m_game_state.enemies[i].render(program);
    }

    for (int i = 0; i < 10; i++) {
        if (m_game_state.crystals[i].get_active()) {
            m_game_state.crystals[i].render(program);
        }
    }

    for (int i = 0; i < 2; i++) {
        m_game_state.chests[i].render(program);
    }

    Utility::draw_text(program, texture_id, "Press e near a chest to open, choose wisely!", 0.15f, 0.0f, glm::vec3(3.0f, -1.0f, 0.0f));

    Utility::draw_text(program, texture_id, std::to_string(m_game_state.count) + "/10", 0.4f, 0.0f, glm::vec3(5.0f, -2.0f, 0.0f));
}

bool LevelB::near_chest_good() {
    if (m_game_state.player->is_near(&m_game_state.chests[0])) {
        return true;
    }
    return false;
}

bool LevelB::near_chest_bad() {
    if (m_game_state.player->is_near(&m_game_state.chests[1])) {
        return true;
    }
    return false;
}