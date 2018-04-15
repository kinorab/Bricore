#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

namespace sys {
	// 2D vector
	template<typename T, typename iter = typename std::vector<std::vector<T>>::iterator
		, typename const_iter = typename std::vector<std::vector<T>>::const_iterator
		, typename iter_row = typename std::vector<T>::iterator
		, typename const_iter_row = typename std::vector<T>::const_iterator>
	class Matrix {
	public:
		Matrix(const size_t row, const size_t col);
		Matrix(const std::vector<std::vector<T>>& matrix);
		Matrix(const Matrix<T>& vector2D);

		void swap(Matrix<T>& vector2D);
		void resize(const size_t row, const size_t col);
		void resize(const size_t row);
		void push_back(const std::vector<T>& vector);
		void pop_back();
		void erase(const_iter it);
		void erase(const_iter first, const_iter last);
		void clear() noexcept;
		void assign(const size_t n, const std::vector<T> & val);
		template<typename inputIter = typename iter>
		void assign(inputIter first, inputIter last);
		void shrink_to_fit();
		std::vector<T> & front();
		const std::vector<T> & front() const;
		std::vector<T> & back();
		const std::vector<T> & back() const;
		T & at(const size_t rowIndex, const size_t colIndex);
		const T &at(const size_t rowIndex, const size_t colIndex) const;
		iter insert(const_iter pos, const std::vector<T>& val, const size_t n = 0);
		template<typename InputIter = typename iter>
		iter insert(const_iter pos, InputIter first, InputIter last);

		iter begin() noexcept;
		const_iter begin() const noexcept;
		iter end() noexcept;
		const_iter end() const noexcept;
		bool empty() const noexcept;
		size_t size() const noexcept;
		size_t capacity() const noexcept;

		//----------------------------------------------------------------------//
		//----------------------------below are row-----------------------------//
		//----------------------------------------------------------------------//

		void swap_row(const size_t indexA, const size_t indexB);
		void swap_element(T &a, T &b);
		void resize_row(const size_t index, const size_t size);
		void resize_row_range(const size_t beginIndex, const size_t range, const size_t size);
		void resize_row_allRange(const size_t size);
		void push_back_row(const size_t index, const T &target);
		void pop_back_row(const size_t index);
		void erase_row(const size_t index, const_iter_row target);
		void erase_row(const size_t index, const_iter_row first, const_iter_row last);
		void clear_row(const size_t index) noexcept;
		void assign_row(const size_t index, const size_t n, const T & val);
		template<typename inputIter_row = typename iter_row>
		void assign_row(const size_t index, inputIter_row first, inputIter_row last);
		void shrink_to_fit_row(const size_t index);
		T & front_row(const size_t index);
		const T & front_row(const size_t index) const;
		T & back_row(const size_t index);
		const T & back_row(const size_t index) const;
		iter_row insert_index_row(const size_t index, const_iter_row pos, const T & val, const size_t n = 0);
		template<typename InputIter_row = typename iter_row>
		iter_row insert_index_row(const size_t index, const_iter_row pos, InputIter_row first_row, InputIter_row last_row);
		
		iter_row begin_row(const size_t index) noexcept;
		const_iter_row begin_row(const size_t index) const noexcept;
		iter_row end_row(const size_t index) noexcept;
		const_iter_row end_row(const size_t index) const noexcept;
		bool empty_row(const size_t index) const noexcept;
		size_t size_row(const size_t index) const noexcept;
		size_t capacity_row(const size_t index) const noexcept;
	private:
		class Proxy {
		public:
			Proxy(std::vector<T>& inputVector);
			T & operator [](const size_t col) noexcept;
		private:
			std::vector<T>& outputVector;
		};
		std::vector<std::vector<T>> matrix;
	public:
		Proxy operator [](const size_t row) noexcept;
		Matrix<T>& operator =(Matrix<T> right) noexcept;
	};
	template<typename T>
	std::ostream& operator <<(std::ostream& os, const Matrix<T>& matrix);
#include "matrix.inl"
	template<typename T>
	using vector2D = Matrix<T>;
}
