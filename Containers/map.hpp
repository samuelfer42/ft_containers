
#ifndef MAP_HPP
# define MAP_HPP

# include "utility.hpp" // ft::pair
# include "vector.hpp"
# include "rbtree.hpp"
# include "rbtree_iterator.hpp"
# include "reverse_iterator.hpp"
# include <cstddef>	  // std::ptrdiff_t, std::size_t

namespace ft
{
	template <typename Pair>
	struct Slect1st
	{
		typename Pair::first_type &operator()(Pair &x) const
		{
			return x.first;
		}

		const typename Pair::first_type &operator()(const Pair &x) const
		{
			return x.first;
		}
	};

	template <typename Key,											  // map::key_type
			  typename T,											  // map::mapped_type
			  typename Compare = std::less<Key>,					  // map::key_compare
			  typename Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
			  >

	class map
	{
	public:
		// Member types
		typedef Key key_type; // cle
		typedef T mapped_type; // valeur
		typedef ft::pair<const key_type, mapped_type> value_type; // paire cle/valeur
		typedef Compare key_compare; // fonction de comparaison des cle
		typedef Alloc allocator_type; // allocateur
		typedef typename allocator_type::reference reference; //reference
		typedef typename allocator_type::const_reference const_reference; // reference const
		typedef typename allocator_type::pointer pointer; // pointeur
		typedef typename allocator_type::const_pointer const_pointer; //  pointeur const
		typedef ft::rbtree_iterator<value_type> iterator; // iterateur
		typedef ft::rbtree_const_iterator<value_type> const_iterator; // iterateur const
		typedef ft::reverse_iterator<iterator> reverse_iterator; // iterateur inverse
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator; // iterateur inverse const
		typedef std::ptrdiff_t difference_type; // difference
		typedef std::size_t size_type; // taille

	protected:
		typedef ft::rbtree<key_type, value_type, Slect1st<value_type>, key_compare, allocator_type> tree_type;
		typedef typename tree_type::node_type node_type; // noeud
		typedef typename tree_type::node_ptr node_ptr; // pointeur de noeud

	public:
		class value_compare
		{
			friend class map; // permet d'acceder a la fonction de comparaison de cle

		protected:
			Compare _comp; // fonction de comparaison de cle (map::key_compare)
			value_compare(Compare c) : _comp(c) {} // construit avec l'objet de comparaison de map

		public:
			typedef bool result_type; // resultat
			typedef value_type first_argument_type; // premier argument
			typedef value_type second_argument_type; // second argument
			bool operator()(const value_type &x, const value_type &y) const
			{
				return _comp(x.first, y.first);
			}
		};

		// (1) Constructeurs par defaut
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
		} //constructeur de conteneur vide

