/*
Q1.C++ offers some bit operations but not bit rotation.To complete that, create a
function that takes three parameters :
n: Integer, which in binary representation should be rotated.
m : Number of rotation steps that should be performed.
d : Boolean value; true = rotation right, false = rotation left.
Your function should return an integer as a result of its rotated binary
representation.
Examples
bitRotate(8, 1, true) ➞ 4
// 8 in bin: 1000, rotated 1 step to the right: 0100, in dec: 4
bitRotate(16, 1, false) ➞ 1
// 16 in bin: 10000, rotated 1 step to the left: 00001, in dec: 1
bitRotate(17, 2, false) ➞ 6
// 17 in bin: 10001, rotated 2 steps to the left: 00110, in dec: 6
Notes
For parameters use unsigned integers only.

*/

#include <iostream>
#include <stdexcept>

class BitRotator {
public:
    // Rotate function
    unsigned int rotate(unsigned int value, unsigned int positions, bool directionRight) const
    {
        // Calculate the size of the unsigned int in bits
        const unsigned int BITS = sizeof(unsigned int) * 8;

        // Ensure positions is within a valid range
        if (positions >= BITS) {
            positions %= BITS;
        }

        // Rotate right
        if (directionRight) {
            return (value >> positions) | (value << (BITS - positions));
        }
        // Rotate left
        else {
            return (value << positions) | (value >> (BITS - positions));
        }
    }
};

int main() {
    try {
        BitRotator rotator;  // Single instance

        std::cout <<" result :"<< rotator.rotate(16, 1, true) << std::endl;
        std::cout << " result :" << rotator.rotate(16, 1, false) << std::endl;
        std::cout << " result :" << rotator.rotate(17, 2, false) << std::endl;

        std::cin.get();  // Wait for keypress
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
