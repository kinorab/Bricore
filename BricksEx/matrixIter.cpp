#include "matrixIter.h"

sys::MatrixIter::MatrixIter(const size_t row, const size_t rowSize) {
	for (size_t i = 0; i < row; ++i) {
		iters.push_back(rowSize);
	}
}