#include <iostream> 
#include <fstream>
#include <vector> 
#include <string>
#include <iterator>
#include <cmath>

using namespace std; 


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


vector<Team>::iterator getWinner(vector<Team>::iterator &start, vector<Team>::iterator &end){
    //if there is just two teams left return the winner
    if(start + 1 == end){

    vector<Team>::iterator winner, loser;              
    if(*start < *end){ winner = start; loser = end; }
    else{ winner = end; loser = start;}
    winner->addWin(); 
    cout << winner->show() << " defeats " << loser->show() << endl; 
    return winner;
    } 
    
    //else split the list in two and get the winner of each side
    int half = (end - start) / 2; 
    auto mid1 = end - half; 
    auto mid2 = end - half - 1; 

    auto one = getWinner(start, mid2);
    auto two = getWinner(mid1, end);


    vector<Team>::iterator winner, loser;              
    if(*one < *two){ 
        winner = one; loser = two; 
        }
    else{ 
        winner = two; loser = one;
        }
    winner->addWin(); 
    cout << winner->show() << " defeats " << loser->show() << endl; 

    return winner;  
}

int main(int argc, char *argv[]){
    ifstream fin; 
    
    if(argc < 2){
        cout << "Missing command line argument (input filename)" << endl;
        return 0;
    } 

    const string FILENAME = argv[1]; 
    
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

    int n = teams.size(); 
    if(ceil(log2(n)) != floor(log2(n))){
        cout << "\nFile must include a number of teams that is a power of 2" << endl; 
        cout << "(There are " << n << " teams in file " << FILENAME << ")" << endl; 
        return 0; 
    }


   cout << "------------\n" << "Tournament: \n" << "------------" << endl;
   
   auto start = teams.begin(); 
   auto last = teams.end() - 1; 
   string region = start->getRegion();
   auto winner =  getWinner(start, last);

   cout << "------------\n" << "Winner: \n" << "------------" << endl;
   cout << winner->show() << " is the winner!" << endl; 

    cout << "------------\n" << "Stats: \n" << "------------" << endl;

    for(auto it = teams.begin(); it != teams.end(); it++ )
        cout << it->showStats() << endl; 
}