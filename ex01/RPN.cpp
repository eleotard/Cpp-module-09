#include "RPN.hpp"

RPN::RPN() {

}

///////////////////////////////////////////////////////////////////
RPN::RPN(std::string const& input) {
	_input = input;
}

RPN::~RPN() {

}

RPN::RPN(RPN const& src) {
	_input = src._input;
	_st = src._st;
	_op = src._op;
}

RPN &RPN::operator=(RPN const& src) {
	_input = src._input;
	_st = src._st;
	_op = src._op;
	return (*this);
}


//GET//SET///////////////////////////////////////////////////////
void	RPN::setStack(std::stack<int> const& st) {
	_st = st;
}
std::stack<int> RPN::getStack(void) const {
	return (_st);
}
void	RPN::setOp(std::string const& op) {
	_op = op;
}
std::string RPN::getOp(void) const {
	return (_op);
}
void	RPN::setInput(std::string const& input) {
	_input = input;
}
std::string RPN::getInput(void) const {
	return (_input);
}

/////////////////////////////////////////////////////////////////
void	RPN::checkInputFormat() {
	size_t	i = 0;
	
	while (_input[i] && _input[i] != '+' && _input[i] != '-'
		&& _input[i] != '*' && _input[i] != '/')
		i++;
	std::string tmp(_input, i, _input.size() - i);
	//std::cout << GREEN << "tmp = " << "[" << tmp << "]" << DEFAULT <<  std::endl;
	i = 0;
	while (tmp[i]) {
		if (tmp[i] != '+' && tmp[i] != '-' && tmp[i] != '*' 
			&& tmp[i] != '/' && tmp[i] != ' ')
			throw (RPN::WrongFormat());
		i++;
	}
}
