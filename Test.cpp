#include "GapBuffer.h"
#include <string>
#include <iostream>
int main() {
	GapBuffer gb;
	gb.insert("Hello world ", 11);
	std::cout << gb.get_string() << '\n';
	gb.stable_insert("meaningless rubbish", 19);
	std::cout << gb.get_string() << '\n';
	gb.move_cursor(11);
	std::cout << gb.get_string() << '\n';
	gb.erase(7);
	std::cout << gb.get_string() << '\n';
	gb.insert("potato ", 7);
	std::cout << gb.get_string() << '\n';
	return 0;
}
