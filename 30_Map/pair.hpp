#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
// ###################################################################################################
// #################################   Pair   ########################################################
// ###################################################################################################
	template <class T1, class T2>
	struct pair
	{
		typedef T1			first_type;
		typedef T2			second_type;

		first_type	first;
		second_type	second;

	// -----------------------------------------------------------------------------------------------------------
	// ------------------------------------ Fonctions menbres --------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------
	

		pair(): first(), second(){};
		
		pair(const first_type& a, const second_type& b): first(a), second(b){};

		template<class U, class V>
		pair(const pair<U,V>& pr): first(pr.first), second(pr.second){};


		// pas de destructor

		// operator= et swap pas dans c++98
		//pair& operator= (const pair& pr)
		//{
		//	this->first = pr.first;
		//	this->second = pr.second;
		//}

	};

	// -----------------------------------------------------------------------------------------------------------
	// ------------------------------------ Fonctions non menbres --------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------
	// TBD a faire
	// code dans norme iso 14882

// ###################################################################################################
// #################################   make_pair  ####################################################
// ###################################################################################################
	template< class T1, class T2 >
	pair<T1, T2> make_pair( T1 t, T2 u )
	{
		return (pair<T1, T2>(t, u));
	}

	//-- Checks if two 'pair' objects have the same value of theirs 'first' and 'second' members.
	//-- Returns 'true' if there are equal and 'false' if there are not. 
	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) 
	{
		return ( lhs.first == rhs.first && lhs.second == rhs.second );
	};

	//-- Returns 'true' if the 'first' and 'second' members
	//-- of the two 'pair' objects are not equal, returns 'false' otherwise. 
	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs==rhs);
	};

	//-- Check if the first element of the left-hand side pair is 
	//-- smaller than the first element of the right-hand side pair
	//-- If true : return true 
	//-- -> left and side pair should come first in the sorted order. 
	//-- second check is here to stop comparison if there first elems are not equal.
	//-- If firsts eleme are equal => comparison of second to determine order.
	template <class T1, class T2>
        bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	};

	//-- Returns true if left-hand side pair <= to the right-hand side pair
	//-- Returns true if both the first and second element of the left-hand side pair
	//-- are equal to the first and second elements og the right-hand side pair. 
	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(rhs<lhs);
	};

	//-- Same as < in the other sens
	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return rhs<lhs;
	};

	//-- Same as <= in the other sens
	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs<rhs);
	};
}
#endif
