#pragma once

#include "../Random/CLHEP/Random/MTwistEngine.h"
#include <string>
class GenerationsWords {
    public :
        explicit GenerationsWords(const std::string& dico) ;
        std::string generateWord(short int word_size);
    private :
        std::string dictionnary ;
        CLHEP::MTwistEngine mercenneTwister{};


};

