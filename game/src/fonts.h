#pragma once

#include <string>
#include <map>

enum Font {
    KONGTEXT,
    DOCOMO,
    FONT_FIN
};

const std::map<Font, std::string> fontPath = {
    {KONGTEXT, "kongtext.ttf"},
    {DOCOMO, "og-dcm-emoji.ttf"}
};