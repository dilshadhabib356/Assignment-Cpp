/*

Q4. Create a function that determines the minimum number of characters needed
to make a strong password.
A password is considered strong if it satisfies the following criteria:
• Its length is at least 6.
• It contains at least one digit.
• It contains at least one lowercase English character.
• It contains at least one uppercase English character.
• It contains at least one special character: !@#$%^&*()-+
• Types of characters in a form you can paste into your solution:
o numbers = "0123456789"
o lower = "abcdefghijklmnopqrstuvwxyz"
o upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
o special = "!@#$%^&*()-+"
Examples
• strongPassword(“Ed1”) ➞ 3
• strongPassword(“#Edabit”) ➞ 1
• strongPassword("W1llth!spass?") ➞ 0
Notes
Try solving this without RegEx.

*/

#include <iostream>
#include <string>

class PasswordStrengthChecker {
public:
    int checkStrength(const std::string& password) const {
        int len = password.size();

        bool hasDigit = false;
        bool hasLower = false;
        bool hasUpper = false;
        bool hasSpecial = false;

        std::string numbers = "0123456789";
        std::string lower = "abcdefghijklmnopqrstuvwxyz";
        std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::string special = "!@#$%^&*()-+";

        for (char c : password) {
            if (numbers.find(c) != std::string::npos) hasDigit = true;
            else if (lower.find(c) != std::string::npos) hasLower = true;
            else if (upper.find(c) != std::string::npos) hasUpper = true;
            else if (special.find(c) != std::string::npos) hasSpecial = true;
        }

        int countRequirements = 0;
        if (!hasDigit) countRequirements++;
        if (!hasLower) countRequirements++;
        if (!hasUpper) countRequirements++;
        if (!hasSpecial) countRequirements++;

        return std::max(countRequirements, 6 - len);
    }
};

int main() {
    PasswordStrengthChecker checker;  

    std::cout <<"password strength  "<< checker.checkStrength("Ed!@!!$%FFS1") << std::endl;
    std::cout << "password strength  " << checker.checkStrength("#Edabit") << std::endl;
    std::cout << "password strength  " <<  checker.checkStrength("W1llth!spass?") << std::endl;

    return 0;
}
