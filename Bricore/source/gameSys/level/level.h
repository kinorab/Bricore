#pragma once
#include "deploy.h"
#include <memory>

class Game;

namespace game {
	enum class Diffculty {
		NoChoose,
		Easy,
		Normal,
		Hard,
		Extreme
	};
	enum class Mode {
		NoChoose,
		_1Player,	// defender
		_2Player,	// defender and pioneer
		_VSMode		// defender vs defender or pioneer vs pioneer
	};
	class Level {
		friend class Game;
	public:
		enum Kind {
			NoChoose,
			Normal,		// others
			Obstacle,	// x3
			Bonus,		// x5
			Iron,		// x8
			Boss		// x0
		};
		explicit Level(const Mode mode, const Diffculty difficulty, const size_t level = 1);
		// explicit Level(const Data saveData);
		void changeSetting(const Mode mode, const Diffculty difficulty, const size_t level);
		void finishLevel();

		bool isDefaultControlKeySettled() const;
		size_t getcurrentLevel() const;
		size_t getTotalLevel() const;
		Mode getMode() const;
		Diffculty getDiffculty() const;
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
		Mode mode;
		Diffculty diffculty;
		Kind currentKind;
	};
}
