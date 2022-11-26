#include <iostream>
#include <vector>
#include <fstream>
using namespace std;



vector<unsigned> Voix_possible_a_0 (vector<string> & candidat){
    // Fonction ayant pour but de définir la quantité de vote possible par votant
    // par exemple, si il y a 5 candidat, les votants pourront voter 5 fois
    // et auront donc un vecteur {0;0;0;0;0}
    int q_vote_possible = 0;
    for(size_t i(0) ; i < candidat.size() ; ++i){
        q_vote_possible++;
    }
    vector<unsigned> vote(q_vote_possible);
    for(size_t i(0) ; i < vote.size(); ++i){
        vote[i] = 0;
    }
    return vote;
}

vector<vector<unsigned>> Q_Vote_Par_Votant (vector<string> & votant){
    // Fonction qui permet de définir la quantité de votant
    // Cette fonction renvoie un vecteur qui se liera avec Voix_Possible_a_0
    // Permet principalement de tranformer le vecteur votant en vecteur de vecteur
    int nbr_votant = 0;
    for(size_t i(0); i< votant.size(); ++i){
        nbr_votant++;
    }
    vector<vector<unsigned>> q_vote(nbr_votant);
    return q_vote;
}

vector<vector<unsigned>> Jointure_qvote_voixa0(vector<vector<unsigned>> & qvote,
                                               vector<unsigned> & vote){
    // Fonction faisant la jonction des fonction Q_vote_par_votant et Voix_possible_a_0
    // renvoie un vecteur de vecteur de la forme {{0;0;0;0;0},{0;0;0;0;0},...}
    // (Il y a une quantité de vecteur de vecteur équivalente à la quantité de votant
    for(size_t i(0); i< qvote.size(); ++i){
        qvote[i] = vote;
    }
    return qvote;
}


vector<unsigned> Voix_candidat(vector<string> & candidat,
                                       vector<vector<unsigned>> & vote){
    // Fonction créant un vecteur des votes totaux reçu dans l'ordre des candidats
    // exemple : {97,12, ...}
    vector<unsigned> vote_par_candidat(candidat.size());
    for(size_t i(0); i< candidat.size();++i){
        vote_par_candidat[i] = 0;
    }
    for(size_t i(0); i < candidat.size(); ++i){
        for(size_t j(0); j < vote.size(); ++j){
            vote_par_candidat[i] = vote_par_candidat[i] + vote[j][i];
        }
    }
    return vote_par_candidat;
}

vector<unsigned> Gagnant (vector<unsigned> & vote_par_candidat){
    // Fonction définissant et renvoyant le nom du gagnant et son nombre de vote,
    vector<unsigned> gagnant{0};
    unsigned num_candid = 0;
    for(size_t i(0); i< vote_par_candidat.size(); ++i){
        if (vote_par_candidat[i] > gagnant[0])
            gagnant[0] = vote_par_candidat[i];
            num_candid = i;
    }
    return num_candid, gagnant;
}

void extractionVote(vector<string> & votant, vector<vector<string>> &
                      vote) {
    ifstream txt ("votants.txt");
    bool passagevotant = false;
    int numligne = 0;
    string l;
    vector<string> tmp(1);
    while(passagevotant == false){
        ++numligne;
        getline(txt,l);
        tmp[0] = l;
        if(tmp[0] == "###"){
            passagevotant = true;
            break;

        }
        if(numligne%3 == 1 or numligne%3 == 2){
            votant.push_back(l);
        }
        else {
            vote.push_back(tmp);
        }
    }
}

void recupCandid(vector<string> candidat){
    ifstream txt ("votants.txt");
    bool passagevotant = false;
    int numligne = 0;
    int sautequestion = 0;
    string l;
    vector<string> tmp(1);
    for(string ligne;getline(txt,ligne);){
        //if (txt.fail()) exit(-1);
        ++numligne;
        tmp[0] = l;
        if(tmp[0] == "###"){
            passagevotant = true;
        }
        if(passagevotant){
            ++sautequestion;
            if(sautequestion>2){
                candidat.push_back(ligne);
            }
        }
    }
}

void affichVectorvect(const vector<vector<string>> & V){
    for(size_t i(0); i < V.size(); ++i){
        cout << V[i][0] << "\t";
    }
}

void affichVector(const vector<string> & V){
    for(size_t i(0); i < V.size(); ++i){
        cout << V[i] << "\t";
    }
}

void affichVectorU(const vector<int> & V){
    for(size_t i(0); i < V.size(); ++i){
        cout << V[i] << "\t";
    }
    cout << endl;
}

vector<int> comptevoixparcandidat(vector<string> candidat,vector<vector<string>> vote){
    vector<int> voteParCandid(0);
    for(size_t i(0); i<candidat.size();++i) voteParCandid.push_back(0);
    for(size_t i(0); i<vote.size();++i){
        unsigned mod = 0;
        for(size_t j(0);j<vote[i].size(); ++j){
            for(size_t k(0);k<vote[i][j].size();++k){
                if(vote[i][j][k] == '1'){
                    voteParCandid[mod] = voteParCandid[mod] + 1;
                    ++mod;
                }
                else{
                    if(vote[i][j][k] == '0'){
                        ++mod;
                    }
                }
            }
        }
    }
    return voteParCandid;
}

int main(){
    vector<string> candidat(0);
    vector<string> votant(0);
    vector<vector<unsigned>> vote(0);
    vector<vector<string>> voteinstring(0);
    recupCandid(candidat);
    affichVector(candidat);
    vector<unsigned>voixp = Voix_possible_a_0(candidat);
    extractionVote(votant,voteinstring);
    vector<int> voteTotaux = comptevoixparcandidat(candidat,voteinstring);
    return 0;
}
