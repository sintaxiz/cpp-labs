#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <ostream>

TEST(ListTest, output_test) {
    LinkedList<int> list1;
    for (int i = 1; i <= 100; ++i) {
        list1.push_front(i);
    }

    LinkedList<int> list2;
    for (int i = 1; i <= 100; ++i) {
        list1.push_back(i);
    }

    std::cout << list1 << std::endl;
    std::cout << list2 << std::endl;

}

TEST(ListTest, constructors_test){
    LinkedList<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    LinkedList<int> list2(list1);
    EXPECT_EQ(list1.getSize(), list2.getSize());

    LinkedList<int>::iterator it_for_l1 = list1.begin();
    LinkedList<int>::iterator it_for_l2 = list2.begin();

    EXPECT_EQ(*it_for_l1, *it_for_l2);
    EXPECT_FALSE(it_for_l1 == it_for_l2);
}

TEST(ListTest, example_test){

    LinkedList<int> myList;
    EXPECT_EQ(myList.getSize(), 0);
    myList.push_front(10);
    EXPECT_EQ(myList.getSize(), 1);
    myList.push_front(100);
    EXPECT_EQ(myList.getSize(),2);
    myList.push_front(1000);
    EXPECT_EQ(myList.getSize(), 3);


    LinkedList<int> anotherList;
    anotherList.push_front(5);
    EXPECT_EQ(anotherList.getSize(), 1);
    myList += anotherList;
    EXPECT_EQ(myList.getSize(), 4);

}

TEST(ListTest, iterator_test) {
    LinkedList<int> list1;
    for (int i = 1; i <= 100; ++i) {
        list1.push_front(i);
    }

    LinkedList<int> list2;
    for (int i = 1; i <= 100; ++i) {
        list2.push_back(i);
    }

    int k = 1;
    // префиксный ++
    for (LinkedList<int>::iterator it = list2.begin(); it != list2.end(); ++it) {
        EXPECT_EQ(*it, k);
        k++;
    }


    int j = 100;
    // префиксный ++
    for (LinkedList<int>::iterator it = list1.begin(); it != list1.end(); ++it) {
        EXPECT_EQ(*it, j);
        j--;
    }
    j = 100;
    // постфиксный ++
    for (LinkedList<int>::iterator it = list1.begin(); it != list1.end(); it++) {
        EXPECT_EQ(*it, j);
        j--;
    }

    j = 100;
    // range-based loop
    // TODO: глянуть как это работает
    for(int & item : list1) {
        EXPECT_EQ(item, j);
        j--;
    }
}

// один тест -- один метод