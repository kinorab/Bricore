#include "enerma.h"

using namespace item;

Enerma::Enerma(const Kind enerma) 
	: it(enerma) {
}

void Enerma::setAppear(const bool isAppear) {
	bAppear = isAppear;
}

Enerma::~Enerma() {
}
