#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>

void print_truth_table(const std::string &formula);

int main() {
	print_truth_table("AB&C|");
	std::cout << "----------------" << std::endl;
	print_truth_table("AB&");
	std::cout << "----------------" << std::endl;
	print_truth_table("AB|C&");
	std::cout << "----------------" << std::endl;
	print_truth_table("AB|C^");
	std::cout << "----------------" << std::endl;
	print_truth_table("AB|C>");
	std::cout << "----------------" << std::endl;
	print_truth_table("AB|C=");
	std::cout << "----------------" << std::endl;
	print_truth_table("A!");
	return 0;
}