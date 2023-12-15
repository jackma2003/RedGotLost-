#include "Main1.hpp"
#define MAIN_WIDTH 14
#define MAIN_HEIGHT 20

#define MAIN_ENEMY_COUNT 0
using namespace std;

unsigned int main_data[] =
{
    110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
    110, 243, 243, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 110,
    110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
    110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
    110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 110,
    110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
    110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
    110, 243, 243, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
    110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 110,
    110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
    110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 110,
    110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
    110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 243, 243, 110,
    110, 110, 110, 110, 110, 110, 244, 246, 110, 110, 110, 110, 110, 110
};

/*
 {
     110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
     110, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110,
     110, 243, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 110, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 0, 110, 0, 0, 0, 0, 0, 0, 0, 0, 110, 110, 110,
     110, 243, 110, 0, 0, 0, 0, 0, 0, 0, 0, 0, 243, 110,
     110, 110, 110, 110, 110, 110, 2, 2, 110, 110, 110, 110, 110, 3
 };

 */

void Main1::Initialize(Entity *player) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("medieval_tilesheet_2X.png");
    state.map = new Map(MAIN_WIDTH, MAIN_HEIGHT, main_data, mapTextureID, 1.0f, 24, 14);
    state.player = player;
    
    /*state.enemies = new Entity[MAIN_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("ctg.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(5, -5.0f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    //state.enemies[0].jumpPower = 5.0f;
    state.enemies[0].acceleration = glm::vec3(0, 0, 0);
        
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(11, 0.0f, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = IDLE;
    //state.enemies[1].jumpPower = 5.0f;
    state.enemies[1].acceleration = glm::vec3(0, 0, 0);
    
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        state.enemies[i].isActive = true;
    }*/
}
void Main1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, MAIN_ENEMY_COUNT, state.map);
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, MAIN_ENEMY_COUNT, state.map);
    }
    if (state.player->numLives == 0) {
        state.nextScene = 4;
        state.player->position = glm::vec3(0,0,0);
    }
    bool anyAlive = false;
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        if (state.enemies[i].isActive == true) {
            anyAlive = true;
            break;
        }
    }
    //cout << "X: " << state.player->position.x << endl;
    //cout << "Y: " << state.player->position.y << endl;
    // open doors for exit
    if (state.player->numDungeonsCleared == 10) {
        main_data[272] = 0;
        main_data[273] = 0;
        state.nextScene = 2;
    }
    // exited building
    if ((state.player->position.x >= 5 && state.player->position.x <= 8) && (state.player->position.y <= -18.5 && state.player->position.y >= -20)) {
        state.nextScene = 1;
        state.player->currentSceneNum = 1;
    }
    // entered dungeon 1
    if ((state.player->position.x >= 0 && state.player->position.x <= 2) && (state.player->position.y <= 0 && state.player->position.y >= -2)) {
        state.nextScene = 3;
        state.player->currentSceneNum = 3;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(2.5f, -0.5f, 0);
    }
    // entered dungeon 2
    if ((state.player->position.x >= 0 && state.player->position.x <= 2) && (state.player->position.y <= -4 && state.player->position.y >= -6)) {
        state.nextScene = 4;
        state.player->currentSceneNum = 4;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(1.0f, -6.5f, 0);
    }

    // entered dungeon 3
    if ((state.player->position.x >= 0 && state.player->position.x <= 2) && (state.player->position.y <= -11.5 && state.player->position.y >= -13.5)) {
        state.nextScene = 5;
        state.player->currentSceneNum = 5;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(2.5f, -12.5f, 0);
    }

    // entered dungeon 4
    if ((state.player->position.x >= 0 && state.player->position.x <= 2) && (state.player->position.y <= -16.5 && state.player->position.y >= -18)) {
        state.nextScene = 6;
        state.player->currentSceneNum = 6;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(1.0f, -15.5f, 0);
    }

    // entered dungeon 5
    if ((state.player->position.x >= 11 && state.player->position.x <= 13) && (state.player->position.y <= 0 && state.player->position.y >= -2)) {
        state.nextScene = 7;
        state.player->currentSceneNum = 7;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(10.5f, -0.5f, 0);
    }

    // entered dungeon 6
    if ((state.player->position.x >= 11 && state.player->position.x <= 13) && (state.player->position.y <= -6.5 && state.player->position.y >= -8.5)) {
        state.nextScene = 8;
        state.player->currentSceneNum = 8;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(10.5f, -7.5f, 0);
    }

    // entered dungeon 7
    if ((state.player->position.x >= 11 && state.player->position.x <= 13) && (state.player->position.y <= -12.5 && state.player->position.y >= -14.5)) {
        state.nextScene = 9;
        state.player->currentSceneNum = 9;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(10.5f, -13.5f, 0);
    }

    // entered dungeon 8
    if ((state.player->position.x >= 11 && state.player->position.x <= 13) && (state.player->position.y <= -14.5 && state.player->position.y >= -16.5)) {
        state.nextScene = 10;
        state.player->currentSceneNum = 10;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(10.5f, -15.5f, 0);
    }

    // entered dungeon 9
    if ((state.player->position.x >= 0 && state.player->position.x <= 2) && (state.player->position.y <= -9 && state.player->position.y >= -10)) {
        state.nextScene = 11;
        state.player->currentSceneNum = 11;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(1.5f, -10.5f, 0);
    }

    // entered dungeon 10
    if ((state.player->position.x >= 11 && state.player->position.x <= 13) && (state.player->position.y <= -16.5 && state.player->position.y >= -18.5)) {
        state.nextScene = 12;
        state.player->currentSceneNum = 12;
        state.player->position.x = 4.5f;
        state.player->position.y = -7.0f;
        state.player->newPosition = glm::vec3(10.5f, -17.5f, 0);
    }

    /*if (state.player->position.x >= 12 && state.player->position.y <= -3) {
        state.nextScene = 2;
    }
    if (state.player->position.y <= -10 || state.player->isActive == false) {
        state.player->isActive = true;
        state.player->numLives -= 1;
        state.player->position = glm::vec3(1, 0, 0);
    }*/
}
void Main1::Render(ShaderProgram *program) {
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < MAIN_ENEMY_COUNT; ++i) {
        state.enemies[i].Render(program);
    }
}
