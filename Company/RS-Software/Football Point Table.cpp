/*
Question on Hackerearth: Football Point Table

Input File

(Sequence is : 
2 - total tournaments, 
name of tournament, 
no of teams participating, 
total number of matches played among the teams
each match event discription
eg. Brazil#2@1#Scotland means Brazil scored 2 goals and Scotland scored 1 goal playing against each other)

2
World Cup 1998 - Group  A
4
Brazil
Norway
Morocco
Scotland
6
Brazil#2@1#Scotland
Norway#2@2#Morocco
Scotland#1@1#Norway
Brazil#3@0#Morocco
Morocco#3@0#Scotland
Brazil#1@2#Norway
Some Strange Tournament
5
Team A
Team B
Team C
Team D
Team E
5
Team A#1@1#Team B
Team A#2@2#Team C
Team A#0@0#Team D
Team E#2@1#Team C
Team E#1@2#Team D


Output File

World Cup 1998 - Group  A
Brazil 6p, 3g (2-0-1), 3gd (6-3)
Norway 5p, 3g (1-2-0), 1gd (5-4)
Morocco 4p, 3g (1-1-1), 0gd (5-5)
Scotland 1p, 3g (0-1-2), -4gd (2-6)

Some Strange Tournament
Team D 4p, 2g (1-1-0), 1gd (2-1)
Team E 3p, 2g (1-0-1), 0gd (3-3)
Team A 3p, 3g (0-3-0), 0gd (3-3)
Team B 1p, 1g (0-1-0), 0gd (1-1)
Team C 1p, 2g (0-1-1), -1gd (3-4)


Algo:
1)First parse the input properly. Remember how to use getline after cin, flush the input buffer or use cin.ignore 
because after cin ,new line character would be left in buffer and geline will stop after reading it.
2)Create a map-node and an unordered_map and go on inserting/updating each team points, win or loss etc.
3)Copy it to a vector and sort them using your comparator function.Check out the comparator function.
4)Instead of vector we may use heap also.
5)String to integer , use stoi() and not atoi().

*/



#include <iostream>
#include <sstream>
#include <unordered_map>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

/*
struct heap_node{
    int a,b,c,d,e,f,g,h,i;
    char* name;
};
*/


struct map_node{
     int points;
     int goals_scored;
     int goals_against;
     int game_played;
     int no_wins;
     int no_tie;
};


void insert_map(unordered_map<string,struct map_node> &m, int g1, int g2, string s)
{
    struct map_node mn;//=new struct map_node;
    mn.goals_scored = g1;
    mn.goals_against = g2;
    mn.game_played =1;

    if( g1 > g2 )
    {
        mn.points =3;
        mn.no_wins =1;
    }

    else if( g1 < g2 )
    {
        mn.points =0;
        mn.no_wins =0;
    }
    else
    {

        mn.points =1;
        mn.no_wins =0;
        mn.no_tie= 1;
    }

    m.insert(make_pair(s, mn) );
    //return;
}

void update_map(unordered_map<string, struct map_node>::iterator &itr, int g1, int g2)
{
    itr->second.goals_scored += g1;
    itr->second.goals_against += g2;
    itr->second.game_played++;

    if( g1 > g2 )
    {
        itr->second.points +=3;
        itr->second.no_wins +=1;
    }

    else if( g1 < g2 )
    {
        itr->second.points +=0;
        itr->second.no_wins +=0;
    }
    else
    {

        itr->second.points +=1;
        itr->second.no_wins +=0;
        itr->second.no_tie +=1;
    }
    //return;
}

struct icompare_char {
  bool operator()(char c1, char c2) {
    return std::toupper(c1) < std::toupper(c2);
  }
};


bool mycomp(const pair<string,struct map_node>& a, const pair<string,struct map_node>& b) {
    //on basis of more number of points
    if(a.second.points > b.second.points)
        return true;
    if(a.second.points < b.second.points)
        return false;

    //on basis of more number of wins
    if(a.second.no_wins > b.second.no_wins)
        return true;
    if(a.second.no_wins < b.second.no_wins)
        return false;

    //on basis of more goal difference
    if( ( a.second.goals_scored - a.second.goals_against ) > ( b.second.goals_scored - b.second.goals_against ) )
        return true;
    if( ( a.second.goals_scored - a.second.goals_against ) < ( b.second.goals_scored - b.second.goals_against ) )
        return false;

    //on basis of more goals scored
    if(a.second.goals_scored > b.second.goals_scored)
        return true;
    if(a.second.goals_scored < b.second.goals_scored)
        return false;

    //on basis of less game played
    if(a.second.game_played < b.second.game_played)
        return true;
    if(a.second.game_played > b.second.game_played)
        return false;

    //else lexicographically
    return lexicographical_compare(a.first.begin(), a.first.end(),
                                   b.first.begin(), b.first.end(),
                                   icompare_char());


}


