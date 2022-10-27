
#ifndef ITERATOR_TRAITS
# define ITERATOR_TRAITS

#include <cstddef> // std::ptrdiff_t

namespace ft
{
	// template generic
	template <typename Category, typename T, typename Distance = std::ptrdiff_t,
			  typename Pointer = T *, typename Reference = T &>

	struct iterator
	{
		typedef Distance difference_type;	// difference
		typedef T value_type;				// l'élément vers lequel l'itérateur peut pointer
		typedef Pointer pointer; 			// pointeur vers lequel l'itérateur peut pointer
		typedef Reference reference;  		// référence renvoyé par l'itérateur
		typedef Category iterator_category; // catégorie pour l'itérateur
	};

	// iterator_category
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	// iterator_traits
	template <typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type; // difference
		typedef typename Iterator::value_type value_type;           // élément vers lequel l'itérateur peut pointer
		typedef typename Iterator::pointer pointer;					// pointeur vers lequel l'itérateur peut pointer
		typedef typename Iterator::reference reference;    			// référence renvoyé par l'itérateur
		typedef typename Iterator::iterator_category iterator_category; // catégorie pour l'itérateur
	};

	template <typename T>
	struct iterator_traits<T *> // specialisation pour les pointeurs (T*)
	{
		typedef typename std::ptrdiff_t difference_type; // difference
		typedef T value_type; 							 // élément vers lequel l'itérateur peut pointer
		typedef T *pointer; 							 // pointeur vers lequel l'itérateur peut pointer
		typedef T &reference; 							 // référence renvoyé par l'itérateur
		typedef typename ft::random_access_iterator_tag iterator_category; // catégorie pour l'itérateur
	};

	template <typename T>
	struct iterator_traits<const T *> // specialisation pour les pointeurs const (const T*)
	{
		typedef typename std::ptrdiff_t difference_type; // difference
		typedef T value_type; 							 // élément vers lequel l'itérateur peut pointer
		typedef const T *pointer; 						 // pointeur vers lequel l'itérateur peut pointer
		typedef const T &reference; 					 // référence renvoyé par l'itérateur
		typedef typename ft::random_access_iterator_tag iterator_category; // catégorie pour l'itérateur
	};
} // namespace ft

#endif
