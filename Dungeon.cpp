#include "Dungeon.hpp"
#define DUNGEON_WIDTH 10
#define DUNGEON_HEIGHT 10

#define DUNGEON_ENEMY_COUNT 1
using namespace std;

void Dungeon::Initialize(Entity *player) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("medieval_tilesheet_2X.png");
    state.map = new Map(DUNGEON_WIDTH, DUNGEON_HEIGHT, dungeon_data, mapTextureID, 1.0f, 24, 14);
    // Initialize Player
    state.player = player;
    
    state.enemies = new Entity[DUNGEON_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("pikachu.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(5, -3.0f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        state.enemies[i].isActive = true;
    }
    
}
void Dungeon::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, DUNGEON_ENEMY_COUNT, state.map);
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, DUNGEON_ENEMY_COUNT, state.map);
    }
    if (state.player->resetLocation == true) {
        state.player->resetLocation = false;
        state.player->numLives -= 1;
        state.nextScene = 2;
        state.player->position = glm::vec3(7, -10, 0);
    }
    if (state.player->numLives == 0) {
        state.nextScene = 0;
    }
    bool anyAlive = false;
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        if (state.enemies[i].isActive == true) {
            anyAlive = true;
            break;
        }
    }

    // touches key part
    if (dungeon_data[25] != 208 && (state.player->position.x >= 4 && state.player->position.x < 6) && (state.player->position.y <= -1 && state.player->position.y >= -3)) {
        state.player->numDungeonsCleared += 1;

        dungeon_data[24] = 208;
        dungeon_data[25] = 208;
        state.enemies[0].newPosition = state.enemies[0].position;
        state.nextScene = state.player->currentSceneNum;
        state.enemies[0].position = state.enemies[0].newPosition;
        
    }
    // exiting dungeon
    if ((state.player->position.x >= 4 && state.player->position.x <= 7) && (state.player->position.y <= -8 && state.player->position.y >= -10)) {
        state.nextScene = 2;
        state.player->position.x = state.player->newPosition.x;
        state.player->position.y = state.player->newPosition.y;
    }
}
void Dungeon::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < DUNGEON_ENEMY_COUNT; ++i) {
        state.enemies[i].Render(program);
    }
}