int main()
{
    int n;
    cin>>n;
    cin.ignore();

    int nog;
    string tourn[1001];
    string team[31];
    string match;
    unordered_map<string,struct map_node> mymap;
    int t;

    for(int i=0; i<n; i++)
    {
        getline(cin, tourn[i]);
        cout<<tourn[i]<<endl;
        cin>>t;
        cin.ignore();

        for(int j=0; j<t; j++)
        {
            getline(cin, team[j]);
        }

        cin>>nog;
        cin.ignore();

        for(int k=0; k < nog; k++)
        {
            getline(cin, match);

            int p=0;
            string tmp[2];
            string goal[2];
            int id=0;
            int l;


            for(l=0; l<match.length(); l++)
            {
                if(id == 0)
                {
                    if(match[l+1] == '#' )
                    {
                        tmp[id]= match.substr(p,l-p+1);
                        p=l+2;
                    }

                    if(match[l+1] == '@' )
                    {
                        goal[id]= match.substr(p,l-p+1);
                        p=l+2;

                        id++;
                    }
                }
                else
                {
                    if(match[l+1] == '#' )
                    {
                        goal[id]= match.substr(p,l-p+1);
                        p=l+2;
                    }
                }
            }

            l--;
            tmp[id] = match.substr(p,l-p+1);

            unordered_map<string, struct map_node>::iterator itr;
            int g1= stoi(goal[0]);
            int g2= stoi(goal[1]);

            itr=mymap.find(tmp[0]);
            if(itr != mymap.end())
            {
                update_map(itr, g1, g2);
            }
            else
            {
                insert_map(mymap,g1, g2, tmp[0]);
            }


            itr=mymap.find(tmp[1]);
            if(itr != mymap.end())
            {
                update_map(itr, g2, g1);
            }
            else
            {
                insert_map(mymap,g2, g1, tmp[1]);
            }
        }

        /*
        //map contents
        unordered_map<string, struct map_node>::iterator itr;
        for(itr= mymap.begin(); itr != mymap.end(); itr++)
        {
            cout<<(*itr).first<< " ";
            cout<<(*itr).second.points<<"p, ";
            cout<<(*itr).second.game_played<< "g ";
            cout<<"("<<(*itr).second.no_wins<< "-" <<(*itr).second.no_tie<<"-"<<( (*itr).second.game_played - ( (*itr).second.no_wins + (*itr).second.no_tie ) )<<"), ";
            cout<<( (*itr).second.goals_scored - (*itr).second.goals_against )<< "gd ";
            cout<<"("<< (*itr).second.goals_scored<< "-" <<(*itr).second.goals_against<<")";
            //cout<<(*itr).second.goals_against<< "(goal_ag)" <<endl;
            cout<<endl;
        }
        */


        //vector manipulation
        vector< pair<string,struct map_node> > myvec( mymap.begin(), mymap.end() );
        sort( myvec.begin(), myvec.end(), mycomp);

        //cout<<endl<<"vector content is "<<endl;
        vector< pair<string,struct map_node> >::iterator it;
        for(it= myvec.begin(); it!= myvec.end(); it++)
        {
            cout<<(*it).first<< " ";
            cout<<(*it).second.points<<"p, ";
            cout<<(*it).second.game_played<< "g ";
            cout<<"("<<(*it).second.no_wins<< "-" <<(*it).second.no_tie<<"-"<<( (*it).second.game_played - ( (*it).second.no_wins + (*it).second.no_tie ) )<<"), ";
            cout<<( (*it).second.goals_scored - (*it).second.goals_against )<< "gd ";
            cout<<"("<< (*it).second.goals_scored<< "-" <<(*it).second.goals_against<<")";
            //cout<<(*itr).second.goals_against<< "(goal_ag)" <<endl;
            cout<<endl;
        }

        cout<<endl;


        mymap.clear();


    }



    return 0;
}
