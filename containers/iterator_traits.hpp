
#ifndef ITERATOR_TRAITS
#define ITERATOR_TRAITS

#include <cstddef> // std::ptrdiff_t

namespace ft
{
	// template generic
	template <typename Category, typename T, typename Distance = std::ptrdiff_t,
			  typename Pointer = T *, typename Reference = T &> 
	
	struct iterator
	{
		typedef Distance difference_type;	// type de difference 
		typedef T value_type;				// type de l'élément vers lequel l'itérateur peut pointer
		typedef Pointer pointer; 			// type de pointeur vers lequel l'itérateur peut pointer
		typedef Reference reference;  		// type de référence renvoyé par l'itérateur
		typedef Category iterator_category; // type de catégorie pour l'itérateur 
	};

	// iterator_category
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// iterator_traits
	template <typename Iterator>
	struct iterator_traits // transforme un iterateur au forme d'un itérateur std
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <typename T>
	struct iterator_traits<T *> // transforme un pointeur (T *) en iterator_traits<T *>
	{
		typedef typename std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef typename ft::random_access_iterator_tag iterator_category;
	}; 

	template <typename T>
	struct iterator_traits<const T *> // // transforme un pointeur (const T *) en iterator_traits<const T *>
	{
		typedef typename std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef typename ft::random_access_iterator_tag iterator_category;
	}; 
} // namespace ft

#endif
