#pragma once
#include "interact/container.h"

namespace sf {
	class Color;
	class RectangleShape;
}
namespace game {
	class Button;
}

class HUD :
	public game::Container {
public:
	enum InterfaceCategory {
		Main,				// game start's page
		SaveLoad,			// load saves page
		Setting,			// setting for keyboard or for graphics
		PrepareArea,		// prepare player's equipment or buy something
		Store,				// supply item to player
		IllustratedList,	// give player to browse list of illustration
		BattleArea			// battle interface in level or vsmode
	};
	explicit HUD(const InterfaceCategory interface = Main);
	virtual bool containsPoint(const sf::Vector2f & point) const override;
	virtual std::shared_ptr<sf::Drawable> getDrawable() const override;
	void changeInterface(const InterfaceCategory nextInterface);
	virtual ~HUD();

protected:
	struct Compnonent {
		size_t uData;
		bool bShow;
		std::shared_ptr<sf::RectangleShape> context;
	};
	struct Panel {
		bool bDisplay;
		std::shared_ptr<sf::RectangleShape> context;
		// name compnonent
		std::map<std::string, Compnonent> compnonents;
	};

private:
	virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;

	InterfaceCategory currentInterface;
	std::map<InterfaceCategory, std::shared_ptr<sf::RectangleShape>> interfaces;
	// buttonName, button()
	std::map<std::string, std::shared_ptr<game::Button>> buttons;
	Panel bossPanel;
	Panel scorePanel;
	Panel playerPanel;
};