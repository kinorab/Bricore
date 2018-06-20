#include "enerma.h"

using namespace item;

Enerma::Enerma(const Kind kind) 
	: enerma(kind) {
}

void Enerma::setAppear(const bool isAppear) {
	appear = isAppear;
}

Enerma::~Enerma() {
}
