#include "Scene.h"

class LevelB : public Scene {
private:
    int ENEMY_COUNT = 5;
public:

    ~LevelB();

    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
};
