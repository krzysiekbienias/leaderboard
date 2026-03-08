#include "api.hpp"
#include <gtest/gtest.h>

TEST(LeaderboardAddScoreTest, AddsSingleNewPlayer) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);

  EXPECT_EQ(leaderboard.top(1), 50);
}

TEST(LeaderboardAddScoreTest, AddsMultipleDifferentPlayers) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);
  leaderboard.addScore(2, 30);
  leaderboard.addScore(3, 20);

  EXPECT_EQ(leaderboard.top(1), 50);
  EXPECT_EQ(leaderboard.top(2), 80);
  EXPECT_EQ(leaderboard.top(3), 100);
}

TEST(LeaderboardAddScoreTest, AccumulatesScoreForExistingPlayer) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);
  leaderboard.addScore(1, 25);

  EXPECT_EQ(leaderboard.top(1), 75);
}

TEST(LeaderboardAddScoreTest, AccumulatesScoreForExistingPlayerAmongOthers) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 40);
  leaderboard.addScore(2, 60);
  leaderboard.addScore(1, 30);

  EXPECT_EQ(leaderboard.top(1), 70);
  EXPECT_EQ(leaderboard.top(2), 130);
}

TEST(LeaderboardAddScoreTest, HandlesZeroScoreAdditionForNewPlayer) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 0);

  EXPECT_EQ(leaderboard.top(1), 0);
}

TEST(LeaderboardAddScoreTest, HandlesZeroScoreAdditionForExistingPlayer) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 25);
  leaderboard.addScore(1, 0);

  EXPECT_EQ(leaderboard.top(1), 25);
}

TEST(LeaderboardAddScoreTest, UpdatesRankingAfterExistingPlayerImprovesScore) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 20);
  leaderboard.addScore(2, 50);
  leaderboard.addScore(1, 40); // player 1 becomes 60

  EXPECT_EQ(leaderboard.top(1), 60);
  EXPECT_EQ(leaderboard.top(2), 110);
}

TEST(LeaderboardAddScoreTest, TopUsesUpdatedScoresAfterMultipleAdds) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 10);
  leaderboard.addScore(2, 20);
  leaderboard.addScore(3, 30);
  leaderboard.addScore(2, 15); // 35
  leaderboard.addScore(1, 50); // 60

  EXPECT_EQ(leaderboard.top(1), 60);
  EXPECT_EQ(leaderboard.top(2), 95);  // 60 + 35
  EXPECT_EQ(leaderboard.top(3), 125); // 60 + 35 + 30
}