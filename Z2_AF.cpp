#include "Z2_AF.h"
#include <iostream>
#include <fstream>
#include <algorithm>

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

    if(nbTransitions>0){
        std::cout << "\nListe des transitions : \n";
        for (std::vector<Transition>::const_iterator i = transitions.begin(); i != transitions.end(); ++i){
            std::cout << "(" << (*i).etatDepart << ")-" << (*i).symbole << "->(" << (char)((*i).etatArrivee == -1 ? 'p':(*i).etatArrivee+'0') << ")\n";
        }
    }


}

bool AF::est_un_automate_asynchrone(){
    std::cout << "\n Test asynchrone : \n";
    bool resultat = false;
    for (std::vector<Transition>::const_iterator i = transitions.begin(); i != transitions.end(); ++i){
        if((*i).symbole == '*'){
            resultat = true;
            std::cout << "(" << (*i).etatDepart << ")-" << (*i).symbole << "->(" << (*i).etatArrivee << ") est une transition epsilon\n";
        }

    }

    std::cout << "L'automate fini est " << (resultat ? "Asynchrone" : "Synchrone") << "\n\n";
    return resultat;
}

/**
 * Retourne un tableau qui associe à chaque symbole le nombre de transition partant de l'etat donné
 * 0=a,1=b,2=c ...etc
 **/
int* AF::compter_transition_partant_d_etat_par_symbole(int etat){
    int *compte;
    compte = new int[nbSymboles];
    int j;
    for(j=0;j<nbSymboles;j++){
        compte[j] = 0;
    }
    for (std::vector<Transition>::const_iterator i = transitions.begin(); i != transitions.end(); ++i){
        if((*i).etatDepart == etat && (*i).symbole != '*'){
            compte[(*i).symbole-'a']++;
        }
    }

    return compte;
}

bool AF::est_un_automate_deterministe(){
    bool resultat = true;
    if(nbEtatsInitiaux>1){
        std::cout << " * L'automate a " << nbEtatsInitiaux << " etats initiaux\n";
        resultat = false;
    }
    int i,j;
    for(i=0; i<nbEtats;i++){
        int *comptes = compter_transition_partant_d_etat_par_symbole(i);
        for(j=0; j<nbSymboles;j++){
            if(comptes[j] > 1){
                std::cout << " * L'etat " << i << " comporte " << comptes[j] << " transitions sortantes \"" << (char)('a'+j) << "\"\n";
                resultat = false;
            }
        }
    }
    std::cout << "L'automate fini est " << (resultat ? "deterministe" : "non-deterministe") << "\n";
    return resultat;

}

bool AF::est_un_automate_complet(){
    bool resultat = true;

    int i,j;
    for(i=0; i<nbEtats;i++){
        int *comptes = compter_transition_partant_d_etat_par_symbole(i);
        for(j=0; j<nbSymboles;j++){
            if(comptes[j] == 0){
                std::cout << " * L'etat " << i << " n'a pas de transition sortante \"" << (char)('a'+j) << "\"\n";
                resultat = false;
            }
        }
    }
    std::cout << "L'automate fini est " << (resultat ? "complet" : "pas complet") << "\n";
    return resultat;

}

void AF::completion(){
    int i,j;
    bool ajouter_poubelle = true;
    for(i=0; i<nbEtats;i++){
        int *comptes = compter_transition_partant_d_etat_par_symbole(i);
        for(j=0; j<nbSymboles;j++){
            if(comptes[j] == 0){
                std::cout << "   -> Ajout d'une transition vers l'etat poubelle " << i << (char)(j+'a') << "p\n";

                Transition transition;
                transition.etatDepart = i;
                transition.symbole = j+'a';
                transition.etatArrivee = -1;

                transitions.push_back(transition);

                nbTransitions++;
                if(ajouter_poubelle){
                    nbEtats++;
                    ajouter_poubelle = false;
                }
            }
        }
    }

    est_un_automate_complet();
}

