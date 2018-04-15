#include "matrix.h"
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::Matrix(const size_t row, const size_t col) {
	matrix.resize(row, std::vector<T>(col));
}

template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::Matrix(const std::vector<std::vector<T>>& matrix)
	:matrix(matrix) {
}

template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::Matrix(const Matrix<T>& vector2D)
	: matrix(vector2D.matrix) {
}
// swap two 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::swap(Matrix<T>& vector2D) {
	matrix.swap(vector2D.matrix);
}
// resize 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::resize(const size_t row, const size_t col) {
	matrix.resize(row, std::vector<T>(col));
}
// resize row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::resize(const size_t row) {
	matrix.resize(row);
}
// push_back a row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::push_back(const std::vector<T>& vector) {
	matrix.push_back(vector);
}
// pop_back a row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::pop_back() {
	matrix.pop_back();
}
// erase a row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::erase(const_iter it) {
	matrix.erase(it);
}
// erase range of rows
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::erase(const_iter first, const_iter last) {
	matrix.erase(first, last);
}
// clear 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::clear() noexcept {
	matrix.clear();
}
// assign row(s) to 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::assign(const size_t n, const std::vector<T>& val) {
	matrix.assign(n, val);
}
// assign row(s) or another 2D vector's row(s) to 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
template<typename inputIter>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::assign(inputIter first, inputIter last) {
	matrix.assign(first, last);
}
// shrink whole 2D vector to fit size
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::shrink_to_fit() {
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<T> & colVector) {
		colVector.shrink_to_fit();
	})
}
// front row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline std::vector<T>& sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::front() {
	return matrix.front();
}
// front row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const std::vector<T>& sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::front() const {
	return matrix.front();
}
// last row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline std::vector<T>& sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::back() {
	return matrix.back();
}
// last row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const std::vector<T>& sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::back() const {
	return matrix.back();
}
// at certain element
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::at(const size_t rowIndex, const size_t colIndex) {
	return matrix.at(rowIndex).at(colIndex);
}
// at certain element
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::at(const size_t rowIndex, const size_t colIndex) const {
	return matrix.at(rowIndex).at(colIndex);
}
// insert row(s) to 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline iter sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::insert(const_iter pos, const std::vector<T>& val, const size_t n) {
	return n == 0 ? matrix.insert(pos, val) : matrix.insert(pos, n, val);
}
// insert row(s) to 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
template<typename InputIter>
inline iter sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::insert(const_iter pos, InputIter first, InputIter last) {
	return matrix.insert(pos, first, last);
}
// row's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline iter sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::begin() noexcept {
	return matrix.begin();
}
// row's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const_iter sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::begin() const noexcept {
	return matrix.begin();
}
// row's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline iter sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::end() noexcept {
	return matrix.end();
}
// row's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const_iter sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::end() const noexcept {
	return matrix.end();
}
// if whole 2D vector is empty return true
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline bool sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::empty() const noexcept {
	return matrix.empty();
}
// 2D vector size
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline size_t sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::size() const noexcept {
	size_t size = 0;
	std::for_each(matrix.begin(), matrix.end(), [&](const std::vector<T>& colVector) {
		size += colVector.size();
	});
	return size;
}
// 2D vector capacity
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline size_t sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::capacity() const noexcept {
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
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::swap_row(const size_t indexA, const size_t indexB) {
	std::swap(matrix.at(indexA), matrix.at(indexB));
}
// swap two elements
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::swap_element(T &a, T &b) {
	std::swap(a, b);
}
// resize same size to specified row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::resize_row(const size_t index, const size_t size) {
	matrix.at(index).resize(size);
}
// resize same size to specified range of rows
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::resize_row_range(const size_t beginIndex, const size_t range, const size_t size) {
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
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::resize_row_allRange(const size_t size) {
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<T> &colVector) {
		colVector.resize(size);
	});
}
// push_back to certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::push_back_row(const size_t index, const T & target) {
	matrix.at(index).push_back(target);
}
// pop_back to certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::pop_back_row(const size_t index) {
	matrix.at(index).pop_back();
}
// erase certain row's element
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::erase_row(const size_t index, const_iter_row target) {
	matrix.at(index).erase(target);
}
// erase range of elements at certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::erase_row(const size_t index, const_iter_row first, const_iter_row last) {
	matrix.at(index).erase(first, last);
}
// clear a row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::clear_row(const size_t index) noexcept {
	matrix[index].clear();
}
// assign certain row with element(s)
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::assign_row(const size_t index, const size_t n, const T & val) {
	matrix.at(index).assign(n, val);
}
// assign certain row with element(s) or another element(s)
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
template<typename inputIter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::assign_row(const size_t index, inputIter_row first, inputIter_row last) {
	matrix.at(index).assign(first, last);
}
// shrink certain row to fit size
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline void sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::shrink_to_fit_row(const size_t index) {
	matrix.at(index).shrink_to_fit();
}
// front element of certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::front_row(const size_t index) {
	return matrix.at(index).front();
}
// front element of certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::front_row(const size_t index) const {
	return matrix.at(index).front();
}
// last element of certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::back_row(const size_t index) {
	return matrix.at(index).back();
}
// last element of certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::back_row(const size_t index) const {
	return matrix.at(index).back();
}
// insert element(s) to certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline iter_row sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::insert_index_row(const size_t index, const_iter_row pos, const T & val, const size_t n) {
	return n == 0 ? matrix.at(index).insert(pos, val) : matrix.at(index).insert(pos, n, val);
}
// insert element(s) to certain row
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
template<typename InputIter_row>
inline iter_row sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::insert_index_row(const size_t index, const_iter_row pos, InputIter_row first_row, InputIter_row last_row) {
	return matrix.at(index).insert(pos, first_row, last_row);
}
// element's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline iter_row sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::begin_row(const size_t index) noexcept {
	return matrix[index].begin();
}
// element's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const_iter_row sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::begin_row(const size_t index) const noexcept {
	return matrix[index].begin();
}
// element's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline iter_row sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::end_row(const size_t index) noexcept {
	return matrix[index].end();
}
// element's iterator of 2D vector
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline const_iter_row sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::end_row(const size_t index) const noexcept {
	return matrix[index].end();
}
// if certain row is empty return true
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline bool sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::empty_row(const size_t index) const noexcept {
	return matrix[index].empty();
}
// certain row's size
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline size_t sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::size_row(const size_t index) const noexcept {
	return matrix[index].size();
}
// certain row's capacity
template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline size_t sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::capacity_row(const size_t index) const noexcept {
	return matrix[index].capacity();
}

template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline sys::Matrix<T>& sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::operator=(Matrix<T> right) noexcept {
	swap(right);
	return *this;
}

template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline typename sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::Proxy sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::operator [](const size_t row) noexcept {
	return Proxy(matrix[row]);
}

template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::Proxy::Proxy(std::vector<T>& inputVector)
	: outputVector(inputVector) {}

template<typename T, typename iter, typename const_iter, typename iter_row, typename const_iter_row>
inline T & sys::Matrix<T, iter, const_iter, iter_row, const_iter_row>::Proxy::operator[](const size_t col) noexcept {
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