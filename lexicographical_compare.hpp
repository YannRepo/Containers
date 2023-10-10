#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{
	template <class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		// équivaut à obj1 < obj2
		// return true si	: un element de 1 < un element de 2
		// 					: il y a moins d'elements dans 1 et ils sont tous identiques a 2
		// return false si	: tous les elements sont == 
		// 					: si un element de 1 > un element de 2
		//					: il y a moins d'elements dans 2 et ils sont tous identiques a 1
		while (first1 != last1)
		{
			if (first2 == last2)
				return (false);
			if (*first1 < *first2)
				return (true);
			if (*first1 > *first2)
				return (false);
			first1++;
			first2++;
		}
		if (first2 == last2)
			return (false);
		else
			return (true);
	}

	template <class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		while (first1 != last1)
		{
	        if (first2 == last2 || comp(*first2, *first1)) 
				return (false);
	        else if (comp(*first1, *first2)) 
				return (true);
	        ++first1;
	        ++first2;
	    }
	    return (first2 != last2);
	}
}
#endif
