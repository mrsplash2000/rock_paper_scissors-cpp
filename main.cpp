#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <string>
#include <random>


//======Random Number Generation Function=======
int random_number(int minimum, int maximum) {
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<> uni_distribution(minimum, maximum);
    return uni_distribution(generator);
}
//============================================

//=======Username And Password Functions========

//---Salt Generation---
std::string generateSalt(size_t length) {
    std::string salt {""};
    for(size_t i{0}; i < length; i++) {
        salt += char(random_number(33, 126));
    }
    return salt;
}
//---Salt Generation---

//---Hashing Function---
std::string hashPassword(const std::string &password, const std::string &salt) {
    std::string input = password + salt; // Combine password and salt
    unsigned char my_hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), my_hash);

    std::ostringstream oss;
    for (const auto &byte : my_hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str(); // Return the hashed password as a hex string
}
//---Hashing Function---

//---Length Check Function---
bool length_check(std::string &input) {
    if(input.length() >= 7)
        return true;
    else
        return false;
}
//---Length Check Function---

//============================================


int main() {

    //Generating 10 passwords with salts and their hashes as an example
    for(int i{0}; i<10; i++) {

        //Asking for password
        std::string password {""};
        while(true){
            std::cout << "Enter A Password: ";
            std::cin >> password;
            //Checking if the password's length is greater than 7
            if(length_check(password) == false) {
                std::cout << "Please Type A Password With A Length Greater Than Or Equal To 7!\n";
                continue;
            }
            else
                break;
        }

        //salt and hash operations
        std::string salt {generateSalt(random_number(15, 20))};
        std::string hash_pass {hashPassword(password, salt)};

        std::cout << "Password: " << password << '\n';
        std::cout << "Salt: " << salt << '\n';
        std::cout << "Hash: " << hash_pass << '\n';
        std::cout << "====================\n";
    }

    return 0;
}
