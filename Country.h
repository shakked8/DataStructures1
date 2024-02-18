//
// Created by shakk on 16/02/2024.
//

#ifndef DATASTRUCTURES1_COUNTRY_H
#define DATASTRUCTURES1_COUNTRY_H


class Country
{

public:
    Country(int countryId, int medals, int numberOfTeams, int numberOfContestants) :
            m_countryId(countryId), m_medals(medals), m_numberOfTeams(numberOfTeams), m_numberOfContestants(numberOfContestants) {}

    int getNumberOfTeams() const
    {
        return m_numberOfTeams;
    }

    int getNumberOfContestants() const
    {
        return m_numberOfContestants;
    }

    int getMedals() const
    {
        return m_medals;
    }

    int getCountryId() const
    {
        return m_countryId;
    }

private:
    int m_countryId;
    int m_medals;
    int m_numberOfTeams;
    int m_numberOfContestants;
};


#endif //DATASTRUCTURES1_COUNTRY_H
