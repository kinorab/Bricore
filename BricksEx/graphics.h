#pragma once
#include <SFML/Config.hpp>
#include <SFML/Window/ContextSettings.hpp>

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
	virtual void handleSettle(FrameRate Fps, Resolution Dpi);
	virtual const sf::ContextSettings & getSettings() const;
	// display in milliseconds
	virtual const float & getFrameSpan() const;

protected:
	virtual void handleFps(FrameRate Fps);
	virtual void handleDpi(Resolution Dpi);

private:
	virtual void setFrameRate();
	virtual void setResolution();

	float frameSpan;
	sf::ContextSettings currentSettings;
	FrameRate currentFps;
	Resolution currentDpi;
};
typedef Graphics::FrameRate GFps;
typedef Graphics::Resolution GDpi;
