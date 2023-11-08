#include "Serializer.hpp"

Serializer::Serializer() {
	std::cout << "Default serializer constructor called" << std::endl;
}

Serializer::~Serializer() {
	std::cout << "Deconstructor called" << std::endl;
}

Serializer::Serializer(const Serializer &cpy)
{
	std::cout << "Copy constructor called" << std::endl;
	if (this != &cpy)
		*this = cpy;
}

Serializer &Serializer::operator=(const Serializer &cpy)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &cpy) {
		*this = cpy;
		return (*this);
	}
	return (*this);
}

uintptr_t Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}