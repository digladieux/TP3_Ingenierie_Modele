/**
 * \file monte_carlo.c
 * \brief Fichier pour l'algorithme de Monte Carlo
 * \author GLADIEUX CUNHA Dimitri
 * \date 17 Octobre 2019
 */

#include "../header/monte_carlo.hpp"
#include "CLHEP/Random/MTwistEngine.h"
#include <exception>
#include <cmath>
/**
 * \fn void experiencesMonteCarlo(const int nb_experiences, const int
 * nb_iterations, char use_random_number_already_generated) \brief Methode
 * effectuant n experiences de Monte Carlo, avec m iterations. On definit si on
 * souhaite utiliser des nombres deja genere ou non. On calcul aussi l'ecart a
 * la moyenne entre les resultats experimentaux du calcul de PI et la valeur
 * theorique de ce dernier \param nb_experiences Le nombre d'experiences que
 * l'on desire \param nb_iterations Le nombre d'iterations que l'on souhaite
 */
void MonteCarlo::nExperiencesMonteCarlo(unsigned long long int nb_iterations,
                            const long long int nb_experiences) const {
    unsigned long long int i;
    double average_gap = 0;

    if (nb_iterations < 0 && nb_experiences < 0) {
        throw std::domain_error("Numbers has to be positive");
    }

    for (i = 0; i < nb_experiences; i++) {
        double pi = monteCarlo(nb_iterations);
        double tmp = M_PI - pi;
        average_gap += tmp < 0 ? tmp * (-1) : tmp;
        std::cout << "Step n°" << i + 1 << " - Value of Pi : " << pi
                  << std::endl;
        
    }

    average_gap /= nb_experiences;
    std::cout << "Average Gap : " << average_gap << std::endl;
}

/**
 * \fn double monteCarlo(const int begin, const int end, char
 * use_random_number_already_generated)
 * \brief Fonction effectuant une experience de Monte Carlo, avec m iterations.
 * On definit si on souhaite utiliser des nombres deja genere ou non \param
 * nb_iterations Le nombre d'iterations que l'on souhaite \return La valeur
 * experimentale de PI.
 */
double MonteCarlo::monteCarlo(unsigned long long int nb_iterations) const {
    unsigned long long int count = 0;
    unsigned long long int i = 0;
    CLHEP::MTwistEngine* mercenneTwister = new CLHEP::MTwistEngine();

    if (nb_iterations < 0) {
        throw std::domain_error("Number of iterations has to be positive");
    }

    for (i = 0; i < nb_iterations; i++) {
        double x = mercenneTwister->flat();
        double y = mercenneTwister->flat();
        double z = x * x + y * y;
        if (z <= 1) {
            count++;
        }
    }

    return (double)count / nb_iterations * 4;
}