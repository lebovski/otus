#include "../hw_11/src/interface.h"
#include "../hw_11/src/linked.hpp"
#include "../hw_11/src/sequence.hpp"

#include <gtest/gtest.h>

TEST(List, Empty)
{
    // Arrange
    Linked<int> list;

    // Act (empty for this test)

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(List, PushBack)
{
    // Arrange
    const size_t count = 10;
    Linked<size_t> list;

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.push_back(i);
    }

    // Assert
    ASSERT_EQ(list.size(), count);
    ASSERT_FALSE(list.empty());
}

TEST(List, AddStart)
{
    // Arrange
    const size_t count = 2;
    Linked<size_t> list;

    list.push_back(1);
    list.insert(0, 0);

    // Assert
    ASSERT_EQ(list.size(), count);
    ASSERT_FALSE(list.empty());
}

TEST(List, AddCenter)
{
    // Arrange
    const size_t count = 3;
    Linked<size_t> list;

    list.push_back(1);
    list.push_back(2);
    list.insert(list.size() / 2, 1234);

    // Assert
    ASSERT_EQ(list.size(), count);
    ASSERT_FALSE(list.empty());
}

TEST(List, PopBack)
{
    // Arrange
    const size_t count = 10;
    Linked<size_t> list;

    for (size_t i = 0; i < count; ++i)
    {
        list.push_back(i);
    }

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list.pop_back();
    }

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

// TEST(List, PopStart)
// {
//     // Arrange
//     const size_t count = 10;
//     Linked<size_t> list;

//     for (size_t i = 0; i < count; ++i)
//     {
//         list.push_back(i);
//     }

//     // Act
//     for (size_t i = 0; i < count; ++i)
//     {
//         list.erase(i);
//     }

//     // Assert
//     ASSERT_EQ(list.size(), 0);
//     ASSERT_TRUE(list.empty());
// }

// TEST(List, RemoveCenter)
// {
//     // Arrange
//     const size_t count = 2;
//     Linked<size_t> list;

//     list.push_back(1);
//     list.push_back(2);

//     size_t position = list.size() / 2;
//     list.insert(position, 1234);
//     // list.erase(position);

//     // Assert
//     ASSERT_EQ(list.size(), count);
//     ASSERT_FALSE(list.empty());
// }

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}