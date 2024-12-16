#include "Volcano.h"
using namespace std;

const auto kBackgroundColor = Color(64, 32, 32);
const auto kVolcanoColor    = Color(192, 128, 0);

const double kVolcanoTopWidth = 100;

const double kVolcanoHeightFraction = 0.5;

const double kMaxLavaXSpeed = 10;
const double kMaxSmokeXSpeed = 0.7;

const int kNumLavaParticles = 6;
const int kNumSmokeParticles = 15;

void Volcano::tick() {
    /* Find where the volcano top is. */
    const double volcanoTopY = (1 - kVolcanoHeightFraction) * SCENE_HEIGHT;

    /* Emit a shower of ejected lava particles. */
    for (int i = 0; i < kNumLavaParticles; i++) {
        Particle lava;
        lava.type = ParticleType::BALLISTIC;

        double lavaOffset = randomReal(-kVolcanoTopWidth / 2, +kVolcanoTopWidth / 2);
        lava.x = SCENE_WIDTH / 2 + lavaOffset;
        lava.y = volcanoTopY;

        lava.dy = -randomReal(0, 20);
        lava.dx = lavaOffset * kMaxLavaXSpeed / (kVolcanoTopWidth / 2);

        lava.color = Color(255, randomInteger(0, 255), 0);
        lava.lifetime = 500;

        system.add(lava);
    }

    /* Emit rising smoke. */
    for (int i = 0; i < kNumSmokeParticles; i++) {
        Particle smoke;
        smoke.type = ParticleType::STREAMER;

        double smokeOffset = randomReal(-kVolcanoTopWidth / 2, +kVolcanoTopWidth / 2);
        smoke.x = SCENE_WIDTH / 2 + smokeOffset;
        smoke.y = volcanoTopY;

        smoke.dy = -randomReal(1, 5);
        smoke.dx = smokeOffset * kMaxSmokeXSpeed / (kVolcanoTopWidth / 2);

        int ashColor = randomInteger(128, 192);
        smoke.color = Color(ashColor, ashColor, ashColor);
        smoke.lifetime = 500;

        system.add(smoke);
    }

    system.moveParticles();
}

void Volcano::draw()  {
    /* Draw background. */
    setColor(kBackgroundColor);
    fillRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

    /* Draw the volcano. */
    const double volcanoTopY = (1 - kVolcanoHeightFraction) * SCENE_HEIGHT;

    setColor(kVolcanoColor);
    fillPoly({ { 0, SCENE_HEIGHT },
               { SCENE_WIDTH / 2 - kVolcanoTopWidth / 2.0, volcanoTopY },
               { SCENE_WIDTH / 2 + kVolcanoTopWidth / 2.0, volcanoTopY },
               { SCENE_WIDTH, SCENE_HEIGHT }
    });

    /* Draw the particles, including both the fireworks and the
     * streamers.
     */
    system.drawParticles();
}
