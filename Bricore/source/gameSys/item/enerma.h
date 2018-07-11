#pragma once
#include "itemKind.h"

namespace item {
	class Enerma :
		public ItemKind<Enerma> {
	public:
		explicit Enerma(const Kind enerma);
		void setAppear(const bool isAppear);
		virtual ~Enerma();
		const Kind it;
		Enerma(const Enerma &) = delete;
		Enerma & operator =(const Enerma &) = delete;
	private:
		bool bAppear;
	};
}