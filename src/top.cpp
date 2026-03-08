#include "api.hpp"

int Leaderboard::top(int k) {
  int sumOfKFirstPlayers = 0; // we want from the end
  auto it = m_scores.rbegin();

  while (k > 0 && it != m_scores.rend()) {
    sumOfKFirstPlayers += *it;
    it++;
    k--;
  }
  return sumOfKFirstPlayers;
}
