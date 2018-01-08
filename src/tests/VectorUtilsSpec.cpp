//
// Created by mcsim on 08.01.18.
//

// tests.cpp
#include "../VectorUtils.cpp"
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

TEST(VectorIntersactionTest, Positive) {
    sf::Vector2f p1(0,0);
    sf::Vector2f p2(1,0);
    sf::Vector2f p3(0.5,-1);
    sf::Vector2f p4(0.5,1);

    ASSERT_EQ(0.5, vectorIntersection(p1,p2,p3,p4));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}