#include "userSystem.h"
#include "gameState.h"
#include <mutex>
#include <Windows.h>

namespace sys {
	const sf::Vector2i getMonitorResolution() {
		RECT desktopRect;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktopRect);
		return sf::Vector2i(static_cast<int>(desktopRect.right), static_cast<int>(desktopRect.bottom));
	}
}