#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Votant {
  string nom;
  string prenom;
  bool negatif;
  unsigned vote_id;
};

struct Candidat {
  string nom;
  int nb_votes = 0;
};

void afficherVotants(vector<Votant> votant) {
  for (size_t i = 0; i < votant.size(); i++) {
    cout << votant[i].nom << " " << votant[i].prenom << endl;
  }
}

pair<vector<Votant>, vector<Candidat>>
extraire_votants_candidats_fichier_entrée() { // extrait les votants et les
                                              // candidats d'un
  // fichier contenant les candidats et les votants, dans le but de pouvoir en
  // faire un fichier d'entrée.
  pair<vector<Votant>, vector<Candidat>> liste_candidats_votants;
  vector<Votant> liste_Votants;
  Votant votant;
  vector<Candidat> liste_Candidats;
  Candidat candidat;
  size_t i = 0;
  size_t compteur = 0;
  for (string ligne; getline(cin, ligne);) {
    if (ligne.find('#') != -1) {
      candidat.nom = ligne;
      liste_Candidats.push_back(candidat);
      ++i;
    } else {
      if (cin.fail())
        break;
      if (compteur == 0) {
        votant.prenom = ligne;
      } else if (compteur % 2 != 0) {
        votant.nom = ligne;
        liste_Votants.push_back(votant);

      } else {
        votant.prenom = ligne;
      }
      ++compteur;
    }
  }
  liste_candidats_votants.first = liste_Votants;
  liste_candidats_votants.second = liste_Candidats;
  for (size_t i = 0; i < liste_candidats_votants.first.size(); i++) {
    liste_candidats_votants.first[i].vote_id =
        rand() % liste_candidats_votants.second.size();
    if ((rand() % 100) % 2 == 0) {
      liste_candidats_votants.first[i].negatif = true;
    } else {
      liste_candidats_votants.first[i].negatif = false;
    }
  }
  return liste_candidats_votants;
}

void creer_fichier_entree(
    const pair<vector<Votant>, vector<Candidat>>
        liste_candidat_votants) { // écrit un fichier d'entrée pour
  // le calcul des votes qui contiendra la liste des candidats ainsi que celle
  // des votants et de leur vote
  for (size_t i = 0; i < liste_candidat_votants.second.size(); i++) {
    cout << i << " ." << liste_candidat_votants.second[i].nom << endl;
  }
  for (size_t i = 0; i < liste_candidat_votants.first.size(); i++) {
    cout << liste_candidat_votants.first[i].nom << " "
         << liste_candidat_votants.first[i].prenom << endl
         << liste_candidat_votants.first[i].vote_id;
    if (liste_candidat_votants.first[i].negatif)
      cout << " "
           << "N";
    cout << endl;
  }
}

void calculer_et_afficher_Gagnant() {
  // Fonction calculant et affichant le gagnant du vote négatif ainsi que son nombre de votes.
  Candidat candidat;
  vector<Candidat> liste_Candidats;
  vector<int> votes;
  unsigned compteur = 0;
  for (string ligne; getline(cin, ligne);) {
    if (ligne.find('#') != -1) {
      candidat.nom = ligne;
      liste_Candidats.push_back(candidat);

    } else {
      if (compteur % 2 != 0) {
        if (ligne.find("N") != -1) {
          liste_Candidats.at(int(ligne[0]) - 48).nb_votes -= 1;

        } else {
          liste_Candidats.at(int(ligne[0]) - 48).nb_votes += 1;
        }
      }
    }
    ++compteur;
  }
  unsigned indice_gagnant;
  int votes_max = -9999;
  for (size_t i = 0; i < liste_Candidats.size(); ++i) {
    if (liste_Candidats.at(i).nb_votes > votes_max) {
      votes_max = liste_Candidats.at(i).nb_votes;
      indice_gagnant = i;
    }
  }
  cout << "Et le grand gagnant du vote négatif est: "
       << liste_Candidats.at(indice_gagnant).nom << " avec " << votes_max
       << " Votes!";
}

int main(int argc, char *argv[]) {
  // creer_fichier_entree(
  //   extraire_votants_candidats_fichier_entrée()); // crée intégralement le
  // fichier d'entrée avec la forme nécessaire à sa lecture par la fonction de
  // calcul du gagnant
  calculer_et_afficher_Gagnant();

  return 0;
}
