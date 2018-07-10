#pragma once
#include "../../definition/matrix.h"
#include <SFML/System/Vector2.hpp>

namespace sf {
	class Color;
}

namespace game {
	class Level;

	class Deploy {
		class ProxyBlock {
		public:
			explicit ProxyBlock(const sys::Matrix<sf::Vector2f> & positionDeploy
				, const sys::Matrix<sf::Vector2f> & sideLengthDeploy
				, const sys::Matrix<sf::Color> & colorDeploy
				, const sys::Matrix<sf::Vector2f> & speedDeploy
				, const size_t currentLevel);
			std::vector<sf::Vector2f> sideLength;
			std::vector<sf::Vector2f> position;
			std::vector<sf::Color> color;
			std::vector<sf::Vector2f> speed;
		};
		class ProxyBrick {
		public:
			explicit ProxyBrick(const sys::Matrix<sf::Color> & colorDeploy
				, const sys::Matrix<float> & brickDeploy
				, const size_t currentLevel);
			std::vector<sf::Color> color;
			std::vector<float> it;
		};
	public:
		explicit Deploy(Level * level);
		// deployment component
		const ProxyBlock getBlock() const noexcept;
		const ProxyBrick getBrick() const noexcept;
		virtual ~Deploy();

	private:
		float fBlockLength;
		float fSpan;
		sys::Matrix<sf::Vector2f> blockPositionDeploy;
		sys::Matrix<sf::Vector2f> blockSideLengthDeploy;
		sys::Matrix<sf::Color> blockColorDeploy;
		sys::Matrix<sf::Vector2f> blockSpeedDeploy;
		// temp settings
		sys::Matrix<sf::Color> brickColorDeploy;
		sys::Matrix<float> brickDeploy;
		Level * level;
	};
}