#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>

namespace sys {

	template<typename T>
	class DPoint {
	public:
		DPoint(const sf::Vector2<T> &D1, const sf::Vector2<T> &D2);

		template<typename U>
		explicit DPoint(const DPoint<U> &vector);

		sf::Vector2<T> dot1;
		sf::Vector2<T> dot2;
	};
	template<typename T>
	std::ostream& operator <<(std::ostream& os, const DPoint<T>& DP);

	template<typename T>
	DPoint<T> operator +(const DPoint<T>& left, const sf::Vector2<T> &right);

	template<typename T>
	DPoint<T> operator +(const sf::Vector2<T> &left, const DPoint<T>& right);

	template<typename T>
	DPoint<T> operator +(const DPoint<T>& left, const T right);

	template<typename T>
	DPoint<T> operator +(const T left, const DPoint<T>& right);

	template<typename T>
	DPoint<T> operator -(const DPoint<T>& left, const sf::Vector2<T> &right);

	template<typename T>
	DPoint<T> operator -(const DPoint<T>& left, const T right);

	template<typename T>
	DPoint<T> operator *(const DPoint<T>& left, const T right);

	template<typename T>
	DPoint<T> operator /(const DPoint<T>& left, const T right);

	template<typename T>
	DPoint<T>& operator +=(DPoint<T>& left, const sf::Vector2<T>& right);

	template<typename T>
	DPoint<T>& operator +=(DPoint<T>& left, const T right);

	template <typename T>
	DPoint<T>& operator -=(DPoint<T>& left, const sf::Vector2<T>& right);

	template<typename T>
	DPoint<T>& operator -=(DPoint<T>& left, const T right);

	template<typename T>
	DPoint<T>& operator *=(DPoint<T>& left, const T right);

	template<typename T>
	DPoint<T>& operator /=(DPoint<T>& left, const T right);

	template <typename T>
	bool operator ==(const DPoint<T>& left, const DPoint<T>& right);

	template <typename T>
	bool operator !=(const DPoint<T>& left, const DPoint<T>& right);
	#include "diagonalPoint.inl"

	typedef DPoint<int>          DPointi;
	typedef DPoint<unsigned int> DPointu;
	typedef DPoint<float>        DPointf;
}
