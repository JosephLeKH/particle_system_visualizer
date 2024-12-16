/******************************************************************************
 * File: Volcano.h
 *
 * A scene containing an erupting volcano
 */

#pragma once

#include "Demos/Scene.h"
#include "ParticleSystem.h"

class Volcano: public Scene<Volcano> {
public:
    void tick();
    void draw();

private:
    ParticleSystem system;
};
