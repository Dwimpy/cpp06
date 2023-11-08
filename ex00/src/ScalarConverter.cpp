#include "ScalarConverter.hpp"
#include <iomanip>
#include <cfloat>

Literals<char> ScalarConverter::_char = 0;
Literals<int> ScalarConverter::_int = 0;
Literals<float> ScalarConverter::_float = 0.0f;
Literals<double> ScalarConverter::_double = 0.0;
std::string	ScalarConverter::_special = "";

t_ScalarType ScalarConverter::_scalar_type = UNKNOWN;

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &copy) {
	*this = copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy)
{
	(void)copy;
	return (*this);
}

void ScalarConverter::reset() {
	_char = 0;
	_int = 0;
	_float = 0.0f;
	_double = 0.0;
	_scalar_type = UNKNOWN;
	_special = "";
}

void ScalarConverter::convert(const std::string &input)
{
	initialize();
	if (parseType(input)) {
		switch(_scalar_type) {
			case CHAR:	convertFromChar();
				break ;
			case INT:	convertFromInt();
				break ;
			case FLOAT:	convertFromFloat();
				break ;
			case DOUBLE: convertFromDouble();
				break ;
			case SPECIAL:
				break ;
			case UNKNOWN: std::cout << "Invalid input" << std::endl;
				break ;
		}
	}
	printData();
	reset();
}

void	ScalarConverter::printData()
{
	if (_scalar_type != UNKNOWN && _scalar_type != SPECIAL)
	{
		std::cout << std::setw(18) << std::right << "Conversion: \n";
		std::cout << std::setw(25) << std::setfill('-') << "\n" << std::setfill(' ');
		std::cout << std::setw(10) << "Char: " << _char << "\n";
		std::cout << std::setw(10) << "Int: " << _int << "\n";
		std::cout << std::setw(10) << "Float: " << _float << "\n";
		std::cout << std::setw(10) << "Double: " << _double << "\n";
		std::cout << std::setw(25) << std::setfill('-') << "\n";
	}
	else if (_scalar_type == SPECIAL) {
		printSpecial();
	}
}

bool ScalarConverter::parseType(const std::string &input)
{
	_scalar_type = UNKNOWN;
	if (checkSpecial(input)) {
		_scalar_type = SPECIAL;
	}
	else if (checkChar(input)) {
		_scalar_type = CHAR;
		convertFromChar();
	}
	else if (checkInt(input)) {
		_scalar_type = INT;

	}
	else if (checkFloat(input)) {
		_scalar_type = FLOAT;
	}
	else if (checkDouble(input)) {
		_scalar_type = DOUBLE;
	}
	return (_scalar_type != UNKNOWN);
}

void ScalarConverter::convertFromChar()
{
	_int.setValue(static_cast<int>(_char.getValue()));
	_float.setValue(static_cast<float>(_char.getValue()));
	_double.setValue(static_cast<double >(_char.getValue()));
	_int.setSuccess(true);
	_float.setSuccess(true);
	_double.setSuccess(true);

}

void ScalarConverter::convertFromInt()
{
	if (isValidChar(_int.getValue()))
	{
		_char.setValue(static_cast<char>(_int.getValue()));
		_char.setSuccess(true);
	}
	_float.setValue(static_cast<float>(_int.getValue()));
	_double.setValue(static_cast<double >(_int.getValue()));
	_float.setSuccess(true);
	_double.setSuccess(true);
}

bool	ScalarConverter::isValidChar(char c)
{
	return (std::isprint(c) || (c < 32 && c > 0) || c == 127);
}

void ScalarConverter::convertFromFloat()
{
	if (isValidChar(_float.getValue()))
	{
		_char.setValue(static_cast<char>(_float.getValue()));
		_char.setSuccess(true);
	}
	if (_float.getValue() >= -2147483648.0 && _float.getValue() <= 2147483647.0)
	{
		_int.setValue(static_cast<int>(_float.getValue()));
		_int.setSuccess(true);
	}
	_double.setValue(_float.getValue());
	_double.setSuccess(true);
}

void ScalarConverter::convertFromDouble()
{
	if (isValidChar(_double.getValue()))
	{
		_char.setValue(static_cast<char>(_double.getValue()));
		_char.setSuccess(true);
	}
	if (_double.getValue() >= -2147483648.0 && _double.getValue() <= 2147483647.0)
	{
		_int.setValue(static_cast<int>(_double.getValue()));
		_int.setSuccess(true);
	}
	if (_double.getValue() >= FLT_MIN && _double.getValue() <= FLT_MAX)
	{
		_float.setValue(static_cast<float>(_double.getValue()));
		_float.setSuccess(true);
	}
}

