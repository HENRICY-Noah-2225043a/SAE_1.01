#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//vote alternatif

typedef vector<int> CVote;

struct candidat {
    string nom;
    unsigned id;
    CVote nbrVotes;
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

void afficherVector(const vector<CVote> & tab) {
    for (size_t i = 0; i < tab.size(); ++i){
        for (size_t j = 0; j < tab[i].size(); ++j){
            cout << tab[i][j] << ' ';
        }
        cout << endl;
    }
}

void afficherVectorCandidat(const vector<candidat> & tab) {
    for (size_t i = 0; i < tab.size(); ++i){
        cout << tab[i].id << ") " << tab[i].nom << " : ";
        for (const unsigned & chiffre : tab[i].nbrVotes) {
            cout << chiffre << ", ";
        }
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
                Candidat.id = numLigne - 3;
                listeCandidats.push_back(Candidat);
            }
            ++numLigne;
        }
    }

    // Initialisation des votes de listeCandidats
    for (int i = 0; i < listeCandidats.size(); ++i) {
        for (int j = 0; j < listeCandidats.size(); ++j) {
            listeCandidats[i].nbrVotes.push_back(0);
        }
    }
}

vector<CVote> transformationVote(const vector<votant> & listeVotants) {
    /**
     *  Recupere la liste des votes extrait du fichier de forme : "0 1 2 3 "
     *  Ou un chiffre represente la priorite d'un candidat pour le votant et la
     *  position du chiffre, l'id du candidat.
     *  Tranforme les votes en entier naturel et les ajoute dans un vecteur de forme {0, 1, 2, 3}.
     *  Chaques vecteurs de votes sont ajoutes dans un autre vecteur.
     */
    vector<CVote> listeVotes;
    CVote vote;
    for (size_t i = 0; i < listeVotants.size(); ++i){
        for (const char entier : listeVotants[i].vote) {
            if (!isspace(entier)) {
                vote.push_back(int(entier) - 48);
            }
        }
        listeVotes.push_back(vote);
        vote.clear();
    }
    return listeVotes;
}

void recalculeVote(vector<CVote> & listeVotes, const int & idPerdant) {
    /**
     *  Recupere la liste des votes et l'id du candidat perdant
     *  Redistribu les votes du candidats perdant aux autres candidats pour permettre
     *  de recalculer le perdant.
     */
    for (size_t i = 0; i < listeVotes.size(); ++i){ // parcours de la liste
        if (listeVotes[i][idPerdant] == 1) { // si le vote qui va etre supprimer est le plus prioritaire on augmente la priorite
            for (size_t j = 0; j < listeVotes[i].size(); ++j)
                --listeVotes[i][j];
        }
        else if (listeVotes[i].size() > 1) { // sinon on augmente les priorites inferieurs a la priorite du perdant
            for (size_t priorite = 2; priorite < listeVotes[i].size() + 1; ++priorite){
                if (listeVotes[i][idPerdant] == priorite) {
                    for (size_t j = 0; j < listeVotes[i].size(); ++j) {
                        if (listeVotes[i][idPerdant] < listeVotes[i][j])
                            --listeVotes[i][j];
                    }
                }
            }
        }
        listeVotes[i][idPerdant] = 0; // on "suprimme" le vote du candidat perdant en lui donnant la valeur 0
    }
}

void calculResultat(vector<candidat> & listeCandidats,const vector<CVote> & listeVotes, const int & nbrCandidats) {
    /**
     *  Signification vector vote en entre {1,2,3,0} : Le chiffre represente la priorite et sa position
     *  l'id du candidat.
     *
     *  Signification vector vote en sortie {21,30,29,34} : Le nombre represente le nombre de vote et sa position
     *  la priorite
     */

    // Reinitialisation des votes de listeCandidats
    for (int i = 0; i < listeCandidats.size(); ++i) {
        for (int j = 0; j < listeCandidats.size(); ++j) {
            listeCandidats[i].nbrVotes[j] = 0;
        }
    }

    // Calcul des votes de listeCandidats
    for (size_t i = 0; i < listeVotes.size(); ++i) { // parcours de la liste contenant les votes
        for (size_t j = 0; j < listeVotes[i].size(); ++j) { // parcours de chaques votes
            if (listeVotes[i][j] > 0) {
                ++listeCandidats[j].nbrVotes[listeVotes[i][j]-1]; // ajoute 1 vote a l'indice de la priorite "listeVotes[i][j]"-1 au candidat d'indice 'j'
                listeCandidats[j].id = j;              // ajoute l'id du candidat
            }
        }
    }
}

int calculPerdant(vector<candidat> & listeCandidats) {
    /**
     *  Calcule le candidat possedant le moins de vote et renvoie sont ID
     */
    int candidatMoinsVote = 0;
    for (size_t candidat = 0; candidat < listeCandidats.size(); ++candidat) {
        if (listeCandidats[candidat].nbrVotes[0] < listeCandidats[candidatMoinsVote].nbrVotes[0] and listeCandidats[candidat].nbrVotes[0] != 0)
            candidatMoinsVote = candidat; // Recupere l'id du candidat le moins vote, a chaque ordre de priorite
    }
    return candidatMoinsVote;
}

int calculGagnant(vector<candidat> & listeCandidats) {
    /**
     *  Calcule le candidat qui a gagne, c'est a dire, celui a qui il reste des
     *  vote.
     */
    for (size_t i = 0; i < listeCandidats.size(); ++i) {
        if (listeCandidats[i].id != 0)
            return listeCandidats[i].id;
    }
    return 0;
}

void afficherGagnant(vector<CVote> & listeVotes, vector<candidat> & listeCandidats) {
    /**
     * Prend en parametre la liste des votes et la liste des candidats, calcule le gagnant
     * et l'affiche.
     */
    calculResultat(listeCandidats, listeVotes, listeCandidats.size());
    int idPerdant = calculPerdant(listeCandidats);
    int idGagnant;
    size_t i = 1;
    bool majorite (false);
    while(i < listeCandidats.size() and !majorite) { // nombre de tour = nombre de candidats
        recalculeVote(listeVotes, idPerdant);
        calculResultat(listeCandidats, listeVotes, listeCandidats.size());
        for(const candidat & candidat : listeCandidats) {
            if (candidat.nbrVotes[0] > listeVotes.size() / 2) {
                idGagnant = candidat.id;
                majorite = true;
            }
        }
        if (i == listeCandidats.size() - 1)
            idGagnant = calculGagnant(listeCandidats);
        else
            idPerdant = calculPerdant(listeCandidats);
        ++i;
    }

    cout << "Le gagnant est " << listeCandidats[idGagnant].nom << " !!" << endl;
}

int main() {
    vector<candidat> listeCandidats;
    vector<votant> listeVotants;
    extractionVotant(listeVotants, listeCandidats);
    vector<CVote> listeVotes = transformationVote(listeVotants);
    afficherGagnant(listeVotes, listeCandidats);
    return 0;
}
