
#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
	template <typename Iterator> // template generic
	class reverse_iterator
		: public iterator<typename ft::iterator_traits<Iterator>::iterator_category, // catégorie pour l'itérateur
						  typename ft::iterator_traits<Iterator>::value_type,		 // l'élément vers lequel l'itérateur peut pointer
						  typename ft::iterator_traits<Iterator>::difference_type,  // difference
						  typename ft::iterator_traits<Iterator>::pointer,          // pointeur vers lequel l'itérateur peut pointer
						  typename ft::iterator_traits<Iterator>::reference> 		// référence renvoyé par l'itérateur
	{
	protected:
		Iterator _base_iterator; // une copie de l'iterateur original
		typedef typename ft::iterator_traits<Iterator> traits_type; // type trait de Iterator

	public:
		// Member types
		typedef Iterator iterator_type; // iterateur
		typedef typename traits_type::iterator_category iterator_category; // catégorie pour l'itérateur
		typedef typename traits_type::value_type value_type; // élément vers lequel l'itérateur peut pointer
		typedef typename traits_type::difference_type difference_type; // difference
		typedef typename traits_type::pointer pointer; // pointeur vers lequel l'itérateur peut pointer
		typedef typename traits_type::reference reference; // référence renvoyé par l'itérateur

		// Member functions
		// (1) constructeur par defaut
		reverse_iterator()
			: _base_iterator(iterator_type())
		{
		}
		// (2) constructeur par initialisation
		explicit reverse_iterator(iterator_type it)
			: _base_iterator(it) // initialization
		{
		}

		// (3) constructeur par copie
		template <typename Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it)
			: _base_iterator(rev_it.base()) // copy-constructor
		{
		}

		// return une une copie de l' itérateur de base
		iterator_type base() const
		{
			return _base_iterator;
		}

		//(a*) retroune une référence à l'élément pointé par l'itérateur.
		reference operator*() const
		{
			iterator_type tmp = _base_iterator;
			return *(--tmp);
		}

		//(+n) retourne un reverse_iterator qui pointe vers l'élément situé à n positions de l'élément vers lequel pointe actuellement l'itérateur
		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(_base_iterator - n);
		}

		//(++) avance le reverse_iterator de 1 positions, soit -1
		reverse_iterator &operator++()
		{
			--(_base_iterator);
			return *this;
		}

		//(++) avance le reverse_iterator de 1 positions mais renvoie la valeur avant l'incrémentation
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		//(+=) avance le reverse_iterator de n positions
		reverse_iterator &operator+=(difference_type n)
		{
			_base_iterator -= n;
			return *this;
		}

		//(-n)retourne un reverse_iterator qui pointe vers l'élément situé à n positions de l'élément vers lequel pointe actuellement l'itérateur
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(_base_iterator + n);
		}

		//(--) recule le reverse_iterator de 1 positions, soit +1
		reverse_iterator &operator--()
		{
			++(_base_iterator);
			return *this;
		}

		//(--) recule le reverse_iterator de 1 positions mais renvoie la valeur avant la décrémentation
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		//(-=) recule le reverse_iterator de n positions
		reverse_iterator &operator-=(difference_type n)
		{
			_base_iterator += n;
			return *this;
		}

		//(->) retourne un pointeur vers l'élément pointé par l'itérateur 
		pointer operator->() const
		{
			return &(operator*());
		}

		// Accède à l'élément situé à n positions de l'élément actuellement pointé par l'itérateur
		reference operator[](difference_type n) const
		{
			return base()[-n - 1];
		}
	};

	// Non-member functions
	// (==) retourne true si les itérateurs lhs et rhs pointent vers le même élément, false sinon
	template <typename Iterator1, typename Iterator2>
	bool operator==(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	// (!=) retourne true si les itérateurs lhs et rhs ne pointent pas vers le même élément, false sinon
	template <typename Iterator1, typename Iterator2>
	bool operator!=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return !(rhs == lhs);
	}

	// (<) retourne true si l'itérateur lhs pointe vers un élément situé avant l'élément pointé par l'itérateur rhs, false sinon
	template <typename Iterator1, typename Iterator2>
	bool operator<(const reverse_iterator<Iterator1> &lhs,
				   const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	// (<=) retourne true si l'itérateur lhs pointe vers un élément situé avant ou au même endroit que l'élément pointé par l'itérateur rhs, false sinon
	template <typename Iterator1, typename Iterator2>
	bool operator<=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return !(rhs < lhs);
	}

	// (>) retourne true si l'itérateur lhs pointe vers un élément situé après l'élément pointé par l'itérateur rhs, false sinon
	template <typename Iterator1, typename Iterator2>
	bool operator>(const reverse_iterator<Iterator1> &lhs,
				   const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs < lhs);
	}

	// (>=) retourne true si l'itérateur lhs pointe vers un élément situé après ou au même endroit que l'élément pointé par l'itérateur rhs, false sinon
	template <typename Iterator1, typename Iterator2>
	bool operator>=(const reverse_iterator<Iterator1> &lhs,
					const reverse_iterator<Iterator2> &rhs)
	{
		return !(lhs < rhs);
	}

	// (+) retourne un reverse_iterator qui pointe vers l'élément situé à n positions de l'élément vers lequel pointe actuellement l'itérateur
	template <typename Iterator>
	reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &it)
	{
		return reverse_iterator<Iterator>(it.base() - n);
	}

	// (-) retourne la distance entre les itérateurs lhs et rhs
	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(
		const reverse_iterator<Iterator1> &lhs,
		const reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
} // namespace ft

#endif
