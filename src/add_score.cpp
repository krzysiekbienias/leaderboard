#include "api.hpp"

void Leaderboard::addScore(int playerId, int score) {
  auto it = m_table.find(playerId);
  if (it == m_table.end()) {
    m_table[playerId] = score;
    m_scores.insert(score);
    return;
  }
  // when we need update scores in multiset (if player exists in the table)
  int oldScoresPerPlayer = it->second;

  // we are looking for points in scores multiset O(logn)
  auto scoreIt = m_scores.find(oldScoresPerPlayer);
  if (scoreIt != m_scores.end()) {
    m_scores.erase(scoreIt);
  }
  int updateScores = oldScoresPerPlayer + score;
  // insert updated values in map and multiset
  it->second = updateScores;
  m_scores.insert(updateScores);
}