		// (2) Constructeur range
		template <typename InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		} // construit un conteneur avec les elements du range [first, last)

		// (3) Constructeur par copie
		map(const map &x)
		{
			*this = x;
		} // construit un conteneur avec une copie de x

		// Destructeur
		~map()
		{
			this->clear();
		}// detruit le conteneur

		// Operateur d'affectation (=)
		map &operator=(const map &x)
		{
			if (this != &x)
			{
				this->clear();
				for (const_iterator it = x.begin(); it != x.end(); ++it)
				{
					this->insert(*it);
				}
			}
			return *this;
		}// affecte x a l'objet courant

		// Funcitons membres
		// Iterateurs
		iterator begin()
		{
			if (this->empty())
				return this->end();
			return iterator(node_type::minimum(_bst.getRoot()));
		}

		const_iterator begin() const
		{
			if (this->empty())
				return this->end();
			return const_iterator(node_type::minimum(_bst.getRoot()));
		}

		iterator end()
		{
			return iterator(_bst.getTNULL());
		}

		const_iterator end() const
		{
			return const_iterator(_bst.getTNULL());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// Capacity
		bool empty() const
		{
			return (_bst.size() == 0);
		} // retourne true si le conteneur est vide

		size_type size() const
		{
			return _bst.size();
		} // retourne le nombre d'elements

		size_type max_size() const
		{
			return _bst.max_size();
		} // retourne le nombre maximal d'elements

		// Element access
		mapped_type &operator[](const key_type &k)
		{
			this->insert(ft::make_pair(k, mapped_type()));
			return this->find(k)->second;
		} // retourne une reference sur l'element de cle k

		// Modifiers
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val.first);
			if (tmp)
			{
				return ft::make_pair(iterator(tmp), false);
			}
			else
			{
				tmp = _bst.rbInsert(val);
				return ft::make_pair(iterator(tmp), true);
			}
		} // insere une paire cle/valeur dans le conteneur

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return this->insert(val).first;
		}// insere une paire cle/valeur dans le conteneur a la position position

		template <typename InputIterator>
		void insert(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		} // insere les elements du range [first, last) dans le conteneur

		void erase(iterator position)
		{
			_bst.rbDelete(position._node);
		} // supprime l'element a la position position

		size_type erase(const key_type &k)
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
			{
				_bst.rbDelete(tmp);
				return 1;
			}
			return 0;
		} // supprime l'element de cle k

		void erase(iterator first, iterator last)
		{
			for (iterator it = first++; it != last; it = first++)
			{
				_bst.rbDelete(it._node);
			}
		} // supprime les elements du range [first, last)

		void swap(map &x)
		{
			_bst.swap(x._bst);
		} // echange le contenu du conteneur avec celui de x

		void clear()
		{
			while (!this->empty())
			{
				this->erase(this->begin());
			}
		} // supprime tous les elements du conteneur

		key_compare key_comp() const
		{
			return key_compare();
		} // retourne l'objet de comparaison des cles

		value_compare value_comp() const
		{
			return value_compare(key_compare());
		} // retourne l'objet de comparaison des valeurs

		// Operations
		iterator find(const key_type &k)
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
				return iterator(tmp);
			else
				return this->end();
		} // retourne un iterateur sur l'element de cle k

		const_iterator find(const key_type &k) const
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
				return const_iterator(tmp);
			else
				return this->end();
		} // retourne un iterateur de cle k qui ne pourra pas modifier l'element

		size_type count(const key_type &k) const
		{
			size_type n = 0;

			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_bst.equal(k, it->first))
				{
					++n;
				}
			}
			return n;
		} // retourne le nombre d'elements de cle k

		iterator lower_bound(const key_type &k)
		{
			iterator it = this->begin();
			while (key_comp()(it->first, k) && it != this->end())
			{
				++it;
			}
			return it;
		} // retourne un iterateur sur le premier element de cle k

		const_iterator lower_bound(const key_type &k) const
		{
			const_iterator it = this->begin();
			while (key_comp()(it->first, k) && it != this->end())
			{
				++it;
			}
			return it;
		}  // retourne un iterateur constant sur le premier element de cle k

		iterator upper_bound(const key_type &k)
		{
			iterator it = this->begin();
			while (!key_comp()(k, it->first) && it != this->end())
			{
				++it;
			}
			return it;
		} // retourne un iterateur sur le premier element de cle superieure a k

		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator it = this->begin();
			while (!key_comp()(k, it->first) && it != this->end())
			{
				++it;
			}
			return it;
		} // retourne un iterateur constant sur le premier element de cle superieure a k

		ft::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		} // retourne un pair d'iterateurs sur le range de cle k

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}  // retourne un pair d'iterateurs constants sur le range de cle k

		// Allocator
		allocator_type get_allocator() const
		{
			return allocator_type();
		} // retourne l'allocateur associe au conteneur

	private:
		tree_type _bst; // arbre binaire de recherche
	};

	// Fonction non-membre
	// Relational operators
	// Operateurs de comparaison (==)
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	// Operateurs de comparaison (!=)
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	// Operateurs de comparaison (<)
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	// Operateurs de comparaison (<=)
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	// Operateurs de comparaison (>)
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	// Operateurs de comparaison (>=)
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	// Swap
	template <typename Key, typename T, typename Compare, typename Alloc>
	void swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif
