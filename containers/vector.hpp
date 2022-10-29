
#ifndef VECTOR_H
# define VECTOR_H

# include "type_traits.hpp"
# include "reverse_iterator.hpp"
# include "normal_iterator.hpp"
# include "algorithm.hpp"
# include <cstddef>	 // std::ptrdiff_t
# include <memory>	 // std::allocator
# include <stdexcept> // std::out_of_range
# include <stdint.h>

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> > // generic template
	class vector
	{
	public:
		typedef T value_type;						// valeur
		typedef Alloc allocator_type;				// allocateur
		typedef value_type &reference;				// reference
		typedef const value_type &const_reference; // reference const
		typedef value_type *pointer;				// pointeur sur valeur
		typedef const value_type *const_pointer;	// pointeur sur valeur qui est const
		typedef ft::normal_iterator<pointer> iterator; // iterateur Generic
		typedef ft::normal_iterator<const_pointer> const_iterator; // iterateur Const
		typedef ft::reverse_iterator<iterator> reverse_iterator; //reverse iterateur
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator; //reverse iterateur constant
		typedef std::ptrdiff_t difference_type;    // difference
		typedef std::size_t size_type;			// taille

	    // Member functions
		// (1)constructeur de conteneur vide
		explicit vector(const allocator_type &alloc = allocator_type())
			: _size(0), _capacity(0), _allocator(alloc), _data(NULL)
		{
		}//constructeur par défaut, vide

		// (2)constructeur de remplissage
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _size(n), _capacity(n), _allocator(alloc)
		{
			_data = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i)
			{
				_allocator.construct(_data + i, val);
			}
		} // Contruit le conteneur avec n valeurs val

		// (3) constructeur de conteneur en fonciton d'un range [first, last]
		template <typename InputIterator>
		vector(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last,
			const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
		{
			_capacity = 0;
			for (InputIterator it = first; it != last; ++it)
			{
				++_capacity;
			}
			_data = _allocator.allocate(_capacity);
			for (_size = 0; _size < _capacity; ++_size)
			{
				_allocator.construct(_data + _size, *first++);
			}
		}

		// (4) constructeur par copie de chacun des éléments de x
		vector(const vector &x)
			: _size(x._size), _capacity(x._capacity), _allocator(x._allocator)
		{
			_data = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i)
			{
				_allocator.construct(_data + i, x[i]);
			}
		}

		// Destructor
		~vector()
		{
			for (size_type i = 0; i < _size; ++i)
			{
				_allocator.destroy(_data + i);
			}
			_allocator.deallocate(_data, _capacity);
		}

		// operateur de copie (=)
		//Affecte un nouveau contenu au conteneur, en remplaçant son contenu actuel et en modifiant sa taille si nécessaire.
		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.destroy(_data + i);
				}
				_allocator.deallocate(_data, _capacity);
				_capacity = x._capacity;
				_data = _allocator.allocate(_capacity);
				for (_size = 0; _size < x._size; ++_size)
				{
					_allocator.construct(_data + _size, x[_size]);
				}
			}
			return *this;
		}

		// Iterators
		// Retourne un iterateur pointant sur le premier élément du conteneur.
		iterator begin()
		{
			return iterator(_data);
		}

		// Retourne un iterateur constant pointant sur le premier élément du conteneur.
		const_iterator begin() const
		{
			return const_iterator(_data);
		}

		// Retourne un iterateur pointant sur la position juste après la dernière valeur du conteneur.
		iterator end()
		{
			return iterator(_data + _size);
		}

		// Retourne un iterateur constant pointant sur la position juste après la dernière valeur du conteneur.
		const_iterator end() const
		{
			return const_iterator(_data + _size);
		}

		// Retourne un reverse iterator pointant sur la dernière valeur du conteneur (c'est-à-dire son élément de fin).
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		// Retourne un reverse iterator constant pointant sur la dernière valeur du conteneur (c'est-à-dire son élément de fin).
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		// Retourne un reverse iterator pointant sur la position juste avant le premier élément du conteneur.
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		// Retourne un reverse iterator constant pointant sur la position juste avant le premier élément du conteneur.
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// Capacity
		// Retourne le nombre d'éléments dans le vecteur
		size_type size() const
		{
			return _size;
		}

		// Retourne le nombre maximum d'éléments que peut contenir le conteneur.
		size_type max_size() const
		{
			return (_allocator.max_size() < PTRDIFF_MAX) ? _allocator.max_size() : PTRDIFF_MAX;
		}

		// redimensionne le conteneur pour qu'il contienne n éléments.
		void resize(size_type n, value_type val = value_type())
		{
			if (n <= _size)
			{
				for (size_type i = n; i < _size; ++i)
				{
					_allocator.destroy(_data + i);
				}
			}
			else
			{
				this->reserve(n);
				for (size_type i = _size; i < n; ++i)
				{
					_allocator.construct(_data + i, val);
				}
			}
			_size = n;
		}

		// Retourne la taille du conteneur allouée actuellement en mémoire.
		size_type capacity() const
		{
			return _capacity;
		}

		// Vérifie si le conteneur est vide.
		bool empty() const
		{
			return (_size == 0);
		}

		// demande à ce que le conteneur ait une capacité suffisante pour contenir n éléments.
		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				pointer tmp = _data;

				if (n < _capacity * 2)
				{
					n = _capacity * 2;
				}
				_data = _allocator.allocate(n);
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.construct(_data + i, tmp[i]);
					_allocator.destroy(tmp + i);
				}
				_allocator.deallocate(tmp, _capacity);
				_capacity = n;
			}
		}

		// Element access
		// Renvoie une référence à l'élément à la position n dans le conteneur.
		reference operator[](size_type n)
		{
			return _data[n];
		}

		// Renvoie une référence constante à l'élément à la position n dans le conteneur.
		const_reference operator[](size_type n) const
		{
			return _data[n];
		}

		// Retourne une référence à l'élément à la position n dans le conteneur.
		reference at(size_type n)
		{
			if (n < _size)
				return _data[n];
			throw std::out_of_range("vector");
		}

		// Retourne une référence constante à l'élément à la position n dans le conteneur.
		const_reference at(size_type n) const
		{
			if (n < _size)
				return _data[n];
			throw std::out_of_range("vector");
		}

		// Retourne une référence à l'élément situé au debut du conteneur.
		reference front()
		{
			return _data[0];
		}

		// Retourne une référence constante à l'élément situé au debut du conteneur.
		const_reference front() const
		{
			return _data[0];
		}

		// Retourne une référence à l'élément situé à la fin du conteneur.
		reference back()
		{
			return _data[_size - 1];
		}

		// Retourne une référence constante à l'élément situé à la fin du conteneur.
		const_reference back() const
		{
			return _data[_size - 1];
		}

		// Modifiers
		// Remplacant un nouveau contenair construit depuis [first, last]
		template <typename InputIterator>
		void assign(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			size_type n = 0;

			for (InputIterator it = first; it != last; ++it)
			{
				++n;
			}
			this->reserve(n);
			for (size_type i = 0; i < n; ++i)
			{
				if (i < _size)
				{
					_allocator.destroy(_data + i);
				}
				_allocator.construct(_data + i, *first++);
			}
			_size = n;
		}

		// Remplacant un nouveau contenair construit depuis n éléments de val.
		void assign(size_type n, const value_type &val)
		{
			this->reserve(n);
			for (size_type i = 0; i < n; ++i)
			{
				if (i < _size)
				{
					_allocator.destroy(_data + i);
				}
				_allocator.construct(_data + i, val);
			}
			_size = n;
		}

		// Ajoute un élément à la fin du conteneur.
		void push_back(const value_type &val)
		{
			if (_size + 1 > _capacity)
			{
				this->resize(_size + 1, val);
			}
			else
			{
				_allocator.construct(_data + _size, val);
				++_size;
			}
		}

		// Supprime le dernier élément du conteneur.
		void pop_back()
		{
			--_size;
			_allocator.destroy(_data + _size);
		}

		// le vecteur est etendu en inserant une nouvelle valeur avant la position indiquée.
		iterator insert(iterator position, const value_type &val)
		{
			size_type i = position - this->begin();

			insert(position, 1, val);

			return iterator(this->begin() + i);
		}

		// le vecteur est etendu en inserant n valeurs avant la position indiquée.
		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type i = position - this->begin();

			this->reserve(_size + n);
			for (iterator it = this->end(); it != this->begin() + i; --it)
			{
				*(it - 1 + n) = *(it - 1);
			}
			for (size_type j = 0; j < n; ++j)
			{
				_allocator.construct(_data + i + j, val);
			}
			_size += n;
		}
		template <typename InputIterator>
		void insert(
			iterator position,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			size_type i = position - this->begin();
			size_type n = 0;

			for (InputIterator it = first; it != last; ++it)
			{
				++n;
			}
			this->reserve(_size + n);
			for (iterator it = this->end(); it != this->begin() + i; --it)
			{
				*(it - 1 + n) = *(it - 1);
			}
			for (size_type j = 0; j < n; ++j)
			{
				_allocator.construct(_data + i + j, *first++);
			}
			_size += n;
		}

		// Supprime un élément du conteneur.
		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}

		// Supprime une plage d'éléments du conteneur  [first,last]
		iterator erase(iterator first, iterator last)
		{
			size_type i = 0;

			for (iterator it = first; it != last; ++it)
			{
				_allocator.destroy(&(*it));
			}
			for (iterator it = last; it != this->end(); ++it)
			{
				*(first + i) = *it;
				++i;
			}
			_size -= last - first;

			return first;
		}

		// Remplace le contenu du conteneur par le contenu de x
		void swap(vector &x)
		{
			if (this != &x)
			{
				ft::swap(_data, x._data);
				ft::swap(_allocator, x._allocator);
				ft::swap(_size, x._size);
				ft::swap(_capacity, x._capacity);
			}
		}

		// Supprime tous les éléments du conteneur.
		void clear()
		{
			this->resize(0);
		}

		// Allocator
		// Retourne l'allocateur utilisé par le conteneur.
		allocator_type get_allocator() const
		{
			return _allocator;
		}

	private:
		size_type _size;	 // current size
		size_type _capacity; // allocated size
		allocator_type _allocator; //type allocator
		pointer _data; 			// pointer to data
	};

	// Non-member function overloads
	// Test d'égalité de deux conteneurs.
	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	// Test d'inégalité de deux conteneurs.
	template <typename T, typename Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	// Test si le premier conteneur est inférieur au second.
	template <typename T, typename Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	// Test si le premier conteneur est inférieur ou égal au second.
	template <typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs); // lhs <= rhs
	}

	// Test si le premier conteneur est supérieur au second.
	template <typename T, typename Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	// Test si le premier conteneur est supérieur ou égal au second.
	template <typename T, typename Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs); // rhs <= lhs
	}

	// Echange le contenu de deux conteneurs.
	template <typename T, typename Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif
