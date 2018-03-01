#pragma once

#include <string>
#include <map>

/**
 * @brief Nom des sons
 */
enum Sound {
    EAT,
    BONUS,
    TELEPORT,
    SOUND_FIN
};

const std::map<Sound, std::string> soundPath = {
        {EAT, "eat.wav"},
        {BONUS, "bonus.wav"},
        {TELEPORT, "teleport.wav"}
};