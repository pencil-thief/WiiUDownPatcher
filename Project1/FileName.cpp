#include <iostream>
using namespace std;

// Function that adds the global variables
void addNumbers(int num1, int num2) {
    int result = num1 + num2;
    cout << "Addition: " << result << endl;
}

// Function that multiplies the global variables
void multiplyNumbers(int num1, int num2) {
    int result = num1 * num2;
    cout << "Multiplication: " << result << endl;
}

int main() {
    int num1 = 10;
    int num2 = 5;
    addNumbers(num1, num2);
    multiplyNumbers(num1, num2);

    return 0;
}
