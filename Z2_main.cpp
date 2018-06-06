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
        AF automate(filename);
        automate.afficherInfos();
        bool testable = false;
        if(!automate.est_un_automate_asynchrone() && automate.est_un_automate_deterministe()){
            testable = true;
            if(!automate.est_un_automate_complet()){
                automate.completion();
            }
        }
        automate.afficherInfos();
        char choice;
        do{
            cout << "\n 1) Changer d'automate\n";
            if(testable){
                cout << " 2) Tester des mots sur cet automate\n";
            }
            cout << "choix > ";
            cin >> choice;

            switch(choice){
                case '2':
                    if(testable){
                        automate.lire_mot();
                    }
                break;
            }

        }
        while(choice != '1');

    }

    return 0;
}
