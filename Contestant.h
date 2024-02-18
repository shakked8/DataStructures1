#ifndef DATASTRUCTURES1_CONTESTANT_H
#define DATASTRUCTURES1_CONTESTANT_H
#include "wet1util.h"
#include "Country.h"
#include "Team.h" //TODO MAYBE CIRCLE INCLUDES?
#include <stack>

class Contestant
{
public:

    Contestant(int contestantId, int strength, Sport sport, int numberOfTeams, Country* country) :
            m_contestantId(contestantId), m_strength(strength), m_sport(sport), m_numberOfTeams(numberOfTeams), m_country(country){}

    int getNumberOfTeams() const
    {
        return m_numberOfTeams;
    }

    int getStrength() const
    {
        return m_strength;
    }

    Sport getSport() const {
        return m_sport;
    }


    Country *getCountry() const {
        return m_country;
    }

    int getContestantId() const {
        return m_contestantId;
    }

    bool isTeamsEmpty(){
        return teams.size()==0;
    }
    Node<Team>* popTeam(){
        Node<Team>* t= teams.top();
        teams.pop();
        return t;
    }
private:
    int m_contestantId;
    int m_strength;
    Sport m_sport;
    int m_numberOfTeams;
    std::stack<Node<Team>*> teams;
    Country* m_country;
};



#endif //DATASTRUCTURES1_CONTESTANT_H
