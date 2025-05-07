#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        
        unsigned long long w[5] = {0};
        int strLength = k.length();
        int index = 4; 
        
        // grabs from back of str 
        while (strLength > 0 && index >= 0) {
            unsigned long long grab = 0;
            unsigned long long place = 1;
    
            // last 6 chars from back
            for (int i = strLength - 1; i >= 0 && i >= strLength - 6; --i) {
                char grabChar = k[i];
                HASH_INDEX_T convDigit = letterDigitToNumber(grabChar);
                grab += convDigit * place;
                place *= 36;
            }
    
            w[index] = grab;
            index--;
            strLength -= 6;
        }
        
        // weighted sum final hash
        unsigned long long finalRes = 0;
        for(int i = 0; i < 5; i++) {
            finalRes = finalRes + rValues[i] * w[i];
        }
        
        return finalRes;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {

        // ascii value mapping
        if (letter >= 'A' && letter <= 'Z') {
            letter = letter + 32;
        }
        
        // letters
        if (letter >= 'a' && letter <= 'z') {
            int val = letter - 97;
            return static_cast<HASH_INDEX_T>(val);
        }

        // digits
        else if (letter >= '0' && letter <= '9') {
            int val = 26 + (letter - 48);
            return static_cast<HASH_INDEX_T>(val);
        }
        
        // anyting else
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
