#pragma once
#include <string>
#include <iostream>
#include <cstddef>
#include <stdint.h>

struct Data {
	int myInt;
	std::string	myStr;
};

class Serializer {
  private:
  	Serializer();
	~Serializer();
	Serializer(const Serializer &cpy);
	Serializer	&operator=(const Serializer &cpy);

  public:
	static uintptr_t	serialize(Data *ptr);
	static Data			*deserialize(uintptr_t raw);
};