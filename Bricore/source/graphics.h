#pragma once
#include <SFML/Config.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Graphics/Image.hpp>

class HUD;
class Graphics {
	friend class HUD;
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
	enum class ResidueShadow {
		None,
		Little,
		Much
	};
	explicit Graphics(const FrameRate Fps = FrameRate::Fps60, const Resolution Dpi = Resolution::High
		, const ResidueShadow afterimage = ResidueShadow::None);

	// display in milliseconds
	float getFrameSpan() const;
	sf::Vector2u getIconSize() const;
	FrameRate getCurrentFps() const;
	Resolution getCurrnetDpi() const;
	ResidueShadow getCurrentAfterimage() const;
	const sf::Uint8 * getIcon() const;
	const sf::ContextSettings & getSettings() const;

protected:
	void setFps(const FrameRate Fps);
	void setDpi(const Resolution Dpi);

private:
	float fFrameSpan;
	sf::Image icon;
	sf::ContextSettings currentSettings;
	ResidueShadow currentAfterimage;
	FrameRate currentFps;
	Resolution currentDpi;
};
typedef Graphics::FrameRate GFps;
typedef Graphics::Resolution GDpi;
typedef Graphics::ResidueShadow GAI;