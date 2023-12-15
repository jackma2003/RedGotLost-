#include "Scene.hpp"

class Dungeon : public Scene {
    unsigned int dungeon_data[100] =
    {
        110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 0, 0, 0, 209, 209, 0, 0, 0, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 0, 0, 0, 0, 0, 0, 0, 0, 110,
        110, 110, 110, 110, 243, 243, 110, 110, 110, 110
    };
public:
    void Initialize(Entity *player) override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
