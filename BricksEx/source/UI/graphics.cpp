#include "graphics.h"

Graphics::Graphics(const FrameRate Fps, const Resolution Dpi) {
	//icon.loadFromFile("");
	setDpi(Dpi);
	setFps(Fps);
}

void Graphics::handleSettle(const FrameRate Fps, const Resolution Dpi) {
	if(currentFps != Fps) setFps(Fps);
	if(currentDpi != Dpi) setDpi(Dpi);
}

const sf::ContextSettings & Graphics::getSettings() const {
	return currentSettings;
}

const float Graphics::getFrameSpan() const {
	return frameSpan;
}

const sf::Uint8 * Graphics::getIcon() const {
	return icon.getPixelsPtr();
}

const sf::Vector2u Graphics::getIconSize() const {
	return icon.getSize();
}

void Graphics::setFps(const FrameRate Fps) {
	currentFps = Fps;
	switch (currentFps) {
	case FrameRate::Fps30:
		frameSpan = (1.f / 30.f) * 1000.f;
		break;
	case FrameRate::Fps60:
		frameSpan = (1.f / 60.f) * 1000.f;
		break;
	case FrameRate::NoLimit:
		frameSpan = 0.0f;
		break;
	}
}

void Graphics::setDpi(const Resolution Dpi) {
	currentDpi = Dpi;
	switch (currentDpi) {
	case Resolution::Low_noAA:
		currentSettings = sf::ContextSettings(8, 4, 0, 3, 1);
		break;
	case Resolution::Low:
		currentSettings = sf::ContextSettings(8, 4, 2, 3, 1);
		break;
	case Resolution::Medium_noAA:
		currentSettings = sf::ContextSettings(16, 6, 0, 4, 1);
		break;
	case Resolution::Medium:
		currentSettings = sf::ContextSettings(16, 6, 4, 4, 1);
		break;
	case Resolution::High_noAA:
		currentSettings = sf::ContextSettings(24, 8, 0, 4, 2);
		break;
	case Resolution::High:
		currentSettings = sf::ContextSettings(24, 8, 6, 4, 2);
		break;
	case Resolution::Quality_noAA:
		currentSettings = sf::ContextSettings(24, 8, 0, 4, 3);
		break;
	case Resolution::Quality:
		currentSettings = sf::ContextSettings(24, 8, 8, 4, 3);
		break;
	}
}
