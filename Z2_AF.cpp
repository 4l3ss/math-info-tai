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

    infile>>nbEtatsTerminaux;
    for(i = 0;i<nbEtatsTerminaux;i++){
        int etat;
        infile >> etat;
        etatsTerminaux.push_back(etat);
    }

    infile>>nbTransitions;
    for(i = 0;i<nbTransitions;i++){
        char str_transition[4];
        infile >> str_transition;
        Transition transition;

        transition.etatDepart = str_transition[0]-'0';
        transition.symbole = str_transition[1];
        transition.etatArrivee = str_transition[2]-'0';

        transitions.push_back(transition);
    }

/*    int
    while(infile >> ){
        std::string line;
        filestream. >> line;
        std::cout << line;
    }*/
    //std::cout << filestream. << std::endl;
}

void AF::afficherInfos(){
    std::cout
    << "\nNombre de symboles       : " << nbSymboles
    << "\nNombre d'etats           : " << nbEtats
    << "\nNombre d'etats initiaux  : " << nbEtatsInitiaux
    << "\nNombre d'etats terminaux : " << nbEtatsTerminaux
    << "\nNombre de transitions    : " << nbTransitions
    << "\n";


    std::cout << "Liste des etats initiaux : ";
    for (std::vector<int>::const_iterator i = etatsInitiaux.begin(); i != etatsInitiaux.end(); ++i){
        std::cout << *i << " ";
    }

    std::cout << "\nListe des etats terminaux : ";
    for (std::vector<int>::const_iterator i = etatsTerminaux.begin(); i != etatsTerminaux.end(); ++i){
        std::cout << *i << " ";
    }

    std::cout << "\nListe des transitions : \n";
    for (std::vector<Transition>::const_iterator i = transitions.begin(); i != transitions.end(); ++i){
        std::cout << "(" << (*i).etatDepart << ")-" << (*i).symbole << "->(" << (*i).etatArrivee << ")\n";
    }


}

bool AF::est_asynchrone(){
    std::cout << "\n Test asynchrone : \n";
    bool resultat = false;
    for (std::vector<Transition>::const_iterator i = transitions.begin(); i != transitions.end(); ++i){
        if((*i).symbole == '*'){
            resultat = true;
            std::cout << "(" << (*i).etatDepart << ")-" << (*i).symbole << "->(" << (*i).etatArrivee << ") est une transition epsilon\n";
        }

    }

    std::cout << "L'automate fini est " << (resultat ? "Asynchrone" : "Synchrone") << "\n";
    return resultat;
}

/**
 * Retourne un tableau qui associe à chaque symbole le nombre de transition partant de l'etat donné
 * 0=a,1=b,2=c ...etc
 **/
int[] AF::compter_transition_partant_d_etat_par_symbole(int etat){
    int compte[] = new int[nbSymboles];
    for (std::vector<Transition>::const_iterator i = transitions.begin(); i != transitions.end(); ++i){
        if((*i).etatDepart == etat){
            compte[(*i).symbole-'a']++;
        }
    }

    return compte;
}

bool AF::est_deterministe(){
    bool resultat = true;
    if(nbEtatsInitiaux>1){
        std::cout << "L'automate a " << nbEtatsInitiaux << "\n";
        resultat = false;
    }
    int i,j;
    for(i=0; i<nbEtats;i++){
        int comptes[] = compter_transition_partant_d_etat_par_symbole(i);
        for(j=0; j<nbSymboles;j++){

        }
    }

}
