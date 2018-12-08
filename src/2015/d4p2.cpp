// Day 4, Part Two

// Santa needs help mining some AdventCoins (very similar to bitcoins)
// to use as gifts for all the economically forward-thinking little
// girls and boys.

// To do this, he needs to find MD5 hashes which, in hexadecimal,
// start with at least five zeroes. The input to the MD5 hash is some
// secret key (your puzzle input, given below) followed by a number in
// decimal. To mine AdventCoins, you must find Santa the lowest
// positive number (no leading zeroes: 1, 2, 3, ...) that produces
// such a hash.

// For example:

// If your secret key is abcdef, the answer is 609043, because the MD5
// hash of abcdef609043 starts with five zeroes (000001dbbfa...), and
// it is the lowest such number to do so.

// If your secret key is pqrstuv, the lowest number it combines with
// to make an MD5 hash starting with five zeroes is 1048970; that is,
// the MD5 hash of pqrstuv1048970 looks like 000006136ef....

// Now find one that starts with six zeroes.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/evp.h>

void md5(const std::string& data, std::vector<unsigned char>& md) {
    const EVP_MD* md_type = EVP_md5();
    EVP_MD_CTX* ctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(ctx, md_type, nullptr);
    EVP_DigestUpdate(ctx, data.c_str(), data.size());
    EVP_DigestFinal_ex(ctx, md.data(), nullptr);
    EVP_MD_CTX_destroy(ctx);
}

int crack(const char* key) {
    // reserve space for digest
    const EVP_MD* md_type = EVP_md5();
    std::vector<unsigned char> md(EVP_MD_size(md_type));

    // store key & original key size
    std::string data(key);
    std::size_t dsize = data.size();

    int num = 0;
    while (true) {
        // overwrite salt part of data
        std::string salt(std::to_string(num));
        data.resize(dsize + salt.size());
        std::copy(salt.begin(), salt.end(), data.begin() + dsize);

        md5(data, md);

        // check 6 lead zeroes
        if (!md[0] && !md[1] && !md[2]) {
            return num;
        }
        ++num;
    }
}

int main() {
    for (std::string line; std::getline(std::cin, line);) {
        std::cout << crack(line.c_str()) << '\n';
    }

    return 0;
}
