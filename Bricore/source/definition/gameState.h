#pragma once
#include <SFML/System/Time.hpp>
extern void getPlayedTime();

constexpr float RESETTIME = 25.f;
constexpr float BOOST = 2.5f;
constexpr float MAXSPEED = 15.f;
constexpr float GAME_WIDTH = 1500.f;
constexpr float GAME_HEIGHT = 900.f;
constexpr float LEVEL_WIDTH = 1200.f;
constexpr float LEVEL_HEIGHT = 900.f;
constexpr float AREA_INTERVAL = 50.f;
constexpr size_t SLICE = 5;

namespace game {
	class GameStateEvent {
	public:
		struct OverEvent {

		};

		struct ReadyEvent {
			float fDurationSeconds;
		};

		struct PausedEvent {
			unsigned int uPausedTimes;
		};

		struct ResumedEvent {
			float fCountDown;
		};

		struct StartedEvent {
			float fDurationSeconds;
		};

		struct FinishedLevelEvent {
			unsigned int uLevel;
		};

		enum EventType {
			GameOver			// over the game(stage mode or vs mode)
			, GameReady			// wait for start(ball still on board)
			, GameStarted		// start on this stage
			, GamePaused		// pause game
			, GameResumed		// from pause back to game(count down), back to ready or start(depend on ball)
			, GameFinishedLevel	// finished current level
		};

		EventType type;

		union {
			OverEvent over;
			ReadyEvent ready;
			PausedEvent paused;
			ResumedEvent resumed;
			StartedEvent started;
			FinishedLevelEvent finishedLevel;
		};
	};
};
