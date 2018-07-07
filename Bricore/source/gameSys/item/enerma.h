#pragma once
#include "itemKind.h"

namespace item {
	class Enerma :
		public ItemKind<Enerma> {
	public:
		explicit Enerma(const Kind kind);
		void setAppear(const bool isAppear);
		virtual ~Enerma();
		const Kind enerma;
		Enerma(const Enerma &) = delete;
		Enerma & operator =(const Enerma &) = delete;
	private:
		bool bAppear;
	};
}