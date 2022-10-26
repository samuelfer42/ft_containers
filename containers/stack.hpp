
#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <cstddef>	 // std::size_t

namespace ft
{
	template<typename T, typename Container = ft::vector<T> > // template generic
	class stack
	{
	public:
		// Member types
		typedef T value_type; 			  // Type de l'element
		typedef Container container_type; // Type du conteneur
		typedef typename std::size_t size_type; // Type de la taille

		// Member functions
		// constructeur par defaut
		explicit stack(const container_type &ctnr = container_type())
			: _cont(ctnr)
		{
		} // initialization du type de conteneur

		// Renvoie si le conteneur est vide
		bool empty() const
		{
			return _cont.empty();
		}

		// Renvoie la taille du conteneur
		size_type size() const
		{
			return _cont.size();
		}

		// Renvoie une référence au dernier élément du conteneur
		value_type& top()
		{
			return _cont.back();
		}

		// Renvoie une référence constante au dernier élément du conteneur
		const value_type& top() const
		{
			return _cont.back();
		}

		// Ajoute un élément au dessus du conteneur
		void push(const value_type &val)
		{
			_cont.push_back(val);
		}

		// Supprime le dernier élément du conteneur
		void pop()
		{
			_cont.pop_back();
		}

		template <typename T1, typename C1>
		// friend sert à acceder aux membres privés de la classe à partir de fonctions non membres
		friend bool operator==(const stack<T1, C1> &x, const stack<T1, C1> &y);
		template <typename T1, typename C1>
		friend bool operator<(const stack<T1, C1> &x, const stack<T1, C1> &y);

	protected:
		container_type _cont;
	};

	// Non-member function overloads
	// Renvoie si les deux conteneurs sont égaux (==)
	template <typename T, typename Container>
	bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return (lhs._cont == rhs._cont);
	}

	// Renvoie si les deux conteneurs sont différents (!=)
	template <typename T, typename Container>
	bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	// Renvoie si le premier conteneur est plus petit que le second (<)
	template <typename T, typename Container>
	bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._cont < rhs._cont;
	}

	// Renvoie si le premier conteneur est plus petit ou égal au second (<=)
	template <typename T, typename Container>
	bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	// Renvoie si le premier conteneur est plus grand que le second (>)
	template <typename T, typename Container>
	bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	// Renvoie si le premier conteneur est plus grand ou égal au second (>=)
	template <typename T, typename Container>
	bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

#endif
