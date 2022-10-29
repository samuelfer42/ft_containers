#include "test.hpp"

void test_stack()
{
	std::cout << "**********************************ft::STACK**********************************" << std::endl;
  std::cout << "-------------------------------STD-------------------------------"<< std::endl;
  {
    std::vector<int> myvector (2,200);        // vecteur avec 2 éléments

    std::stack<int> first;                    // stack vide

    std::stack<int,std::vector<int> > third;  // stack vide utilisant un vecteur comme conteneur
    std::stack<int,std::vector<int> > fourth (myvector);

    std::cout << "taille de stack vide: " << first.size() << '\n';
    std::cout << "taille de stack vide utilisant un vecteur comme conteneur: " << third.size() << '\n';
    std::cout << "taille du vecteur (2,200): " << fourth.size() << '\n';
  }
  std::cout << "--------------------------------FT--------------------------------" << std::endl;
  {
  	  ft::vector<int> myvector (2,200);        // vecteur avec 2 éléments
    ft::stack<int> first;                    // stack vide
    ft::stack<int,ft::vector<int> > third;  // stack vide utilisant un vecteur comme conteneur
    ft::stack<int,ft::vector<int> > fourth (myvector);
    std::cout << "taille de stack vide: " << first.size() << '\n';
    std::cout << "taille de stack vide utilisant un vecteur comme conteneur: " << third.size() << '\n';
    std::cout << "taille du vecteur (2,200): " << fourth.size() << '\n';
  }
  std::cout << std::endl;
  std::cout << "-----------------------------STL_SIZE-----------------------------" << std::endl;
  {
  	  std::stack<int> myints;
    std::cout << "taille 0: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(i);
    std::cout << "taille 5: " << myints.size() << '\n';

    myints.pop();
    std::cout << "pop (retire 1 element) :" << myints.size() << '\n';

  }

  std::cout << "-----------------------------FT_SIZE-----------------------------" << std::endl;
  {
  	  ft::stack<int> myints;
    std::cout << "taille 0: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(i);
    std::cout << "taille 5: " << myints.size() << '\n';

    myints.pop();
    std::cout << "pop (retire 1 element) :" << myints.size() << '\n';

  }
  std::cout << std::endl;
  std::cout << "-----------------------------STL_EMPTY-----------------------------" << std::endl;
  {
  	 std::stack<int> mystack;
    int sum (0);

     std::cout << "Push (1,2,3,4,5,6,7,8,9,10)" << '\n';
    for (int i=1;i<=10;i++) mystack.push(i);

    std::cout << "Parcours en ajoute a mon compteur et supprime chaque elements" << '\n';
    while (!mystack.empty())
    {
      std::cout << "+= " << mystack.top() << " & pop " << '\n';
       sum += mystack.top();
       mystack.pop();
    }
    std::cout << "total = " << sum << '\n';
    std::cout << "taille = " << mystack.size() << '\n';

  }
  std::cout << "-----------------------------FT_EMPTY-----------------------------" << std::endl;
  {
  	ft::stack<int> mystack;
    int sum (0);

    for (int i=1;i<=10;i++) mystack.push(i);

    std::cout << "Push (1,2,3,4,5,6,7,8,9,10)" << '\n';
    std::cout << "Parcours en ajoute a mon total et supprime chaque elements" << '\n';
    while (!mystack.empty())
    {
      std::cout << "+= " << mystack.top() << " & pop " << '\n';
       sum += mystack.top();
       mystack.pop();
    }
    std::cout << "total = " << sum << '\n';
    std::cout << "taille = " << mystack.size() << '\n';

  }
  std::cout << std::endl;
  std::cout << "-----------------------------STL_TOP-----------------------------" << std::endl;
  {
  	ft::stack<int> mystack;
    std::cout << "Push (10)" << '\n';
    mystack.push(10);
    std::cout << "Push (20)" << '\n';
    mystack.push(20);
    std::cout << "top -= 5" << '\n';
    mystack.top() -= 5;

    std::cout << "mystack.top() = " << mystack.top() << '\n';

  }
  std::cout << "-----------------------------FT_TOP-----------------------------" << std::endl;
  { ft::stack<int> mystack;
    std::cout << "Push (10)" << '\n';
    mystack.push(10);
    std::cout << "Push (20)" << '\n';
    mystack.push(20);
    std::cout << "top -= 5" << '\n';
    mystack.top() -= 5;

    std::cout << "mystack.top() = " << mystack.top() << '\n';
  }
  std::cout << std::endl;
  std::cout << "-----------------------------STL_PUSH_&_POP-----------------------------" << std::endl;
  {
  	  std::stack<int> mystack;

    std::cout << "Push (0, 1, 2, 3, 4)" << '\n';
    for (int i=0; i<5; ++i) mystack.push(i);

    std::cout << "Pop elements...";
    while (!mystack.empty())
    {
       std::cout << ' ' << mystack.top();
       mystack.pop();
    }
    std::cout << '\n';

  }
  std::cout << "-----------------------------FT_PUSH_&_POP-----------------------------" << std::endl;
  {
  	  ft::stack<int> mystack;
    std::cout << "Push (0, 1, 2, 3, 4)" << '\n';
    for (int i=0; i<5; ++i) mystack.push(i);

    std::cout << "Pop elements...";
    while (!mystack.empty())
    {
       std::cout << ' ' << mystack.top();
       mystack.pop();
    }
    std::cout << '\n';

  }
}