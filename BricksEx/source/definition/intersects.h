#pragma once

namespace sys {
	template<typename T> class DPoint;
	//=============================================================================================//
	//-------------------------------below are rects intersects------------------------------------//
	//=============================================================================================//

	// exclude 4-points edge frame
	template<typename T>
	extern const bool EXCIntersects(const sf::Rect<T> &a, const sf::Rect<T> &b) {

		const sf::Vector2<T> ALT(a.left, a.top);
		const sf::Vector2<T> ARB(a.left + a.width, a.top + a.height);
		const sf::Vector2<T> BLT(b.left, b.top);
		const sf::Vector2<T> BRB(b.left + b.width, b.top + b.height);
		return ARB.x > BLT.x && ARB.y > BLT.y && ALT.x < BRB.x && ALT.y < BRB.y;
	}
	// exclude 4-points edge frame
	template<typename T>
	extern const bool EXCIntersects(const sys::DPoint<T> &a, const sys::DPoint<T> &b) {

		const sf::Vector2<T> ALT(a.dot1);
		const sf::Vector2<T> ARB(a.dot2);
		const sf::Vector2<T> BLT(b.dot1);
		const sf::Vector2<T> BRB(b.dot2);
		return ARB.x > BLT.x && ARB.y > BLT.y && ALT.x < BRB.x && ALT.y < BRB.y;
	}
	// include 4-points edge frame
	template<typename T>
	extern const bool INCIntersects(const sf::Rect<T> &a, const sf::Rect<T> &b) {

		const sf::Vector2<T> ALT(a.left, a.top);
		const sf::Vector2<T> ARB(a.left + a.width, a.top + a.height);
		const sf::Vector2<T> BLT(b.left, b.top);
		const sf::Vector2<T> BRB(b.left + b.width, b.top + b.height);
		return ARB.x >= BLT.x && ARB.y >= BLT.y && ALT.x <= BRB.x && ALT.y <= BRB.y;
	}
	// include 4-points edge frame
	template<typename T>
	extern const bool INCIntersects(const sys::DPoint<T> &a, const sys::DPoint<T> &b) {

		const sf::Vector2<T> ALT(a.dot1);
		const sf::Vector2<T> ARB(a.dot2);
		const sf::Vector2<T> BLT(b.dot1);
		const sf::Vector2<T> BRB(b.dot2);
		return ARB.x >= BLT.x && ARB.y >= BLT.y && ALT.x <= BRB.x && ALT.y <= BRB.y;
	}

	//=============================================================================================//
	//---------------------------below are point to rect intersects--------------------------------//
	//=============================================================================================//

	template<typename T>
	extern const bool pointIntersects(const sf::Vector2<T> &point, const sf::Rect<T> &rect) {

		const sf::Vector2<T> LT(rect.left, rect.top);
		const sf::Vector2<T> RB(rect.left + rect.width, rect.top + rect.height);
		return point.x >= LT.x && point.x <= RB.x && point.y >= LT.y && point.y <= RB.y;
	}

	template<typename T>
	extern const bool pointIntersects(const sf::Vector2<T> &point, const sys::DPoint<T> &rectDP) {

		const sf::Vector2<T> LT(rectDP.dot1);
		const sf::Vector2<T> RB(rectDP.dot2);
		return point.x >= LT.x && point.x <= RB.x && point.y >= LT.y && point.y <= RB.y;
	}

	//=============================================================================================//
	//-------------------------------below are balls intersects------------------------------------//
	//=============================================================================================//

	template<typename T>
	extern const bool ballsIntersects(const sf::Vector2<T> &APos, const T &ARadius
		, const sf::Vector2<T> &BPos, const T &BRadius) {

		const T pow2Delta = (APos.x - BPos.x) * (APos.x - BPos.x) + (APos.y - BPos.y) * (APos.y - BPos.y);
		const T pow2Distance = (ARadius + BRadius) * (ARadius + BRadius);
		return pow2Delta <= pow2Distance;
	}

	template<typename T>
	extern const T ballsDistance(const sf::Vector2<T> &APos, const T &ARadius
		, const sf::Vector2<T> &BPos, const T &BRadius) {

		const T distance = std::sqrt((APos.x - BPos.x) * (APos.x - BPos.x) + (APos.y - BPos.y) * (APos.y - BPos.y))
			- (ARadius + BRadius);
		return distance;
	}

