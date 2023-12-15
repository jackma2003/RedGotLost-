#include "Scene.hpp"

class Lose : public Scene {
public:
    void Initialize(Entity *player) override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
