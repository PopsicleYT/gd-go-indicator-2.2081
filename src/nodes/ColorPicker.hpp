#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Remove geode::ColorPickPopupDelegate as it no longer exists in v5
class ColorPicker : public CCMenuItemSpriteExtra {
protected:
    // Standard init
    bool init(cocos2d::ccColor4B const& value, std::function<void(cocos2d::ccColor4B const&)> const& callback);
    
    // updateColor is no longer an 'override' because the delegate is gone
    void updateColor(cocos2d::ccColor4B const& color);
    
    // This handles the button click to open the popup
    void onPickColor(cocos2d::CCObject* sender);

public:
    static ColorPicker* create(cocos2d::ccColor4B const& value, std::function<void(cocos2d::ccColor4B const&)> const& callback);

protected:
    std::function<void(cocos2d::ccColor4B const&)> m_callback;
    cocos2d::CCSprite* m_colorSprite = nullptr;
    cocos2d::ccColor4B m_color{};
};
