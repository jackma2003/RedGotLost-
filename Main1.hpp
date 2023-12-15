#include "Scene.hpp"

class Main1 : public Scene {
public:
    void Initialize(Entity *player) override;
    void Update(float deltaTime) override;
    void Render(ShaderProgram *program) override;
};
