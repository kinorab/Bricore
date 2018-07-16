#pragma once
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

enum class GameState {
	LEVEL_FINISHED,
	STARTED,
	READY,
	NOT_READY,
};

namespace game {
	extern GameState currentGameState;
	class GameEvent {
	public:		
		struct ReadyEvent {

		};

		struct PausedEvent {
			bool bPaused;
			unsigned int uPausedTimes;
		};

		struct StartedEvent {
			bool bStarted;
		};

		struct FinishedLevelEvent {
			unsigned int uLevel;
		};

		enum EventType {
			GameReady
			, GameStarted
			, GamePaused
			, GameFinishedLevel
		};

		EventType type;

		union {
			ReadyEvent ready;
			PausedEvent paused;
			StartedEvent started;
			FinishedLevelEvent finishedLevel;
		};
	};
};
