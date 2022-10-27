
#ifndef UTILITY_HPP
# define UTILITY_HPP

# include "algorithm.hpp"

namespace ft
{
    template <typename T1, typename T2> // template generic std::pair
    struct pair
    {
        // types:
        typedef T1 first_type;
        typedef T2 second_type;

        // variables:
        first_type first;
        second_type second;

        // constructeur par defaut
        pair()
            : first(), second()
        {
        }

		// constructeur d'initialisation
        template <typename U, typename V>
        pair(const pair<U, V> &pr)
            : first(pr.first), second(pr.second)
        {
        }
        pair(const first_type &a, const second_type &b)
            : first(a), second(b)
        {
        }

        // operateur d'assignement (=)
        pair &operator=(const pair &pr)
        {
            if (this != &pr)
            {
                first = pr.first;
                second = pr.second;
            }
            return (*this);
        };
    };

    //  Non-member function overloads
	// operteur "=="
    template <typename T1, typename T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }

	// operteur "!="
    template <typename T1, typename T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }

	// opérateur "<"
    template <typename T1, typename T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }

	// opérateur "<="
    template <typename T1, typename T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }

	// opérateur ">"
    template <typename T1, typename T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return (rhs < lhs);
    }

	// opérateur ">="
    template <typename T1, typename T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }

	// std::make_pair: Pour faire une paire à partir de deux valeurs"
    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    }

} // namespace ft

#endif
