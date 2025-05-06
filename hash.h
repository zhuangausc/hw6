#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

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
        // Add your code here
        HASH_INDEX_T base36[30] = {0}; // Array of the 26 letters, set all values to 0
        // NOTE: it is 30 letters to allow for an equal number of batches of 6 numbers
        for(int i=0; i<k.length(); i++){ // Convert all letters to base36
          base36[29-k.length()+1+i] = letterDigitToNumber(k[i]);
          // std::cout << "base36 is" << base36[29-i] << std::endl;
        }
        // Translate substrings of 6 letters
        HASH_INDEX_T w[5]; // Array of the converted numbers (base36 -> decimal)
        for(int i=0; i<6; i++){
          HASH_INDEX_T res;
          res = base36[i*6];
          for(int j=1; j<6; j++){
            res = res*36 + base36[i*6+j];
            //std::cout << res << std::endl;
          }
          w[i] = res;
        }
        // Final hash result
        HASH_INDEX_T finalHash;
        for(int i=0; i<5; i++){
          //std::cout << w[i] << std::endl;
          finalHash+=(rValues[i]*w[i]);
        }
        return finalHash;
    }

    // A likely helper function is to convert a-z,0-9 to an integer value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // Check if letter is a letter
        if(std::isalpha(letter)){
          letter = std::tolower(letter); // Convert to lowercase
          HASH_INDEX_T res = letter-97; // Convert to base 36
          return res;
        } else { // letter is a number
          HASH_INDEX_T res = letter-48; // Convert to base 36
          return res;
        }
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
