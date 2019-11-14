#include "../header/generation_words.hpp"
#include "../Random/CLHEP/Random/MTwistEngine.h"

/**
 * @brief Construct a new Generations Words:: Generations Words object
 * 
 * @param dico Le dictionnaire a utilise pour la generation des mots
 */
GenerationsWords::GenerationsWords(const std::string& dico)
    : dictionnary(dico) {}

/**
 * @brief Genere un mot aleatoire suivant une taille donnee
 * 
 * @param word_size Longueur du mot souhaite
 * @return std::string Le mot genere aleatoirement
 */
std::string GenerationsWords::generateWord(short int word_size) {
    std::string word_generated;
    for (auto i = 0; i < word_size; i++) {
        auto index = static_cast<int>(this->mercenneTwister.flat() * this->dictionnary.size());
        word_generated.push_back(this->dictionnary[index]);
    }

    return word_generated;
}
