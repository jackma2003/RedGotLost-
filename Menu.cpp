#include "Menu.hpp"

void Menu::Initialize(Entity *player) {
    state.nextScene = -1;
    state.player = player;
    state.player->position = glm::vec3(0);
}
void Menu::Update(float deltaTime) {
    if (deltaTime == -1) {
        state.nextScene = 2;
        state.player->position = glm::vec3(7, -10, 0);
    }
}
void Menu::Render(ShaderProgram *program) {
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Red Got Lost!", 1, -0.5, glm::vec3(-3.0f, 1.0f, 0));
    Util::DrawText(program, Util::LoadTexture("font1.png"), "By Jack Ma", 1, -0.5, glm::vec3(-2.25f, 0.0f, 0));
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Press Enter", 1, -0.5, glm::vec3(-2.25f, -2.0f, 0));
    Util::DrawText(program, Util::LoadTexture("font1.png"), "to Start", 1, -0.5, glm::vec3(-1.75f, -3.0f, 0));
}

