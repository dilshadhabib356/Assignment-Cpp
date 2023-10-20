/*

Q2. Write a function that adds two numbers. The catch, however, is that the
numbers will be strings.
Examples
addStrNums("4", "5") ➞ "9"
addStrNums("abcdefg", "3") ➞ "-1"
addStrNums("1", "") ➞ "1"
addStrNums("1874682736267235927359283579235789257",
"32652983572985729") ➞ "1874682736267235927391936562808774986"
Notes
• If there are any non-numerical characters, return "-1".
• An empty parameter should be treated as "0".
• Your function should be able to add any size number.
• Your function doesn't have to add negative numbers.
• Zeros at the beginning of the string should be trimmed.

*/



#include <iostream>
#include <string>
#include <algorithm>

class StringAdder {
public:
    // Method to add two strings representing numbers
    std::string add(const std::string& num1, const std::string& num2) const {
        // Helper function to check if a string is numeric
        auto isNumeric = [](const std::string& s) {
            return std::all_of(s.begin(), s.end(), [](char c) { return std::isdigit(c); });
        };

        if (!isNumeric(num1) || !isNumeric(num2)) {
            return "-1";
        }

        int carry = 0;
        std::string result;

        auto it1 = num1.rbegin(), it2 = num2.rbegin();
        while (it1 != num1.rend() || it2 != num2.rend() || carry) {
            int n1 = (it1 != num1.rend()) ? *it1 - '0' : 0;
            int n2 = (it2 != num2.rend()) ? *it2 - '0' : 0;

            int sum = n1 + n2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');

            if (it1 != num1.rend()) ++it1;
            if (it2 != num2.rend()) ++it2;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    StringAdder adder;  // Single instance

    std::cout <<"result of addition "<< adder.add("4", "5") << std::endl;      // Outputs 9
    std::cout << "result of addition " << adder.add("abcdefg", "3") << std::endl; // Outputs -1
    std::cout << "result of addition " << adder.add("1", "15") << std::endl;       // Outputs 1

    return 0;
}
