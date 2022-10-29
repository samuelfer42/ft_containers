#include "test.hpp"

void test_vector()
{
	std::cout << "**********************************ft::VECTOR**********************************" << std::endl;
	std::cout << "-----------------------------STL_CONSTRUCTORS-----------------------------" << std::endl;
	{
    std::cout << "ajoute 16,2,77,29 dans le premier vecteur" << std::endl;
    std::cout << "ajoute 4 elements de valeur 100 dans le deuxieme vecteur" << std::endl;
	  std::vector<int> premier (4,100);
	  std::vector<int> deuxieme (premier.begin(),premier.end());
    std::cout << "creer un troisieme vecteur avec le deuxieme vecteur" << std::endl;
	  std::vector<int> troisieme (deuxieme);
	
	  int myints[] = {16,2,77,29};

	  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	  std::cout << "Le contenu du premier est :";
	  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	    std::cout << "Le contenu du second est :";
	  for (std::vector<int>::iterator it = deuxieme.begin(); it != deuxieme.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	      std::cout << "Le contenu du troisieme est :";
	  for (std::vector<int>::iterator it = troisieme.begin(); it != troisieme.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	}
	std::cout << "------------------------------FT_CONSTRUCTORS-------------------------------" << std::endl;
	{
		std::cout << "ajoute 4 elements de valeur 100" << std::endl;
	  ft::vector<int> premier (4,100);
	  ft::vector<int> deuxieme (premier.begin(),premier.end());
      std::cout << "creer un troisieme vecteur avec le deuxieme vecteur" << std::endl;
	  ft::vector<int> troisieme (deuxieme);
     std::cout << "ajoute 16,2,77,29 dans le premier vecteur" << std::endl;
	  int myints[] = {16,2,77,29};

	  ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	  std::cout << "Le contenu du premier est :";
	  for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	      std::cout << "Le contenu du second est :";
	  for (ft::vector<int>::iterator it = deuxieme.begin(); it != deuxieme.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	       std::cout << "Le contenu du troisieme est :";
	    for (ft::vector<int>::iterator it = troisieme.begin(); it != troisieme.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	}
  std::cout << '\n';
	std::cout << "------------------------------STL_OPERATOR==--------------------------------" << std::endl;
	{
		std::vector<int> foo (3,0);
	  std::vector<int> bar (5,0);
	  bar = foo;
	  foo = std::vector<int>();

	  std::cout << "Taille de foo: " << int(foo.size()) << '\n';
	  std::cout << "Taille de bar: " << int(bar.size()) << '\n';
	}
	std::cout << "--------------------------------FT_OPERATOR==--------------------------------" << std::endl;
	{
		std::vector<int> foo (3,0);
	  std::vector<int> bar (5,0);
	  bar = foo;
	  foo = std::vector<int>();

	  std::cout << "Taille de foo: " << int(foo.size()) << '\n';
	  std::cout << "Taille de bar: " << int(bar.size()) << '\n';
	}
  std::cout << '\n';
	std::cout << "--------------------------------STL_SIZE--------------------------------" << std::endl;
	{
		  std::vector<int> myints;
	  std::cout << "Vide; taille =  " << myints.size() << '\n';

	  for (int i=0; i<10; i++) myints.push_back(i);
	  std::cout << "push_back 10; taille = " << myints.size() << '\n';

	  myints.insert (myints.end(),10,100);
	  std::cout << "insert 10; taille = " << myints.size() << '\n';

	  myints.pop_back();
	  std::cout << "Pop_back; taille = " << myints.size() << '\n';

	}
	std::cout << "--------------------------------FT_SIZE---------------------------------" << std::endl;
	{  ft::vector<int> myints;
	  std::cout << "Vide; taille =  " << myints.size() << '\n';

	  for (int i=0; i<10; i++) myints.push_back(i);
	  std::cout << "push_back 10; taille = " << myints.size() << '\n';

	  myints.insert (myints.end(),10,100);
	  std::cout << "insert 10; taille = " << myints.size() << '\n';

	  myints.pop_back();
	  std::cout << "Pop_back; taille = " << myints.size() << '\n';
	}

  std::cout << '\n';
	std::cout << "--------------------------------STL_PUSH__BACK---------------------------------" << std::endl;
	{
	  std::vector<int> myvector;
    std::cout << " ajout de 24 elements de 19 a 42" << std::endl;
	  for (int i = 19; i <= 42; i++)
	    myvector.push_back(i);

	  std::cout << "myvector à " << int(myvector.size()) << " elements.\n";
		std::cout << "vector contient:";
		for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end() ; it++)
			std::cout << " " << *it;
		std::cout << std::endl;
	}
	std::cout << "---------------------------------FT_PUSH__BACK----------------------------------" << std::endl;
	{
	  ft::vector<int> myvector;
    std::cout << " ajout de 24 elements de 19 a 42" << std::endl;
	  for (int i = 19; i <= 42; i++)
	    myvector.push_back (i);

	  std::cout << "myvector à " << int(myvector.size()) << " elements.\n";
		std::cout << "vector contient:";
		for (ft::vector<int>::iterator it=myvector.begin(); it != myvector.end() ; it++)
			std::cout << " " << *it;
		std::cout << std::endl;
	}
  std::cout << '\n';
	std::cout << "---------------------------------STL_RESIZE----------------------------------" << std::endl;
	{
		 std::vector<int> myvector;
     std::cout << "ajoute 10 elements de 1 a 10" << std::endl;
	  for (int i=1;i<10;i++) myvector.push_back(i);
    std::cout << "resize 5" << std::endl;
	  myvector.resize(5);
    std::cout << "resize a 8 en ajoutant 100" << std::endl;
	  myvector.resize(8,100);
    std::cout << "resize 12" << std::endl;
	  myvector.resize(12);

	  std::cout << "myvector contient:";
	  for (size_t i=0;i<myvector.size();i++)
	    std::cout << ' ' << myvector[i];
	  std::cout << '\n';

	}
	std::cout << "----------------------------------FT_RESIZE-----------------------------------" << std::endl;
	{ 
		ft::vector<int> myvector;
    std::cout << "ajoute 10 elements de 1 a 10" << std::endl;
	  for (int i=1;i<10;i++) myvector.push_back(i);
    std::cout << "resize 5" << std::endl;
	  myvector.resize(5);
    std::cout << "resize a 8 en ajoutant 100" << std::endl;
	  myvector.resize(8,100);
    std::cout << "resize 12" << std::endl;
	  myvector.resize(12);

	  std::cout << "myvector contient:";
	  for (size_t i=0;i<myvector.size();i++)
	    std::cout << ' ' << myvector[i];
	  std::cout << '\n';
	}	
  std::cout << '\n';	
	std::cout << "----------------------------------STL_FRONT-----------------------------------" << std::endl;
	{
		std::vector<int> myvector;
    std::cout << "Push_back 70 puis 10" << std::endl;
	  myvector.push_back(70);
	  myvector.push_back(10);
	  myvector.front() -= myvector.back();
    std::cout << "front -= back" << std::endl;
	  std::cout << "myvector.front() est " << myvector.front() << '\n';
	}
	std::cout << "----------------------------------FT_FRONT-----------------------------------" << std::endl;
	{
		ft::vector<int> myvector;
	  std::cout << "Push_back 70 puis 10" << std::endl;
	  myvector.push_back(70);
	  myvector.push_back(10);
	  myvector.front() -= myvector.back();
    std::cout << "front -= back" << std::endl;
	  std::cout << "myvector.front() est " << myvector.front() << '\n';
	  std::cout << "myvector.front() is now " << myvector.front() << '\n';
	}
  std::cout << '\n';

	std::cout << "----------------------------------STL_RESERVE-----------------------------------" << std::endl;
	{
	  std::vector<int> foo;
	  foo.reserve(19);
    std::cout << "Modifie la capacity a 19 elements,capacity= ";
	  std::cout << foo.capacity() << std::endl;
	  foo.reserve(42);
    std::cout << "Modifie la capacity a 42 elements,capacity = ";
	  std::cout << foo.capacity() << std::endl;
	}
	std::cout << "-----------------------------------FT_RESERVE------------------------------------" << std::endl;
	{
	  ft::vector<int> foo;
    foo.reserve(19);
    std::cout << "Modifie la capacity a 19 elements,capacity= ";
	  std::cout << foo.capacity() << std::endl;
	  foo.reserve(42);
    std::cout << "Modifie la capacity a 42 elements,capacity = ";
	  std::cout << foo.capacity() << std::endl;
	}
  std::cout << '\n';
	std::cout << "-----------------------------------STL_NMO_REL_OP------------------------------------" << std::endl;
	{
    std::cout << "foo a 3 element de 100" << std::endl;
	  std::vector<int> foo (3,100);  
    std::cout << "bar a 2 element de 200" << std::endl;
	  std::vector<int> bar (2,200);  

	  if (foo==bar) std::cout << "foo et bar sont égaux\n";
	  if (foo!=bar) std::cout << "foo et bar sont different\n";
	  if (foo< bar) std::cout << "foo est inférieur à bar\n";
	  if (foo> bar) std::cout << "foo est plus grand que bar\n";
	  if (foo<=bar) std::cout << "foo est inférieur ou égal à bar\n";
	  if (foo>=bar) std::cout << "foo est supérieur ou égal à bar\n";

	}
	std::cout << "-----------------------------------MINE_NMO_REL_OP------------------------------------" << std::endl;
	{
    std::cout << "foo a 3 element de 100" << std::endl;
		ft::vector<int> foo (3,100);
    std::cout << "bar a 2 element de 200" << std::endl;
	  ft::vector<int> bar (2,200); 
    if (foo==bar) std::cout << "foo et bar sont égaux\n";
	  if (foo!=bar) std::cout << "foo et bar sont different\n";
	  if (foo< bar) std::cout << "foo est inférieur à bar\n";
	  if (foo> bar) std::cout << "foo est plus grand que bar\n";
	  if (foo<=bar) std::cout << "foo est inférieur ou égal à bar\n";
	  if (foo>=bar) std::cout << "foo est supérieur ou égal à bar\n";
	}
  std::cout << '\n';
	std::cout << "-----------------------------------MINE_NMO_SWAP------------------------------------" << std::endl;
	{
    std::cout << "foo a 3 element de 100" << std::endl;
	  std::vector<int> foo (3,100);
    std::cout << "bar a 5 element de 200" << std::endl;
	  std::vector<int> bar (5,200);

	  foo.swap(bar);
    std::cout << "==> swap foo et bar" << std::endl;

	  std::cout << "foo contient:";
	  for (std::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';

	  std::cout << "bar contient:";
	  for (std::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	}
	std::cout << "----------MINE_NMO_SWAP-----------" << std::endl;
	{
    std::cout << "foo a 3 element de 100" << std::endl;
	  ft::vector<int> foo (3,100);
    std::cout << "bar a 5 element de 200" << std::endl;
	  ft::vector<int> bar (5,200);

	  foo.swap(bar);
    std::cout << "==> swap foo et bar" << std::endl;

	  std::cout << "foo contient:";
	  for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';

	  std::cout << "bar contient:";
	  for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	    std::cout << ' ' << *it;
	  std::cout << '\n';
	}
}