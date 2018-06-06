#ifndef AF_H
#define AF_H
#include <string>
#include <vector>

typedef struct Transition{
    int etatDepart;
    char symbole;
    int etatArrivee;
}Transition;

class AF
{

    public:
        AF();
        void charger_fichier(std::string);
        bool est_un_automate_asynchrone();
        bool est_un_automate_deterministe();
        bool est_un_automate_complet();
        void afficherInfos();
        void completion();
        void lire_mot();
        void reconnaitre_mot(std::string);
        AF automate_complementaire();

        int nbSymboles;
        int nbEtats;

        int nbEtatsInitiaux;
        std::vector<int> etatsInitiaux;

        int nbEtatsTerminaux;
        std::vector<int> etatsTerminaux;

        int nbTransitions;
        std::vector<Transition> transitions;

    private:
        std::vector<Transition> rechercher_transition(int, char);
        int* compter_transition_partant_d_etat_par_symbole(int);
        bool etat_est_terminal(int);
        bool mot_est_valide(const char*, int, bool);
        bool possede_etat_poubelle();
};

#endif // AF_H
