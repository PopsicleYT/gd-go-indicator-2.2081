#include "FontPicker.hpp"
#include <algorithm>
#include <array>

using namespace geode::prelude;

static constexpr std::array FontFiles = {
    "bigFont.fnt", "chatFont.fnt", "goldFont.fnt", "gjFont01.fnt",
    "gjFont02.fnt", "gjFont03.fnt", "gjFont04.fnt", "gjFont05.fnt",
    "gjFont06.fnt", "gjFont07.fnt", "gjFont08.fnt", "gjFont09.fnt",
    "gjFont10.fnt", "gjFont11.fnt", "gjFont12.fnt", "gjFont13.fnt",
    "gjFont14.fnt", "gjFont15.fnt", "gjFont16.fnt", "gjFont17.fnt",
    "gjFont18.fnt", "gjFont19.fnt", "gjFont20.fnt", "gjFont21.fnt",
    "gjFont22.fnt", "gjFont23.fnt", "gjFont24.fnt", "gjFont25.fnt",
    "gjFont26.fnt", "gjFont27.fnt", "gjFont28.fnt", "gjFont29.fnt",
    "gjFont30.fnt", "gjFont31.fnt", "gjFont32.fnt", "gjFont33.fnt",
    "gjFont34.fnt", "gjFont35.fnt", "gjFont36.fnt", "gjFont37.fnt",
    "gjFont38.fnt", "gjFont39.fnt", "gjFont40.fnt", "gjFont41.fnt",
    "gjFont42.fnt", "gjFont43.fnt", "gjFont44.fnt", "gjFont45.fnt",
    "gjFont46.fnt", "gjFont47.fnt", "gjFont48.fnt", "gjFont49.fnt",
    "gjFont50.fnt", "gjFont51.fnt", "gjFont52.fnt", "gjFont53.fnt",
    "gjFont54.fnt", "gjFont55.fnt", "gjFont56.fnt", "gjFont57.fnt",
    "gjFont58.fnt", "gjFont59.fnt"
};

static constexpr std::array FontNames = {
    "Pusab", "Aller", "Gold Pusab", "FONT01", "FONT02", "FONT03", "FONT04", "FONT05",
    "FONT06", "FONT07", "FONT08", "FONT09", "FONT10", "FONT11", "Gargle", "Amatic",
    "Cartwheel", "MothproofScript", "LEMON MILK", "LEMON MILK 2", "Minecraft", 
    "OptimusPrincepsSemiBold", "Autolova", "Karate", "a Annyeong Haseyo", 
    "Ausweis Hollow", "Gypsy Curse", "Magic School Two", "Old English Five", 
    "Yeah Papa", "Ninja Naruto", "Metal Lord", "Drip Drop", "Electroharmonix", 
    "Aladin", "Creepster", "Call Of Ops Duty", "BlocParty", "Astron Boy", 
    "Osaka-Sans Serif", "Some Time Later", "Fatboy Slim BLTC BRK", "Moria Citadel", 
    "Rise of Kingdom", "FantaisieArtistique", "Edge of the Galaxy", "Wash Your Hand", 
    "Bitwise", "Foul Fiend", "Nandaka Western", "Evil Empire", "Comical Cartoon",
    "Carton Six", "aAssassinNinja", "Public Pixel", "New Walt Disney UI",
    "Random 5", "Crafting Lesson", "Game Of Squids", "Monster Game",
    "Lo-Sumires", "Gewtymol"
};

void FontPickerPopup::updateFont() {
    auto font = FontFiles[m_fontIndex];
    m_fontLabel->setFntFile(font);
    m_fontLabel->setString(lookupFont(font).c_str());
    m_fontLabel->limitLabelWidth(150.f, 1.f, 0.1f);
}

bool FontPickerPopup::setup(std::string const& font, std::function<void(std::string const&)> const& callback) {
    this->setTitle("Select a font");
    m_fontIndex = getFontIndex(font);

    m_fontLabel = cocos2d::CCLabelBMFont::create(" ", "bigFont.fnt");
    m_fontLabel->setID("font-label"_spr);
    m_mainLayer->addChildAtPosition(m_fontLabel, geode::Anchor::Center);
    updateFont();

    auto sprNext = cocos2d::CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
    sprNext->setFlipX(true);
    sprNext->setScale(0.6f);
    m_nextFontButton = geode::cocos::CCMenuItemExt::createSpriteExtra(sprNext, [this](auto s) { nextFont(s); });
    m_buttonMenu->addChildAtPosition(m_nextFontButton, geode::Anchor::Right, { -30.f, 0 });

    m_prevFontButton = geode::cocos::CCMenuItemExt::createSpriteExtraWithFrameName("GJ_arrow_02_001.png", 0.6f, [this](auto s) { prevFont(s); });
    m_buttonMenu->addChildAtPosition(m_prevFontButton, geode::Anchor::Left, { 30.f, 0 });

    auto okButton = geode::cocos::CCMenuItemExt::createSpriteExtra(
        ButtonSprite::create("OK", 30.f, true, "bigFont.fnt", "GJ_button_01.png", 24.f, 0.5),
        [this, callback](auto c) {
            callback(FontFiles[m_fontIndex]);
            this->onClose(c);
        }
    );
    m_buttonMenu->addChildAtPosition(okButton, geode::Anchor::Bottom, { 0, 20 });

    return true;
}

void FontPickerPopup::nextFont(cocos2d::CCObject*) {
    m_fontIndex = (m_fontIndex + 1) % FontFiles.size();
    updateFont();
}

void FontPickerPopup::prevFont(cocos2d::CCObject*) {
    m_fontIndex = (m_fontIndex + FontFiles.size() - 1) % FontFiles.size();
    updateFont();
}

size_t FontPickerPopup::getFontIndex(std::string const& fontFile) {
    auto it = std::find(FontFiles.begin(), FontFiles.end(), fontFile);
    return (it == FontFiles.end()) ? 0 : std::distance(FontFiles.begin(), it);
}

std::string FontPickerPopup::lookupFont(std::string const& fontFile) {
    return FontNames[getFontIndex(fontFile)];
}

FontPickerPopup* FontPickerPopup::create(std::string const& font, std::function<void(std::string const&)> const& callback) {
    auto ret = new FontPickerPopup;
    if (ret && ret->init(300.f, 200.f, font, callback)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool FontPicker::init(std::string const& font, std::function<void(std::string const&)> const& callback) {
    auto spr = ButtonSprite::create("A", 10.f, true, font.c_str(), "GJ_button_05.png", 24.f, 0.4);
    if (!spr) return false;
    spr->setScale(0.75f);
    m_fontLabel = spr->getChildByType<cocos2d::CCLabelBMFont>(0);
    m_font = font;
    m_callback = callback;
    return CCMenuItemSpriteExtra::init(spr, nullptr, this, menu_selector(FontPicker::onPickFont));
}

void FontPicker::onPickFont(cocos2d::CCObject*) {
    if (auto popup = FontPickerPopup::create(m_font, [this](std::string const& newFont) {
        m_callback(newFont);
        this->setFont(newFont);
    })) {
        popup->show();
    }
}

void FontPicker::setFont(std::string const& font) {
    m_font = font;
    if (m_fontLabel) m_fontLabel->setFntFile(font.c_str());
}

FontPicker* FontPicker::create(std::string const& font, std::function<void(std::string const&)> const& callback) {
    auto ret = new FontPicker;
    if (ret && ret->init(font, callback)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
