#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
	template <typename T>
	struct is_integral
	{
		static const bool value = false; // 'static const' allows the value to be evaluated at compile time
	};

	template <>
	struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <>
	struct is_integral<char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<short>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<short unsigned>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long long>
	{
		static const bool value = true;
	};

	template <>
	struct	is_integral<long long unsigned>
	{
		static const bool value = true;
	};
}
#endif
