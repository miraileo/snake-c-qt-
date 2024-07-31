#include <gtest/gtest.h>
#include "../brick_game/snake/snakeModel/snakemodel.cpp"

using namespace s21;

// Test Fixture for SnakeModel
class SnakeModelTest : public ::testing::Test {
protected:
    SnakeModel* snakeModel;

    void SetUp() override {
        snakeModel = new SnakeModel();
    }

    void TearDown() override {
        delete snakeModel;
    }
};

TEST_F(SnakeModelTest, SnakeMove) {
    snakeModel->snakeMove(); 
    snakeModel->snakeMove();// Move right first
    EXPECT_EQ(snakeModel->getSnakeBody().front()->getX(), 5);
    EXPECT_EQ(snakeModel->getSnakeBody().front()->getY(), 0);
}

// // Test the SnakeCollision function
TEST_F(SnakeModelTest, SnakeCollisionWithWall) {
    for (int i = 0; i < 10; ++i) {
        snakeModel->snakeMove(); // Move up until collision
    }
    EXPECT_TRUE(snakeModel->SnakeCollision());
}

// Test the eatApple function
TEST_F(SnakeModelTest, EatApple) {
    Apple apple(4, 0); 
    snakeModel->snakeMove();
    snakeModel->eatApple(&apple);
    EXPECT_EQ(apple.getNumOfApples(), 1);
    EXPECT_EQ(snakeModel->getSnakeBody().size(), 5); 
}

// Test Fixture for Apple
class AppleTest : public ::testing::Test {
protected:
    Apple* apple;

    void SetUp() override {
        apple = new Apple(5, 10);
    }

    void TearDown() override {
        delete apple;
    }
};

// Test the SpawnApple function
TEST_F(AppleTest, SpawnApple) {
    int originalX = apple->getX();
    int originalY = apple->getY();
    apple->SpawnApple();
    EXPECT_NE(originalX, apple->getX());
    EXPECT_NE(originalY, apple->getY());
}

// Test Fixture for Level
class LevelTest : public ::testing::Test {
protected:
    Level* level;

    void SetUp() override {
        level = new Level();
    }

    void TearDown() override {
        delete level;
    }
};

// Test the countScore function
TEST_F(LevelTest, CountScore) {
    Apple apple(0, 0);
    apple.setNumOfApples(3);
    level->countScore(&apple);
    EXPECT_EQ(level->getScore(), 3); // Check if score is set correctly
}

// Test the countLevel function
TEST_F(LevelTest, CountLevel) {
    Apple apple(0, 0);
    apple.setNumOfApples(10); // Score is 10
    level->countScore(&apple);
    EXPECT_TRUE(level->countLevel()); // Level should increase
    EXPECT_EQ(level->getLevel(), 2); // Level should be 2
}

// Test the winGame function
TEST_F(LevelTest, WinGame) {
    level->setScore(196); // Set max score to 200
    EXPECT_TRUE(level->winGame()); // Should return true
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}