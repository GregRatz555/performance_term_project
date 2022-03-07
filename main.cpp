#include <iostream>
#include "VM.cpp"
using namespace std;

int main() {
	// Attempt to create machine state
	cout << "Creating Machine!\n";
	VM rv32i;
	cout << "Create Machine Successful!\n";
	rv32i.init_registers();
	cout << "Register creation Successful!\n";
	return 0;
}