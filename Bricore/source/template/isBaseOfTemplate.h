#pragma once

template <template <typename...> class Class, typename...Types>
std::true_type is_base_of_template_impl(const Class<Types...>*) {
	return std::true_type();
}

template <template <typename...> class Class>
std::false_type is_base_of_template_impl(...) { 
	return std::false_type();
}

template <template <typename...> class Class, typename Type>
using is_base_of_template = decltype(is_base_of_template_impl<Class>(std::declval<Type*>()));