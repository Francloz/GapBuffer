#include "GapBuffer.h"
#include <string>
#include <iostream>
int main() {
	GapBuffer gb;
	gb.insert("Hola mundo ", 11);
	std::cout << gb.get_string() << '\n';
	gb.stable_insert("patata brava", 12);
	std::cout << gb.get_string() << '\n';
	gb.move_cursor(11);
	std::cout << gb.get_string() << '\n';
	gb.erase(7);
	std::cout << gb.get_string() << '\n';
	gb.insert("patata ", 7);
	std::cout << gb.get_string() << '\n';

	std::cout << gb.get_string() << '\n';
	return 0;
}