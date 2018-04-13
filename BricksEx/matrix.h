#pragma once

#include <iostream>
#include "matrixIter.h"

namespace sys {
	// 2D Matrix
	template<typename T, typename iter = std::enable_if_t<std::_Is_iterator_v<iter>>>
	class Matrix {
	public:
		Matrix(const size_t row, const size_t col);
		Matrix(const std::vector<std::vector<T>>& matrix);
		template<typename U>
		Matrix(const Matrix<U>& matrix);

		void resize(const size_t row, const size_t col);
		void push_back(const std::vector<T>& vector);
		void pop_back();
		void erase(iter &it);
		void erase(const size_t index);
		void clear();
		//-------------------------------row------------------------------------//
		void resize_row(const size_t index, const size_t col);
		void resize_row_range(const size_t begin, const size_t range, const size_t col);
		void resize_row_allRange(const size_t col);
		void push_back_row(const size_t index, const T &target);
		void pop_back_row(const size_t index);
		void erase_row(const size_t inX, const size_t inY);
		void clear_row(const size_t index);

		const iter insert(iter pos, iter val, const size_t n = 0);
		const iter begin() const;
		const iter end() const;
		const bool empty() const;
		const size_t size() const;
		//-------------------------------row------------------------------------//
		const iter insert_index_row(const size_t index, iter pos, const T &val, const size_t n = 0);
		const iter row_begin(const size_t index) const;
		const iter row_end(const size_t index) const;
		const bool empty_row(const size_t index) const;
		const size_t size_row(const size_t index) const;

	private:
		std::vector<std::vector<T>> matrix;
	};
#include "matrix.inl"
}
