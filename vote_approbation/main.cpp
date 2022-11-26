#include <iostream>
#include <vector>
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

void extractionVote(vector<string> & votant, vector<vector<string>> &
                      vote, vector<string> & candidat) {
    bool passagevotant = false;
    int numligne = 0;
    string l;
    vector<string> tmp(1);
    while(passagevotant == false){
        ++numligne;
        getline(cin,l);
        //if(cin.fail()) exit(-2);
        tmp[0] = l;
        if(tmp[0] == "###"){
            passagevotant = true;
            int numligne2 = 0;
            for(string ligne;getline(cin,ligne);){
                //if (cin.fail()) exit(-1);
                tmp[0] = ligne;
                if(tmp[0] == "###"){
                    passagevotant = true;
                }
                if(passagevotant){
                    ++numligne2;
                    if(numligne2 > 1){
                        candidat.push_back(ligne);
                        //cout << candidat[numligne - 1];
                    }
                }
            }
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

/**vector<string> recupCandid(vector<string> candidat){
    bool passagevotant = false;
    size_t numligne = 0;
    string l;
    vector<string> tmp(1);
    for(string ligne;getline(cin,ligne);){
        //if (cin.fail()) exit(-1);
        tmp[0] = ligne;
        if(tmp[0] == "###"){
            passagevotant = true;
        }
        if(passagevotant){
            ++numligne;
            if(numligne > 2){
                candidat.push_back(ligne);
                //cout << candidat[numligne - 1];
            }
        }
    }
    return candidat;
}
*/
void affichVectorvect(const vector<vector<string>> & V){
    for(size_t i(0); i < V.size(); ++i){
        cout << V[i][0] << "\t";
    }
}

void affichVector(const vector<string> & V){
    for(size_t i(0); i < V.size(); ++i){
        cout << V[i] << "\n";
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

void affichClassement(vector<int> & voteTotaux, vector<string> & candidat){
    for(size_t i(0); i<candidat.size(); i++){
        cout << candidat[i] << "  " << voteTotaux[i] << endl;
    }
}

void affichGagnant(vector<int> & voteTotaux, vector<string> & candidat){
    int winner = 0;
    for(size_t i(0); i<candidat.size(); i++){
        if(voteTotaux[winner] < voteTotaux[i]) winner = i;
    }
    cout << "Le gagnant est " << candidat[winner] << " avec "
         << voteTotaux[winner] << " voix. \n";
}

int main(){
    vector<string> candidat (0);
    vector<string> votant(0);
    vector<vector<unsigned>> vote(0);
    vector<vector<string>> voteinstring(0);
    extractionVote(votant,voteinstring,candidat);
    vector<int> voteTotaux = comptevoixparcandidat(candidat,voteinstring);
    affichGagnant(voteTotaux, candidat);
    return 0;
}
