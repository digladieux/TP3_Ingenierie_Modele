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
 * @brief Construct a new Monte Carlo:: Monte Carlo object
 * 
 * @param status The status to copy for MonteCarlo
 */
MonteCarlo::MonteCarlo(const StatusMT& status) : status_mt(status) {}

/**
 * @brief Launch the function to recover the status of MT
 * 
 * @param index The status you want to recover
 */
void MonteCarlo::recoverStatusMT(int index) {
    this->status_mt.recoverStatus(index);
}

/**
 * @brief Methode effectuant n experiences de Monte Carlo, avec m iterations. On definit si on
 * souhaite utiliser des nombres deja genere ou non. On calcul aussi l'ecart a
 * la moyenne entre les resultats experimentaux du calcul de PI et la valeur
 * theorique de ce dernier
 *
 */
void MonteCarlo::nExperiencesMonteCarlo() {
    unsigned long long int i;
    double average_gap = 0;

    for (i = 0; i < status_mt.getStatusNumber(); i++) {
        double pi = monteCarlo();
        double tmp = M_PI - pi;
        average_gap += tmp < 0 ? tmp * (-1) : tmp;
        std::cout << "Step n°" << i + 1 << " - Value of Pi : " << pi << std::endl;
    }

    average_gap /= status_mt.getStatusNumber();
    std::cout << "Average Gap : " << average_gap << std::endl;
}

/**
 * @brief Fonction effectuant une experience de Monte Carlo, avec m iterations.
 * @return double La valeur experimentale de PI.
 */
double MonteCarlo::monteCarlo() {
    unsigned long long int count = 0;
    unsigned long long int i = 0;

    for (i = 0; i < status_mt.getNumbersNumber(); i++) {
        double x = status_mt.getRandomNumber();
        double y = status_mt.getRandomNumber();
        double z = x * x + y * y;
        if (z <= 1) {
            count++;
        }
    }

    return (double)count / status_mt.getNumbersNumber() * 4;
}