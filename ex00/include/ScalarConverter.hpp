#include <string>
#include <iostream>
#include <iomanip>
#include <typeinfo>

template<typename T>
class Literals {

  public:
	Literals(T value): _value(value) {}
	void	setValue(T value) {_value = value;};
	T		getValue() { return ( this->_value );};
	bool	isSuccess() { return ( this->_failed );};
	void	setSuccess(bool val) { this->_failed = val;}

  private:
	T		_value;
	bool	_failed;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, Literals<T> &literal)
{
	if (!literal.isSuccess())
		os << "Impossible";
	else if (typeid(T) == typeid(char))
	{
		if (std::isprint(literal.getValue()))
			os << literal.getValue();
		else if ((literal.getValue() < 32 && literal.getValue() > 0) || literal.getValue() == 127)
			os << "Non Displayable";
	}
	else if (typeid(T) == typeid(int))
		os << literal.getValue();
	else if (typeid(T) == typeid(float))
		os << std::fixed << std::setprecision(1) << literal.getValue() << "f";
	else if (typeid(T) == typeid(double ))
		os << std::fixed << std::setprecision(1) << literal.getValue();
	else
		os << "";
	return (os);
}

typedef enum {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	SPECIAL,
	UNKNOWN,
}	t_ScalarType;

class ScalarConverter {

  public:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter &copy);
	ScalarConverter &operator=(const ScalarConverter &copy);


	static void	convert(const std::string &input);

  private:
	static Literals<int>		_int;
	static Literals<char>		_char;
	static Literals<float>		_float;
	static Literals<double>		_double;
	static t_ScalarType			_scalar_type;

	static bool parseType(const std::string &input);
	static bool checkInt(const std::string &input);
	static bool checkFloat(const std::string &input);
	static bool checkDouble(const std::string &input);
	static bool checkChar(const std::string &input);
	static bool checkSpecial(const std::string &input);
	static void convertFromChar();
	static void convertFromInt();
	static void convertFromFloat();
	static void convertFromDouble();
	static bool isValidChar(char c);
	static void printData();
	static void initialize();

};

