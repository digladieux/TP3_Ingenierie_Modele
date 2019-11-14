/**
 * @file generation_words.hpp
 * @author Gladieux Cunha Dimitri (cdimitri@orange.fr)
 * @brief Fichier d'en tete de generation_words.cpp
 * @version 1.0
 * @date 14-11-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include "../Random/CLHEP/Random/MTwistEngine.h"
#include <string>

/**
 * @brief Classe GenerationsWords to generate a random word with a dictionnary and a size
 * 
 */
class GenerationsWords {
    public :
        explicit GenerationsWords(const std::string& dico) ;
        std::string generateWord(short int word_size);
    private :
        std::string dictionnary ;
        CLHEP::MTwistEngine mercenneTwister{};


};

