#include "../header/generation_words.hpp"
#include "../header/monte_carlo.hpp"
#include "CLHEP/Random/MTwistEngine.h"
#include <numeric>
#include <thread>
void Question2(long long int nb_numbers, int nb_files);
void Question2_1(int nb_numbers, int nb_files);
void Question2_2(int nb_numbers, const char* file_name);
void Question2_3(int threads_number, long long int nb_iterations);
void Question4();
void Question5_A();
unsigned long long int CountGenerationWord(const char* dictionnary,
                                           const char* word_to_find);

int main(int argc, char** argv) {
    Question2(10, 10);
    Question4();
    Question5_A();
}

void Question2(long long int nb_numbers, int nb_files) {

    try {
        Question2_1(nb_numbers, nb_files);
        for (auto i = 0; i < nb_files; i++) {
            std::stringstream ss;
            ss << "./Status/" << i << ".conf";
            Question2_2(nb_numbers, ss.str().c_str());
        }
        Question2_3(nb_files, nb_numbers);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Question2_1(int nb_numbers, int nb_files) {
    CLHEP::MTwistEngine* mercenneTwister = new CLHEP::MTwistEngine();

    if (nb_numbers < 0 || nb_files < 0) {
        throw std::domain_error("Numbers has to be positif");
    }
    for (auto i = 0; i < nb_files; i++) {
        std::stringstream ss;
        ss << "./Status/" << i << ".conf";
        mercenneTwister->saveStatus(ss.str().c_str());
        for (auto j = 0; j < nb_numbers; j++) {
            mercenneTwister->flat();
        }
    }

    delete mercenneTwister;
}

void Question2_2(int nb_numbers, const char* file_name) {
    CLHEP::MTwistEngine* mercenneTwister = new CLHEP::MTwistEngine();
    std::ifstream file;
    if (nb_numbers < 0) {
        throw std::domain_error("Number has to be positif");
    }

    mercenneTwister->restoreStatus(file_name);
    file.open(file_name, std::ios::in);

    if (!file.is_open()) {
        throw std::ifstream::failure("FileName incorrect");
    }
    // TODO : verifier si fichier status bien ouvert ;
    for (auto i = 0; i < nb_numbers; i++) {
        auto number_from_mt = mercenneTwister->flat();
        auto number_from_file = file.get();
        if (number_from_file != number_from_mt) {
            throw std::domain_error("Error to recover the MT random numbers");
        }
    }

    delete mercenneTwister;
    file.close();
}

void Question2_3(int threads_number, long long int nb_iterations) {
    std::vector<std::thread> monte_carlo_threads;
    if (threads_number < 0) {
        throw std::domain_error("The number of thread has to be positive");
    }

    monte_carlo_threads.reserve(threads_number);
    for (unsigned i = 0; i < threads_number; i++) {
        monte_carlo_threads.emplace_back([&]() {
            auto mc = MonteCarlo();
            mc.monteCarlo(nb_iterations);
        });
    }
    for (auto& it : monte_carlo_threads) {
        it.join();
    }
}

void Question4() {
    const unsigned short int replications = 10;
    std::vector<std::thread> monte_carlo_threads;
    monte_carlo_threads.reserve(replications);
    for (unsigned i = 0; i < replications; i++) {
        monte_carlo_threads.emplace_back([&]() {
            auto mc = MonteCarlo();
            mc.monteCarlo(1000000000);
        });
    }
}

void Question5_A() {

    const char *dictionnary = "acgt", *word_to_find = "gattaca";
    short int nb_experiences = 40;
    unsigned long long int counts[nb_experiences];
    unsigned long long int count;
    double average, real_probability = 1 / (4 * 4 * 4 * 4 * 4 * 4 * 4);
    std::cout << "QUESTION 5.A" << std::endl;

    count = CountGenerationWord(dictionnary, word_to_find);

    std::cout
        << "Number of iteration to find the word gattaca the first time : "
        << count << std::endl;

    for (auto i = 0; i < nb_experiences; i++) {
        counts[i] = CountGenerationWord(dictionnary, word_to_find);
        std::cout << i << " : " << count << std::endl;
    }

    average =
        std::accumulate(counts, counts + nb_experiences, 0) / nb_experiences;

    std::cout << "Average of iterations : " << average << std::endl;
    std::cout << "Real : " << (double)1 / average << std::endl;
    std::cout << "Theoric Probability : " << real_probability << std::endl;
    std::cout << "Confidence Intervale : ["
              << real_probability - (double)1 / nb_experiences << " ; "
              << real_probability + (double)1 / nb_experiences << "]"
              << std::endl;
}

unsigned long long int CountGenerationWord(const char* dictionnary,
                                           const char* word_to_find) {
    GenerationsWords gw = GenerationsWords((char*)dictionnary);
    unsigned long long int count = 0;

    while (gw.generateWord(7) != word_to_find) {
        count++;
    }

    return count;
}
