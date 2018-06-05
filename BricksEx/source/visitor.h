#pragma once

template<typename... Types>
class Visitor;

template<typename Type>
class Visitor<Type> {
public:
	virtual void visitFailedHandler() = 0;
	virtual void visit(Type * visitable) {
		visitFailedHandler();
	}
};

template<typename Type, typename... Types>
class Visitor<Type, Types...> :
	public Visitor<Types...> {
public:
	using Visitor<Types...>::visit;
	using Visitor<Types...>::visitFailedHandler;
	virtual void visit(Type * visitable) {
		visitFailedHandler();
	}
};