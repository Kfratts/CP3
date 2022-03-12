#include <iostream> 
#include <fstream>
#include <vector> 
#include <string>

using namespace std; 

const string FILENAME = "animals.txt";  

class Team{
    private:
        string teamName; 
        string region; 
        int seed;
        
    public: 
        Team(string name = "", string reg = "", int sed = 0) {
            teamName = name;
            region = reg; 
            seed = sed; 
        }

        string getName() const {return teamName;}
        string show(){ return this->teamName; }

        friend bool operator<(Team const &ltm, Team const &rtm){ return ltm.getName() < rtm.getName(); }

};


Team getWinner(vector<Team> &teams){
    if(teams.size() == 1){
        return teams[0];
    }

    //elminate players, effectively cutting list in half
    for(int i = 0; i < teams.size(); i = i + 2){
        int x = teams[i] < teams[i + 1] ? i + 1 : i; 
        teams.erase(teams.begin() + x); 
    }

    return getWinner(teams); 

}


int main(){

    ifstream fin; 
    fin.open(FILENAME); 
    vector<Team> teams;
    //read in the all the teams from the file
    while(!fin.eof())
    {
        string name, region; 
        int seed; 
        fin >> name; 
        fin >> region; 
        fin >> seed; 
        teams.push_back(Team(name, region, seed)); 
    }

    
   cout << "The winner is: " << getWinner(teams).show() << endl; 
}