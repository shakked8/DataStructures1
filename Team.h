#ifndef DATASTRUCTURES1_TEAM_H
#define DATASTRUCTURES1_TEAM_H
#include "wet1util.h"
#include "Country.h"
#include "AVLTree.h"
#include "Contestant.h"


class Team
{
public:

    Team(int teamId, Sport sport, int numberOfTeamContestants, Country* country) :
            m_teamId(teamId), m_sport(sport), m_numberOfTeamContestants(numberOfTeamContestants), m_country(country)
            , tree1Size(0), tree2Size(0), tree3Size(0){}

    int getNumberOfTeamContestants() const
    {
        return m_numberOfTeamContestants;
    }

    Sport getSport() const {
        return m_sport;
    }



    Country *getCountry() const {
        return m_country;
    }

//    void insertTree1(Contestant* contestant);
//    void insertTree2(Contestant* contestant);
//    void insertTree3(Contestant* contestant);
//    void removeFromTree1(Contestant* contestant);
//    void removeFromTree2(Contestant* contestant);
//    void removeFromTree3(Contestant* contestant);
    void moveToRightTree(AVLTree<Contestant>* t1, AVLTree<Contestant>* t2);
//    Node<Contestant>* getNodeByStrength(Node<Contestant>* node);
//    Node<Contestant>* getNodeById(Node<Contestant>* node);
//    AVLTree<Contestant>* StrengthTree(AVLTree<Contestant>* t);
    bool isContestantInTeam(Contestant* contestant);
    void deleteNodeFronStrength(Node<Contestant>* node);
    void insertNodeToStrength(Node<Contestant> *node);
    AVLTree<Contestant>* getMinTree();

private:
    int m_teamId;
    Sport m_sport;
    int m_numberOfTeamContestants;
//    (Some kind of contestants holder)
    Country* m_country;
    AVLTree<Contestant> m_tree1;
    AVLTree<Contestant> m_tree2;
    AVLTree<Contestant> m_tree3;
    AVLTree<Contestant> m_tree1Strength;
    AVLTree<Contestant> m_tree2Strength;
    AVLTree<Contestant> m_tree3Strength;
    int tree1Size,tree2Size,tree3Size;
};



#endif //DATASTRUCTURES1_TEAM_H
