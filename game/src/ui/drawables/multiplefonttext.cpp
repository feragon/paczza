#include <iostream>
#include "multiplefonttext.h"


MultipleFontText::MultipleFontText(const std::wstring& text, const sf::Font& font, unsigned int fontSize) :
    _text(text),
    _defaultFont(font),
    _fontSize(fontSize),
    _bounds(0, 0, 0, 0) {

    createText();
    _needsUpdate = true;
}

sf::Sprite MultipleFontText::createText() const {
    _needsUpdate = false;

    _glyphs.clear();
    _bounds = sf::FloatRect();

    for(sf::Uint32 c : _text) {
        sf::Font& font = getFont(c);

        const sf::Glyph& glyph = _defaultFont.getGlyph(c, _fontSize, false);
        sf::Sprite s(_defaultFont.getTexture(_fontSize), glyph.textureRect);

        s.move(_bounds.width + 1, 0);

        _bounds.width += glyph.bounds.width + 1;
        _bounds.height = std::max(_bounds.height, glyph.bounds.height);

        _glyphs.push_back(s);
    }
}

sf::Font& MultipleFontText::getFont(sf::Uint32 c) const {
    for(unsigned long i = 0; i < _fonts.size(); i++) {
        if(c >= _fonts[i].first.first && c <= _fonts[i].first.second) {
            return _fonts[i].second;
        }
    }

    return _defaultFont;
}

void MultipleFontText::addFont(int begin, int end, const sf::Font& font) {
    _fonts.push_back(std::pair<std::pair<int, int>, sf::Font>(std::pair<int, int>(begin, end), font));

    createText();
    _needsUpdate = true;
}

const sf::FloatRect& MultipleFontText::bounds() const {
    return _bounds;
}

void MultipleFontText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(_needsUpdate) {
        createText();
    }

    states.transform *= getTransform();

    for (sf::Sprite sprite : _glyphs) {
        target.draw(sprite, states);
    }
}

void MultipleFontText::setColor(const sf::Color& color) {
    for(sf::Sprite& sprite : _glyphs) {
        sprite.setColor(color);
    }
}
