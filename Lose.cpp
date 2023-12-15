#include "Lose.hpp"

void Lose::Initialize(Entity *player) {
    state.nextScene = -1;
    state.player = player;
    state.player->position = glm::vec3(0);
}
void Lose::Update(float deltaTime) {
    
}
void Lose::Render(ShaderProgram *program) {
    Util::DrawText(program, Util::LoadTexture("font1.png"), "You Lose!", 1, -0.5, glm::vec3(-2.0f, 0, 0));
}