bool ScalarConverter::checkChar(const std::string &input)
{
	if (input.size() == 1 &&
		input.at(0) > std::numeric_limits<char>::min() &&
		input.at(0) < std::numeric_limits<char>::max() &&
		!std::isdigit(input.at(0))) {
		_char.setValue(input.at(0));
		_char.setSuccess(true);
		std::cout << "Input: " << input.at(0) << "\n"
		  << std::setw(12) << std::right
		  << "Type: Char\n";
		_char.setSuccess(true);
		return (true);
	}
	return (false);
}

bool ScalarConverter::checkInt(const std::string &input)
{
	for (size_t i = 0; i < input.size(); ++i) {
		if (!std::isdigit(input[i]))
			return (false);
	}
	_int = std::strtol(input.c_str(), NULL, 10);
	std::cout << "Input: " << input << "\n"
			  << std::setw(12) << std::right
			  << "Type: Int\n";
	_int.setSuccess(true);
	return (true);
}

bool ScalarConverter::checkFloat(const std::string &input)
{
	size_t	idx;
	std::string	beforeDot;
	std::string afterDot;

	idx = input.find('.');
	if (idx != std::string::npos) {
		beforeDot = input.substr(0, idx);
		afterDot = input.substr(idx + 1, input.size() - 1);
	}
	else
		return (false);

	for (size_t i = 0; i < beforeDot.size(); ++i) {
		if (!std::isdigit(beforeDot[i]))
			return (false);
	}
	for (size_t i = 0; i < afterDot.size() - 1; ++i) {
		if (!std::isdigit(afterDot[i]))
			return (false);
	}

	if (afterDot[afterDot.length() - 1] != 'f')
		return (false);
	_float.setValue(std::strtof(input.c_str(), NULL));
	std::cout << "Input: " << input << "\n"
			  << std::setw(12) << std::right
			  << "Type: Float\n";
	_float.setSuccess(true);
	return (true);
}

bool ScalarConverter::checkDouble(const std::string &input)
{
	size_t	idx;
	std::string	beforeDot;
	std::string afterDot;

	idx = input.find('.');
	if (idx != std::string::npos) {
		beforeDot = input.substr(0, idx);
		afterDot = input.substr(idx + 1, input.size() - 1);

	}
	else
		return (false);

	for (size_t i = 0; i < beforeDot.size(); ++i) {
		if (!std::isdigit(beforeDot[i]))
			return (false);
	}
	for (size_t i = 0; i < afterDot.size(); ++i) {
		if (!std::isdigit(afterDot[i]))
			return (false);
	}
	_double.setValue(std::strtod(input.c_str(), NULL));
	std::cout << "Input: " << input << "\n"
			  << std::setw(12) << std::right
			  << "Type: Double\n";
	_double.setSuccess(true);
	return (true);
}



bool ScalarConverter::checkSpecial(const std::string &input) {
	std::string specials[8] = {"-inf", "+inf", "inf", "nan", "-inff", "+inff", "nanf", "inff"};
	for (ssize_t i = 0; i < 8; ++i) {
		if (input == specials[i])
		{
			_special = specials[i];
			return (true);
		}
	}
	return (false);
}

void ScalarConverter::printSpecial() {
	std::cout << std::setw(18) << std::right << "Conversion: \n";
	std::cout << std::setw(25) << std::setfill('-') << "\n" << std::setfill(' ');
	std::cout << std::setw(10) << "   Char: impossible" << "\n";
	std::cout << std::setw(10) << "   Int: impossible" << "\n";
	if (_special == "-inf" || _special == "+inf" || _special == "inf" || _special == "nan") {
		std::cout << std::setw(10) << "Float: " << _special + "f" << "\n";
		std::cout << std::setw(10) << "Double: " << _special << "\n";
	}
	else if (_special == "-inff" || _special == "+inff" || _special == "inff" || _special == "nanf") {
		std::cout << std::setw(10) << "Float: " << _special << "\n";
		std::cout << std::setw(10) << "Double: " << _special.substr(0, _special.length() - 1) << "\n";
	}
	std::cout << std::setw(25) << std::setfill('-') << "\n";
}


void	ScalarConverter::initialize() {
	_char.setSuccess(false);
	_int.setSuccess(false);
	_float.setSuccess(false);
	_double.setSuccess(false);
}
