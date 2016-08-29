#pragma once

#include <string>
#include <vector>
#include <cmath>

class ELOPlayer
{
public:
    std::string name;
    
    int place;
    float eloPre;
    float eloPost;
    float eloChange;

};

class ELOMatch
{
public:
    std::vector<ELOPlayer> players;
    void addPlayer(std::string name, int place, float elo)
    {
        ELOPlayer player;
        
        player.name    = name;
        player.place   = place;
        player.eloPre  = elo;
	player.eloChange = 0.000f;
        
        players.push_back(player);
    }
/**
    int getELO(std::string name)
    {
        for (ELOPlayer& p : players)
        {
            if (p.name == name)
                return p.eloPost;
        }
        return 1500;
    }

    int getELOChange(std::string name)
    {
        for (ELOPlayer& p : players)
        {
            if (p.name == name)
                return p.eloChange;
        }
        return 0;
    }
**/
    void calculateELOs()
    {
        int n = int(players.size());
        
	float K = 106.000f/(n-1);

        for (int i = 0; i < n; i++)
        {
            int curPlace = players[i].place;
            int curELO   = players[i].eloPre;
            
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    
		    int opponentPlace = players[j].place;
                    int opponentELO   = players[j].eloPre;
                    /**
                    //work out S
                    float S;
                    if (curPlace > opponentPlace)
                        S = 1;
                    else if (curPlace == opponentPlace)
                        S = 0.5;
                    else
                        S = 0;
                    **/
		    float S = players[i].place/1.000f;
                    //work out EA
                    float EA = 1 / (1.000f + std::pow(10.000f, (opponentELO - curELO) / 400.000f));
                    
                    //calculate ELO change vs this one opponent, add it to our change bucket
                    //I currently round at this point, this keeps rounding changes symetrical between EA and EB, but changes K more than it should
                    players[i].eloChange += (K * (S - EA));
                }
            }
            //add accumulated change to initial ELO for final ELO   
            players[i].eloPost = players[i].eloPre + players[i].eloChange;
        }
    }
};
