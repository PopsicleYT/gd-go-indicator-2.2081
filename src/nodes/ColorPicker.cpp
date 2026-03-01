#include <Geode/Geode.hpp>
#include <Geode/ui/ColorPickPopup.hpp>
#include "ColorPicker.hpp"

using namespace geode::prelude;

bool ColorPicker::init(cocos2d::ccColor4B const& value, std::function<void(cocos2d::ccColor4B const&)> const& callback) {
    // Initialize the sprite for the button
    m_colorSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_colorBtn_001.png");
    if (!m_colorSprite) return false;

    m_color = value;
    m_callback = callback;

    // Set initial color and scale
    m_colorSprite->setColor({ value.r, value.g, value.b });
    m_colorSprite->setScale(0.5f);

    // Initialize the menu item with the sprite and the click selector
    if (!CCMenuItemSpriteExtra::init(m_colorSprite, nullptr, this, menu_selector(ColorPicker::onPickColor)))
        return false;

    return true;
}

void ColorPicker::onPickColor(cocos2d::CCObject* sender) {
    // Create the Geode ColorPickPopup
    auto picker = ColorPickPopup::create(m_color);
    
    // Set the callback using the Geode v5 lambda pattern
    picker->setColorCallback([this](cocos2d::ccColor4B const& color) {
        this->updateColor(color);
    });
    
    picker->show();
}

void ColorPicker::updateColor(cocos2d::ccColor4B const& color) {
    m_color = color;
    // Update the button's visual color
    if (m_colorSprite) {
        m_colorSprite->setColor({ color.r, color.g, color.b });
    }
    // Run the user-provided callback
    if (m_callback) {
        m_callback(color);
    }
}

ColorPicker* ColorPicker::create(cocos2d::ccColor4B const& value, std::function<void(cocos2d::ccColor4B const&)> const& callback) {
    auto ret = new ColorPicker;
    if (ret && ret->init(value, callback)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
