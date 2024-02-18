#include "Olympicsa1.h"
#include <stack>

Olympics::Olympics(){

}

Olympics::~Olympics()
{
    m_countryTree.deleteTree(m_countryTree.root());
    m_teamTree.deleteTree(m_teamTree.root());
    m_contestantTree.deleteTree(m_contestantTree.root());

}

StatusType Olympics::add_country(int countryId, int medals)
{

    if(countryId <= 0 || medals < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    if(m_countryTree.recursiveSearch(m_countryTree.root(), countryId) != nullptr)
    {
        return StatusType::FAILURE;
    }

    try
    {
        Country* country = new Country(countryId, medals, 0, 0);
        m_countryTree.insert(new Node<Country>(countryId, country));
        return StatusType::SUCCESS;
    }

    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_country(int countryId)
{

    if(countryId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Country>* countryNode = m_countryTree.recursiveSearch(m_countryTree.root(), countryId);

    if(countryNode == nullptr || countryNode->m_object->getNumberOfTeams() != 0 ||
       countryNode->m_object->getNumberOfContestants() != 0)
    {
        return StatusType::FAILURE;
    }

    try
    {
        m_countryTree.deleteNode(countryNode);
        return StatusType::SUCCESS;
    }
    catch (std::exception& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport)
{

    if(countryId <= 0 || teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Country>* countryNode = m_countryTree.recursiveSearch(m_countryTree.root(), countryId);

    if(m_teamTree.recursiveSearch(m_teamTree.root(), teamId) != nullptr || countryNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    try
    {
        Team* team = new Team(teamId, sport, 0, countryNode->m_object);
        m_teamTree.insert(new Node<Team>(teamId, team));
        return StatusType::SUCCESS;
    }

    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }

}

StatusType Olympics::remove_team(int teamId)
{

    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Team>* team = m_teamTree.recursiveSearch(m_teamTree.root(), teamId);
    if(team == nullptr || team->m_object->getNumberOfTeamContestants() != 0)
    {
        return StatusType::FAILURE;
    }

    try
    {
        m_teamTree.deleteNode(team);
        return StatusType::SUCCESS;
    }
    catch (std::exception& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength)
{

    if(contestantId <= 0 || countryId <= 0 || strength < 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Country>* countryNode = m_countryTree.recursiveSearch(m_countryTree.root(), countryId);

    if(m_contestantTree.recursiveSearch(m_contestantTree.root(), contestantId) != nullptr || countryNode == nullptr)
    {
        return StatusType::FAILURE;
    }

    try
    {
        Contestant* contestant = new Contestant(contestantId, strength, sport, 0, countryNode->m_object);
        m_contestantTree.insert(new Node<Contestant>(contestantId, contestant));
        return StatusType::SUCCESS;
    }

    catch (std::bad_alloc&)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::remove_contestant(int contestantId)
{

    if(contestantId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }

    Node<Contestant>* contestant = m_contestantTree.recursiveSearch(m_contestantTree.root(), contestantId);
    if(contestant == nullptr || contestant->m_object->getNumberOfTeams() != 0)
    {
        return StatusType::FAILURE;
    }

    try
    {
        m_contestantTree.deleteNode(contestant);
        return StatusType::SUCCESS;
    }
    catch (std::exception& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType Olympics::add_contestant_to_team(int teamId,int contestantId)
{
    Node<Contestant>* contestant = m_contestantTree.recursiveSearch(m_contestantTree.root(), contestantId);
    Node<Team>* team = m_teamTree.recursiveSearch(m_teamTree.root(), teamId);
    if(teamId<=0 || contestantId<=0){ return StatusType::INVALID_INPUT;}
    if(contestant->m_object->getCountry()->getCountryId() != team->m_object->getCountry()->getCountryId() ||
            contestant->m_object->getSport() != team->m_object->getSport() ||
            contestant->m_object->getNumberOfTeams()>=3){
        return StatusType::FAILURE;
    }
    try {
        Node<Contestant>* ContestantByStrength = new Node<Contestant>(contestant->m_object->getStrength(), contestant->m_object);
        Node<Contestant>* ContestantById = new Node<Contestant>(contestant->m_object->getContestantId(), contestant->m_object, ContestantByStrength);
        // now we will add the nodes to the tree with the least nodes:
        AVLTree<Contestant>* minTree = team->m_object->getMinTree();
        minTree->insert(ContestantById);
        team->m_object->insertNodeToStrength(ContestantById->strengthNode);

    }catch (...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}


StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId)
{
    if(teamId <=0 || contestantId<=0){
        return StatusType::INVALID_INPUT;
    }
    Node<Contestant>* contestantNode = m_contestantTree.findNode(contestantId);
    Node<Team>* teamNode = m_teamTree.findNode(teamId);
    if(contestantNode== nullptr || teamNode== nullptr ||
    !teamNode->m_object->isContestantInTeam(contestantNode->m_object)){
        return StatusType::FAILURE;
    }
    try{
        teamNode->m_object->deleteNodeFronStrength(contestantNode); // out of tree by strength
        teamNode->m_object->deleteNodeFronStrength(contestantNode); //out of tree by id
    }catch (...){
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}
//TODO finish this function
StatusType Olympics::update_contestant_strength(int contestantId ,int change)
{
    Node<Contestant>* contestantNode = m_contestantTree.findNode(contestantId);
    std::stack<Team> s;
    while(contestantNode->m_object->isTeamsEmpty()){
        Node<Team>* team = contestantNode->m_object->popTeam();
        team->m_object->deleteNodeFronStrength(contestantNode);
//        team->m_object->(contestantNode);
    }
    return StatusType::FAILURE;
}

output_t<int> Olympics::get_strength(int contestantId)
{

    if(contestantId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    Node<Contestant>* contestant = m_contestantTree.recursiveSearch(m_contestantTree.root(), contestantId);
    if(contestant == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(contestant->m_object->getStrength());

}

output_t<int> Olympics::get_medals(int countryId)
{

    if(countryId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    Node<Country>* country = m_countryTree.recursiveSearch(m_countryTree.root(), countryId);
    if(country == nullptr)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(country->m_object->getMedals());
}

output_t<int> Olympics::get_team_strength(int teamId)
{

    //TODO SHAKED
    return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2)
{

    //TODO TOGETHER

    return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2)
{
    //TODO TOGETHER

    return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId)
{
    //TODO TOGETHER

    return 0;
}



