/**
 * @file generation_string.hpp
 * @author Gladieux Cunha Dimitri (cdimitri@orange.fr)
 * @brief Fichier d'en tete de generation_string.cpp
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
 * @brief Classe GenerationString to generate a random string with a dictionnary
 * 
 */
class GenerationString {
    public :
        explicit GenerationString(const std::string& dico) ;
        std::string generateWord(short int word_size);
        unsigned long long int tryGenerateString(const std::string& word_to_find) ;

    private :
        std::string dictionnary ;


};

