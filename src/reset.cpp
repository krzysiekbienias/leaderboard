#include "api.hpp"

void Leaderboard::reset(int playerId) {
  auto it = m_table.find(playerId);

  int scoresPerPlayer = 0;
  if (it != m_table.end()) {
    scoresPerPlayer = it->second;
    m_table.erase(playerId);
  }
  auto scoreIt = m_scores.find(scoresPerPlayer);
  if (scoreIt != m_scores.end()) {
    m_scores.erase(scoreIt); //not erase value because if there are duplicates will disappear both
  }
}
