#include "../header/status_mt.hpp"
#include "../Random/CLHEP/Random/MTwistEngine.h"

bool doubleAlmostEqual(double a, double b) ;

/**
 * @brief Construct a new StatusMT:: Status MT object
 * 
 * @param status_nb Nombre de status a generer
 * @param numbers_nb Nombre de numbers a generer
 */
StatusMT::StatusMT(int status_nb, long long int numbers_nb) : numbers_saved(false), status_generated(false), index_status(-1) {
    if (status_nb < 0 || numbers_nb < 0) {
        throw std::domain_error("Numbers has to be positive") ;
    }

    mercenneTwister = {} ;
    this -> status_number = status_nb ;
    this -> numbers_number = numbers_nb ;
}

/**
 * @brief Construct a new Status M T:: Status M T object
 * 
 * @param gs Le statut a copier
 */
StatusMT::StatusMT(const StatusMT& gs) : mercenneTwister(gs.mercenneTwister), 
status_number(gs.status_number), numbers_number(gs.numbers_number),  index_status(gs.index_status), 
numbers_saved(gs.numbers_saved), status_generated(gs.status_generated) {} 

/**
 * @brief Generation de statut avec sauvegarde ou non des nombres dans un fichier
 * 
 * @param save_number Choix de la sauvegarde ou non des nombres aleatoires
 */
void StatusMT::generateStatus(bool save_number) {
    this->status_generated = true;
    this->numbers_saved = save_number ;
    system("rm -rf ../Status/* ../Numbers/*") ;

    for (auto i = 0; i < this -> status_number; i++) {

        std::stringstream ss_status;
        ss_status << "../Status/" << i << ".conf";

        this->mercenneTwister.saveStatus(ss_status.str().c_str());

        if (save_number) {
            std::stringstream ss_file;
            ss_file << "../Numbers/" << i << ".txt";
            
            std::ofstream file_number(ss_file.str().c_str());

            if (!file_number) {
                throw std::ifstream::failure("FileName incorrect");
            }

            for (auto j = 0; j < this -> numbers_number; j++) {
                file_number << std::scientific << this->mercenneTwister.flat() << std::endl;
            }
        }

        else {
            for (auto j = 0; j < this -> numbers_number; j++) {

                this->mercenneTwister.flat();
            }
        }
    }
}

/**
 * @brief Restauration du status du nombre aleatoire
 * 
 * @param index Numero de fichier a recuperer
 */
void StatusMT::recoverStatus(int index) {

    if (!this->status_generated) {
        throw std::domain_error("No status have been generated") ;
    }

    if (index > this -> status_number) {
        throw std::domain_error("Status don't exist") ;
    }

    this->index_status = index ;
    std::stringstream status_name ;
    status_name << "../Status/" << index << ".conf" ;

    // TODO : verifier si fichier status bien ouvert ;

    this->mercenneTwister.restoreStatus(status_name.str().c_str()) ;
}

/**
 * @brief On verifie si les status genere reproduisent les memes nombres qu'avant
 * 
 * @return true Si les nombres regeneres sont correctes
 * @return false Si les nombres regeneres sont incorrectes
 */
bool StatusMT::checkStatus() {

    if (!this->status_generated) {
        throw std::domain_error("Status was not generated");
    }

    if (!this -> numbers_saved) {
        throw std::domain_error("Numbers were not saved") ;
    }

    std::stringstream file_name ;
    file_name << "../Numbers/" << this -> index_status << ".txt" ;

    std::ifstream file(file_name.str().c_str());
    if (!file) {
        throw std::ifstream::failure("FileName incorrect");
    }

    for (auto i = 0; i < this-> numbers_number; i++) {
        auto number_from_mt = this->mercenneTwister.flat();
        double number_from_file;
        file >> number_from_file;

        if (!doubleAlmostEqual(number_from_file, number_from_mt)) {
            std::cerr << std::scientific << number_from_file << " " << number_from_mt << std::endl;
            return false ;
        }
    }

    file.close();
    return true ;
}

/**
 * @brief Getteur sur le nombre de status
 * 
 * @return unsigned int Nombre de status
 */
unsigned int StatusMT::getStatusNumber() const {
    return this -> status_number ;
}

/**
 * @brief Getteur sur le nombre de nombres genere
 * 
 * @return unsigned long long int 
 */
unsigned long long int StatusMT::getNumbersNumber() const {
    return this -> numbers_number ;
}

/**
 * @brief Generation d'un nombre aleatoire grace a MT
 * 
 * @return double Le nombre aleatoire genere
 */
double StatusMT::getRandomNumber() {
    return this -> mercenneTwister.flat() ;
}

/**
 * @brief Changer les valeurs des status. Par consequent il faut regenerer les status en consequent
 * 
 * @param status_nb Le nombre de status a generer
 * @param numbers_nb Le nombre de nombres genere
 * @param save_number Le souhait ou non de sauvegarder les nombres
 */
void StatusMT::setValues(int status_nb, unsigned long long int numbers_nb, bool save_number) {
    if (this -> status_number != status_nb || this -> numbers_number != numbers_nb || this ->numbers_saved != save_number) {
        this -> status_number = status_nb ;
        this -> numbers_number = numbers_nb ;
        this -> numbers_saved = save_number ;
        this->generateStatus(save_number) ;
    }
}

/**
 * @brief Savoir si 2 doubles sont egaux
 * @param a 1er nombre
 * @param b 2eme nombre
 * @return true Les nombres sont egaux
 * @return false Les nombres sont differents
 */
bool doubleAlmostEqual(double a, double b) {
    double epsilon = 0.00001;
    return std::abs(a - b) <= epsilon * std::abs(a);
}