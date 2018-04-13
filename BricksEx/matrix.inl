#include "matrix.h"
template<typename T, typename iter>
inline sys::Matrix<T, iter>::Matrix(const size_t row, const size_t col) {
	matrix.resize(row, std::vector<T>(col));
}

template<typename T, typename iter>
inline sys::Matrix<T, iter>::Matrix(const std::vector<std::vector<T>>& matrix)
	:matrix(matrix) {
}

template<typename T, typename iter>
template<typename U>
inline sys::Matrix<T, iter>::Matrix(const Matrix<U>& matrix)
	: matrix(static_cast<T>(matrix.matrix)) {
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::resize(const size_t row, const size_t col) {
	matrix.resize(row, std::vector<T>(col));
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::push_back(const std::vector<T>& vector) {
	matrix.push_back(vector);
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::pop_back() {
	matrix.pop_back();
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::erase(iter & it) {
	matrix.erase(it);
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::erase(const size_t index) {
	matrix.erase(matrix.begin() + index);
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::clear() {
	matrix.clear();
}
//-------------------------------row------------------------------------//


template<typename T, typename iter>
inline void sys::Matrix<T, iter>::resize_row(const size_t index, const size_t col) {
	matrix.at(index).resize(col);
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::resize_row_range(const size_t begin, const size_t range, const size_t col) {
	if (range > 0) {
		std::for_each_n(matrix.begin() + begin, range, [](std::vector<T> &colVector) {
			colVector.resize(col);
		});
	}
	else {
		std::cout << "Range most be positive number." << std::endl;
	}
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::resize_row_allRange(const size_t col) {
	std::for_each(matrix.begin(), matrix.end(), [](std::vector<T> &colVector) {
		colVector.resize(col);
	});
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::push_back_row(const size_t index, const T & target) {
	matrix.at(index).push_back(target);
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::pop_back_row(const size_t index) {
	matrix.at(index).pop_back();
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::erase_row(const size_t inX, const size_t inY) {
	matrix.at(inX).erase(matrix.at(inX).begin() + inY);
}

template<typename T, typename iter>
inline void sys::Matrix<T, iter>::clear_row(const size_t index) {
	matrix.at(index).clear();
}

template<typename T, typename iter>
inline const iter sys::Matrix<T, iter>::insert(iter pos, iter val, const size_t n) {
	return n == 0 ? matrix.insert(pos, val) : matrix.insert(pos, n, val);
}

template<typename T, typename iter>
inline const iter sys::Matrix<T, iter>::begin() const {
	return matrix.begin();
}

template<typename T, typename iter>
inline const iter sys::Matrix<T, iter>::end() const {
	return matrix.end();
}

/*template<typename T>
inline const std::vector::const_iterator sys::Matrix<T>::insert(std::vector::const_iterator pos, std::vector::const_iterator val, const size_t n) {
	return n == 0 ? matrix.insert(pos, val) : matrix.insert(pos, n, val);
}*/

/*template<typename T>
inline const std::vector::const_iterator sys::Matrix<T>::begin() const {
	return matrix.begin();
}

template<typename T>
inline const std::vector::const_iterator sys::Matrix<T>::end() const {
	return matrix.end();
}*/

template<typename T, typename iter>
inline const bool sys::Matrix<T, iter>::empty() const {
	return matrix.empty();
}

template<typename T, typename iter>
inline const size_t sys::Matrix<T, iter>::size() const {
	size_t size = 0;
	std::for_each(matrix.begin(), matrix.end(), [&](const std::vector<T>& colVector) {
		size += colVector.size();
	});
	return size;
}
//-------------------------------row------------------------------------//

template<typename T, typename iter>
inline const iter sys::Matrix<T, iter>::insert_index_row(const size_t index, iter pos, const T & val, const size_t n) {
	return n == 0 ? matrix.at(index).insert(pos, val) : matrix.at(index).insert(pos, n, val);
}

template<typename T, typename iter>
inline const iter sys::Matrix<T, iter>::row_begin(const size_t index) const {
	return matrix.at(index).begin();
}

template<typename T, typename iter>
inline const iter sys::Matrix<T, iter>::row_end(const size_t index) const {
	return matrix.at(index).end();
}

/*template<typename T>
inline const std::vector::const_iterator sys::Matrix<T>::insert_index_row(const size_t index, const std::vector<T>::iterator pos, const T & val, const size_t n) {
	return n == 0 ? matrix.at(index).insert(pos, val) : matrix.at(index).insert(pos, n, val);
}

template<typename T>
inline const std::vector::const_iterator sys::Matrix<T>::row_begin(const size_t index) const {
	return matrix.at(index).begin();
}

template<typename T>
inline const std::vector::const_iterator sys::Matrix<T>::row_end(const size_t index) const {
	return matrix.at(index).end();
}*/

template<typename T, typename iter>
inline const bool sys::Matrix<T, iter>::empty_row(const size_t index) const {
	return matrix.at(index).empty();
}

template<typename T, typename iter>
inline const size_t sys::Matrix<T, iter>::size_row(const size_t index) const {
	return matrix.at(index).size();
}