	//=============================================================================================//
	//---------------------------below are ball to rect intersects---------------------------------//
	//=============================================================================================//

	// include 4-points edge frame
	template<typename T>
	extern const bool ballRectINCIntersects(const sf::Vector2<T> &ballPos, const T &ballRadius
		, const sf::Rect<T> &rect) {

		const sf::Vector2<T> LT(rect.left, rect.top);
		const sf::Vector2<T> RB(rect.left + rect.width, rect.top + rect.height);
		const sf::Vector2<T> nearPos(std::max(LT.x, std::min(ballPos.x, RB.x))
			, std::max(LT.y, std::min(ballPos.y, RB.y)));
		const T pow2Delta = (nearPos.x - ballPos.x) * (nearPos.x - ballPos.x)
			+ (nearPos.y - ballPos.y) * (nearPos.y - ballPos.y);
		const T pow2Distance = ballRadius * ballRadius;
		return pow2Delta <= pow2Distance;
	}
	// include 4-points edge frame
	template<typename T>
	extern const bool ballRectINCIntersects(const sf::Vector2<T> &ballPos, const T &ballRadius
		, const sys::DPoint<T> &rectDP) {

		const sf::Vector2<T> LT(rectDP.dot1);
		const sf::Vector2<T> RB(rectDP.dot2);
		const sf::Vector2<T> nearPos(std::max(LT.x, std::min(ballPos.x, RB.x))
			, std::max(LT.y, std::min(ballPos.y, RB.y)));
		const T pow2Delta = (nearPos.x - ballPos.x) * (nearPos.x - ballPos.x)
			+ (nearPos.y - ballPos.y) * (nearPos.y - ballPos.y);
		const T pow2Distance = ballRadius * ballRadius;
		return pow2Delta <= pow2Distance;
	}
	// exclude 4-points edge frame
	template<typename T>
	extern const bool ballRectEXCIntersects(const sf::Vector2<T> &ballPos, const T &ballRadius
		, const sf::Rect<T> &rect) {

		const sf::Vector2<T> LT(rect.left, rect.top);
		const sf::Vector2<T> RB(rect.left + rect.width, rect.top + rect.height);
		const sf::Vector2<T> nearPos(std::max(LT.x, std::min(ballPos.x, RB.x))
			, std::max(LT.y, std::min(ballPos.y, RB.y)));
		const T pow2Delta = (nearPos.x - ballPos.x) * (nearPos.x - ballPos.x)
			+ (nearPos.y - ballPos.y) * (nearPos.y - ballPos.y);
		const T pow2Distance = ballRadius * ballRadius;
		return pow2Delta < pow2Distance;
	}
	// exclude 4-points edge frame
	template<typename T>
	extern const bool ballRectEXCIntersects(const sf::Vector2<T> &ballPos, const T &ballRadius
		, const sys::DPoint<T> &rectDP) {

		const sf::Vector2<T> LT(rectDP.dot1);
		const sf::Vector2<T> RB(rectDP.dot2);
		const sf::Vector2<T> nearPos(std::max(LT.x, std::min(ballPos.x, RB.x))
			, std::max(LT.y, std::min(ballPos.y, RB.y)));
		const T pow2Delta = (nearPos.x - ballPos.x) * (nearPos.x - ballPos.x)
			+ (nearPos.y - ballPos.y) * (nearPos.y - ballPos.y);
		const T pow2Distance = ballRadius * ballRadius;
		return pow2Delta < pow2Distance;
	}
	// return intersection point
	template<typename T>
	extern const sf::Vector2<T> lineToLineIntersects(const sf::Vector2<T> &previousA, const sf::Vector2<T> &A
		, const sf::Vector2<T> &previousB, const sf::Vector2<T> &B) {
		const T slopeA = (A.y - previousA.y) / (A.x - previousA.x);
		const T slopeB = (B.y - previousB.y) / (B.x - previousB.x);
		const T interceptY_A = A.y - slopeA * A.x;
		const T interceptY_B = B.y - slopeB * B.x;
		const T pointX = (interceptY_B - interceptY_A) / (slopeA - slopeB);
		const sf::Vector2<T> intersectPoint(pointX, pointX * slopeA + interceptY_A);
		return intersectPoint;
	}
}