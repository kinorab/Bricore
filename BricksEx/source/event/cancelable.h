#pragma once

namespace game {
	class Cancelable {
	public:
		virtual ~Cancelable() = default;
		virtual bool getDefaultPrevented() const;
		virtual void preventDefault();
	protected:
		Cancelable() = default;
	private:
		bool defaultPrevented = false;
	};
}