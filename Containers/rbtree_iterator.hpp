
#ifndef RBTREE_ITERATOR
# define RBTREE_ITERATOR

#  include "rbtree.hpp"
#  include "iterator_traits.hpp" // iterator_tag
#  include <cstddef> // std::ptrdiff_t

namespace ft
{
    template <typename Val>
    class rbtree_iterator
    {
	public:
		typedef Val value_type; // element
		typedef Val *pointer; // pointer vers element
		typedef Val &reference; // reference vers element
		typedef rbtree_iterator<Val> self_type; // iterateur de l'arbre
		typedef ft::bidirectional_iterator_tag iterator_category; // categorie de l'iterateur
		typedef std::ptrdiff_t difference_type; // difference
		typedef ft::rbtree_node<Val> node_type; // noeud de l'arbre
		typedef typename node_type::node_ptr node_ptr; // pointeur vers noeud

        // Constructeur par defaut
		rbtree_iterator()
			: _node(0)
		{
		}

		// initialization
		explicit rbtree_iterator(node_ptr x)
			: _node(x)
		{
		}

		// constructeur par copie
		template <typename T>
		rbtree_iterator(const rbtree_iterator<T> &rhs)
			: _node(rhs._node)
		{
		}

		// destructeur
		virtual ~rbtree_iterator()
		{
		}

		// opérateur de copie (=)
		template <typename T>
		self_type &operator=(const rbtree_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// opérateur de déréférencement (*a)
		reference operator*() const
		{
			return _node->data;
		}

		// operateur d'incrementation (a++)
		self_type &operator++()
		{
			_node = _increment(_node);
			return *this;
		}

		// operateur d'incrementation (a+n)
		self_type operator++(int)
		{
			self_type tmp(*this);
			++(*this);
			return tmp;
		}

		// operateur de décrementation (a--)
		self_type &operator--()
		{
			_node = _decrement(_node);
			return *this;
		}

		// operateur de décrementation (a-n)
		self_type operator--(int)
		{
			self_type tmp(*this);
			--(*this);
			return tmp;
		}

		// operateur pointeur (a->)
		pointer operator->() const
		{
			return &(_node->data);
		}

		// opérateur d'égalité (a == b)
		friend bool operator==(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node == rhs._node);
		}

		// opérateur d'inégalité (a != b)
		friend bool operator!=(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node != rhs._node);
		}

		// Member variables
		node_ptr _node; // pointeur vers le noeud

