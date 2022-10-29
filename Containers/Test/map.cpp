#include "test.hpp"

void test_map()
{
	std::cout << "**********************************ft::MAP**********************************" << std::endl;
	std::cout << "-----------------------------STL_INSERT-----------------------------" << std::endl;
	{
		std::map<char,int> mymap;
	  std::cout << "Insert dans mymap : (a,100); (z,200)" << '\n';
	  mymap.insert ( std::pair<char,int>('a',100) );
	  mymap.insert ( std::pair<char,int>('z',200) );

	  std::pair<std::map<char,int>::iterator,bool> ret;
	  std::cout << "Insert element existant dans mymap : (z,500)" << '\n';
	  ret = mymap.insert ( std::pair<char,int>('z',500) );
	  if (ret.second==false) {
	    std::cout << "==> l'élément 'z' existe déjà dans mymap avec une valeur de : " << ret.first->second << '\n';
	  }
	    std::map<char,int>::iterator it = mymap.begin();
	    std::cout << "Insert dans mymap :(b,300)" << '\n';
		 mymap.insert (it, std::pair<char,int>('b',300));
	   std::cout << "Insert dans mymap : (c,400)" << '\n';
	  mymap.insert (it, std::pair<char,int>('c',400));  

	  std::cout << "Insert dans anothermap la range (begin, find(c)):" << '\n';
	  std::map<char,int> anothermap;
	  anothermap.insert(mymap.begin(),mymap.find('c'));

	  std::cout << "mymap :\n";
	  for (it=mymap.begin(); it!=mymap.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';
	 std::cout << "anothermap :\n";
	  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "------------------------------FT_INSERT------------------------------" << std::endl;
	{
		ft::map<char,int> mymap;

	  std::cout << "Insert dans mymap : (a,100); (z,200)" << '\n';
	  mymap.insert ( ft::pair<char,int>('a',100) );
	  mymap.insert ( ft::pair<char,int>('z',200) );

	  ft::pair<ft::map<char,int>::iterator,bool> ret;
	  std::cout << "Insert element existant dans mymap : (z,500)" << '\n';
	  ret = mymap.insert ( ft::pair<char,int>('z',500) );
	  if (ret.second==false) {
	    std::cout << "==> l'élément 'z' existe déjà avec une valeur de : " << ret.first->second << '\n';
	  }
	  ft::map<char, int>::iterator it = mymap.begin();
	  std::cout << "Insert dans mymap : (b,300)" << '\n';
	  mymap.insert (it, ft::pair<char,int>('b',300));
	  std::cout << "Insert dans mymap : (c,400)" << '\n';
	  mymap.insert (it, ft::pair<char,int>('c',400));

	  std::cout << "Insert dans anothermap la range (begin, find(c)):" << '\n';
	  ft::map<char,int> anothermap;
	  anothermap.insert(mymap.begin(), mymap.find('c'));


	  std::cout << "mymap :\n";
	  for (it=mymap.begin(); it!=mymap.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';
	 std::cout << "anothermap :\n";
	  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';
	}

	std::cout << "------------------------------STL_OPERATOR[]------------------------------" << std::endl;
	{
		std::map<char,std::string> mymap;
	  std::cout << "mymap[a] = \"Element A\"; mymap[b] = \"Element\" B"<< '\n';
	  mymap['a']="Element A";
	  mymap['b']="Element B";
	  std::cout << "mymap[c] = mymap[b]" << '\n';
	  mymap['c']=mymap['b'];
	  std::cout << "affiche mymap :" << '\n';
	  std::cout << "mymap['a'] ==> " << mymap['a'] << '\n';
	  std::cout << "mymap['b'] ==> " << mymap['b'] << '\n';
	  std::cout << "mymap['c'] ==> " << mymap['c'] << '\n';
	  std::cout << "mymap['d'] ==> " << mymap['d'] << '\n';

	}
	std::cout << "-------------------------------FT_OPERATOR[]-------------------------------" << std::endl;
	{
	  ft::map<char,std::string> mymap;

	  std::cout << "mymap[a] = \"Element A\"; mymap[b] = \"Element\" B"<< '\n';
	  mymap['a']="Element A";
	  mymap['b']="Element B";
	  std::cout << "mymap[c] = mymap[b]" << '\n';
	  mymap['c']=mymap['b'];
	  std::cout << "affiche mymap :" << '\n';
	  std::cout << "mymap['a'] ==> " << mymap['a'] << '\n';
	  std::cout << "mymap['b'] ==> " << mymap['b'] << '\n';
	  std::cout << "mymap['c'] ==> " << mymap['c'] << '\n';
	  std::cout << "mymap['d'] ==> " << mymap['d'] << '\n';

	}

	std::cout << "------------------------------STL_SIZE[]------------------------------" << std::endl;
	{
		  std::map<char,int> mymap;
	   std::cout << "mymap[a] = 101; mymap[b] = 202; mymap[c] = 302"<< '\n';
	  mymap['a']=101;
	  mymap['b']=202;
	  mymap['c']=302;

	  std::cout << "mymap.size() ==> " << mymap.size() << '\n';
	}
	std::cout << "------------------------------MINE_SIZE[]------------------------------" << std::endl;
	{  
		ft::map<char,int> mymap;
	  std::cout << "mymap[a] = 101; mymap[b] = 202; mymap[c] = 302"<< '\n';
	  mymap['a']=101;
	  mymap['b']=202;
	  mymap['c']=302;

	  std::cout << "mymap.size() ==> " << mymap.size() << '\n';
	  }
	std::cout << "-------------------------------STL_EMPTY_ECRASE-------------------------------" << std::endl;
	  {
		   std::map<char,int> mymap;
	  std::cout << "mymap[a] = 10; mymap[b] = 20; mymap[c] = 30"<< '\n';
	  mymap['a']=10;
	  mymap['b']=20;
	  mymap['c']=30;

	  while (!mymap.empty())
	  {
	    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << " ecrase" << '\n';
	    mymap.erase(mymap.begin());
	  }
	  std::cout << "mymap['a'] ==> " << mymap['a'] << '\n';
	  std::cout << "mymap['b'] ==> " << mymap['b'] << '\n';
	  std::cout << "mymap['c'] ==> " << mymap['c'] << '\n';
	  }
	std::cout << "-------------------------------FT_EMPTY_ECRASE-------------------------------" << std::endl;
	  {
		   std::map<char,int> mymap;
	  std::cout << "mymap[a] = 10; mymap[b] = 20; mymap[c] = 30"<< '\n';
	  mymap['a']=10;
	  mymap['b']=20;
	  mymap['c']=30;

	  while (!mymap.empty())
	  {
	    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << " ecrase" << '\n';
	    mymap.erase(mymap.begin());
	  }
	  std::cout << "mymap[a] ==> " << mymap['a'] << '\n';
	  std::cout << "mymap[b] ==> " << mymap['b'] << '\n';
	  std::cout << "mymap[c] ==> " << mymap['c'] << '\n';
	  }
	std::cout << "-------------------------------STL_SWAP-------------------------------" << std::endl;
	 {
		   std::map<char,int> foo,bar;
	  std::cout << "foo[x] = 100; foo[y] = 200"<< '\n';
	  foo['x']=100;
	  foo['y']=200;

	  std::cout << "bar[a] = 11; bar[b] = 22; bar[c] = 33"<< '\n';
	  bar['a']=11;
	  bar['b']=22;
	  bar['c']=33;

	  std::cout << "foo.swap(bar)" << '\n';
	  foo.swap(bar);

	  std::cout << "foo contient:\n";
	  for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';

	  std::cout << "bar contient:\n";
	  for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';

	 }
	std::cout << "--------------------------------FT_SWAP---------------------------------" << std::endl;
	 {
		   ft::map<char,int> foo,bar;
	  std::cout << "foo[x] = 100; foo[y] = 200"<< '\n';
	  foo['x']=100;
	  foo['y']=200;

	  std::cout << "bar[a] = 11; bar[b] = 22; bar[c] = 33"<< '\n';
	  bar['a']=11;
	  bar['b']=22;
	  bar['c']=33;

	  std::cout << "foo.swap(bar)" << '\n';
	  foo.swap(bar);

	  std::cout << "foo contient:\n";
	  for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';

	  std::cout << "bar contient:\n";
	  for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';

	 }

	std::cout << "-----------------------------------------STL_ERASE_&_FIND-----------------------------------------" << std::endl;
	 {
		   std::map<char,int> mymap;
	  std::map<char,int>::iterator it;

	  std::cout << "mymap[a] = 10; mymap[b] = 20; mymap[c] = 30; mymap[d] = 40; mymap[e] = 50; mymap[f] = 60"<< '\n';
	  mymap['a']=10;
	  mymap['b']=20;
	  mymap['c']=30;
	  mymap['d']=40;
	  mymap['e']=50;
	  mymap['f']=60;
	  std::cout << "==> mymap.erase(mymap.find('b')" << '\n';
	  it=mymap.find('b');
	  mymap.erase (it);                   
	  std::cout << "==> mymap.erase('c')" << '\n';
	  mymap.erase ('c');

	  it=mymap.find ('e');
	  mymap.erase ( it, mymap.end() );

	  std::cout << "mymap contient:\n";
	  for (it=mymap.begin(); it!=mymap.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';

	 }
	std::cout << "----------------------------------------FT_ERASE_&_FIND-----------------------------------------" << std::endl;
	{  ft::map<char,int> mymap;
	  ft::map<char,int>::iterator it;

	  std::cout << "mymap[a] = 10; mymap[b] = 20; mymap[c] = 30; mymap[d] = 40; mymap[e] = 50; mymap[f] = 60"<< '\n';
	  mymap['a']=10;
	  mymap['b']=20;
	  mymap['c']=30;
	  mymap['d']=40;
	  mymap['e']=50;
	  mymap['f']=60;
	  std::cout << "==> mymap.erase(mymap.find('b')" << '\n';
	  it=mymap.find('b');
	  mymap.erase (it);                   
	  std::cout << "==> mymap.erase('c')" << '\n';
	  mymap.erase ('c');

	  it=mymap.find ('e');
	  mymap.erase ( it, mymap.end() );

	  std::cout << "mymap contient:\n";
	  for (it=mymap.begin(); it!=mymap.end(); ++it)
	    std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "-----------------------------------------STL_COUNT-----------------------------------------" << std::endl;
	{
	    std::map<char,int> mymap;
	 std::map<char,int>::iterator it;
	 std::cout << "mymap[a] = 50; mymap[c] = 150 ; mymap[d] = 200"<< '\n';
	 mymap['a']=50;
	 mymap['c']=150;
	 mymap['d']=200;
	 for (char c='a'; c<'e'; c++)
	 {
	   std::cout << c;
	   if (mymap.count(c)>0)
	     std::cout << " est un element de mymap" << '\n';
	   else
	     std::cout << " n'est pas un element de mymap" << '\n';
	 }
	}
	std::cout << "----------------------------------------FT_COUNT-----------------------------------------" << std::endl;
	{
	    ft::map<char,int> mymap;
	 ft::map<char,int>::iterator it;
	 std::cout << "mymap[a] = 50; mymap[c] = 150 ; mymap[d] = 200"<< '\n';
	 mymap['a']=50;
	 mymap['c']=150;
	 mymap['d']=200;
	 for (char c='a'; c<'e'; c++)
	 {
	   std::cout << c;
	   if (mymap.count(c)>0)
	     std::cout << " est un element de mymap" << '\n';
	   else
	     std::cout << " n'est pas un element de mymap" << '\n';
	 }
	}
	std::cout << "-----------------------------------------STL_LOWER_BOUND_MAKE_PAIR-----------------------------------------" << std::endl;
	{
	    std::map<char,int> mymap;
	 std::map<char,int>::iterator itlow,itup;
	 std::cout << "mymap[a] = 20; mymap[b] = 40; mymap[c] = 60; mymap[d] = 80; mymap[e] = 100"<< '\n';
	 mymap['a']=20;
	 mymap['b']=40;
	 mymap['c']=60;
	 mymap['d']=80;
	 mymap['e']=100;
	 itlow=mymap.lower_bound ('b');  
	 itup=mymap.upper_bound ('d');   
	 std::cout << "==> mymap.erase(mymap.lower_bound('b'), mymap.upper_bound('d'))" << '\n';
	 std::cout << "mymap contient maintenant :\n";
	 mymap.erase(itlow,itup);       
	 for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
	   std::cout << it->first << " => " << it->second << '\n';
	}
	std::cout << "----------------------------------------FT_LOWER_BOUND_MAKE_PAIR-----------------------------------------" << std::endl;
	{
	    ft::map<char,int> mymap;
	 ft::map<char,int>::iterator itlow,itup;
	 std::cout << "mymap[a] = 20; mymap[b] = 40; mymap[c] = 60; mymap[d] = 80; mymap[e] = 100"<< '\n';
	 mymap['a']=20;
	 mymap['b']=40;
	 mymap['c']=60;
	 mymap['d']=80;
	 mymap['e']=100;
	 itlow=mymap.lower_bound ('b');  
	 itup=mymap.upper_bound ('d');   
	 std::cout << "==> mymap.erase(mymap.lower_bound('b'), mymap.upper_bound('d'))" << '\n';
	 std::cout << "mymap contient maintenant :\n";
	 mymap.erase(itlow,itup);        
	 for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
	   std::cout << it->first << " => " << it->second << '\n';
	}
}
