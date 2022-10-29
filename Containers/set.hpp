
#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "utility.hpp" // ft::pair
# include "rbtree.hpp"
# include "rbtree_iterator.hpp"
# include "reverse_iterator.hpp"
# include <functional> // std::less
# include <cstddef>	  // std::ptrdiff_t, std::size_t

namespace ft
{
	template <typename T>
	struct Identity
	{
		T &operator()(T &x) const
		{
			return x;
		}

		const T &operator()(const T &x) const
		{
			return x;
		}
	};

	template <typename Key,							   // set::key_type/value_type
			  typename Compare = std::less<Key>,	   // set::key_compare/value_compare
			  typename Alloc = std::allocator<Key> // set::allocator_type
			  >
	class set
	{
	public:
		// Member types
		typedef Key key_type; // clé
		typedef Key value_type; // valeur
		typedef Compare key_compare; // fonction de comparaison des clés
		typedef Compare value_compare; // fonction de comparaison des valeurs
		typedef Alloc allocator_type; // allocateur
		typedef typename allocator_type::reference reference; // référence
		typedef typename allocator_type::const_reference const_reference; // référence const
		typedef typename allocator_type::pointer pointer; // pointeur
		typedef typename allocator_type::const_pointer const_pointer; // pointeur const
		typedef ft::rbtree_const_iterator<value_type> iterator; // itérateur
		typedef ft::rbtree_const_iterator<value_type> const_iterator; // itérateur constant
		typedef ft::reverse_iterator<iterator> reverse_iterator; // itérateur réversible
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator; // itérateur réversible constant
		typedef std::ptrdiff_t difference_type; // différence
		typedef std::size_t size_type; // taille

	protected:
		typedef ft::rbtree<key_type, value_type, Identity<value_type>, key_compare, allocator_type> tree_type; // type de l'arbre
		typedef typename tree_type::node_type node_type; // noeud
		typedef typename tree_type::node_ptr node_ptr; // pointeur de noeud

	public:

		// (1)Constructeurs par défaut
		explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
		} // construit un conteneur vide

		// (2) Constructeur de gamme
		template <typename InputIterator>
		set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
		{
			(void)comp;
			(void)alloc;
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		} // construit un conteneur avec les éléments de la gamme [first, last)

		// (3) Constructeur de copie
		set(const set &x)
		{
			*this = x;
		} // construit un conteneur avec une copie des éléments de x

		// Destructeur
		~set()
		{
			this->clear();
		} // détruit le conteneur

