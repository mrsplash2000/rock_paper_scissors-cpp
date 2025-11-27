#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include <string>
#include <random>

int random_number(int minimum, int maximum) {
    std::random_device seed;
    std::mt19937 generator(seed());
    std::uniform_int_distribution<> uni_distribution(minimum, maximum);
    return uni_distribution(generator);
}

std::string generateSalt(size_t length) {
    const std::string charset {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+=-`~?/>.<,|;}{]["};
    std::string salt {""};
    for(size_t i{0}; i < length; i++) {
        salt += charset[random_number(0, charset.size() - 1)];
    }
    return salt;
}

std::string hashPassword(const std::string &password, const std::string &salt) {
    std::string input = password + salt; // Combine password and salt
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::ostringstream oss;
    for (const auto &byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str(); // Return the hashed password as a hex string
}


int main() {
    //Generating 10 passwords with salts and their hashes as an example
    for(int i{0}; i<10; i++) {
        //Asking for password
        std::string password {""};
        std::cout << "Enter A Password: ";
        std::cin >> password;
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
