#pragma once
#include <unordered_map>
#include <map>
#include <set>
class Leaderboard {
public:
    explicit Leaderboard() {};

    void addScore(int playerId, int score);

    int top(int k) ;

    void reset(int playerId);
private:
    std::unordered_map<int,int> m_table;
    std::multiset<int> m_scores;

};