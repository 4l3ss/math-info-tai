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
        void ajouterTransition();
        void afficherInfos();
};

#endif // AF_H
