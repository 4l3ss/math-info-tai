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
        int nbSymboles;
        int nbEtats;

        int nbEtatsInitiaux;
        std::vector<int> etatsInitiaux;

        int nbEtatsTerminaux;
        std::vector<int> etatsTerminaux;

        int nbTransitions;
        std::vector<Transition> transitions;

        AF(std::string);
        bool est_un_automate_asynchrone();
        bool est_un_automate_deterministe();
        bool est_un_automate_complet();
        void afficherInfos();
        int* compter_transition_partant_d_etat_par_symbole(int);
        void completion();
        void lire_mot();
        void reconnaitre_mot(std::string);
    private:
        std::vector<Transition> rechercher_transition(int, char);
        bool etat_est_terminal(int);
        bool mot_est_valide(const char*, int, bool);
};

#endif // AF_H