		// Opérateur d'affectation (=)
		set &operator=(const set &x)
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
		} //  Attribue un nouveau contenu au conteneur

		// Function membres
		// retournent un itérateur sur le premier élément du conteneur
		iterator begin()
		{
			if (this->empty())
				return this->end();
			return iterator(node_type::minimum(_bst.getRoot()));
		}

		// retournent un itérateur constant sur le premier élément du conteneur
		const_iterator begin() const
		{
			if (this->empty())
				return this->end();
			return const_iterator(node_type::minimum(_bst.getRoot()));
		}

		// retournent un itérateur sur le dernier élément du conteneur
		iterator end()
		{
			return iterator(_bst.getTNULL());
		}

		// retournent un itérateur constant sur le dernier élément du conteneur
		const_iterator end() const
		{
			return const_iterator(_bst.getTNULL());
		}

		// retournent un itérateur réversible sur le premier élément du conteneur
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		// retournent un itérateur réversible constant sur le premier élément du conteneur
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		// retournent un itérateur réversible sur le dernier élément du conteneur
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		// retournent un itérateur réversible constant sur le dernier élément du conteneur
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// retournent true si le conteneur est vide
		// Capacity
		bool empty() const
		{
			return (_bst.size() == 0);
		}

		// retournent le nombre d'éléments du conteneur
		size_type size() const
		{
			return _bst.size();
		}

		// retournent le nombre maximal d'éléments que peut contenir le conteneur
		size_type max_size() const
		{
			return _bst.max_size();
		}

		// Modifiers
		// insère une copie de val dans le conteneur
		ft::pair<iterator, bool> insert(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val);
			if (tmp)
			{
				return ft::make_pair(iterator(tmp), false);
			}
			else
			{
				tmp = _bst.rbInsert(val);
				return ft::make_pair(iterator(tmp), true);
			}
		}

		// insère une copie de val dans le conteneur a l'endroit indiqué par position
		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return this->insert(val).first;
		}

		// insère les éléments de la gamme [first, last) dans le conteneur
		template <typename InputIterator>
		void insert(
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last)
		{
			for (InputIterator it = first; it != last; ++it)
			{
				this->insert(*it);
			}
		}

		// supprime l'element de la position indiquée par position
		void erase(iterator position)
		{
			_bst.rbDelete(const_cast<node_ptr>(position._node));
		}


		// supprime l'element val du conteneur
		size_type erase(const value_type &val)
		{
			node_ptr tmp = _bst.searchKey(val);
			if (tmp)
			{
				_bst.rbDelete(const_cast<node_ptr>(tmp));
				return 1;
			}
			return 0;
		}

		// supprime les éléments de la gamme [first, last) du conteneur
		void erase(iterator first, iterator last)
		{
			for (iterator it = first++; it != last; it = first++)
			{
				_bst.rbDelete(const_cast<node_ptr>(it._node));
			}
		}

		// echange le contenu du conteneur avec celui de x
		void swap(set &x)
		{
			_bst.swap(x._bst);
		}

		// supprime tous les éléments du conteneur
		void clear()
		{
			while (!this->empty())
			{
				this->erase(this->begin());
			}
		}

		// Observers
		key_compare key_comp() const
		{
			return key_compare();
		}

		value_compare value_comp() const
		{
			return key_compare();
		}

		// Operations
		// retournent un itérateur sur l'élément val s'il existe dans le conteneur
		iterator find(const key_type &k) const
		{
			node_ptr tmp = _bst.searchKey(k);
			if (tmp)
				return iterator(tmp);
			else
				return this->end();
		}

		// retournent le nombre d'éléments équivalents a val dans le conteneur
		size_type count(const key_type &k) const
		{
			size_type n = 0;

			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (_bst.equal(k, *it))
				{
					++n;
				}
			}
			return n;
		}

		// retournent un itérateur vers le premier élément du conteneur qui n'est pas considéré comme précédant a val
		iterator lower_bound(const key_type &k) const
		{
			iterator it = this->begin();
			while (key_comp()(*it, k) && it != this->end())
			{
				++it;
			}
			return it;
		}

		// retournent un itérateur vers le premier élément du conteneur qui est considéré comme précédant a val
		iterator upper_bound(const key_type &k) const
		{
			iterator it = this->begin();
			while (!key_comp()(k, *it) && it != this->end())
			{
				++it;
			}
			return it;
		}

		// retournent un pair d'itérateurs correspondant a la gamme d'éléments équivalents a val
		ft::pair<iterator, iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
		}

		// Allocator
		// retourne l'allocateur utilisé par le conteneur
		allocator_type get_allocator() const
		{
			return allocator_type();
		}

	private:
		tree_type _bst; // arbre binaire de recherche
	};

	// Function  non-membre overloads
	// Operateurs d'egalité (==)
	template <typename Key, typename Compare, typename Alloc>
	bool operator==(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	// Operateurs d'inegalité (!=)
	template <typename Key, typename Compare, typename Alloc>
	bool operator!=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	// Operateur inferieur (<)
	template <typename Key, typename Compare, typename Alloc>
	bool operator<(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	// Operateur inferieur ou egal (<=)
	template <typename Key, typename Compare, typename Alloc>
	bool operator<=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	// Operateur superieur (>)
	template <typename Key, typename Compare, typename Alloc>
	bool operator>(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	// Operateur superieur ou egal (>=)
	template <typename Key, typename Compare, typename Alloc>
	bool operator>=(const set<Key, Compare, Alloc> &lhs, const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	// Echange le contenu du conteneur x avec celui de y
	template <typename Key, typename Compare, typename Alloc>
	void swap(set<Key, Compare, Alloc> &x, set<Key, Compare, Alloc> &y)
	{
		x.swap(y);
	}

} // namespace ft

#endif