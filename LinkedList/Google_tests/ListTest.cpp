#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <ostream>

class ListTest : public ::testing::Test {
protected:

    LinkedList<int> left;
    LinkedList<int> right;
    LinkedList<int> integerList; // 4 3 2 1 0

    void SetUp() override {
        for (int i = 0; i < 5; ++i) {
            left.pushFront(i);
        }
        right = left;
        integerList = left;
    }
};

int magicNumbers[] = {666, 13, 1488, 1337, 228};

std::string listToString (const LinkedList<int> &list) {
    if (list.isEmpty()) {
        return "";
    }
    std::string listString;
    for (auto item : list) {
        listString += std::to_string(item) + " ";
    }
    listString.pop_back();
    return listString;
}

TEST_F(ListTest, insertTest) {
    integerList.insert(++integerList.begin(), magicNumbers[0]); // insert element after head
    EXPECT_EQ(*(++integerList.begin()), magicNumbers[0]);

    integerList.insert(integerList.begin(), magicNumbers[1]); // insert element before head (to begin)
    EXPECT_EQ(*(integerList.begin()), magicNumbers[1]);

    EXPECT_EQ(listToString(integerList), "13 4 666 3 2 1 0");
}

TEST_F(ListTest, eraseTest) {
    integerList.erase(++integerList.begin());
    EXPECT_EQ(listToString(integerList), "4 2 1 0");

    integerList.erase(++integerList.begin());
    EXPECT_EQ(listToString(integerList), "4 1 0");
}

TEST_F(ListTest, eraseInRangeTest) {
    integerList.erase(++integerList.begin(), --integerList.end());
    EXPECT_EQ(listToString(integerList), "4 0");

    left.erase(left.begin(), left.end());
    EXPECT_EQ(listToString(left), "");

    right.erase(right.begin(), --right.end());
    EXPECT_EQ(listToString(right), "0");
}

TEST_F(ListTest, clearTest) {
    integerList.clear();
    EXPECT_EQ(integerList.isEmpty(), true);
    EXPECT_EQ(integerList.getSize(), 0);

    LinkedList<int> emptyList;
    left.clear();
    EXPECT_TRUE(left == emptyList);
}

TEST_F(ListTest, sizeTest){
    EXPECT_EQ(integerList.getSize(), 5);
    integerList.erase(integerList.begin(), ++integerList.begin()); // Deleting 1 element
    EXPECT_EQ(integerList.getSize(), 4);
}

TEST_F(ListTest, operatorEqualTest) {
    EXPECT_TRUE(left == right);
    left.popFront();
    EXPECT_FALSE(left == right);
}

TEST_F(ListTest, listConcatenationTest) {
    left += right;
    EXPECT_EQ(listToString(left), "4 3 2 1 0 4 3 2 1 0");
    EXPECT_EQ(listToString(right), "4 3 2 1 0");
}

TEST_F(ListTest, operatorPlusTest) {
    LinkedList<int> sumOfAllLists = left + right + integerList;
    EXPECT_EQ(listToString(sumOfAllLists), "4 3 2 1 0 4 3 2 1 0 4 3 2 1 0");
}