
#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	//swap (echanger les valeurs de a et de b)
    template <typename T>
    void swap(T &a, T &b)
    {
        T c(a);
        a = b;
        b = c;
    }
	//equal avec operateur(compare les elements d'une integrale [first1, last1] avec ceux de first2)
    template <typename InputIterator1, typename InputIterator2>
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
            {
                return false;
            }
        }
        return true;
    }

	//equal avec fonction binaire predicate (qui compare les elements)
    template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
    bool equal(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, BinaryPredicate pred)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!pred(*first1, *first2))
            {
                return false;
            }
        }
        return true;
    }

	// lexicographical_compare avec operateur (compare les elements d'une integrale [first1, last1] avec ceux de first2)
    template <typename InputIterator1, typename InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

	// lexicographical_compare avec focntion binaire (compare les elements d'une integrale [first1, last1] avec ceux de first2)
    template <typename InputIterator1, typename InputIterator2, typename Compare>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                                 InputIterator2 first2, InputIterator2 last2,
                                 Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

} // namespace ft

#endif
