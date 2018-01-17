#pragma once

#include <string>
#include <map>

enum Font {
    KONGTEXT,
    FONT_FIN
};

const std::map<Font, std::string> fontPath = {
    {KONGTEXT, "kongtext.ttf"}
};