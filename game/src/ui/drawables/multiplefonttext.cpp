#include <iostream>
#include "multiplefonttext.h"


MultipleFontText::MultipleFontText(const std::wstring& text, const sf::Font& font, unsigned int fontSize) :
    _text(text),
    _defaultFont(font),
    _fontSize(fontSize),
    _bounds(0, 0, 0, 0),
    _color(255, 255, 255) {

    createText();
    _needsUpdate = true;

}

void MultipleFontText::createText() const {
    _needsUpdate = false;

    _glyphs.clear();
    _bounds = sf::FloatRect();
    _bounds.height = _fontSize;

    sf::Uint32 lastChar = 0;
    for(sf::Uint32 c : _text) {
        sf::Font& font = getFont(c);

        _bounds.width += font.getKerning(lastChar, c, _fontSize);
        lastChar = c;

        const sf::Glyph& glyph = font.getGlyph(c, _fontSize, false);
        sf::Sprite s(font.getTexture(_fontSize), glyph.textureRect);
        s.setPosition(_bounds.width + glyph.bounds.left, glyph.bounds.top);
        s.setColor(_color);

        _bounds.width += glyph.advance;

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

void MultipleFontText::addFont(sf::Uint32 begin, sf::Uint32 end, const sf::Font& font) {
    _fonts.emplace_back(std::pair<int, int>(begin, end), font);

    _needsUpdate = true;
}

const sf::FloatRect& MultipleFontText::bounds() const {
    if(_needsUpdate) {
        createText();
        _needsUpdate = true;
    }

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
    _color = color;
    for(sf::Sprite& sprite : _glyphs) {
        sprite.setColor(color);
    }
}
