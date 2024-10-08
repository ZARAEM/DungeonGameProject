/**
* Author: Mearaj Ahmed
* Assignment: Make it out the Dungeon ?
* Date due: 2024-08-15, 1:00pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

// All assets from itch.io

#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
#define LEVEL1_LEFT_EDGE 5.0f

constexpr int PLAY_ONCE = 0,
NEXT_CHNL = -1,
MUTE_VOL = 0,
MILS_IN_SEC = 1000,
ALL_SFX_CHN = -1;


#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Entity.h"
#include "Map.h"
#include "Utility.h"
#include "Scene.h"
#include "LevelA.h"
#include "LevelB.h"
#include "LevelC.h"
#include "Effects.h"
#include "Menu.h"
#include "BetweenScreen.h"
#include "Win.h"
#include "Lose.h"

// ––––– CONSTANTS ––––– //
constexpr int WINDOW_WIDTH  = 640 * 2,
          WINDOW_HEIGHT = 480 * 2;

constexpr float BG_RED     = 40/256.0,
            BG_BLUE    = 20/256.0,
            BG_GREEN   = 28/256.0,
            BG_OPACITY = 1.0f;

constexpr int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

constexpr char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

constexpr char V_SHADER_PATH_NOLIGHT[] = "shaders/vertex_lit.glsl",
           F_SHADER_PATH_NOLIGHT[] = "shaders/fragment_lit.glsl";

constexpr float MILLISECONDS_IN_SECOND = 1000.0;

enum AppStatus { RUNNING, TERMINATED };

// ––––– GLOBAL VARIABLES ––––– //
Scene  *g_current_scene;
Menu *mainmenu;
LevelA* levela;
LevelB* levelb;
LevelC* levelc;
Win* win;
Lose* lose;

Effects *g_effects;
Scene   *g_levels[6];

SDL_Window* g_display_window;

ShaderProgram g_shader_program;
ShaderProgram g_shader_program_nolight;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

bool g_is_colliding_bottom = false;

bool g_foundlight = false;

AppStatus g_app_status = RUNNING;

void switch_to_scene(Scene *scene);
void initialise();
void process_input();
void update();
void render();
void shutdown();

// ––––– GENERAL FUNCTIONS ––––– //
void switch_to_scene(Scene *scene)
{    
    g_current_scene = scene;
    g_current_scene->initialise(); // DON'T FORGET THIS STEP!

    if (scene == win) {
        glUseProgram(g_shader_program.get_program_id());
        g_current_scene = scene;
        g_current_scene->initialise();
    }

    if (scene == lose) {
        glUseProgram(g_shader_program.get_program_id());
        g_current_scene = scene;
        g_current_scene->initialise();
    }
}

void initialise()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("MAKE IT OUT THE DUNGEON ?",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    g_shader_program_nolight.load(V_SHADER_PATH_NOLIGHT, F_SHADER_PATH_NOLIGHT);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);

    g_shader_program_nolight.set_projection_matrix(g_projection_matrix);
    g_shader_program_nolight.set_view_matrix(g_view_matrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mainmenu = new Menu();
    levela = new LevelA();
    levelb = new LevelB();
    levelc = new LevelC();
    win = new Win();
    lose = new Lose();
    
    g_levels[0] = mainmenu;
    g_levels[1] = levela;
    g_levels[2] = levelb;
    g_levels[3] = levelc;
    g_levels[4] = lose;
    g_levels[5] = win;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    switch_to_scene(mainmenu);

    g_effects = new Effects(g_projection_matrix, g_view_matrix);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
}

void process_input()
{
    g_current_scene->get_state().player->set_movement(glm::vec3(0.0f));
    
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
            // End game
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_app_status = TERMINATED;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_q:
                    g_app_status = TERMINATED;
                    break;
                case SDLK_w:
                    break;
                case SDLK_a:
                    break;
                case SDLK_s:
                    break;
                case SDLK_d:
                    break;
                case SDLK_e:
                    if (g_current_scene == levelb) {
                        if (levelb->near_chest_bad()) {
                            switch_to_scene(lose);
                        }
                        else if (levelb->near_chest_good()) {
                            g_foundlight = true;
                        }
                    }
                }
            default:
                break;
        }
    }
    
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    if (g_current_scene == mainmenu) {
        if (key_state[SDL_SCANCODE_RETURN]) {
            glUseProgram(g_shader_program_nolight.get_program_id());
            switch_to_scene(levela);
            g_effects->start(FADEIN, 1.0f);
        }
    }
    
    if (g_current_scene == levela || g_current_scene == levelb || g_current_scene == levelc) {
        //Mix_Chunk* walk_sfx = Mix_LoadWAV("assets/walk.wav");
        //Mix_VolumeChunk(walk_sfx, MIX_MAX_VOLUME / 4);

        if (key_state[SDL_SCANCODE_W]) {
            g_current_scene->get_state().player->move_up();
            //Mix_PlayChannel(-1, walk_sfx, 0);
        }
        else if (key_state[SDL_SCANCODE_A]) {
            g_current_scene->get_state().player->move_left();
            //Mix_PlayChannel(-1, walk_sfx, 0);
        }
        else if (key_state[SDL_SCANCODE_S]) {
            g_current_scene->get_state().player->move_down();
            //Mix_PlayChannel(-1, walk_sfx, 0);
        }
        else if (key_state[SDL_SCANCODE_D]) {
            g_current_scene->get_state().player->move_right();
            //Mix_PlayChannel(-1, walk_sfx, 0);
        }
    }
}

void update()
{
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND; 
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    delta_time += g_accumulator;
    
    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }
    
    while (delta_time >= FIXED_TIMESTEP) {
        g_current_scene->update(FIXED_TIMESTEP);
        g_effects->update(FIXED_TIMESTEP);
        
        if (g_is_colliding_bottom == false && g_current_scene->get_state().player->get_collided_bottom()) g_effects->start(SHAKE, 1.0f);
        
        g_is_colliding_bottom = g_current_scene->get_state().player->get_collided_bottom();
        
        delta_time -= FIXED_TIMESTEP;
    }
    
    g_accumulator = delta_time;
    
    g_view_matrix = glm::mat4(1.0f);
    
    if (g_current_scene->get_state().player->get_position().x > LEVEL1_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->get_state().player->get_position().x, 3.75, 0));
    } else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-5, 3.75, 0));
    }
    g_view_matrix = glm::translate(g_view_matrix, g_effects->get_view_offset());

}

void render()
{

    GLuint texture_id = Utility::load_texture("assets/font1.png");

    g_shader_program_nolight.set_light_position(g_current_scene->get_state().player->get_position());

    g_shader_program.set_view_matrix(g_view_matrix);
    g_shader_program_nolight.set_view_matrix(g_view_matrix);
       
    glClear(GL_COLOR_BUFFER_BIT);
       
    // ————— RENDERING THE SCENE (i.e. map, character, enemies...) ————— //
    if (g_current_scene == levelb && !g_foundlight) {
        g_current_scene->render(&g_shader_program_nolight);
    }
    else if (g_current_scene == levelb && g_foundlight) {
        g_current_scene->render(&g_shader_program);

        Utility::draw_text(&g_shader_program, texture_id, "CONGRATS!", 0.15f, 0.0f, glm::vec3(2.0f, -3.0f, 0.0f));
        Utility::draw_text(&g_shader_program, texture_id, "YOU TURNED", 0.15f, 0.0f, glm::vec3(2.0f, -3.2f, 0.0f));
        Utility::draw_text(&g_shader_program, texture_id, " THE LIGHTS ON!", 0.15f, 0.0f, glm::vec3(2.0f, -3.4f, 0.0f));
    }
    else if (g_current_scene == levela) {
        g_current_scene->render(&g_shader_program_nolight);
    }
    else {
        g_current_scene->render(&g_shader_program);
    }
       
    g_effects->render();
    
    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{    
    SDL_Quit();
    
    delete mainmenu;
    delete levela;
    delete levelb;
    delete levelc;
    delete g_effects;
    delete lose;
    delete win;
}

// ––––– DRIVER GAME LOOP ––––– //
int main(int argc, char* argv[])
{
    initialise();
    
    while (g_app_status == RUNNING)
    {
        process_input();
        update();

        if (g_current_scene->get_state().next_scene_id >= 0) {
            g_effects->start(FADEIN, 1.0f);
            switch_to_scene(g_levels[g_current_scene->get_state().next_scene_id]);
        }
        
        render();
    }
    
    shutdown();
    return 0;
}
