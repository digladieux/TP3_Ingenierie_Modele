/**
 * @file monte_carlo.cpp
 * @author Gladieux Cunha Dimitri (cdimitri@orange.fr)
 * @brief Fichier pour l'algorithme de Monte Carlo
 * @version 1.0
 * @date 14-11-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include "../header/monte_carlo.hpp"
#include "CLHEP/Random/MTwistEngine.h"
#include <cmath>
#include <exception>

/**
 * @brief Methode effectuant n experiences de Monte Carlo, avec m iterations. On calcul aussi l'ecart a
 * la moyenne entre les resultats experimentaux du calcul de PI et la valeur
 * theorique de ce dernier
 * 
 * @param status_mt La classe qui gere les status de MT
 */
void MonteCarlo::nExperiencesMonteCarlo(const StatusMT& status_mt) {
    unsigned long long int i;
    double average_gap = 0;

    for (i = 0; i < status_mt.getStatusNumber(); i++) {
        double pi = monteCarlo(status_mt, i);
        double tmp = M_PI - pi;
        average_gap += std::abs(M_PI - pi);
        std::cout << "Step n°" << i + 1 << " - Value of Pi : " << pi << std::endl;
    }

    average_gap /= status_mt.getStatusNumber();
    std::cout << "Average Gap : " << average_gap << std::endl;
}

/**
 * @brief Fonction effectuant une experience de Monte Carlo, avec m iterations.
 * @return double La valeur experimentale de PI.
 */
double MonteCarlo::monteCarlo(const StatusMT& status_mt, int index_file) {
    unsigned long long int count = 0;
    unsigned long long int i = 0;
    CLHEP::MTwistEngine mercenneTwister{} ;
    std::stringstream ss ;
    ss << "../Status/" << index_file << ".conf" ;
    mercenneTwister.restoreStatus(ss.str().c_str()) ;
    for (i = 0; i < status_mt.getNumbersNumber() ; i++) {
        double x = mercenneTwister.flat();
        double y = mercenneTwister.flat();
        double z = x * x + y * y;
        if (z <= 1) {
            count++;
        }
    }

    return (double)count / status_mt.getNumbersNumber() * 4;
}