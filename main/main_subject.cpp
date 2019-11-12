#include "../header/generation_words.hpp"
#include "../header/monte_carlo.hpp"
#include "CLHEP/Random/MTwistEngine.h"
#include <cmath>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>

std::mutex mutex_output;

void Question2(long long int nb_numbers, int nb_files);
void Question2_1(int nb_numbers, int nb_files);
void Question2_2(int nb_numbers, const char* status_name, const char* file_name);
void Question2_3(int threads_number, long long int nb_iterations);
void Question4();
void Question5_A();
bool doubleAlmostEqual(double a, double b);
unsigned long long int CountGenerationWord(const std::string& dictionnary, const std::string& word_to_find);

int main(int argc, char** argv) {
    // Question2(10, 10);
    // Question4();
    Question5_A();
}

void Question2(long long int nb_numbers, int nb_files) {

    try {
        Question2_1(nb_numbers, nb_files);
        for (auto i = 0; i < nb_files; i++) {
            std::stringstream ss_status, ss_file;
            ss_status << "../Status/" << i << ".conf";
            ss_file << "../Numbers/" << i << ".txt";
            Question2_2(nb_numbers, ss_status.str().c_str(), ss_file.str().c_str());
        }
        std::cout << "All numbers are correct !" << std::endl;
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

        std::stringstream ss_status, ss_file;
        ss_status << "../Status/" << i << ".conf";
        ss_file << "../Numbers/" << i << ".txt";

        mercenneTwister->saveStatus(ss_status.str().c_str());
        std::ofstream file_number(ss_file.str().c_str());

        if (!file_number) {
            throw std::ifstream::failure("FileName incorrect");
        }

        for (auto j = 0; j < nb_numbers; j++) {
            file_number << std::scientific << mercenneTwister->flat() << std::endl;
        }
    }

    delete mercenneTwister;
}

void Question2_2(int nb_numbers, const char* status_name, const char* file_name) {
    CLHEP::MTwistEngine* mercenneTwister = new CLHEP::MTwistEngine();
    std::ifstream file(file_name);
    if (nb_numbers < 0) {
        throw std::domain_error("Number has to be positif");
    }

    mercenneTwister->restoreStatus(status_name);

    if (!file) {
        throw std::ifstream::failure("FileName incorrect");
    }
    // TODO : verifier si fichier status bien ouvert ;
    for (auto i = 0; i < nb_numbers; i++) {
        auto number_from_mt = mercenneTwister->flat();
        double number_from_file;
        file >> number_from_file;

        if (!doubleAlmostEqual(number_from_file, number_from_mt)) {
            std::cerr << std::scientific << number_from_file << " " << number_from_mt << std::endl;
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
            auto pi = mc.monteCarlo(nb_iterations);
            std::lock_guard lock(mutex_output);
            std::cout << "Value of Pi : " << pi << std::endl;
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
            auto mc = MonteCarlo{};
            auto pi = mc.monteCarlo(1000000000);
            std::lock_guard lock(mutex_output);
            std::cout << "Value of Pi : " << pi << std::endl;
        });
    }
    for (auto& it : monte_carlo_threads) {
        it.join();
    }
}

void Question5_A() {

    std::string dictionnary = "acgt", word_to_find = "gattaca";
    short int nb_experiences = 40;
    unsigned long long int counts[nb_experiences];
    unsigned long long int count;
    double theoric_probability = 1.0 / (4 * 4 * 4 * 4 * 4 * 4 * 4);
    std::cout << "QUESTION 5.A" << std::endl;

    count = CountGenerationWord(dictionnary, word_to_find);

    std::cout << "Number of iteration to find the word gattaca the first time : " << count << std::endl;

    for (auto i = 0; i < nb_experiences; i++) {
        counts[i] = CountGenerationWord(dictionnary, word_to_find);
    }

    double average = std::accumulate(counts, counts + nb_experiences, 0) / nb_experiences;
    double real_probability = 1.0 / average;
    // std::accumulate(std::begin(counts), std::end(counts), 0) / nb_experiences;
    auto confidence_interval_min = theoric_probability - 1.0 / std::sqrt(nb_experiences);
    auto confidence_interval_max = theoric_probability + 1.0 / std::sqrt(nb_experiences);
    std::cout << "Average of iterations : " << average << std::endl;
    std::cout << "Real : " << real_probability << std::endl;
    std::cout << "Theoric Probability : " << theoric_probability << std::endl;
    std::cout << "Confidence Interval : [" << confidence_interval_min << " ; " << confidence_interval_max << "]"
              << std::endl;
    if ((real_probability < confidence_interval_min) || (real_probability > confidence_interval_max)) {
        std::cout << "BAD : The real probability is outside the confidence interval" << std::endl;
    } else {
        std::cout << "GOOD : The real probability is inside the confidence interval" << std::endl;
    }
}

unsigned long long int CountGenerationWord(const std::string& dictionnary, const std::string& word_to_find) {
    GenerationsWords gw = GenerationsWords(dictionnary);
    unsigned long long int count = 0;

    while (gw.generateWord(word_to_find.size()) != word_to_find) {
        count++;
    }

    return count;
}

bool doubleAlmostEqual(double a, double b) {
    double epsilon = 0.00001;
    return std::abs(a - b) <= epsilon * std::abs(a);
}
