#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/ui/ColorPickPopup.hpp>

using namespace geode::prelude;

#include "LevelIndicatorsList.hpp"
#include "../GoIndicatorPlayLayer.hpp"
#include "../structs/IndicatorData.hpp"
#include "../nodes/ColorPicker.hpp"
#include "../nodes/FloatSlider.hpp"
#include "../nodes/FontPicker.hpp"

// ... (escapeNewlines / unescapeNewlines logic stays the same) ...

bool LevelIndicatorsList::setup(std::string const& id) {
    this->setTitle("Progress Indicators");
    if (m_titleLabel) m_titleLabel->setPositionX(170.f);

    m_levelId = id;
    m_indicators = IndicatorData::getIndicators(id);
    
    m_scrollLayer = geode::ScrollLayer::create({0.f, 0.f, 320.f, 215.f});
    m_scrollLayer->setAnchorPoint({ 0, 0.5f });
    m_scrollLayer->setID("scroll-layer"_spr);
    m_scrollLayer->setZOrder(2);
    m_mainLayer->addChildAtPosition(m_scrollLayer, geode::Anchor::BottomLeft, {10.f, 10.f});

    auto scrollBg = cocos2d::extension::CCScale9Sprite::create("square02b_001.png");
    scrollBg->setAnchorPoint({ 0, 0 });
    scrollBg->setColor({ 0, 0, 0 });
    scrollBg->setOpacity(128);
    scrollBg->setContentSize({ 320.f, 215.f });
    scrollBg->setID("content-bg"_spr);
    m_mainLayer->addChildAtPosition(scrollBg, geode::Anchor::BottomLeft, {10.f, 10.f});

    auto togglerMenu = cocos2d::CCMenu::create();
    togglerMenu->setContentSize(m_mainLayer->getContentSize());
    togglerMenu->setPosition({0, 0});
    togglerMenu->setAnchorPoint({0, 0});
    
    m_enableToggler = geode::cocos::CCMenuItemExt::createTogglerWithStandardSprites(0.6f, [this](auto) {
        auto enabled = IndicatorData::hasIndicators(m_levelId);
        IndicatorData::setIndicatorsEnabled(m_levelId, !enabled);
    });
    m_enableToggler->toggle(IndicatorData::hasIndicators(m_levelId));
    togglerMenu->addChildAtPosition(m_enableToggler, geode::Anchor::TopRight, {-75.f, -20.f});

    auto enabledLabel = cocos2d::CCLabelBMFont::create("Enabled", "bigFont.fnt");
    enabledLabel->setScale(0.4f);
    togglerMenu->addChildAtPosition(enabledLabel, geode::Anchor::TopRight, {-35.f, -20.f});
    m_mainLayer->addChild(togglerMenu);

    // Sidebar and Layout Logic
    auto sidebarMenu = cocos2d::CCMenu::create();
    sidebarMenu->setContentSize({ 76.f, 260.f });
    sidebarMenu->setPosition({335, -96});
    sidebarMenu->setAnchorPoint({0, 0});

    auto addIndicatorButton = geode::cocos::CCMenuItemExt::createSpriteExtra(ButtonSprite::create(
        "Add", 60.f, true, "bigFont.fnt", "GJ_button_01.png", 24.f, 0.5
        ), [this](auto) {
        m_indicators.push_back(IndicatorData { 50.0, "Go!", "bigFont.fnt", { 255, 255, 255, 255 }, true });
        this->refreshList();
    });
    sidebarMenu->addChild(addIndicatorButton);

    sidebarMenu->setLayout(
        geode::ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAutoScale(false)
            ->setCrossAxisOverflow(true)
            ->setAxisAlignment(geode::AxisAlignment::End)
            ->setGap(2)
    );
    m_mainLayer->addChild(sidebarMenu);

    this->refreshList();
    return true;
}

void LevelIndicatorsList::refreshList() {
    auto layer = m_scrollLayer->m_contentLayer;
    layer->removeAllChildrenWithCleanup(true);

    for (int i = 0; i < (int)m_indicators.size(); i++) {
        auto cell = createIndicatorCell(m_indicators[i], i);
        layer->addChild(cell);
    }

    auto height = std::max(42.f * static_cast<float>(m_indicators.size()), 215.f);
    layer->setLayout(
        geode::ColumnLayout::create()
            ->setAxisReverse(true)
            ->setCrossAxisOverflow(true) // Fixed member name
            ->setAxisAlignment(geode::AxisAlignment::End)
            ->setGap(2)
    );

    layer->setContentSize({ 320.f, height });
    layer->updateLayout();
    m_scrollLayer->scrollToTop();
}

LevelIndicatorsList* LevelIndicatorsList::create(std::string const& id) {
    auto ret = new LevelIndicatorsList;
    if (ret && ret->init(420.f, 260.f, id)) { // Changed to init
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void LevelIndicatorsList::onExit() {
    Popup::onExit(); // Simplified base call
    IndicatorData::saveIndicators(m_levelId, m_indicators);
    if (auto pl = static_cast<GoIndicatorPlayLayer*>(PlayLayer::get()))
        pl->recreateIndicators();
}
