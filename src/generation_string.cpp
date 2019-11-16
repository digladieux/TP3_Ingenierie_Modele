#include "../header/generation_string.hpp"
#include "../Random/CLHEP/Random/MTwistEngine.h"

/**
 * @brief Construct a new Generations String:: Generations String object
 * 
 * @param dico Le dictionnaire a utilise pour la generation des mots
 */
GenerationString::GenerationString(const std::string& dico)
    : dictionnary(dico) {}

/**
 * @brief Genere un mot aleatoire suivant une taille donnee
 * 
 * @param word_size Longueur du mot souhaite
 * @return std::string Le mot genere aleatoirement
 */
std::string GenerationString::generateWord(short int word_size) {
    std::string word_generated;
    CLHEP::MTwistEngine mercenneTwister{};
    for (auto i = 0; i < word_size; i++) {
        auto index = static_cast<int>(mercenneTwister.flat() * this->dictionnary.size());
        word_generated.push_back(this->dictionnary[index]);
    }

    return word_generated;
}

/**
 * @brief Compte le nombre d'iteration pour trouver un mot
 * 
 * @param word_to_find Le mot a trouver
 * @return unsigned long long int Le nombre d'iteration
 */
unsigned long long int GenerationString::tryGenerateString(const std::string& word_to_find) {
    unsigned long long int count = 0;
    while (this->generateWord(word_to_find.size()) != word_to_find) {
        count++;
    }

    return count;
}
