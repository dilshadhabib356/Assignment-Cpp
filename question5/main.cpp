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
Q5. Create a function that converts color in RGB format to Hex format.
Examples
rgbToHex("rgb(0, 128, 192)") ➞ "#0080c0"
rgbToHex("rgb(45, 255, 192)") ➞ "#2dffc0"
rgbToHex("rgb(0, 0, 0)") ➞ "#000000"
Notes
The Hex format should be displayed in lowercase.


*/



#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

class RGBConverter {
public:
    std::string toHex(const std::string& rgb) const {
        int r, g, b;
        sscanf_s(rgb.c_str(), "rgb(%d, %d, %d)", &r, &g, &b);


        std::stringstream hex;
        hex << "#" << std::setfill('0') << std::setw(2) << std::hex << r
            << std::setfill('0') << std::setw(2) << std::hex << g
            << std::setfill('0') << std::setw(2) << std::hex << b;

        return hex.str();
    }
};

int main() {
    RGBConverter converter;

    std::cout <<"rgb to hex : "<< converter.toHex("rgb(0, 128, 192)") << std::endl;      
    std::cout << "rgb to hex : " << converter.toHex("rgb(45, 255, 192)") << std::endl;
    std::cout << "rgb to hex : " <<  converter.toHex("rgb(0, 0, 0)") << std::endl;

    return 0;
}
