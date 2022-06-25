#include "../hw_11/src/interface.h"
#include "../hw_11/src/linked.hpp"
#include "../hw_11/src/sequence.hpp"

#include <gtest/gtest.h>

void run_test(void (*body)(IContainer<int> *list))
{
    IContainer<int> *containers[2];

    containers[0] = new Linked<int>{};
    containers[1] = new Sequence<int>{};

    for (int i = 0; i < 2; i++)
    {
        body(containers[i]);
    }
}

TEST(List, Empty)
{
    run_test([](IContainer<int> *list)
             {
        ASSERT_EQ(list->size(), 0);
        ASSERT_TRUE(list->empty()); });
}

TEST(List, PushBack)
{
    run_test([](IContainer<int> *list)
             {
    const size_t count = 10;

    for (size_t i = 0; i < count; ++i)
    {
        list->push_back(i);
    }

    ASSERT_EQ(list->size(), count);
    ASSERT_FALSE(list->empty()); });
}

TEST(List, AddStart)
{
    run_test([](IContainer<int> *list)
             {
    const size_t count = 2;

    list->push_back(1);
    list->insert(0, 0);

    ASSERT_EQ(list->size(), count);
    ASSERT_FALSE(list->empty()); });
}

TEST(List, AddCenter)
{
    run_test([](IContainer<int> *list)
             {
    const size_t count = 3;

    list->push_back(1);
    list->push_back(2);
    list->insert(list->size() / 2, 1234);

    // Assert
    ASSERT_EQ(list->size(), count);
    ASSERT_FALSE(list->empty()); });
}

TEST(List, PopBack)
{
    run_test([](IContainer<int> *list)
             {
    const size_t count = 10;

    for (size_t i = 0; i < count; ++i)
    {
        list->push_back(i);
    }

    // Act
    for (size_t i = 0; i < count; ++i)
    {
        list->pop_back();
    }

    // Assert
    ASSERT_EQ(list->size(), 0);
    ASSERT_TRUE(list->empty()); });
}

TEST(List, PopStart)
{
    // run_test([](IContainer<int> *list) {});
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
        list.erase(1);
    }

    // Assert
    ASSERT_EQ(list.size(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(List, RemoveCenter)
{
    // run_test([](IContainer<int> *list) {});
    // Arrange
    const size_t count = 2;
    Linked<size_t> list;

    list.push_back(1);
    list.push_back(2);

    size_t position = list.size() / 2;
    list.insert(position, 1234);
    list.erase(position);

    // Assert
    ASSERT_EQ(list.size(), count);
    ASSERT_FALSE(list.empty());
}

TEST(List, GetVal)
{
    // run_test([](IContainer<int> *list) {});
    const size_t val = 1;
    Linked<size_t> list;

    list.push_back(val);

    ASSERT_EQ(list[0], val);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}