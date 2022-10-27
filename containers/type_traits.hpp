
#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# include <cstddef> // std::ptrdiff_t

namespace ft
{
	// enable_if
	template <bool Cond, typename T = void> //template generic
	struct enable_if
	{
	}; // active le type T si Cond est vrai

	// specialisation pour true
	template <typename T>
	struct enable_if<true, T> //second template parameter uniquement disponible
	{						  //si la première condition est vraie (true)
		typedef T type; // def
	};

	// is_integral
	template <typename T> //template generic
	struct is_integral
	{
		static const bool value = false;
	}; //

	// boolean — Value-type
	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	// char type
	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	// char16_t
	template <>
	struct is_integral<char16_t>
	{
		static const bool value = true;
	};

	// char32_t
	template <>
	struct is_integral<char32_t>
	{
		static const bool value = true;
	};

	//wchar_t
	template <>
	struct is_integral<wchar_t>
	{
		static const bool value = true;
	};

	// signed char
	template <>
	struct is_integral<signed char>
	{
		static const bool value = true;
	};

	// short int
	template <>
	struct is_integral<short int>
	{
		static const bool value = true;
	};

	// int
	template <>
	struct is_integral<int>
	{
		static const bool value = true;
	};

	// long int
	template <>
	struct is_integral<long int>
	{
		static const bool value = true;
	};

	// long long int
	template <>
	struct is_integral<__int64_t>
	{
		static const bool value = true;
	};

	// unsigned char
	template <>
	struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	// unsigned short int
	template <>
	struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};

	// unsigned int
	template <>
	struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	// unsigned long int
	template <>
	struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};

	// unsigned long long int
	template <>
	struct is_integral<__uint64_t>
	{
		static const bool value = true;
	};
} // namespace ft

#endif
