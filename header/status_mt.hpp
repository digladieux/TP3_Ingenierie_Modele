/**
 * @file status_mt.hpp
 * @author Gladieux Cunha Dimitri (cdimitri@orange.fr)
 * @brief Fichier d'en tete du fichier status_mt.cpp
 * @version 1.0
 * @date 14-11-2019
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once
#include "../Random/CLHEP/Random/MTwistEngine.h"

/**
 * @brief Classe StatusMT pour sauvegarder des status et generer des nombres aleatoires
 * 
 */
class StatusMT {
    public:

        StatusMT(int status_nb, long long int numbers_nb) ;
        StatusMT(StatusMT&&) = delete ;
        StatusMT(const StatusMT& gs) ;

        void generateStatus(bool save_number) ;
        void recoverStatus(int index) ;
        bool checkStatus() ;

        void setValues(int status_nb, unsigned long long int numbers_nb, bool save_number) ;
        unsigned int getStatusNumber() const;
        unsigned long long int getNumbersNumber() const;
        double getRandomNumber() ;

    private:
        
        CLHEP::MTwistEngine mercenneTwister ;
        unsigned int status_number ;
        unsigned long long int numbers_number ; 
        int index_status ;
        bool numbers_saved ;
        bool status_generated ;
};