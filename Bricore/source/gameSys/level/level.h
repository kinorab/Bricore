#pragma once
#include "deploy.h"
#include <memory>

class Game;

namespace game {
	enum class Mode {
		_1Player,	// defender
		_2Player,	// defender and pioneer
		_VSMode		// defender vs defender or pioneer vs pioneer
	};
	enum class Diffculty {
		Not_StageMode,
		Easy,
		Normal,
		Hard,
		Extreme
	};
	class Data;
	class Level {
		friend class Game;
	public:
		enum Kind {
			Not_StageMode,	// Is not a level
			Normal,			// others
			Obstacle,		// x3
			Bonus,			// x5
			Iron,			// x8
			Boss			// x0
		};
		Level();
		// new stage game or vs mode
		void changeSetting(const Mode mode, const Diffculty difficulty);
		// load stage game
		void changeSetting(const Data & saveData);
		void finishLevel();

		bool isDefaultControlKeySettled() const;
		size_t getcurrentLevel() const;
		size_t getTotalLevel() const;
		Mode getMode() const;
		Diffculty getDiffculty() const;
		Kind getLevelKind() const;
		virtual ~Level();

		explicit Level(const Level &) = delete;
		Level &operator =(const Level &) = delete;
		std::unique_ptr<Deploy> deploy;

	private:
		void settleKind();

		static bool bInstance;
		bool bDefaultControlKeySettled;
		size_t uCurrentLevel;
		size_t uTotalLevel;
		Kind currentKind;
		Mode currentMode;
		Diffculty currentDifficulty;
	};
}
