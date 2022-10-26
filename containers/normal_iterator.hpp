
#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator_traits.hpp"
# include <cstddef> // std::ptrdiff_t

namespace ft
{
	template <typename Iterator> // template generic
	class normal_iterator
	{
	protected:
		Iterator _current; // notre iterateur
		typedef typename ft::iterator_traits<Iterator> traits_type; // type trait de Iterator

	public:
		typedef typename traits_type::difference_type difference_type; // type de difference
		typedef typename traits_type::value_type value_type; // type de l'élément vers lequel l'itérateur peut pointer
		typedef typename traits_type::pointer pointer; // type de pointeur vers lequel l'itérateur peut pointer
		typedef typename traits_type::reference reference; // type de référence renvoyé par l'itérateur
		typedef typename traits_type::iterator_category iterator_category; // type de catégorie pour l'itérateur

		// constructeur par defaut
		normal_iterator()
			: _current(0)
		{
		}
		// initialisation
		explicit normal_iterator(Iterator iter)
			: _current(iter)
		{
		}

		// copy-constructeur
		template <typename Iter>
		normal_iterator(const normal_iterator<Iter> &rhs)
			: _current(rhs.base())
		{
		}

		// destructeur
		virtual ~normal_iterator()
		{
		}

		// copy-assignment operator
		template <typename Iter>
		normal_iterator &operator=(const normal_iterator<Iter> &rhs)
		{
			_current = rhs.base();
			return *this;
		}


		Iterator base() const
		{
			return _current;
		} // retourne l'iterateur actuel

		//  opérateur de déréférencement(*a)
		reference operator*() const
		{
			return *_current;
		}

		// operateur a+n
		normal_iterator operator+(difference_type n) const
		{
			return normal_iterator(_current + n);
		}

		// opérateur d'incrément (a++)
		normal_iterator &operator++()
		{
			++_current;
			return *this;
		}

		// opérateur d'incrément (++a)
		normal_iterator operator++(int)
		{
			normal_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		// opérateur d'ajout (a+=n)
		normal_iterator &operator+=(difference_type n)
		{
			_current += n;
			return *this;
		}

		// opérateur de retrait (a-n)
		normal_iterator operator-(difference_type n) const
		{
			return normal_iterator(_current - n);
		}

		// opérateur de décrémentation (a--)
		normal_iterator &operator--()
		{
			--_current;
			return *this;
		}

		// opérateur de décrémentation (--a)
		normal_iterator operator--(int)
		{
			normal_iterator tmp(*this);
			--(*this);
			return tmp;
		}

		// opérateur de retranchement (a-=n)
		normal_iterator &operator-=(difference_type n)
		{
			_current -= n;
			return *this;
		}

		// opérateur d'accès ->()
		pointer operator->() const
		{
			return _current;
		}

		// opérateur d'accès (a[n])
		reference operator[](const int n) const
		{
			return _current[n];
		}
	};

	// fonction non-membre
	// opérateur de comparaison (a == b)
	template <typename Iterator1, typename Iterator2>
	bool operator==(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// opérateur de comparaison (a != b)
	template <typename Iterator1, typename Iterator2>
	bool operator!=(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return !(lhs == rhs);
	}

	// opérateur de comparaison inferieur (a < b)
	template <typename Iterator1, typename Iterator2>
	bool operator<(const normal_iterator<Iterator1> &lhs,
				   const normal_iterator<Iterator2> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	// opérateur de comparaison egal (a <= b)
	template <typename Iterator1, typename Iterator2>
	bool operator<=(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return !(rhs < lhs);
	}

	// opérateur de comparaison supérieur (a > b)
	template <typename Iterator1, typename Iterator2>
	bool operator>(const normal_iterator<Iterator1> &lhs,
				   const normal_iterator<Iterator2> &rhs)
	{
		return (rhs < lhs);
	}

	// opérateur de comparaison supérieur egal (a >= b)
	template <typename Iterator1, typename Iterator2>
	bool operator>=(const normal_iterator<Iterator1> &lhs,
					const normal_iterator<Iterator2> &rhs)
	{
		return !(lhs < rhs);
	}

	// operaeteur d'addition (a + n)
	template <typename Iterator>
	normal_iterator<Iterator> operator+(
		typename normal_iterator<Iterator>::difference_type n,
		const normal_iterator<Iterator> &it) 
	{
		return normal_iterator<Iterator>(it.base() + n); 
	} 

	// opérateur de difference (b - a)
	template <typename Iterator1, typename Iterator2>
	typename normal_iterator<Iterator1>::difference_type operator-(
		const normal_iterator<Iterator1> &lhs,
		const normal_iterator<Iterator2> &rhs)
	{
		return (lhs.base() - rhs.base());
	} //renvoie la différence entre it1 et it2
}

#endif
