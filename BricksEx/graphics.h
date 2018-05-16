#pragma once
#include <SFML/Config.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Graphics {
public:
	enum class FrameRate {
		Fps30,
		Fps60,
		NoLimit
	};
	enum class Resolution {
		Low_noAA,
		Low,
		Medium_noAA,
		Medium,
		High_noAA,
		High,
		Quality_noAA,
		Quality
	};
	Graphics(FrameRate Fps = FrameRate::Fps60, Resolution Dpi = Resolution::High);
	virtual void handleSettle(const FrameRate Fps, const Resolution Dpi);
	virtual const sf::ContextSettings & getSettings() const;
	// display in milliseconds
	virtual const float & getFrameSpan() const;
	virtual const sf::Uint8 * getIcon() const;
	virtual const sf::Vector2u getIconSize() const;

protected:
	virtual void handleFps(const FrameRate Fps);
	virtual void handleDpi(const Resolution Dpi);

private:
	virtual void setFrameRate();
	virtual void setResolution();

	float frameSpan;
	sf::Image icon;
	sf::ContextSettings currentSettings;
	FrameRate currentFps;
	Resolution currentDpi;
};
typedef Graphics::FrameRate GFps;
typedef Graphics::Resolution GDpi;
