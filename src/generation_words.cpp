#include "../header/generation_words.hpp"
#include "../Random/CLHEP/Random/MTwistEngine.h"

GenerationsWords::GenerationsWords(char * dico) : dictionnary(dico) {}

const char * GenerationsWords::generateWord(short int word_size) const {
    std::stringstream word_generated ;
    CLHEP::MTwistEngine* mercenneTwister = new CLHEP::MTwistEngine();
    for (auto i = 0 ; i < word_size ; i++) {
        mercenneTwister->flat() ;
        word_generated << "a" ;
    }

    return word_generated.str().c_str();
}
