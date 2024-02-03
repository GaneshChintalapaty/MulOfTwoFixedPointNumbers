#pragma region Header Files
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <stdint.h>
#pragma endregion

#pragma region To multiply two fixed point numbers
// Function to multiply two fixed-point numbers using shifting and addition
uint32_t multiplyFixedPoint(uint32_t a, uint32_t b) 
{

    uint64_t result = 0;
    // Iterate through each bit of the second operand (b)
    for (int i = 0; i <= 31; i++) 
    {
        // Check if the i-th bit of b is set high
        if (b & (1U << i)) 
        {
            // If the bit is set, add the product of a and 2^i to the result
            result += ((uint64_t)a << i);
        }
    }

    result >>= 32;
    return (uint32_t)result;

}
#pragma endregion

#pragma region Main Function
int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <first number> <second number>\n";
        return 1;
    }

    std::string hexStr1 = argv[1];
    std::string hexStr2 = argv[2];

    // Ensure that the input strings start with "0x" and are exactly 10 characters (32 bits) long
    if ((hexStr1.substr(0, 2) != "0x" || hexStr1.length() != 10) || (hexStr2.substr(0, 2) != "0x" || hexStr2.length() != 10)) 
    {
        std::cerr << "Invalid input. Each hexadecimal number should start with '0x' and be 32 bits long." << std::endl;
        return 1;
    }

    // Convert hexadecimal input to unsigned integers
    unsigned int num1, num2;
    std::stringstream ss;
    ss << std::hex << hexStr1.substr(2);    //Remove '0x' and convert to integer
    ss >> num1;
    ss.clear(); //Clear string stream
    ss << std::hex << hexStr2.substr(2);    //Remove '0x' and convert to integer
    ss >> num2;
    ss.clear(); //Clear string stream

    // Multiply the numbers
    uint32_t result = multiplyFixedPoint((uint32_t)num1, (uint32_t)num2);

    // Check for underflow
    if (result == 0 && (num1 != 0 && num2 != 0)) 
    {
        std::cout << "Warning: Potential underflow detected." << std::endl;
    }
    else
    {
        // Output the result in hexadecimal, preserving leading zeros
        std::cout << "Product in Hex: 0x" << std::setfill('0') << std::setw(8) << std::hex << result << std::endl;
        
    }

    return 0;
}
#pragma endregion