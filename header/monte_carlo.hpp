/**
 * @file monte_carlo.hpp
 * @author Gladieux Cunha Dimitri (cdimitri@orange.fr)
 * @brief Fichier d'en tete de monte_carlo.cpp
 * @version 1.0
 * @date 14-11-2019
 *
 * @copyright Copyright (c) 2019
 *
 */
#pragma once
#include "status_mt.hpp"

/**
 * @brief Class MonteCarlo pour la generation de cette experience avec l'utilisation de Mercenne Twister
 *
 */
class MonteCarlo {
  public:
    explicit MonteCarlo() = default;
    MonteCarlo(const MonteCarlo&) = delete;
    MonteCarlo(const MonteCarlo&&) = delete;
    void nExperiencesMonteCarlo(const StatusMT& status_mt);
    double monteCarlo(const StatusMT& status_mt, int index_file) ;
};