void AF::lire_mot(){
    std::cin.ignore();
    std::cout << "Ecrivez des mots, entrez \"fin\" pour revenir au menu\n";
    while(1){
        std::cin.clear();
        std::string mot = "";
        getline(std::cin, mot);
        if(mot == "fin"){
            break;
        }

        reconnaitre_mot(mot);
    }
    std::cin.clear();

}

std::vector<Transition> AF::rechercher_transition(int etatDepart, char symbole){
    std::vector<Transition> liste;
    for (std::vector<Transition>::iterator i = transitions.begin(); i != transitions.end(); ++i){
        if((*i).etatDepart == etatDepart && ((*i).symbole == symbole || (*i).symbole == '*')){
            //return &*i;
            liste.push_back(*i);
        }
    }

    return liste;
}

bool AF::etat_est_terminal(int etat){
    return std::find(etatsTerminaux.begin(), etatsTerminaux.end(), etat) != etatsTerminaux.end();
}

bool AF::mot_est_valide(const char* mot, int etatActuel, bool debut){
    if(debut == true){
        //for each etat de depart
        for (std::vector<int>::iterator etatDepart = etatsInitiaux.begin(); etatDepart != etatsInitiaux.end(); ++etatDepart){
            if(this->mot_est_valide(mot, *etatDepart, false)){
                return true; //L'etat de depart choisi amene à une reonnaissance
            }
        }

        return false; //Aucune etat de départ ne conduit à une reconnaissance du mot

    }

    if(*mot == 0){ //On arrive à la fin du mot
        if(etat_est_terminal(etatActuel)){ /** TODO: Tester si une transition epsilon mene a un etat terminal **/
            return true; //Le mot est reconnu
        }else{
            return false; //Le mot n'est pas reconnu
        }
    }else{
        std::vector<Transition> transitions_possibles = rechercher_transition(etatActuel, *mot);
        for (std::vector<Transition>::iterator i = transitions_possibles.begin(); i != transitions_possibles.end(); ++i){
            if(mot_est_valide(i->symbole == '*' ? mot : (mot+1), i->etatArrivee, false)){
                return true;
            }
        }
        return false; //Aucune transition depuis l'etat actuel ne conduit à une reconnaissance du mot
    }
}
void AF::reconnaitre_mot(std::string mot){
    if(this->mot_est_valide(mot.c_str(), 0, true)){
        std::cout << "Le mot est reconnu\n";
    }else{
        std::cout << "Le mot n'est pas reconnu\n";
    }
   /* int etat = etatsInitiaux.front();
    int position_mot = 0;
    std::cout << etat;
    std::cout << "\n->("<<etat<<")-";
    while(mot[position_mot] != 0){
        if(mot[position_mot]<'a' || mot[position_mot]>'a'+nbSymboles){
            std::cout<< "Le symbole " << mot[position_mot] << " ne fait pas parti de l'alphabet\n";
            return;
        }
        Transition* chemin = rechercher_transition(etat, mot[position_mot]);
        if(chemin != 0){
            etat = chemin->etatArrivee;
        }else{
            break;
        }
        std::cout << mot[position_mot] << "->("<<(char)(etat == -1 ? 'p':(etat+'0'))<<")-";
        position_mot++;
    }

    if(mot[position_mot] != 0){
        std::cout << "\nLe mot n'est pas reconnu : Le mot n'est pas fini mais aucune transition n'accepte le symbole suivant\n";
    }else if(std::find(etatsTerminaux.begin(), etatsTerminaux.end(), etat) == etatsTerminaux.end()){
        std::cout << " \nLe mot n'est pas reconnu : l'etat " << (char)(etat == -1 ? 'p':(etat+'0')) << " n'est pas terminal\n";
    }else{
        //on est a un etat terminal
        std::cout << "\nLe mot est reconnu\n";
    }*/

}
