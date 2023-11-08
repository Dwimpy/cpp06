#include <cstdlib>
#include <iostream>
#include <ctime>
#include <unistd.h> // for getpid

class Base {
  public:
	virtual ~Base() {};
};

class A: public Base {};
class B: public Base {};
class C: public Base {};

Base	*generate();
void	identify(Base *p);
void	identify(Base &p);