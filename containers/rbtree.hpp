
#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "type_traits.hpp"
# include <functional>  // std::less

namespace ft
{
	enum
	{
		RED,
		BLACK
	};

	template <typename Val>
	struct rbtree_node
	{
		typedef Val value_type; // element
		typedef rbtree_node<value_type> node_type; // noeud de l'arbre
		typedef std::allocator<node_type> node_allocator_type; // allocator de noeud
		typedef node_type *node_ptr; // pointeur vers noeud
		typedef const node_type *const_node_ptr; // pointeur vers noeud constant

		node_ptr parent; // pointeur vers le parent
		node_ptr left; // pointeur vers le fils gauche
		node_ptr right; // pointeur vers le fils droit
		value_type data; // element
		int color; // couleur du noeud

		// Initialisation
		rbtree_node(node_ptr parent, node_ptr left, node_ptr right, value_type data, int color)
			: parent(parent), left(left), right(right), data(data), color(color)
		{
		}

		// si le noeud est une feuille (pas de fils)
		static bool isTNULL(node_ptr x)
		{
			if (x && x->left == NULL)
				return true;
			else
				return false;
		}
		static bool isTNULL(const_node_ptr x)
		{
			if (x && x->left == NULL)
				return true;
			else
				return false;
		}

		// retourne le noeud le plus à gauche
		static node_ptr minimum(node_ptr x)
		{
			while (x && !isTNULL(x->left))
				x = x->left;
			return x;
		}
		static const_node_ptr minimum(const_node_ptr x)
		{
			while (x && !isTNULL(x->left))
				x = x->left;
			return x;
		}

		// retourne le noeud le plus à droite
		static node_ptr maximum(node_ptr x)
		{
			while (x && !isTNULL(x->right))
				x = x->right;
			return x;
		}
		static const_node_ptr maximum(const_node_ptr x)
		{
			while (x && !isTNULL(x->right))
				x = x->right;
			return x;
		}
	};

	template <typename Key, // cle
			  typename Val, // element
			  typename KeyOfValue, // cle de l'element
			  typename Compare = std::less<Key>, // comparaison
			  typename Alloc = std::allocator<Val> // allocator
			  >
	class rbtree
	{
	public:
		// Member types
		typedef Key key_type; // cle
		typedef Val value_type; // element
		typedef Compare key_compare; // comparaison
		typedef std::size_t size_type; // taille
		typedef rbtree_node<value_type> node_type; // noeud de l'arbre
		typedef typename node_type::node_allocator_type node_allocator_type; // allocator de noeud
		typedef typename node_type::node_ptr node_ptr; // pointeur vers noeud
		typedef typename node_type::const_node_ptr const_node_ptr; // pointeur vers noeud constant

		// Member functions
		rbtree()
			: _size(0)
		{
			_TNULL = _getnode(node_type(NULL, NULL, NULL, value_type(), BLACK));
			_root = _TNULL;
		} // constructeur par defaut

		const node_ptr &getRoot() const
		{
			return _root;
		} // retourne la racine de l'arbre

		const node_ptr &getTNULL() const
		{
			return _TNULL;
		} // retourne le TNULL

		bool equal(const key_type &a, const key_type &b) const
		{
			return !_comp(a, b) && !_comp(b, a);
		} // retourne true si a == b

		// retourne le noeud contenant la cle key
		node_ptr searchKey(key_type key) const
		{
			node_ptr t = _root;

			if (_root->color == RED)
			{
				return NULL;
			}
			while (t != _TNULL && !equal(key, KeyOfValue()(t->data)))
			{
				if (_comp(key, KeyOfValue()(t->data)))
				{
					t = t->left;
				}
				else
				{
					t = t->right;
				}
			}
			if (t == _TNULL)
			{
				return NULL;
			}
			return t;
		}

		// insere un element dans l'arbre
		node_ptr rbInsert(const value_type &data)
		{
			node_ptr ret;
			if (_size == 0)
			{
				_root = _getnode(node_type(NULL, _TNULL, _TNULL, data, BLACK));
				ret = _root;
			}
			else
			{
				ret = _insertNode(data);
			}
			++_size;
			_TNULL->parent = _root;
			return ret;
		}

		// supprime un element de l'arbre
		void rbDelete(const node_ptr &z)
		{
			--_size;
			_deleteNode(z);
			_TNULL->parent = _root;
		}

		// swap
		void swap(rbtree &x)
		{
			ft::swap(_size, x._size);
			ft::swap(_root, x._root);
			ft::swap(_TNULL, x._TNULL);
			ft::swap(_comp, x._comp);
			ft::swap(_node_alloc, x._node_alloc);
		}

		size_type size() const
		{
			return _size;
		} // retourne la taille de l'arbre

		size_type max_size() const
		{
			return (_node_alloc.max_size() < PTRDIFF_MAX) ? _node_alloc.max_size() : PTRDIFF_MAX;
		} // retourne la taille maximale de l'arbre

	private:
		// Private member functions
		node_ptr _getnode(node_type tmp)
		{
			node_ptr ptr = _node_alloc.allocate(1);
			_node_alloc.construct(ptr, tmp);
			return ptr;
		} // alloue un noeud

