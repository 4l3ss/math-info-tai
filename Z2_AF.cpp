#include "Z2_AF.h"
#include <iostream>
#include <fstream>

AF::AF(std::string filename)
{
    std::ifstream infile(filename.c_str());

    infile>>nbSymboles>>nbEtats>>nbEtatsInitiaux;
    int i;
    for(i = 0;i<nbEtatsInitiaux;i++){
        int etat;
        infile >> etat;
        etatsInitiaux.push_back(etat);
    }
    std::cout << nbEtats << std::endl;
/*    int
    while(infile >> ){
        std::string line;
        filestream. >> line;
        std::cout << line;
    }*/
    //std::cout << filestream. << std::endl;
}

void AF::afficherInfos(){
    std::cout << "Nombre de symboles : " << nbSymboles << "Nombre d'etats : " << nbEtats << "\n";
}
