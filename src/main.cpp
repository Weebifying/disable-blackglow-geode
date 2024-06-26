#include <Geode/Geode.hpp>

#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

#include <Geode/modify/SimplePlayer.hpp>

using namespace geode::prelude;


class $modify(PlayLayer) {
	bool init(GJGameLevel* p0, bool p1, bool p2) {
		if (!PlayLayer::init(p0, p1, p2)) return false;

        auto player1 = this->m_player1;
        auto player2 = this->m_player2;

        if (player1->m_iconSprite->getColor() == ccColor3B{0,0,0} && !player1->m_hasGlow) {
            player1->m_iconGlow->getParent()->setVisible(false);
        }

        bool hasGlow = player2->m_hasGlow;

        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            hasGlow = Loader::get()->getLoadedMod("weebify.separate_dual_icons")->getSavedValue<bool>("glow");
        }

        if (player2->m_iconSprite->getColor() == ccColor3B{0,0,0} && !hasGlow) {
            player2->m_iconGlow->getParent()->setVisible(false);
        }
		
		return true;
	}
};

class $modify(LevelEditorLayer) {
	bool init(GJGameLevel* p0, bool p1) {
		if (!LevelEditorLayer::init(p0, p1)) return false;

        auto player1 = this->m_player1;
        auto player2 = this->m_player2;

        if (player1->m_iconSprite->getColor() == ccColor3B{0,0,0} && !player1->m_hasGlow) {
            player1->m_iconGlow->getParent()->setVisible(false);
        }

        bool hasGlow = player2->m_hasGlow;

        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            hasGlow = Loader::get()->getLoadedMod("weebify.separate_dual_icons")->getSavedValue<bool>("glow");
        }

        if (player2->m_iconSprite->getColor() == ccColor3B{0,0,0} && !hasGlow) {
            player2->m_iconGlow->getParent()->setVisible(false);
        }
		
		return true;
	}
};

class $modify(GJBaseGameLayer) {
    void toggleDualMode(GameObject* p0, bool p1, PlayerObject* p2, bool p3) {
        GJBaseGameLayer::toggleDualMode(p0, p1, p2, p3);

        auto player1 = this->m_player1;
        auto player2 = this->m_player2;

        bool hasGlow = player2->m_hasGlow;

        if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
            hasGlow = Loader::get()->getLoadedMod("weebify.separate_dual_icons")->getSavedValue<bool>("glow");
        }

        if (player1->m_isRobot) {
            if (player2->m_iconSprite->getColor() == ccColor3B{0,0,0} && !hasGlow) {
                CCArrayExt<CCNode*> children = getChildOfType<CCPartAnimSprite>(player2->m_robotSprite, 0)->getChildren();
                for (auto* child : children) {
                    if (child->getZOrder() == -1){
                        child->setVisible(false);
                        break;
                    }
                }
            }
        } else if (player1->m_isSpider) {
            if (player2->m_iconSprite->getColor() == ccColor3B{0,0,0} && !hasGlow) {
                CCArrayExt<CCNode*> children = getChildOfType<CCPartAnimSprite>(player2->m_spiderSprite, 0)->getChildren();
                for (auto* child : children) {
                    if (child->getZOrder() == -1){
                        child->setVisible(false);
                        break;
                    }
                }
            }
        }
    }
};

class $modify(PlayerObject) {
    void toggleRobotMode(bool p0, bool p1) {
        PlayerObject::toggleRobotMode(p0, p1);

        if (PlayLayer::get() || LevelEditorLayer::get()) {
            PlayerObject* player2;
            if (PlayLayer::get()) player2 = PlayLayer::get()->m_player2;
            else player2 = LevelEditorLayer::get()->m_player2;

            bool hasGlow = player2->m_hasGlow;

            if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
                hasGlow = Loader::get()->getLoadedMod("weebify.separate_dual_icons")->getSavedValue<bool>("glow");
            }

            if (this->m_iconSprite->getColor() == ccColor3B{0,0,0} && !hasGlow) {
                CCArrayExt<CCNode*> children = getChildOfType<CCPartAnimSprite>(this->m_robotSprite, 0)->getChildren();
                for (auto* child : children) {
                    if (child->getZOrder() == -1){
                        child->setVisible(false);
                        break;
                    }
                }
            }
        }
    }

    void toggleSpiderMode(bool p0, bool p1) {
        PlayerObject::toggleSpiderMode(p0, p1);

        if (PlayLayer::get() || LevelEditorLayer::get()) {
            PlayerObject* player2;
            if (PlayLayer::get()) player2 = PlayLayer::get()->m_player2;
            else player2 = LevelEditorLayer::get()->m_player2;

            bool hasGlow = player2->m_hasGlow;

            if (Loader::get()->isModLoaded("weebify.separate_dual_icons")) {
                hasGlow = Loader::get()->getLoadedMod("weebify.separate_dual_icons")->getSavedValue<bool>("glow");
            }

            if (this->m_iconSprite->getColor() == ccColor3B{0,0,0} && !hasGlow) {
                CCArrayExt<CCNode*> children = getChildOfType<CCPartAnimSprite>(this->m_spiderSprite, 0)->getChildren();
                for (auto* child : children) {
                    if (child->getZOrder() == -1){
                        child->setVisible(false);
                        break;
                    }
                }
            }
        }
    }
};