#include "matrix.h"
template<typename T>
inline sys::Matrix<T>::Matrix() 
	:matrix({ {} }) {
}

template<typename T>
inline sys::Matrix<T>::Matrix(const size_t row, const size_t col) {
	matrix.resize(row, std::vector<T>(col));
}

template<typename T>
inline sys::Matrix<T>::Matrix(const std::vector<std::vector<T>>& matrix)
	:matrix(matrix) {
}

template<typename T>
inline sys::Matrix<T>::Matrix(const Matrix<T>& vector2D)
	: matrix(vector2D.matrix) {
}
// swap two 2D vector
template<typename T>
inline void sys::Matrix<T>::swap(Matrix<T>& vector2D) {
	matrix.swap(vector2D.matrix);
}
// resize 2D vector
template<typename T>
inline void sys::Matrix<T>::resize(const size_t row, const size_t col) {
	matrix.resize(row, std::vector<T>(col));
}
// resize row
template<typename T>
inline void sys::Matrix<T>::resize(const size_t row) {
	matrix.resize(row);
}
// push_back a row
template<typename T>
inline void sys::Matrix<T>::push_back(const std::vector<T>& vector) {
	matrix.push_back(vector);
}
// pop_back a row
template<typename T>
inline void sys::Matrix<T>::pop_back() {
	matrix.pop_back();
}
// erase a row
template<typename T>
inline void sys::Matrix<T>::erase(const_iter it) {
	matrix.erase(it);
}
// erase range of rows
template<typename T>
inline void sys::Matrix<T>::erase(const_iter first, const_iter last) {
	matrix.erase(first, last);
}
// clear 2D vector
template<typename T>
inline void sys::Matrix<T>::clear() noexcept {
	matrix.clear();
}
// assign row(s) to 2D vector
template<typename T>
inline void sys::Matrix<T>::assign(const size_t n, const std::vector<T>& val) {
	matrix.assign(n, val);
}
// assign row(s) or another 2D vector's row(s) to 2D vector
template<typename T>
inline void sys::Matrix<T>::assign(inputIter first, inputIter last) {
	matrix.assign(first, last);
}
// shrink whole 2D vector to fit size
template<typename T>
inline void sys::Matrix<T>::shrink_to_fit() {
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<T> & colVector) {
		colVector.shrink_to_fit();
	});
}
// front row
template<typename T>
inline std::vector<T>& sys::Matrix<T>::front() {
	return matrix.front();
}
// front row
template<typename T>
inline const std::vector<T>& sys::Matrix<T>::front() const {
	return matrix.front();
}
// last row
template<typename T>
inline std::vector<T>& sys::Matrix<T>::back() {
	return matrix.back();
}
// last row
template<typename T>
inline const std::vector<T>& sys::Matrix<T>::back() const {
	return matrix.back();
}
// at certain element
template<typename T>
inline T & sys::Matrix<T>::at(const size_t rowIndex, const size_t colIndex) {
	return matrix.at(rowIndex).at(colIndex);
}
// at certain element
template<typename T>
inline const T & sys::Matrix<T>::at(const size_t rowIndex, const size_t colIndex) const {
	return matrix.at(rowIndex).at(colIndex);
}
// insert row(s) to 2D vector
template<typename T>
inline typename sys::Matrix<T>::iter sys::Matrix<T>::insert(const_iter pos, const std::vector<T>& val, const size_t n) {
	return n == 0 ? matrix.insert(pos, val) : matrix.insert(pos, n, val);
}
// insert row(s) or another 2D vector's row(s) to 2D vector
template<typename T>
inline typename sys::Matrix<T>::iter sys::Matrix<T>::insert(const_iter pos, inputIter first, inputIter last) {
	return matrix.insert(pos, first, last);
}
// row's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::iter sys::Matrix<T>::begin() noexcept {
	return matrix.begin();
}
// row's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::const_iter sys::Matrix<T>::begin() const noexcept {
	return matrix.begin();
}
// row's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::iter sys::Matrix<T>::end() noexcept {
	return matrix.end();
}
// row's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::const_iter sys::Matrix<T>::end() const noexcept {
	return matrix.end();
}
// if whole 2D vector is empty return true
template<typename T>
inline bool sys::Matrix<T>::empty() const noexcept {
	return matrix.empty();
}
// 2D vector size
template<typename T>
inline size_t sys::Matrix<T>::size() const noexcept {
	size_t size = 0;
	std::for_each(matrix.begin(), matrix.end(), [&](const std::vector<T>& colVector) {
		size += colVector.size();
	});
	return size;
}
// 2D vector capacity
template<typename T>
inline size_t sys::Matrix<T>::capacity() const noexcept {
	size_t capacity = 0;
	std::for_each(matrix.begin(), matrix.end(), [&](const std::vector<T>& colVector) {
		capacity += colVector.capacity();
	});
	return capacity;
}

//----------------------------------------------------------------------//
//----------------------------below are row-----------------------------//
//----------------------------------------------------------------------//

