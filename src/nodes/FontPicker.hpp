#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>

using namespace geode::prelude;

class FontPickerPopup : public geode::Popup<std::string const&, std::function<void(std::string const&)> const&> {
protected:
    bool setup(std::string const& font, std::function<void(std::string const&)> const& callback) override;
    
    // Changed CCObject to cocos2d::CCObject for safety
    void nextFont(cocos2d::CCObject* sender);
    void prevFont(cocos2d::CCObject* sender);
    void updateFont(); // Removed 'const' to match .cpp

public:
    static FontPickerPopup* create(std::string const& font, std::function<void(std::string const&)> const& callback);
    static size_t getFontIndex(std::string const& fontFile);
    static std::string lookupFont(std::string const& fontFile);

private:
    size_t m_fontIndex = 0;
    cocos2d::CCLabelBMFont* m_fontLabel = nullptr;
    CCMenuItemSpriteExtra* m_nextFontButton = nullptr;
    CCMenuItemSpriteExtra* m_prevFontButton = nullptr;
};

class FontPicker : public CCMenuItemSpriteExtra {
protected:
    bool init(std::string const& font, std::function<void(std::string const&)> const& callback);
    void onPickFont(cocos2d::CCObject* sender);

public:
    static FontPicker* create(std::string const& font, std::function<void(std::string const&)> const& callback);
    void setFont(std::string const& font);

protected:
    cocos2d::CCLabelBMFont* m_fontLabel = nullptr;
    std::string m_font;
    std::function<void(std::string const&)> m_callback;
};
