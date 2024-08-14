#include "Scene.h"

class LevelA : public Scene {
public:
    ~LevelA();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