// swap two rows in same 2D vector
template<typename T>
inline void sys::Matrix<T>::swap_row(const size_t indexA, const size_t indexB) {
	std::swap(matrix.at(indexA), matrix.at(indexB));
}
// swap two elements
template<typename T>
inline void sys::Matrix<T>::swap_element(T &a, T &b) {
	std::swap(a, b);
}
// resize same size to specified row
template<typename T>
inline void sys::Matrix<T>::resize_row(const size_t index, const size_t size) {
	matrix.at(index).resize(size);
}
// resize same size to specified range of rows
template<typename T>
inline void sys::Matrix<T>::resize_row_range(const size_t beginIndex, const size_t range, const size_t size) {
	if (range > 0) {
		std::for_each_n(matrix.begin() + beginIndex, range, [](std::vector<T> &colVector) {
			colVector.resize(size);
		});
	}
	else {
		throw std::invalid_argument("Range most be positive number.");
	}
}
// resize all rows with same size
template<typename T>
inline void sys::Matrix<T>::resize_row_allRange(const size_t size) {
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<T> &colVector) {
		colVector.resize(size);
	});
}
// push_back to certain row
template<typename T>
inline void sys::Matrix<T>::push_back_row(const size_t index, const T & target) {
	matrix.at(index).push_back(target);
}
// pop_back to certain row
template<typename T>
inline void sys::Matrix<T>::pop_back_row(const size_t index) {
	matrix.at(index).pop_back();
}
// erase certain row's element
template<typename T>
inline void sys::Matrix<T>::erase_row(const size_t index, const_iter_row target) {
	matrix.at(index).erase(target);
}
// erase range of elements at certain row
template<typename T>
inline void sys::Matrix<T>::erase_row(const size_t index, const_iter_row first, const_iter_row last) {
	matrix.at(index).erase(first, last);
}
// clear a row
template<typename T>
inline void sys::Matrix<T>::clear_row(const size_t index) noexcept {
	matrix[index].clear();
}
// assign certain row with element(s)
template<typename T>
inline void sys::Matrix<T>::assign_row(const size_t index, const size_t n, const T & val) {
	matrix.at(index).assign(n, val);
}
// assign certain row with element(s)
template<typename T>
inline void sys::Matrix<T>::assign_row(const size_t index, inputIter_row first, inputIter_row last) {
	matrix.at(index).assign(first, last);
}
// shrink certain row to fit size
template<typename T>
inline void sys::Matrix<T>::shrink_to_fit_row(const size_t index) {
	matrix.at(index).shrink_to_fit();
}
// front element of certain row
template<typename T>
inline T & sys::Matrix<T>::front_row(const size_t index) {
	return matrix.at(index).front();
}
// front element of certain row
template<typename T>
inline const T & sys::Matrix<T>::front_row(const size_t index) const {
	return matrix.at(index).front();
}
// last element of certain row
template<typename T>
inline T & sys::Matrix<T>::back_row(const size_t index) {
	return matrix.at(index).back();
}
// last element of certain row
template<typename T>
inline const T & sys::Matrix<T>::back_row(const size_t index) const {
	return matrix.at(index).back();
}
// insert element(s) to certain row
template<typename T>
inline typename sys::Matrix<T>::iter_row sys::Matrix<T>::insert_index_row(const size_t index, const_iter_row pos, const T & val, const size_t n) {
	return n == 0 ? matrix.at(index).insert(pos, val) : matrix.at(index).insert(pos, n, val);
}
// insert element(s) to certain row
template<typename T>
inline typename sys::Matrix<T>::iter_row sys::Matrix<T>::insert_index_row(const size_t index, const_iter_row pos, inputIter_row first_row, inputIter_row last_row) {
	return matrix.at(index).insert(pos, first_row, last_row);
}
// element's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::iter_row sys::Matrix<T>::begin_row(const size_t index) noexcept {
	return matrix[index].begin();
}
// element's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::const_iter_row sys::Matrix<T>::begin_row(const size_t index) const noexcept {
	return matrix[index].begin();
}
// element's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::iter_row sys::Matrix<T>::end_row(const size_t index) noexcept {
	return matrix[index].end();
}
// element's iterator of 2D vector
template<typename T>
inline typename sys::Matrix<T>::const_iter_row sys::Matrix<T>::end_row(const size_t index) const noexcept {
	return matrix[index].end();
}
// if certain row is empty return true
template<typename T>
inline bool sys::Matrix<T>::empty_row(const size_t index) const noexcept {
	return matrix[index].empty();
}
// certain row's size
template<typename T>
inline size_t sys::Matrix<T>::size_row(const size_t index) const noexcept {
	return matrix[index].size();
}
// certain row's capacity
template<typename T>
inline size_t sys::Matrix<T>::capacity_row(const size_t index) const noexcept {
	return matrix[index].capacity();
}

template<typename T>
inline sys::Matrix<T>& sys::Matrix<T>::operator=(Matrix<T> right) noexcept {
	swap(right);
	return *this;
}

template<typename T>
inline typename sys::Matrix<T>::Proxy sys::Matrix<T>::operator [](const size_t row) noexcept {
	return Proxy(matrix[row]);
}

template<typename T>
inline sys::Matrix<T>::Proxy::Proxy(std::vector<T>& inputVector)
	: outputVector(inputVector) {}

template<typename T>
inline T & sys::Matrix<T>::Proxy::operator[](const size_t col) noexcept {
	return outputVector[col];
}

template<typename T>
inline std::ostream & sys::operator <<(std::ostream & os, const Matrix<T>& matrix) {
	std::for_each(matrix.begin(), matrix.end(), [&](const std::vector<T> &colVector) {
		os << "{";
		std::for_each(colVector.begin(), colVector.end() - 1, [&](const T &element) {
			os << element << ", ";
		});
		os << colVector.back() << "}\n";
	});
	return os;
}