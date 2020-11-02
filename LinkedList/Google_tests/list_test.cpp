#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <ostream>


// Достаточно покрыть несколько основных методов:
//insert, erase, clear, size, доступ по итератору
//Конструкторы и операторы =
//И оператор +=

TEST(ListTest, insert_test) {
    LinkedList<int> list1;
    for (int i = 1; i <= 100; ++i) {
        list1.push_front(i);
    }

    LinkedList<int> list2;
    for (int i = 1; i <= 100; ++i) {
        list1.push_back(i);
    }

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


TEST(ListTest, constructors_test){
    LinkedList<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    LinkedList<int> list2(list1);
    EXPECT_EQ(list1.getSize(), list2.getSize());

    LinkedList<int>::iterator it_for_l1 = list1.begin();
    LinkedList<int>::iterator it_for_l2 = list2.begin();

    EXPECT_EQ(*it_for_l1, *it_for_l2);
    EXPECT_FALSE(it_for_l1 == it_for_l2);
}

TEST(ListTest, operator_equal_test) {

}

TEST(ListTest, operator_plus_equal_test) {

}