		 // rotation a gauche
		void _leftRotate(node_ptr x)
		{
			node_ptr y = x->right;
			x->right = y->left;
			if (y->left != _TNULL)
			{
				y->left->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				_root = y;
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
			y->left = x;
			x->parent = y;
		}

		// rotation a droite
		void _rightRotate(node_ptr x)
		{
			node_ptr y = x->left;
			x->left = y->right;
			if (y->right != _TNULL)
			{
				y->right->parent = x;
			}
			y->parent = x->parent;
			if (x->parent == NULL)
			{
				_root = y;
			}
			else if (x == x->parent->right)
			{
				x->parent->right = y;
			}
			else
			{
				x->parent->left = y;
			}
			y->right = x;
			x->parent = y;
		}

		// insere un noeud dans l'arbre
		node_ptr _insertNode(const value_type &data)
		{
			node_ptr z = _getnode(node_type(NULL, _TNULL, _TNULL, data, RED));
			node_ptr y = NULL;
			node_ptr x = _root;

			while (x != _TNULL)
			{
				y = x;
				if (_comp(KeyOfValue()(z->data), KeyOfValue()(x->data))) // data < x->data
				{
					x = x->left;
				}
				else
				{
					x = x->right;
				}
			}

			z->parent = y;

			if (y == NULL)
			{
				_root = z;
			}
			else if (_comp(KeyOfValue()(z->data), KeyOfValue()(y->data)))
			{
				y->left = z;
			}
			else
			{
				y->right = z;
			}

			// si Z est la racine, on le colore en noir
			if (z == _root)
			{
				z->color = BLACK;
				return z;
			}

			// si le parent de Z est la racine, on ne fait rien
			if (z->parent == _root)
			{
				return z;
			}

			_insertFix(z);
			return z;
		}

		// fixe l'arbre apres l'insertion
		void _insertFix(node_ptr k)
		{
			while (k != _root && k->parent->color == RED)
			{
				// si le parent de k est le fils gauche du grand-parent de k
				bool side = (k->parent == k->parent->parent->left);
				// set oncle node
				node_ptr u = side ? k->parent->parent->right : k->parent->parent->left;

				if (u->color == RED)
				{
					// si l'oncle de k est rouge -> recoloration en noir
					k->parent->color = BLACK;
					u->color = BLACK;
					k->parent->parent->color = RED;
					k = k->parent->parent;
				}
				else
				{
					// si l'oncle n'existe pas ou est noir -> rotation
					if (k == (side ? k->parent->right : k->parent->left))
					{
						k = k->parent;
						side ? _leftRotate(k) : _rightRotate(k);
					}
					k->parent->color = BLACK;
					k->parent->parent->color = RED;
					side ? _rightRotate(k->parent->parent) : _leftRotate(k->parent->parent);
				}
			}
			_root->color = BLACK;
		}

		// remplace un noeud par un autre
		void _rbTransplant(node_ptr u, node_ptr v)
		{
			if (u->parent == NULL)
			{
				_root = v;
			}
			else if (u == u->parent->left)
			{
				u->parent->left = v;
			}
			else
			{
				u->parent->right = v;
			}
			v->parent = u->parent;
		}

		// supprime un noeud de l'arbre
		bool _deleteNode(const node_ptr &z)
		{
			node_ptr x, y;
			y = z;
			int y_original_color = y->color;
			if (z->left == _TNULL)
			{
				x = z->right;
				_rbTransplant(z, z->right);
			}
			else if (z->right == _TNULL)
			{
				x = z->left;
				_rbTransplant(z, z->left);
			}
			else
			{
				y = node_type::minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
				{
					x->parent = y;
				}
				else
				{
					_rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			_node_alloc.destroy(z);
			_node_alloc.deallocate(z, 1);
			if (y_original_color == BLACK)
			{
				_deleteFix(x);
			}
			return true;
		}

		// fixe l'arbre apres la suppression
		void _deleteFix(node_ptr x)
		{
			while (x != _root && x->color == BLACK)
			{
				// si x est le fils gauche du parent de x
				bool side = (x == x->parent->left);
				// set noeud frere
				node_ptr s = side ? x->parent->right : x->parent->left;

				// cas 1: le frere de x est rouge
				if (s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					side ? _leftRotate(x->parent) : _rightRotate(x->parent);
					s = side ? x->parent->right : x->parent->left;
				}
				// cas 2: le frere de x est noirs
				if (s->left->color == BLACK && s->right->color == BLACK)
				{
					s->color = RED;
					x = x->parent;
				}
				else
				{
					// cas 3: le frere de x est noir et son fils gauche est rouge
					if ((side ? s->right->color : s->left->color) == BLACK)
					{
						(side ? s->left->color : s->right->color) = BLACK;
						s->color = RED;
						side ? _rightRotate(s) : _leftRotate(s);
						s = side ? x->parent->right : x->parent->left;
					}
					// cas 4: le frere de x est noir et son fils droit est rouge
					s->color = x->parent->color;
					x->parent->color = BLACK;
					(side ? s->right->color : s->left->color) = BLACK;
					side ? _leftRotate(x->parent) : _rightRotate(x->parent);
					x = _root;
				}
			}
			x->color = BLACK;
			_root->color = BLACK;
		}

		// Member variables
		size_type _size; // nombre de noeuds
		node_ptr _root; // racine de l'arbre
		node_ptr _TNULL; // noeud NULL (feuille)
		key_compare _comp; // comparateur de cle
		node_allocator_type _node_alloc; // allocateur de noeud
	};
} // namespace ft

#endif
