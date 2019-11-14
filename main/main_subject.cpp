/**
 * @file main_subject.cpp
 * @author Gladieux Cunha Dimitri (cdimitri@orange.fr)
 * @brief Fichier principal du programme principal
 * @version 1.0
 * @date 14-11-2019
 * @copyright Copyright (c) 2019
 * 
 */

#include "../header/status_mt.hpp"
#include "../header/generation_words.hpp"
#include "../header/monte_carlo.hpp"
#include <cmath>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>

std::mutex mutex_output;

void Question2(StatusMT& status_mt);
void Question2_1(StatusMT& status_mt);
void Question2_2AND3(StatusMT& status_mt);
void Question2_3(StatusMT& status_mt);
void Question4(StatusMT& status_mt) ;
void Question5_B(StatusMT& status_mt);
void Question5_A();
bool doubleAlmostEqual(double a, double b);
unsigned long long int CountGenerationWord(const std::string& dictionnary, const std::string& word_to_find);

/**
 * @brief Main of the program
 * 
 * @param argc Number of argument
 * @param argv Arguments in command line
 * @return int The error number 
 */
int main(int argc, char** argv) {

    StatusMT status_mt(10, 10);
    Question2(status_mt);
    Question4(status_mt);
    Question5_B(status_mt);
    Question5_A();
    return EXIT_SUCCESS;
}

/**
 * @brief Launching the Question 2
 * 
 * @param status_mt The class to manage the status
 */
void Question2(StatusMT& status_mt) {

    std::cout << "QUESTION 2" << std::endl ;
    try {
        Question2_1(status_mt);
        Question2_2AND3(status_mt);
        Question2_3(status_mt);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

/**
 * @brief QUESTION 2.1. Generate 10 status and save it inside Status/*. Save also the number generated in Numbers/*
 * 
 * @param status_mt The class to manage the status
 */
void Question2_1(StatusMT& status_mt) {

    std::cout << "QUESTION 2.1" << std::endl;
    std::cout << "Generate 10 status and save it inside Status/*" << std::endl ;
    std::cout << "Save also the number generated in Numbers/*" << std::endl ;
    status_mt.generateStatus(true);
    std::cout << std::endl ;

}

/**
 * @brief QUESTION 2.2 AND QUESTION 3. Check if we can recover all the status and check if we have generated the same number
 * 
 * @param status_mt The class to manage the status
 */
void Question2_2AND3(StatusMT& status_mt) {

    std::cout << "QUESTION 2.2 AND QUESTION 3" << std::endl;
    std::cout << "Check if we can recover all the status and check if we have generated the same number" << std::endl ;
    bool all_numbers_correct = true;
    for (auto i = 0; i < status_mt.getStatusNumber(); i++) {
        status_mt.recoverStatus(i);
        if (!status_mt.checkStatus()) {
            all_numbers_correct = false;
            std::cout << "There is a problem with the status " << i << std::endl;
        }
    }

    if (all_numbers_correct) {
        std::cout << "All the status are well recovered !" << std::endl;
    }
    std::cout << std::endl ;
}

/**
 * @brief Question 2_3. We launch 10 MonteCarlo experiences with 10 iterations inside 10 threads
 * 
 * @param status_mt The class to manage the status
 */
void Question2_3(StatusMT& status_mt) {

    std::cout << "QUESTION 2.3" << std::endl;
    std::cout << "We launch 10 MonteCarlo experiences with 10 iterations inside 10 threads" << std::endl ;
    std::vector<std::thread> monte_carlo_threads;
    auto threads_number = status_mt.getStatusNumber() - 1;
    auto mc = MonteCarlo(status_mt);

    monte_carlo_threads.reserve(threads_number);
    for (unsigned i = 0; i < threads_number; i++) {
        monte_carlo_threads.emplace_back([&]() {
            std::lock_guard lock(mutex_output);
            mc.recoverStatusMT(i);
            auto pi = mc.monteCarlo();
            std::cout << "Value of Pi : " << pi << std::endl;
        });
    }
    for (auto& it : monte_carlo_threads) {
        it.join();
    }
    std::cout << std::endl ;

}

/**
 * @brief Question 4. 
 * Generation of 10 status with 1 000 000 000 & 
 * Generation of 10 MonteCarlo experiences with 1 000 000 000
 * @param status_mt The class to manage the status
 */
void Question4(StatusMT& status_mt) {

    std::cout << "QUESTION 4" << std::endl ;
    std::cout << "Generation of 10 status with 1 000 000 000" << std::endl ;
    
    status_mt.setValues(10, 1000000000, false);
    auto mc = MonteCarlo(status_mt);
    std::cout << "Generation of 10 MonteCarlo experiences with 1 000 000 000 " << std::endl ;
    
    for (unsigned i = 0; i < status_mt.getStatusNumber(); i++) {
        mc.recoverStatusMT(i);
        auto pi = mc.monteCarlo();
        std::cout << "Value of Pi : " << pi << std::endl;
    }
    std::cout << std::endl ;

}

/**
 * @brief Question 5.A. Find the word gattaca with the dictionnary acgtand give some statistic
 * 
 */
void Question5_A() {

    std::string dictionnary = "acgt", word_to_find = "gattaca";
    short int nb_experiences = 40;
    unsigned long long int counts[nb_experiences] = {};
    unsigned long long int count;
    double theoric_probability = 1.0 / (4 * 4 * 4 * 4 * 4 * 4 * 4);

    std::cout << "QUESTION 5.A" << std::endl;
    std::cout << "Find the word gattaca with the dictionnary acgt" << std::endl ;
    count = CountGenerationWord(dictionnary, word_to_find);

    std::cout << "Number of iteration to find the word gattaca the first time : " << count << std::endl;

    for (auto i = 0; i < nb_experiences; i++) {
        counts[i] = CountGenerationWord(dictionnary, word_to_find);
    }

    double average = std::accumulate(counts, counts + nb_experiences, 0) / nb_experiences;
    double real_probability = 1.0 / average;
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
    std::cout << std::endl ;

}


/**
 * @brief Question 5.B. Same algorithm as the Question 4, but using threads 
 * 
 * @param status_mt 
 */
void Question5_B(StatusMT& status_mt) {

    std::cout << "QUESTION 5.B" << std::endl ;

    std::cout << "Same algorithm as the Question 4, but using threads" << std::endl ;
    std::vector<std::thread> monte_carlo_threads;

    auto threads_number = status_mt.getStatusNumber() - 1;

    monte_carlo_threads.reserve(threads_number);

    auto mc = MonteCarlo(status_mt);

    for (unsigned i = 0; i < threads_number; i++) {
        monte_carlo_threads.emplace_back([&]() {
            std::lock_guard lock(mutex_output);
            mc.recoverStatusMT(i);
            auto pi = mc.monteCarlo();
            std::cout << "Value of Pi : " << pi << std::endl;
        });
    }
    for (auto& it : monte_carlo_threads) {
        it.join();
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
