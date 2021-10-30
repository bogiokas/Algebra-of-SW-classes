#include<iostream>

class Counter {
public:
	Counter() { std::cout<<"Constructor"<<std::endl; }
	Counter(const Counter&) { std::cout<<"Copy Constructor"<<std::endl; }
	Counter(Counter&&) { std::cout<<"Move Constructor"<<std::endl; }
	
	Counter& operator=(const Counter&) { std::cout<<"Copy Operator"<<std::endl; return *this; }
	Counter& operator=(Counter&&) { std::cout<<"Move Operator"<<std::endl; return *this; }
};
