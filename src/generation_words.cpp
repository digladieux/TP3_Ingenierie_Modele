#include "../header/generation_words.hpp"
#include "../Random/CLHEP/Random/MTwistEngine.h"

GenerationsWords::GenerationsWords(const std::string& dico)
    : dictionnary(dico) {}

std::string GenerationsWords::generateWord(short int word_size) {
    std::string word_generated;
    for (auto i = 0; i < word_size; i++) {
        auto index = static_cast<int>(this->mercenneTwister.flat() * this->dictionnary.size());
        word_generated.push_back(this->dictionnary[index]);
    }

    return word_generated;
}
