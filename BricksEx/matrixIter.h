#pragma once

#include <vector>

namespace sys {
	class MatrixIter {
	public:
		MatrixIter(const size_t row, const size_t rowSize);

	private:
		std::vector<size_t> iters;
	};
}