		private:
			node_ptr _increment(node_ptr x)
			{
				// Cas 1 : l'enfant de droite existe, retourner le noeud le plus à gauche
				if (!node_type::isTNULL(x->right))
				{
					return node_type::minimum(x->right);
				}
				// backup _TNULL
				node_ptr _TNULL = x->right;
				// cas 2 : si il y a pas d'enfant droit, on remonte jusqu'à ce qu'on trouve un noeud qui est un enfant gauche
				while (x->parent)
				{
					if (x->parent->left == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Cas 3 : si on a pas trouvé de noeud qui est un enfant gauche, on retourne _TNULL (feuille)
				return _TNULL;
			}

			node_ptr _decrement(node_ptr x)
			{
				// Cas 0: si le noeud est _TNULL, on retourne le noeud le plus à droite
				if (node_type::isTNULL(x))
				{
					return node_type::maximum(x->parent);
				}
				// Cas 1: si le noeud a un enfant gauche, on retourne le noeud le plus à droite
				if (!node_type::isTNULL(x->left))
				{
					return node_type::maximum(x->left);
				}
				// Cas 2: si le noeud n'a pas d'enfant gauche, on remonte jusqu'à ce qu'on trouve un noeud qui est un enfant droit
				while (x->parent)
				{
					if (x->parent->right == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Cas 3: si on a pas trouvé de noeud qui est un enfant droit, on retourne _TNULL
				return NULL;
			}
	};

	template <typename Val>
    class rbtree_const_iterator
    {
	public:
		typedef Val value_type;
		typedef const Val *pointer;
		typedef const Val &reference;
		typedef rbtree_const_iterator<Val> self_type;
		typedef ft::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef ft::rbtree_node<Val> node_type;
		typedef typename node_type::const_node_ptr node_ptr;

        // constructeur par defaut
		rbtree_const_iterator()
			: _node(NULL)
		{
		}

		// constructeur d'initialisation
		explicit rbtree_const_iterator(node_ptr x)
			: _node(x)
		{
		}

		// constructeur par copie
		template <typename T>
		rbtree_const_iterator(const rbtree_iterator<T> &rhs) // copy-constructor
			: _node(rhs._node)
		{
		}

		// // constructeur par copie const
		template <typename T>
		rbtree_const_iterator(const rbtree_const_iterator<T> &rhs)
			: _node(rhs._node)
		{
		}

		// destructeur
		virtual ~rbtree_const_iterator()
		{
		}

		// opérateur d'affectation (a = b)
		template <typename T>
		self_type &operator=(const rbtree_const_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// opérateur d'affectation const (a = b)
		template <typename T>
		self_type &operator=(const rbtree_iterator<T> &rhs) // copy-assignment
		{
			_node = rhs._node;
			return *this;
		}

		// operator de dereferencement (*a)
		reference operator*() const
		{
			return _node->data;
		}

		// operateur d'incrementation (a++)
		self_type &operator++()
		{
			_node = _increment(_node);
			return *this;
		}

		// operateur d'incrementation (a+n)
		self_type operator++(int)
		{
			self_type tmp(*this);
			++(*this);
			return tmp;
		}

		// operateur de decrementation (a--)
		self_type &operator--()
		{
			_node = _decrement(_node);
			return *this;
		}

		// operateur de decrementation (a-n)
		self_type operator--(int)
		{
			self_type tmp(*this);
			--(*this);
			return tmp;
		}

		// pointeur vers l'objet
		pointer operator->() const
		{
			return &(_node->data);
		}

		// operateur d'egalite (a == b)
		friend bool operator==(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node == rhs._node);
		}

		// operateur de difference (a != b)
		friend bool operator!=(const self_type &lhs, const self_type &rhs)
		{
			return (lhs._node != rhs._node);
		}

		// Member variables
		node_ptr _node;

		private:
			node_ptr _increment(node_ptr x)
			{
				// Cas 1: si le noeud a un enfant droit, on retourne le noeud le plus à gauche
				if (!node_type::isTNULL(x->right))
				{
					return node_type::minimum(x->right);
				}
				// backup _TNULL
				node_ptr _TNULL = x->right;
				// Cas 2: si le noeud n'a pas d'enfant droit, on remonte jusqu'à ce qu'on trouve un noeud qui est un enfant gauche : 
				while (x->parent)
				{
					if (x->parent->left == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Cas 3: si on a pas trouvé de noeud qui est un enfant gauche, on retourne _TNULL
				return _TNULL;
			}

			node_ptr _decrement(node_ptr x)
			{
				// Cas 0: si le noeud est _TNULL, on retourne le noeud le plus à droite
				if (node_type::isTNULL(x))
				{
					return node_type::maximum(x->parent);
				}
				// Cas 1: si le noeud a un enfant gauche, on retourne le noeud le plus à droite
				if (!node_type::isTNULL(x->left))
				{
					return node_type::maximum(x->left);
				}
				// Cas 2: si le noeud n'a pas d'enfant gauche, on remonte jusqu'à ce qu'on trouve un noeud qui est un enfant droit :
				while (x->parent)
				{
					if (x->parent->right == x)
					{
						return x->parent;
					}
					x = x->parent;
				}
				// Cas 3: si on a pas trouvé de noeud qui est un enfant droit, on retourne _TNULL
				return NULL;
			}
	};

	// operateur d'egalite (a == b)
	template <typename Val>
	bool operator==(const rbtree_iterator<Val> &lhs, const rbtree_const_iterator<Val> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	// operateur de difference (a != b)
	template <typename Val>
	bool operator!=(const rbtree_iterator<Val> &lhs, const rbtree_const_iterator<Val> &rhs)
	{
		return (lhs._node != rhs._node);
	}

	// operateur d'egalite const (a == b)
	template <typename Val>
	bool operator==(const rbtree_const_iterator<Val> &lhs, const rbtree_iterator<Val> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	// operateur de difference (a != b)
	template <typename Val>
	bool operator!=(const rbtree_const_iterator<Val> &lhs, const rbtree_iterator<Val> &rhs)
	{
		return (lhs._node != rhs._node);
	}
} // namespace ft

#endif
