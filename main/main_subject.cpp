#include "../header/generation_status.hpp"
#include "../header/generation_words.hpp"
#include "../header/monte_carlo.hpp"
#include <cmath>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>

std::mutex mutex_output;

void Question2(GenerationStatus& gs);
void Question2_1(GenerationStatus& gs);
void Question2_2(GenerationStatus& gs);
void Question2_3(GenerationStatus& gs);
void Question4(GenerationStatus& gs);
void Question5_A();
bool doubleAlmostEqual(double a, double b);
unsigned long long int CountGenerationWord(const std::string& dictionnary, const std::string& word_to_find);

int main(int argc, char** argv) {

    GenerationStatus gs(10, 10);
    Question2(gs);
    // Question4(gs);
    // Question5_A();
}

void Question2(GenerationStatus& gs) {

    try {
        Question2_1(gs);
        Question2_2(gs);
        Question2_3(gs);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Question2_1(GenerationStatus& gs) {

    std::cout << "QUESTION 2.1" << std::endl ;
    gs.generateStatus(true);
}

void Question2_2(GenerationStatus& gs) {
    
    std::cout << "QUESTION 2.2" << std::endl ;
    bool all_numbers_correct = true ;
    for (auto i = 0; i < gs.getStatusNumber(); i++) {
        gs.recoverStatus(i);
        if(!gs.checkStatus()) {
            all_numbers_correct = false ;
            std::cout << "There is a problem with the status " << i << std::endl ;
        }
    }

    if (all_numbers_correct) {
        std::cout << "All the status are well recovered !" << std::endl ;
    }
}

void Question2_3(GenerationStatus& gs) {

    std::cout << "QUESTION 2.3" << std::endl ;
    std::vector<std::thread> monte_carlo_threads;
    auto threads_number = gs.getStatusNumber() ;
    auto mc = MonteCarlo(gs);

    monte_carlo_threads.reserve(threads_number);

    for (unsigned i = 0; i < threads_number; i++) {
        monte_carlo_threads.emplace_back([&]() {
            std::lock_guard lock(mutex_output);
            mc.recoverStatusMT(i) ;
            auto pi = mc.monteCarlo();
            std::cout << "Value of Pi : " << pi << std::endl;
        });
    }
    for (auto& it : monte_carlo_threads) {
        it.join();
    }
}

void Question4(GenerationStatus& gs) {

    gs.setValues(10, 1000000000, false) ;
    std::vector<std::thread> monte_carlo_threads;
    monte_carlo_threads.reserve(gs.getStatusNumber());

    auto mc = MonteCarlo(gs);

    for (unsigned i = 0; i < gs.getStatusNumber(); i++) {
        monte_carlo_threads.emplace_back([&]() {
            std::lock_guard lock(mutex_output);
            mc.recoverStatusMT(i) ;
            auto pi = mc.monteCarlo();
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
