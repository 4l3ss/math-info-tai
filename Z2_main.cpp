#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>

#define PREFIX "Z2_"

#include "Z2_AF.h"

using namespace std;

bool fexists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}


string askFilename(){
    string filename = "Z2_none";
    do{
        cout << "Choisir un fichier test (seulement le numero) : ";
        int testNumber;
        cin >> testNumber;

        stringstream path;
        path << PREFIX << testNumber << ".txt";
        filename = path.str();
    }while(!fexists(filename));

    return filename;
}

int main()
{
    while(true){
        string filename = askFilename();
        cout << "Fichier choisi : " << filename << endl;
        AF automate;
        automate.charger_fichier(filename);
        automate.afficherInfos();

        bool est_complet = false;

        if(!automate.est_un_automate_asynchrone()){
            if(automate.est_un_automate_deterministe()){
                if(!automate.est_un_automate_complet()){
                    automate.completion();
                }
                est_complet = true;
            }
        }
        automate.afficherInfos();
        char choice;
        do{
            cout << "\n 1) Changer d'automate\n";
            cout << " 2) Tester des mots sur cet automate\n";
            if(est_complet){
                cout << " 3) Passer a l'automate complementaire\n";
            }
            cout << "\n 0) Quitter\n";

            cout << "choix > ";
            cin >> choice;

            switch(choice){
                case '2': automate.lire_mot(); break;
                case '3':
                    if(est_complet){
                        automate = automate.automate_complementaire();
                        automate.afficherInfos();
                    }
                break;
                case '0' : return 0;
            }

        }
        while(choice != '1');

    }

    return 0;
}
