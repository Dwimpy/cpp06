#include "Base.hpp"


Base	*generate() {


    // Generate a random integer between 1 and 3
    int random = (std::rand() % 3) + 1;
	std::cout << random << std::endl;
	switch (random)
	{
		case 1: return (new A);
		case 2: return (new B);
		case 3: return (new C);
		default:
			std::cout << "There was an error" << std::endl;
			return (NULL);
	}
}

void	identify(Base *p) {
	if (dynamic_cast<A *>(p) != NULL)
		std::cout << "Base *p: A" << "\n";
	else if (dynamic_cast<B *>(p) != NULL)
		std::cout << "Base *p: B" << "\n";
	else if (dynamic_cast<C *>(p) != NULL)
		std::cout << "Base *p: C" << "\n";
	else
		std::cout << "Invalid input" << std::endl;
}

void	identify(Base &p) {
	if (dynamic_cast<A *>(&p) != NULL)
		std::cout << "Base &p: A" << "\n";
	else if (dynamic_cast<B *>(&p) != NULL)
		std::cout << "Base &p: B" << "\n";
	else if (dynamic_cast<C *>(&p) != NULL)
		std::cout << "Base &p: C" << "\n";
	else
		std::cout << "Invalid input" << std::endl;
}