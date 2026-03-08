#include <gtest/gtest.h>
#include "api.hpp"

TEST(LeaderboardTopTest, ReturnsHighestScoreWhenKIsOne) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 50);
    leaderboard.addScore(2, 20);
    leaderboard.addScore(3, 80);

    EXPECT_EQ(leaderboard.top(1), 80);
}

TEST(LeaderboardTopTest, ReturnsSumOfTopTwoScores) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 50);
    leaderboard.addScore(2, 20);
    leaderboard.addScore(3, 80);

    EXPECT_EQ(leaderboard.top(2), 130); // 80 + 50
}

TEST(LeaderboardTopTest, ReturnsSumOfAllScoresWhenKEqualsPlayerCount) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 40);
    leaderboard.addScore(2, 60);
    leaderboard.addScore(3, 10);

    EXPECT_EQ(leaderboard.top(3), 110);
}

TEST(LeaderboardTopTest, ReturnsSumOfAllScoresWhenKIsGreaterThanPlayerCount) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 40);
    leaderboard.addScore(2, 60);

    EXPECT_EQ(leaderboard.top(5), 100);
}

TEST(LeaderboardTopTest, ReturnsZeroForEmptyLeaderboard) {
    Leaderboard leaderboard;

    EXPECT_EQ(leaderboard.top(3), 0);
}

TEST(LeaderboardTopTest, ReturnsZeroWhenKIsZero) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 40);
    leaderboard.addScore(2, 60);

    EXPECT_EQ(leaderboard.top(0), 0);
}

TEST(LeaderboardTopTest, HandlesDuplicateScoresCorrectly) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 50);
    leaderboard.addScore(2, 50);
    leaderboard.addScore(3, 20);

    EXPECT_EQ(leaderboard.top(2), 100); // 50 + 50
}

TEST(LeaderboardTopTest, UsesUpdatedScoresAfterAddScoreOnExistingPlayer) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 30);
    leaderboard.addScore(2, 40);
    leaderboard.addScore(1, 50); // player 1 total becomes 80

    EXPECT_EQ(leaderboard.top(2), 120); // 80 + 40
}

TEST(LeaderboardTopTest, ReturnsCorrectSumWhenOnlyOnePlayerExists) {
    Leaderboard leaderboard;

    leaderboard.addScore(1, 77);

    EXPECT_EQ(leaderboard.top(1), 77);
}