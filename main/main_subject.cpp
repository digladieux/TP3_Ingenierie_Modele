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
#include "../header/generation_string.hpp"
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
void Question5_A();
void displayStatistic(unsigned long long int counts[], short int nb_experiences, double theoric_probability) ;
void Question5_B(StatusMT& status_mt);

/**
 * @brief Main du programme
 * 
 * @param argc Nombre d'arguments
 * @param argv Arguments en ligne de commande
 * @return int Le code erreur 
 */
int main(int argc, char** argv) {

    StatusMT status_mt(10, 10);
    Question2(status_mt);
    Question4(status_mt);
    Question5_A();
    Question5_B(status_mt);
    return EXIT_SUCCESS;
}

/**
 * @brief Lancement de la question 2
 * 
 * @param status_mt La classe qui gere les status de MT
 * 
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
 * @brief QUESTION 2.1. 
 * Genere 10 status et les sauvegarde dans Status/*.
 * Sauvegarde aussi les nombres aleatoires dans Numbers/*
 * @param status_mt La classe qui gere les status de MT
 */
void Question2_1(StatusMT& status_mt) {

    std::cout << "QUESTION 2.1" << std::endl;
    std::cout << "Generate 10 status and save it inside Status/*" << std::endl ;
    std::cout << "Save also the number generated in Numbers/*" << std::endl ;
    status_mt.generateStatus(true);
    std::cout << std::endl ;

}

/**
 * @brief QUESTION 2.2 AND QUESTION 3. 
 * Verifie que l'on retrouve les bons nombres quand on recupere un status sauvegardé*
 * 
 * @param status_mt La classe qui gere les status de MT
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
 * @brief Question 2_3. 
 * Lancement de 10 experiences de MonteCarlo, 10 iterations et 10 threads
 * @param status_mt La classe qui gere les status de MT
 */
void Question2_3(StatusMT& status_mt) {

    std::cout << "QUESTION 2.3" << std::endl;
    std::cout << "We launch 10 MonteCarlo experiences with 10 iterations inside 10 threads" << std::endl ;
    std::vector<std::thread> monte_carlo_threads;

    auto status_number = status_mt.getStatusNumber() - 1;

    monte_carlo_threads.reserve(status_number);
    for (unsigned i = 0; i < status_number; i++) {
        monte_carlo_threads.emplace_back([&]() {
            auto mc = MonteCarlo();
            auto pi = mc.monteCarlo(status_mt, i);
            std::lock_guard lock(mutex_output);
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
 * Generation de 10 status avec 2 000 000 000 nombres  
 * Generation de 10 experiences de MonteCarlo avec 1 000 000 000 iterations
 * @param status_mt La classe qui gere les status de MT
 */
void Question4(StatusMT& status_mt) {

    std::cout << "QUESTION 4" << std::endl ;
    std::cout << "Generation of 10 status with 1 000 000 000" << std::endl ;
    status_mt.setValues(10, 2000000000, false);
    auto mc = MonteCarlo();
    std::cout << "Generation of 10 MonteCarlo experiences with 1 000 000 000 " << std::endl ;
    
    for (unsigned i = 0; i < status_mt.getStatusNumber(); i++) {
        auto pi = mc.monteCarlo(status_mt, i);
        std::cout << "Value of Pi : " << pi << std::endl;
    }
    std::cout << std::endl ;

}

/**
 * @brief Question 5.A. 
 * 1) Trouve le mot gattaca avec le dictionnaire acgt 
 * 2) Calcul la probabilite d'obtenir la phrase Le hasard n'est pas un programme.
 * 3) Calcul la probabilite d'obtenir un ADN humain (3 milliard de base)
 */
void Question5_A() {

    std::string dictionnary = "acgt", string_to_find = "gattaca";
    short int nb_experiences = 40;
    unsigned long long int counts[nb_experiences] = {};
    unsigned long long int count;
    double theoric_probability = 1.0 / (std::pow(4,7));
    GenerationString gs(dictionnary) ;
    std::cout << "QUESTION 5.A" << std::endl;
    std::cout << "Find the word gattaca with the dictionnary acgt" << std::endl ;
    count = gs.tryGenerateString(string_to_find);

    std::cout << "Number of iteration to find the word gattaca the first time : " << count << std::endl;

    for (auto i = 0; i < nb_experiences; i++) {
        counts[i] = gs.tryGenerateString(string_to_find);
    }

    displayStatistic(counts, nb_experiences, theoric_probability) ;

    std::cout << "To find the sentence << Le hasard n'est pas un programme. >> we will suppose : " << std::endl ;
    std::cout << "- Dictionnary [a-zA-Z '.]" << std::endl ;
    std::cout << "=> Meaning 26 letters * 2 + 3 specials caracters which are ' space and . " << std::endl ;
    std::cout << "- Size of the sentence : 33" << std::endl ;
    std::cout << "The chance to find that is 1/pow(54,33) = " << 1.0/std::pow(54,33) << std::endl << std::endl ; 
    std::cout << "To find one DNA : the chance is 1/pow(4,3 000 000 000). " << std::endl ;
    std::cout << "I can't display on command line the result " << std::endl << std::endl ;
}


/**
 * @brief Affiche les statistiques a l'utilisateur
 * 
 * @param counts Tableau qui contient le nombre d'iterations a chaque recherche du mot gattaca
 * @param nb_experiences Le nombre d'experience
 * @param theoric_probability La probabilite theorique de l'experience
 */
void displayStatistic(unsigned long long int counts[], short int nb_experiences, double theoric_probability) {
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
 * @brief Question 5.B. 
 * Meme algo que la question 4 (Monte Carlo 10 experiences, 1 Milliards iterations) mais en utilisant des threads 
 * 
 * @param status_mt La classe qui gere les status de MT
 */
void Question5_B(StatusMT& status_mt) {

    std::cout << "QUESTION 5.B" << std::endl ;

    std::cout << "Same algorithm as the Question 4, but using threads" << std::endl ;
    std::vector<std::thread> monte_carlo_threads;

    auto threads_number = status_mt.getStatusNumber() - 1;

    monte_carlo_threads.reserve(threads_number);

    auto mc = MonteCarlo();

    for (unsigned i = 0; i < threads_number; i++) {
        monte_carlo_threads.emplace_back([&]() {
            auto pi = mc.monteCarlo(status_mt, i);
            std::lock_guard lock(mutex_output);
            std::cout << "Value of Pi : " << pi << std::endl;
        });
    }
    for (auto& it : monte_carlo_threads) {
        it.join();
    }
}




