#pragma once
#include "Subsystem.h"
class Sounds :
    public Subsystem
{
public:
    irrklang::ISoundEngine* engine;

    void Start();

    void CheckEvent(SoundEvent* ev);

    void playSound(std::string name, bool loop);
};

