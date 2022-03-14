#include <iostream> 
#include <fstream>
#include <vector> 
#include <string>
#include <iterator>

using namespace std; 

const string FILENAME = "animals.txt";  


class Team{
    private:
        string teamName; 
        string region; 
        int seed;
        int wins = 0; 
        
    public: 
        Team(string name = "", string reg = "", int sed = 0) {
            teamName = name;
            region = reg; 
            seed = sed; 
        }
        string show(){ return teamName + " (" + region + " " + to_string(seed) + ") [" + to_string(wins) + " wins]"; }
        string showStats(){ return teamName + " (" + region +  " " + to_string(seed) + ") - " + to_string(wins) + " wins"; }
        friend bool operator<(Team const &ltm, Team const &rtm){ return ltm.teamName < rtm.teamName; }
        void addWin(){ wins++;}
        string getRegion() {return region;}

};


Team& getWinner(vector<Team>::iterator start, vector<Team>::iterator end){
    //if there is just two teams left return the winner
    if(start + 1 == end){
                
    Team * winner, *loser; 
    if(*start < *end){ winner = &*start; loser = &*end; }
    else{ winner = &*end; loser = &*start;}
    winner->addWin(); 
    cout << winner->show() << " defeats " << loser->show() << endl; 
    return *winner;
    } 
    
    //else split the list in two and get the winner of each side
    int half = (end - start) / 2; 
    Team one = getWinner(start, end - half - 1);
    Team two = getWinner(end - half, end);

    Team* winner,* loser; 
    if(one < two){ winner = &one; loser = &two; }
    else{ winner = &two; loser = &one;}
    winner->addWin(); 
    cout << winner->show() << " defeats " << loser->show() << endl; 

    return *winner;  
}

int main(){
    ifstream fin; 
    fin.open(FILENAME);
    vector<Team> teams; 
    
    //read in the all the teams from the file
    while(true)
    {
        string name, region; 
        int seed; 
        fin >> name; 
        if(name == "") break; 
        fin >> region; 
        fin >> seed; 
        teams.push_back(Team(name, region, seed)); 
    }
   cout << "------------\n" << "Tournament:\n" << "------------" << endl;
   
   auto temp = teams.begin(); 
   string region = temp->getRegion();
   Team winner =  getWinner(teams.begin(), teams.end() - 1);

   cout << "------------\n" << "Winner:\n" << "------------" << endl;
   cout << winner.show() << " is the winner!" << endl; 

    cout << "------------\n" << "Stats:\n" << "------------" << endl;

    for(Team tm : teams)
        cout << tm.showStats() << endl; 
}