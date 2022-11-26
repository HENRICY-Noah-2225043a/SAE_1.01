#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//vote blanc

struct candidat {
    string nom;
    unsigned id;
    unsigned nbrVotes;
};

struct votant {
    string nom;
    string prenom;
    string vote;
};

void afficherVectorVotant(const vector<votant> & tab) {
    for (size_t i = 0; i < tab.size(); ++i){
        cout << tab[i].nom << tab[i].prenom << endl
             << tab[i].vote << endl;
    }
}

void afficherVectorCandidat(const vector<candidat> & tab) {
    for (size_t i = 0; i < tab.size(); ++i){
        cout << tab[i].id << ") " << tab[i].nom << " : " << tab[i].nbrVotes;
        cout << endl;
    }
}

void extractionVotant(vector<votant> & listeVotants, vector<candidat> & listeCandidats) {
    /**
     *  Extrait les informations du fichier texte et ajoute les donnees de chaques votants
     *  (nom, prenom, vote) dans un struct eux memes dans un vecteur.
     *  Liste egalement les candidats et leur ajoute un ID.
     */
    votant Votant;
    vector<unsigned> Vote;
    candidat Candidat;
    Candidat.nom = "Blanc";
    Candidat.id = 0;
    Candidat.nbrVotes = 0;
    listeCandidats.push_back(Candidat);
    unsigned numLigne = 1;
    bool passageVotantCandidat = false;
    for (string ligne; getline(cin, ligne);) { // parcours le fichier
        if (ligne == "###")
            passageVotantCandidat = true;
        if (cin.fail()) break;
        if (!passageVotantCandidat) { // liste les votants
            if (numLigne == 1) {
                Votant.nom = ligne;
            }
            else if (numLigne == 2) {
                Votant.prenom = ligne;
            }

            else {
                Votant.vote = ligne;
                listeVotants.push_back(Votant);
                numLigne = 0;
            }
            ++numLigne;
        }
        else { // liste les candidats
            if (numLigne > 2) {
                Candidat.nom = ligne;
                Candidat.id = numLigne - 2;
                listeCandidats.push_back(Candidat);
            }
            ++numLigne;
        }
    }
}

void ajoutNbrVotesCandidats(vector<candidat> & listeCandidats, const vector<votant> & listeVotants) {
    /**
     * parcours la liste de votants puis la liste de candidats
     * Si le vote est egal a l'id du candidat
     * on ajoute 1 au nombre de vote du candidats
     */
    for (size_t i = 0; i < listeVotants.size(); ++i) {
        for (size_t j = 0; j < listeCandidats.size(); ++j) {
            if (unsigned(listeVotants[i].vote[0] - 48) == listeCandidats[j].id)
                ++listeCandidats[j].nbrVotes;
        }
    }
}

void afficherGagnant(vector<candidat> & listeCandidats) {
    unsigned idGagnant (1);
    for (size_t i = 2; i < listeCandidats.size(); ++i) {
        if (listeCandidats[i].nbrVotes > listeCandidats[idGagnant].nbrVotes)
            idGagnant = i;
    }

    // verification si il n'y a pas d'egalite
    for (size_t i = 1; i < listeCandidats.size(); ++i) {
        if (idGagnant != i and listeCandidats[idGagnant].nbrVotes == listeCandidats[i].nbrVotes ){
            cout << "Il y a une égalité, refaire les votes." << endl;
            exit(-1);
        }
    }
    cout << "Le gagnant est " << listeCandidats[idGagnant].nom << " !!" << endl;

}

int main() {
    vector<candidat> listeCandidats;
    vector<votant> listeVotants;
    extractionVotant(listeVotants, listeCandidats);
    ajoutNbrVotesCandidats(listeCandidats, listeVotants);
    afficherGagnant(listeCandidats);
    return 0;
}
