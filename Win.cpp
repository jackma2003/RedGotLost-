#include "Win.hpp"

void Win::Initialize(Entity *player) {
    state.nextScene = -1;
    state.player = player;
    state.player->position = glm::vec3(0);
}
void Win::Update(float deltaTime) {
    
}
void Win::Render(ShaderProgram *program) {
    Util::DrawText(program, Util::LoadTexture("font1.png"), "You Win!", 1, -0.5, glm::vec3(-2.0f, 0, 0));
}
