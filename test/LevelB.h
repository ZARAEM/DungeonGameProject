#include "Scene.h"

class LevelB : public Scene {
    bool GOOD_CHEST = false;
    bool BAD_CHEST = false;
public:

    ~LevelB();

    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram* program) override;
    bool near_chest_good();
    bool near_chest_bad();
};
