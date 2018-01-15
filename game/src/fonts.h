#pragma once

#include <string>
#include <map>

enum Font {
    PIXELLARI,
    FONT_FIN
};

const std::map<Font, std::string> fontPath = {
    {PIXELLARI, "Pixellari.ttf"}
};