#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}
RPN::RPN(RPN const& src) { *this = src; }

RPN &RPN::operator=(RPN const& src) {
	_st = src._st;
	return (*this);
}

void	RPN::printStack() {
	std::stack<int> st = _st;
	while (!st.empty()) {
		std::cout << st.top() << std::endl;
		st.pop();
	}
}

void	RPN::addition() {
	int res = 0;

	res = _st.top();
	_st.pop();
	_st.top() = _st.top() + res;
}

void	RPN::substraction() {
	int	res = 0;

	res = _st.top();
	_st.pop();
	_st.top() = _st.top() - res;
}

void	RPN::multiplication() {
	int res = 0;

	res = _st.top();
	_st.pop();
	_st.top() = _st.top() * res;
}

void	RPN::division() {
	int	res = 0;

	res = _st.top();
	_st.pop();
	_st.top() = _st.top() / res;
}


std::string RPN::calcul(std::string input) {
	std::ostringstream	result;
	size_t	i;
	long int		nb = 0;

	for (i = 0; i < input.size() && input[i]; i++) {
		if (isdigit(input[i]))
			_st.push(input[i] - 48); //std::cout << _st.top() << std::endl;}
		else if (input[i] == '-' && input[i + 1] && isdigit(input[i + 1]))
		{
			i++;
			nb = input[i] - 48;
			i++;
			while (input[i] && isdigit(input[i])) {
				nb = nb * 10 + (input[i] - 48);
				i++;
			}
			nb *=-1;
			if (nb < INT_MIN)
				return ("Error");
			_st.push(nb);
		}
		else if (input[i] == '+' && _st.size() > 1)
			addition();
		else if (input[i] == '-' && _st.size() > 1)
			substraction();
		else if (input[i] == '*' && _st.size() > 1)
			multiplication();
		else if (input[i] == '/' && _st.size() > 1 && _st.top() != 0)
			division();
		else if (input[i] != ' ')
			return ("Error");
	}
	if (_st.size() != 1)
		return ("Error");
	result << _st.top();
	return (result.str());
}















/////////////////////////////////////////////////////////////////
// void	RPN::checkInputFormat() {
// 	size_t	i = 0;
	
// 	while (_input[i] && _input[i] != '+' && _input[i] != '-'
// 		&& _input[i] != '*' && _input[i] != '/')
// 		i++;
// 	std::string tmp(_input, i, _input.size() - i);
// 	//std::cout << GREEN << "tmp = " << "[" << tmp << "]" << DEFAULT <<  std::endl;
// 	i = 0;
// 	while (tmp[i]) {
// 		if (tmp[i] != '+' && tmp[i] != '-' && tmp[i] != '*' 
// 			&& tmp[i] != '/' && tmp[i] != ' ')
// 			throw (RPN::WrongFormat());
// 		i++;
// 	}
// }
