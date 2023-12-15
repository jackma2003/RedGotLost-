/**
* Author:  Jack Ma
* Assignment: Red Got Lost!
* Date due: 2023-12-15, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#include <SDL_mixer.h>

#include "Entity.h"
#include "Map.hpp"

#include <iostream>
#include <vector>

#include "Util.hpp"

#include "Scene.hpp"
#include "Menu.hpp"
#include "Main1.hpp"
#include "Dungeon.hpp"
#include "Lose.hpp"
#include "Win.hpp"

using namespace std;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

Mix_Music *music;
Mix_Chunk *bounce;

// Add some variables and SwitchToScene function
Scene *currentScene;
Scene *sceneList[14];

void SwitchToScene(Scene *scene) {
    Entity *player;
    if (currentScene == nullptr) {
        player = new Entity();
        player->entityType = PLAYER;
        player->position = glm::vec3(7, -10, 0);
        player->movement = glm::vec3(0);
        player->acceleration = glm::vec3(0, 0, 0);
        player->speed = 3.0f;
        player->textureID = Util::LoadTexture("player_red.png");
        
        player->animRight = new int[4] {8, 9, 10, 11};
        player->animLeft = new int[4] {4, 5, 6, 7};
        player->animUp = new int[4] {12, 13, 14, 15};
        player->animDown = new int[4] {0, 1, 2, 3};
        
        player->animIndices = player->animRight;
        player->animFrames = 4;
        player->animIndex = 0;
        player->animTime = 0;
        player->animCols = 4;
        player->animRows = 4;
        
        player->numLives = 3;
        
        player->height = 0.8f;
        player->width = 0.8f;
        player->numDungeonsCleared = 0;
        
    } else {
        player = currentScene->state.player;
    }
    currentScene = scene;
    currentScene->Initialize(player);
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("Red Got Lost!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    glViewport(0, 0, 640, 480);
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Audio stuff
    // Start Audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    music = Mix_LoadMUS("Opening.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
    
    // Roblox death sound lol
    bounce = Mix_LoadWAV("bounce.wav");
    

    sceneList[0] = new Lose();
    sceneList[1] = new Win();
    sceneList[2] = new Main1();
    for (int i = 3; i < 13; ++i) {
        sceneList[i] = new Dungeon();
    }
    sceneList[13] = new Menu();
    SwitchToScene(sceneList[13]);
}

void ProcessInput() {
    
    currentScene->state.player->movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // Move the player left
                        break;
                        
                    case SDLK_RIGHT:
                        // Move the player right
                        break;
                        
                    case SDLK_SPACE:
                        break;
                    case SDLK_RETURN:
                        if (currentScene == sceneList[13]) {
                            currentScene->Update(-1);
                        }
                }
                break; // SDL_KEYDOWN
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        currentScene->state.player->movement.x = -1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animLeft;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        currentScene->state.player->movement.x = 1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animRight;
    }
    else if (keys[SDL_SCANCODE_UP]) {
        currentScene->state.player->movement.y = 1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animUp;
    }
    else if (keys[SDL_SCANCODE_DOWN]) {
        currentScene->state.player->movement.y = -1.0f;
        currentScene->state.player->animIndices = currentScene->state.player->animDown;
    }
    

    if (glm::length(currentScene->state.player->movement) > 1.0f) {
        currentScene->state.player->movement = glm::normalize(currentScene->state.player->movement);
    }

}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;
void Update() {
   float ticks = (float)SDL_GetTicks() / 1000.0f;
   float deltaTime = ticks - lastTicks;
   lastTicks = ticks;
   deltaTime += accumulator;
   if (deltaTime < FIXED_TIMESTEP) {
       accumulator = deltaTime;
       return;
   }
   while (deltaTime >= FIXED_TIMESTEP) {
       // Update. Notice it's FIXED_TIMESTEP. Not deltaTime
       currentScene->Update(FIXED_TIMESTEP);
       
       deltaTime -= FIXED_TIMESTEP;
   }
   accumulator = deltaTime;
    
    // Inside Update
    viewMatrix = glm::mat4(1.0f);
    float x = 0;
    float y = 0;
    // fixes boundary on left side
    /*if (currentScene->state.player->position.x > 5) {
        x = -currentScene->state.player->position.x;
    } else {
        x = -5;
    }*/
    x = -currentScene->state.player->position.x;
    y = -currentScene->state.player->position.y;

    viewMatrix = glm::translate(viewMatrix, glm::vec3(x, y, 0));
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    program.SetViewMatrix(viewMatrix);
    
    currentScene->Render(&program);
    
    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();
        
        if (currentScene->state.nextScene >= 0) SwitchToScene(sceneList[currentScene->state.nextScene]);
        
        Render();
    }
    
    Shutdown();
    return 0;
}
