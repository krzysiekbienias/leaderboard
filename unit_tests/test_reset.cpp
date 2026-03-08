#include "api.hpp"
#include <gtest/gtest.h>

TEST(LeaderboardResetTest, RemovesSinglePlayerFromLeaderboard) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);
  leaderboard.reset(1);

  EXPECT_EQ(leaderboard.top(1), 0);
}

TEST(LeaderboardResetTest, RemovesOnlyRequestedPlayer) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);
  leaderboard.addScore(2, 30);

  leaderboard.reset(1);

  EXPECT_EQ(leaderboard.top(1), 30);
}

TEST(LeaderboardResetTest, RemovesHighestPlayerAndPromotesNextOne) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 100);
  leaderboard.addScore(2, 70);
  leaderboard.addScore(3, 40);

  leaderboard.reset(1);

  EXPECT_EQ(leaderboard.top(1), 70);
}

TEST(LeaderboardResetTest, UpdatesTopKAfterRemovingOnePlayer) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 100);
  leaderboard.addScore(2, 80);
  leaderboard.addScore(3, 60);

  leaderboard.reset(2);

  EXPECT_EQ(leaderboard.top(2), 160); // 100 + 60
}

TEST(LeaderboardResetTest, ResetPlayerWithAccumulatedScoreRemovesWholeTotal) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);
  leaderboard.addScore(1, 25); // total = 75
  leaderboard.addScore(2, 40);

  leaderboard.reset(1);

  EXPECT_EQ(leaderboard.top(1), 40);
}

TEST(LeaderboardResetTest, ResetOnePlayerWhenMultiplePlayersShareSameScore) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 50);
  leaderboard.addScore(2, 50);
  leaderboard.addScore(3, 20);

  leaderboard.reset(1);

  EXPECT_EQ(leaderboard.top(2), 70); // remaining 50 + 20
}

TEST(LeaderboardResetTest, ResetMiddleScorePlayerKeepsOtherEqualScoresIntact) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 80);
  leaderboard.addScore(2, 50);
  leaderboard.addScore(3, 50);
  leaderboard.addScore(4, 10);

  leaderboard.reset(2);

  EXPECT_EQ(leaderboard.top(3), 140); // 80 + 50 + 10
}

TEST(LeaderboardResetTest, ResetThenAddSamePlayerAgainStartsFromFreshScore) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 60);
  leaderboard.reset(1);
  leaderboard.addScore(1, 15);

  EXPECT_EQ(leaderboard.top(1), 15);
}

TEST(LeaderboardResetTest, ResetOneOfManyPlayersDoesNotAffectOthers) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 90);
  leaderboard.addScore(2, 70);
  leaderboard.addScore(3, 50);
  leaderboard.addScore(4, 30);

  leaderboard.reset(3);

  EXPECT_EQ(leaderboard.top(3), 190); // 90 + 70 + 30
}

TEST(LeaderboardResetTest, ResetLastRemainingPlayerLeavesLeaderboardEmpty) {
  Leaderboard leaderboard;

  leaderboard.addScore(1, 42);
  leaderboard.reset(1);

  EXPECT_EQ(leaderboard.top(3), 0);
}