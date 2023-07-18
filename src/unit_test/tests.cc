#include <gtest/gtest.h>

#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>

#include "../s21_containers.h"

/* ------------------------ LIST -------------------------- */

template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = true;
  if (my_list.size() == std_list.size()) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size(); ++i) {
      if (*my_it != *std_it) {
        result = false;
        break;
      }
      my_it++;
      std_it++;
    }
  } else {
    result = false;
  }
  return result;
}

TEST(ListTest, CompareLists) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  EXPECT_TRUE(compare_lists(my_list, std_list));
  std_list.push_back(6);
  EXPECT_FALSE(compare_lists(my_list, std_list));
  std_list.pop_back();
  my_list.push_front(0);
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, DefaultConstructor) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), 0);
  EXPECT_TRUE(my_list.empty());

  EXPECT_TRUE(compare_lists(my_list, std_list));
};

TEST(ListTest, SizeConstructor) {
  s21::list<int> my_list(1000000);
  std::list<int> std_list(1000000);
  EXPECT_EQ(my_list.size(), 1000000);
  EXPECT_TRUE(compare_lists(my_list, std_list));
};

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> my_list{1, 2, 3, 7, 9};
  std::list<int> std_list{1, 2, 3, 7, 9};
  EXPECT_TRUE(compare_lists(my_list, std_list));
};

TEST(ListTest, InitializerListConstructor_2) {
  std::initializer_list<int> b;
  s21::list<int> my_list{b};
  std::list<int> std_list{b};
  EXPECT_TRUE(compare_lists(my_list, std_list));
};

TEST(ListTest, CopyConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
};

TEST(ListTest, CopyConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
};

TEST(ListTest, MoveConstructor) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, MoveAssignmentOperatorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
}

TEST(ListTest, Front) {
  s21::list<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListTest, Back) {
  s21::list<int> my_list{1, 2, 3, 4, 99};
  std::list<int> std_list{1, 2, 3, 4, 99};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListTest, Empty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.empty(), std_list.empty());
  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListTest, Size) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, SizeEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListTest, Clear) {
  s21::list<int> my_list{1, 2, 3, 4};
  my_list.clear();
  std::list<int> std_list{1, 2, 5, 4, 3};
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, ClearEmpty) {
  s21::list<int> my_list;
  my_list.clear();
  std::list<int> std_list;
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_back(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopBack) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_back();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PushFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_front(0);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_front(0);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, PopFront) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Swap) {
  s21::list<int> my_list1{1, 2, 3, 4, 5};
  s21::list<int> my_list2{6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 2, 3, 4, 5};
  std::list<int> std_list2{6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, Swap_2) {
  s21::list<int> my_list1{1, 5, 8, 100};
  s21::list<int> my_list2;
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 5, 8, 100};
  std::list<int> std_list2;
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}
//
TEST(ListTest, begin_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_2) {
  s21::list<int> my_list1(4);

  std::list<int> std_list2(4);
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, begin_3_throw) {
  s21::list<int> my_list1;
  std::list<int> std_list2;

  EXPECT_EQ(*my_list1.begin(), 0);
}
//
TEST(ListTest, end_1) {
  s21::list<int> my_list1{500, 15000, 30000};

  std::list<int> std_list2{500, 15000, 30000};
  EXPECT_EQ(*my_list1.begin(), *std_list2.begin());
}

TEST(ListTest, end_2) {
  s21::list<int> my_list1(4);

  std::list<int> std_list2(4);
  EXPECT_EQ(*my_list1.end(), *std_list2.end());
}
//
TEST(ListTest, end_3) {
  s21::list<int> my_list1;

  std::list<int> std_list2;
  EXPECT_EQ(*my_list1.end(), *std_list2.end());
}
//
TEST(ListTest, Merge_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_3) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_5) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Merge_6) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Reverse_1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Reverse_3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_1) {
  s21::list<int> my_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  std::list<int> std_list{90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_2) {
  s21::list<int> my_list(3);
  std::list<int> std_list(3);
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Unique_3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, Splice_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Splice_2) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_3) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Splice_4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Insert_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Insert_2) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Insert_3) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Insert_4) {
  s21::list<int> my_list1;
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1;
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Insert_5) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.begin(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
//
TEST(ListTest, Insert_6) {
  s21::list<int> my_list1(4);
  my_list1.insert(my_list1.end(), 5);

  std::list<int> std_list1(4);
  std_list1.insert(std_list1.end(), 5);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}
TEST(ListTest, Erase_1) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(my_list1.begin());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.begin());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_3) {
  s21::list<int> my_list1{1, 9999, 20000};
  my_list1.erase(--my_list1.end());

  std::list<int> std_list1{1, 9999, 20000};
  std_list1.erase(std_list1.end().operator--());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListTest, Erase_5) {
  s21::list<int> my_list1(5);
  my_list1.erase(--my_list1.end());

  std::list<int> std_list1(5);
  std_list1.erase(std_list1.end().operator--());

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

/* ------------------------- VECTOR --------------------------- */

TEST(VectorTest, constructor_default_size) {
  s21::Vector<char> test_vector;
  std::vector<char> std_test_vector;
  EXPECT_EQ(std_test_vector.size(), test_vector.size());
}

TEST(VectorTest, constructor_default_capacity) {
  s21::Vector<char> test_vector;
  std::vector<char> std_test_vector;
  EXPECT_EQ(std_test_vector.capacity(), test_vector.capacity());
}

TEST(VectorTest, constructor_default_capacity_1) {
  s21::Vector<char> test_vector;
  std::vector<char> std_test_vector;
  test_vector.push_back(1);
  std_test_vector.push_back(1);
  EXPECT_EQ(std_test_vector.capacity(), test_vector.capacity());
}

TEST(VectorTest, constructor_parametrized) {
  s21::Vector<int> test_vector(5);
  std::vector<int> std_test_vector(5);
  EXPECT_EQ(std_test_vector.size(), test_vector.size());
}

TEST(VectorTest, constructor_initializer_list) {
  std::initializer_list<int> il1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector(il1);
  std::vector<int> std_test_vector(il1);
  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector.at(4), std_test_vector.at(4));
}

TEST(VectorTest, constructor_copy) {
  std::initializer_list<int> il1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector(il1);
  s21::Vector<int> copy_vector(test_vector);
  std::vector<int> std_test_vector(il1);
  std::vector<int> std_copy_vector(std_test_vector);
  EXPECT_EQ(copy_vector.at(0), std_copy_vector.at(0));
  EXPECT_EQ(copy_vector.at(1), std_copy_vector.at(1));
  EXPECT_EQ(copy_vector.at(2), std_copy_vector.at(2));
  EXPECT_EQ(copy_vector.at(3), std_copy_vector.at(3));
  EXPECT_EQ(copy_vector.at(4), std_copy_vector.at(4));
}

TEST(VectorTest, constructor_move) {
  std::initializer_list<int> il1{1, 2, 3, 4, 5};
  s21::Vector<int> test_vector(il1);
  s21::Vector<int> copy_vector(std::move(test_vector));
  std::vector<int> std_test_vector(il1);
  std::vector<int> std_copy_vector(std::move(std_test_vector));
  EXPECT_EQ(copy_vector.at(0), std_copy_vector.at(0));
  EXPECT_EQ(copy_vector.at(1), std_copy_vector.at(1));
  EXPECT_EQ(copy_vector.at(2), std_copy_vector.at(2));
  EXPECT_EQ(copy_vector.at(3), std_copy_vector.at(3));
  EXPECT_EQ(copy_vector.at(4), std_copy_vector.at(4));
}

TEST(VectorTest, constructor_operator) {
  s21::Vector<int> test_vector_1 = {1, 2, 3, 4, 5};
  s21::Vector<int> test_vector_2;
  test_vector_2 = std::move(test_vector_1);
  std::vector<int> std_test_vector = {1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector_2.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector_2.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector_2.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector_2.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector_2.at(4), std_test_vector.at(4));
}

TEST(VectorTest, at_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector.at(4), std_test_vector.at(4));
}

TEST(VectorTest, at_func_throw) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  EXPECT_ANY_THROW(test_vector.at(1));
  EXPECT_ANY_THROW(std_test_vector.at(1));
}

TEST(VectorTest, square_brackets_operator) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
  EXPECT_EQ(test_vector.at(4), std_test_vector.at(4));
}

TEST(VectorTest, front_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.front(), std_test_vector.front());
}

TEST(VectorTest, back_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.back(), std_test_vector.back());
}

TEST(VectorTest, data_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(*test_vector.data(), *std_test_vector.data());
}

TEST(VectorTest, empty) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  EXPECT_EQ(test_vector.empty(), std_test_vector.empty());
}

TEST(VectorTest, size_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.size(), std_test_vector.size());
}

TEST(VectorTest, max_size_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;

  EXPECT_EQ(test_vector.max_size(), std_test_vector.max_size());
}

TEST(VectorTest, reserve_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  test_vector.reserve(10);
  std_test_vector.reserve(10);
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, reserve_func_1) {
  s21::Vector<int> test_vector(10);
  std::vector<int> std_test_vector(10);
  test_vector.reserve(2);
  std_test_vector.reserve(2);
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, reserve_func_except) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  EXPECT_THROW(test_vector.reserve(2305843009213693952), std::length_error);
  EXPECT_THROW(std_test_vector.reserve(2305843009213693952), std::length_error);
}

TEST(VectorTest, capacity_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, shrink_to_fit_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  test_vector.reserve(10);
  std_test_vector.reserve(10);
  test_vector.shrink_to_fit();
  std_test_vector.shrink_to_fit();
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());
}

TEST(VectorTest, clear_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;
  test_vector.clear();
  std_test_vector.clear();
  EXPECT_EQ(test_vector.size(), std_test_vector.size());
}

TEST(VectorTest, insert_func) {
  s21::Vector<int> test_vector{1, 2, 3};
  std::vector<int> std_test_vector{1, 2, 3};
  test_vector.insert(test_vector.begin() + 1, 5);
  std_test_vector.insert(std_test_vector.begin() + 1, 5);

  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
}

TEST(VectorTest, erase_func) {
  s21::Vector<int> test_vector{1, 2, 3, 4};
  std::vector<int> std_test_vector{1, 2, 3, 4};

  test_vector.erase(test_vector.begin() + 1);
  std_test_vector.erase(std_test_vector.begin() + 1);

  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
}

TEST(VectorTest, push_back_func) {
  s21::Vector<int> test_vector;
  std::vector<int> std_test_vector;

  test_vector.push_back(2);
  test_vector.push_back(3);
  test_vector.push_back(4);
  test_vector.push_back(5);

  std_test_vector.push_back(2);
  std_test_vector.push_back(3);
  std_test_vector.push_back(4);
  std_test_vector.push_back(5);

  EXPECT_EQ(test_vector.at(0), std_test_vector.at(0));
  EXPECT_EQ(test_vector.at(1), std_test_vector.at(1));
  EXPECT_EQ(test_vector.at(2), std_test_vector.at(2));
  EXPECT_EQ(test_vector.at(3), std_test_vector.at(3));
}

TEST(VectorTest, pop_back_func) {
  s21::Vector<int> test_vector{1, 2};

  test_vector.pop_back();
  test_vector.pop_back();
  test_vector.pop_back();
  test_vector.pop_back();

  EXPECT_EQ(test_vector.size(), 0);
  EXPECT_EQ(test_vector.capacity(), 2);
}

TEST(VectorTest, swap_func) {
  s21::Vector<int> test_vector;
  s21::Vector<int> test_vector_copy;

  std::vector<int> std_test_vector;
  std::vector<int> std_test_vector_copy;

  test_vector_copy.swap(test_vector);
  std_test_vector_copy.swap(std_test_vector);

  EXPECT_EQ(test_vector.size(), std_test_vector.size());
  EXPECT_EQ(test_vector.capacity(), std_test_vector.capacity());

  EXPECT_EQ(test_vector_copy.size(), std_test_vector_copy.size());
  EXPECT_EQ(test_vector_copy.capacity(), std_test_vector_copy.capacity());
}

TEST(VectorTest, iterator_operator_minus_minus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(2)--, std_test_vector.at(2)--);
}
TEST(VectorTest, iterator_operator_plus_plus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(1)++, std_test_vector.at(1)++);
}
TEST(VectorTest, iterator_operator_plus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(0) + test_vector.at(1),
            std_test_vector.at(0) + std_test_vector.at(1));
}
TEST(VectorTest, iterator_operator_minus) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(2) - test_vector.at(1),
            std_test_vector.at(2) - std_test_vector.at(1));
}
TEST(VectorTest, iterator_operator_eq) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(4) == std_test_vector.at(4), 1);
}
TEST(VectorTest, iterator_operator_not_eq) {
  s21::Vector<int> test_vector{1, 2, 3, 4, 5};
  std::vector<int> std_test_vector{1, 2, 3, 4, 5};
  EXPECT_EQ(test_vector.at(3) != std_test_vector.at(4), 1);
}

/* -------------------- SET ----------------------- */

class SetTest {
 public:
  s21::set<int> empty_set;
  s21::set<int> set_int{3, 5, 7, 2, 1, 1, 4, 6};
  s21::set<std::string> set_string{"baka", "obon", "kokoro"};
  s21::set<double> set_double{1.2, 2.0, 3.345, -1.233};

  std::set<int> empty_set_orig;
  std::set<int> set_int_orig{3, 5, 7, 2, 1, 1, 4, 6};
  std::set<std::string> set_string_orig{"baka", "obon", "kokoro"};
  std::set<double> set_double_orig{1.2, 2.0, 3.345, -1.233};

  s21::set<int> swapped{100, 101, 102};
  std::set<int> swapped_orig{100, 101, 102};

  s21::set<int> merged{1, 50, 60};
  std::set<int> merged_orig{1, 50, 60};
};

TEST(set, Constructor) {
  SetTest tmp;
  EXPECT_EQ(*(tmp.empty_set.begin()) == *(tmp.empty_set_orig.begin()), true);
  EXPECT_EQ(*(tmp.empty_set.end()) == *(tmp.empty_set_orig.end()), true);
}

TEST(set, ConstructorList) {
  SetTest tmp;
  int eq[7]{1, 2, 3, 4, 5, 6, 7};
  int* pos = eq;
  for (auto it : tmp.set_int) {
    EXPECT_EQ(it == *(pos++), true);
  }
}

TEST(set, ConstructorCopy) {
  SetTest tmp;
  s21::set<double> two{tmp.set_double};
  double eq[4]{-1.233, 1.2, 2.0, 3.345};
  double* pos = eq;
  for (auto it : two) {
    EXPECT_EQ(it == *(pos++), true);
  }
  tmp.set_double.clear();
  EXPECT_TRUE(tmp.set_double.empty());
  EXPECT_TRUE(!two.empty());
}

TEST(set, ConstructorMove) {
  SetTest tmp;
  s21::set<double> two{std::move(tmp.set_double)};
  double eq[4]{-1.233, 1.2, 2.0, 3.345};
  double* pos = eq;
  for (auto it : two) {
    EXPECT_EQ(it == *(pos++), true);
  }
  EXPECT_TRUE(tmp.set_double.empty());
  EXPECT_TRUE(!two.empty());
}

TEST(set, OperatorsPlusTest) {
  SetTest tmp;
  s21::set<int>::iterator it(tmp.set_int.begin());
  EXPECT_TRUE(*(it++) == 1);
  EXPECT_TRUE(*(it) == 2);
  EXPECT_TRUE(*(++it) == 3);
}

TEST(set, OperatorsMinusTest) {
  SetTest tmp;
  s21::set<int>::iterator it(tmp.set_int.find(7));
  EXPECT_TRUE(*(it--) == 7);
  EXPECT_TRUE(*(it) == 6);
  EXPECT_TRUE(*(--it) == 5);
}

TEST(set, EmptyTest) {
  SetTest tmp;
  EXPECT_TRUE(tmp.set_int.empty() == tmp.set_int_orig.empty());
  EXPECT_TRUE(tmp.empty_set.empty() == tmp.empty_set_orig.empty());
  EXPECT_TRUE(tmp.set_string.empty() == tmp.set_string_orig.empty());
  EXPECT_TRUE(tmp.set_double.empty() == tmp.set_double_orig.empty());
}

TEST(set, SizeTest) {
  SetTest tmp;
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  EXPECT_TRUE(tmp.empty_set.size() == tmp.empty_set_orig.size());
  EXPECT_TRUE(tmp.set_string.size() == tmp.set_string_orig.size());
  EXPECT_TRUE(tmp.set_double.size() == tmp.set_double_orig.size());
}

TEST(set, MaxSizeTest) {
  SetTest tmp;
  EXPECT_TRUE(tmp.set_int.max_size() == tmp.set_int_orig.max_size());
  EXPECT_TRUE(tmp.empty_set.max_size() == tmp.empty_set_orig.max_size());
}

TEST(set, ClearTest) {
  SetTest tmp;
  tmp.set_int.clear();
  tmp.set_int_orig.clear();
  EXPECT_TRUE(tmp.set_int.empty() == tmp.set_int_orig.empty());
}

TEST(set, InsertTest) {
  SetTest tmp;
  tmp.empty_set.insert(1);
  tmp.empty_set.insert(1);
  EXPECT_TRUE(tmp.set_int.empty() == tmp.set_int_orig.empty());
  EXPECT_TRUE(*(tmp.set_int.find(1)) == *(tmp.set_int_orig.find(1)));
  EXPECT_EQ(tmp.set_int.find(2) == tmp.set_int.end(),
            tmp.set_int_orig.find(2) == tmp.set_int_orig.end());
}

TEST(set, EraseTest) {
  SetTest tmp;
  tmp.set_int.erase(tmp.set_int.find(5));
  tmp.set_int_orig.erase(5);
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  EXPECT_EQ(tmp.set_int.find(5) == tmp.set_int.end(),
            tmp.set_int_orig.find(5) == tmp.set_int_orig.end());
}

TEST(set, SwapTest) {
  SetTest tmp;
  tmp.set_int.swap(tmp.swapped);
  tmp.set_int_orig.swap(tmp.swapped_orig);
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  auto it_orig = tmp.set_int_orig.begin();
  for (auto it = tmp.set_int.begin(); it != tmp.set_int.end(); ++it) {
    EXPECT_TRUE(*it == *(it_orig++));
  }
}

TEST(set, FindTest) {
  SetTest tmp;
  for (int i = 1; i < 8; ++i) {
    EXPECT_TRUE(tmp.set_int.find(i) != tmp.set_int.end());
    EXPECT_TRUE(tmp.set_int.find(i + 10) == tmp.set_int.end());
  }
}

TEST(set, ContainsTest) {
  SetTest tmp;
  for (int i = 1; i < 8; ++i) {
    EXPECT_TRUE(tmp.set_int.contains(i));
    EXPECT_FALSE(tmp.set_int.contains(i + 10));
  }
}

TEST(set, MergeTest) {
  SetTest tmp;
  tmp.set_int.merge(tmp.merged);
  tmp.set_int_orig.merge(tmp.merged_orig);
  EXPECT_TRUE(tmp.set_int.size() == tmp.set_int_orig.size());
  EXPECT_TRUE(tmp.merged.size() == tmp.merged_orig.size());
  auto it_orig = tmp.set_int_orig.begin();
  for (auto it = tmp.set_int.begin(); it != tmp.set_int.end(); ++it) {
    EXPECT_TRUE(*it == *(it_orig++));
  }
}

/* -------------------- MAP ----------------------- */

class MapTest {
 public:
  s21::map<int, int> empty_map;
  s21::map<int, int> map_int{{1, 2}, {2, 3}, {3, 4}, {4, 5},
                             {5, 6}, {6, 7}, {7, 8}, {8, 9}};
  s21::map<std::string, std::string> map_string{
      {"baka", "mitai"}, {"obon", "katsurage"}, {"kokoro", "desu"}};
  s21::map<double, double> map_double{
      {1.2, 3.4}, {5.2, 1.1}, {-10.2, 1.123}, {0.02, 12.33}};

  std::map<int, int> empty_map_orig;
  std::map<int, int> map_int_orig{{1, 2}, {2, 3}, {3, 4}, {4, 5},
                                  {5, 6}, {6, 7}, {7, 8}, {8, 9}};
  std::map<std::string, std::string> map_string_orig{
      {"baka", "mitai"}, {"obon", "katsurage"}, {"kokoro", "desu"}};
  std::map<double, double> map_double_orig{
      {1.2, 3.4}, {5.2, 1.1}, {-10.2, 1.123}, {0.02, 12.33}};

  s21::map<int, int> swapped{{100, 0}, {101, 1}, {102, 2}};
  std::map<int, int> swapped_orig{{100, 0}, {101, 1}, {102, 2}};

  s21::map<int, int> merged{{1, 1}, {50, 2}, {60, 3}};
  std::map<int, int> merged_orig{{1, 1}, {50, 2}, {60, 3}};
};

TEST(map, Constructor) {
  MapTest tmp;
  EXPECT_EQ(*(tmp.empty_map.begin()) == *(tmp.empty_map_orig.begin()), true);
  EXPECT_EQ(*(tmp.empty_map.end()) == *(tmp.empty_map_orig.end()), true);
}

TEST(map, ConstructorList) {
  MapTest tmp;
  for (int i = 0; static_cast<size_t>(i) < tmp.map_int_orig.size(); ++i) {
    EXPECT_NEAR(tmp.map_int_orig[i], tmp.map_int[i], 0.001);
  }
}

TEST(map, ConstructorCopy) {
  MapTest tmp;
  s21::map<double, double> two{tmp.map_double};
  std::map<double, double> two_orig{tmp.map_double_orig};
  for (int i = 0; static_cast<size_t>(i) < two_orig.size(); ++i) {
    EXPECT_NEAR(two[i], tmp.map_double_orig[i], 0.001);
  }
  tmp.map_double.clear();
  EXPECT_TRUE(tmp.map_double.empty());
  EXPECT_TRUE(!two.empty());
}

TEST(map, ConstructorMove) {
  MapTest tmp;
  s21::map<double, double> two{std::move(tmp.map_double)};
  int size = static_cast<int>(two.size());
  for (int i = 0; i < size; ++i) {
    EXPECT_NEAR(two[i], tmp.map_double_orig[i], 0.001);
  }
  EXPECT_TRUE(tmp.map_double.empty());
  EXPECT_TRUE(!two.empty());
}

TEST(map, EmptyTest) {
  MapTest tmp;
  EXPECT_TRUE(tmp.map_int.empty() == tmp.map_int_orig.empty());
  EXPECT_TRUE(tmp.empty_map.empty() == tmp.empty_map_orig.empty());
  EXPECT_TRUE(tmp.map_string.empty() == tmp.map_string_orig.empty());
  EXPECT_TRUE(tmp.map_double.empty() == tmp.map_double.empty());
}

TEST(map, SizeTest) {
  MapTest tmp;
  EXPECT_TRUE(tmp.map_int.size() == tmp.map_int.size());
  EXPECT_TRUE(tmp.empty_map.size() == tmp.empty_map.size());
  EXPECT_TRUE(tmp.map_string.size() == tmp.map_string.size());
  EXPECT_TRUE(tmp.map_double.size() == tmp.map_double_orig.size());
}

TEST(map, MaxSizeTest) {
  MapTest tmp;
  EXPECT_TRUE(tmp.map_int.max_size() == tmp.map_int.max_size());
  EXPECT_TRUE(tmp.empty_map.max_size() == tmp.empty_map_orig.max_size());
}

TEST(map, ClearTest) {
  MapTest tmp;
  tmp.map_int.clear();
  tmp.map_int_orig.clear();
  EXPECT_TRUE(tmp.map_int.empty() == tmp.map_int_orig.empty());
}

TEST(map, EraseTest) {
  MapTest tmp;
  tmp.map_int.erase(tmp.map_int.begin());
  tmp.map_int_orig.erase(tmp.map_int_orig.begin());
  EXPECT_TRUE(tmp.empty_map.size() == tmp.empty_map_orig.size());
  EXPECT_THROW(tmp.map_int.at(1), std::out_of_range);
  EXPECT_THROW(tmp.map_int.at(1), std::out_of_range);
}

TEST(map, InsertTest) {
  MapTest tmp;
  auto s21_pair = tmp.empty_map.insert({1, 2});
  auto std_pair = tmp.empty_map_orig.insert({1, 2});
  EXPECT_TRUE(tmp.empty_map[1] == tmp.empty_map_orig[1]);
  EXPECT_TRUE(s21_pair.second == std_pair.second);
  s21_pair = tmp.empty_map.insert(5, 3);
  EXPECT_TRUE(tmp.empty_map[5] == 3);
  EXPECT_TRUE(s21_pair.second);
  s21_pair = tmp.empty_map.insert_or_assign(5, 10);
  EXPECT_TRUE(tmp.empty_map[5] == 10);
  EXPECT_FALSE(s21_pair.second);
}

TEST(map, SwapTest) {
  MapTest tmp;
  tmp.map_int.swap(tmp.swapped);
  tmp.map_int_orig.swap(tmp.swapped_orig);
  EXPECT_TRUE(tmp.map_int.size() == tmp.map_int_orig.size());
  auto it_orig = tmp.map_int_orig.begin();
  for (auto it = tmp.map_int.begin(); it != tmp.map_int.end(); ++it) {
    EXPECT_TRUE(*it == *(it_orig++));
  }
}

TEST(map, ContainsTest) {
  MapTest tmp;
  for (auto it : tmp.map_int_orig) {
    EXPECT_TRUE(tmp.map_int.contains(it.first));
    EXPECT_FALSE(tmp.map_int.contains(it.first + 10));
  }
}

TEST(map, MergeTest) {
  MapTest tmp;
  tmp.map_int.merge(tmp.merged);
  tmp.map_int_orig.merge(tmp.merged_orig);
  EXPECT_EQ(tmp.map_int.size(), tmp.map_int_orig.size());
  EXPECT_EQ(tmp.merged.size(), tmp.merged_orig.size());
  auto it_orig = tmp.map_int_orig.begin();
  for (auto it = tmp.map_int.begin(); it != tmp.map_int.end(); ++it) {
    EXPECT_TRUE(*it == *(it_orig++));
  }
}

/* ------------------------ ARRRAY ----------------------------- */

class s21ArrayTest : public testing::Test {
 protected:
  s21::Array<int, 0> s21_array_empty;
  s21::Array<char, 5> s21_array_init{'a', 'b', 'c', 'd'};
  s21::Array<int, 5> s21_array_for_copy{1, 2, 3, 4, 5};
  s21::Array<int, 5> s21_array_for_swap_1{12, 23, 23, 435, -51};
  s21::Array<int, 5> s21_array_for_swap_2{423423, 234, 623, 12, 1};

  std::array<int, 0> std_array_empty;
  std::array<char, 5> std_array_init{'a', 'b', 'c', 'd'};
  std::array<int, 5> std_array_for_copy{1, 2, 3, 4, 5};
  std::array<int, 5> std_array_for_swap_1{12, 23, 23, 435, -51};
  std::array<int, 5> std_array_for_swap_2{423423, 234, 623, 12, 1};
};

TEST_F(s21ArrayTest, DefaultConstructor) {
  EXPECT_EQ(s21_array_empty.size(), std_array_empty.size());
  EXPECT_EQ(s21_array_empty.empty(), std_array_empty.empty());
}

TEST_F(s21ArrayTest, InitializerListConstructor) {
  EXPECT_EQ(s21_array_init.size(), std_array_init.size());
  EXPECT_EQ(s21_array_init.front(), std_array_init.front());
  EXPECT_EQ(s21_array_init.back(), std_array_init.back());
  for (size_t i = 0; i < s21_array_init.size(); i++) {
    EXPECT_EQ(s21_array_init[i], std_array_init[i]);
  }
  s21::Array<int, 4> s21_array_init_throw;
  std::initializer_list<int> init_list_for_throw = {1, 1, 2, 3, 5, 8, 13};
  EXPECT_THROW(s21_array_init_throw = init_list_for_throw, std::out_of_range);
}

TEST_F(s21ArrayTest, CopyConstructor) {
  s21::Array<int, 5> s21_array(s21_array_for_copy);
  std::array<int, 5> std_array(std_array_for_copy);

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  EXPECT_EQ(s21_array.max_size(), std_array.max_size());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST_F(s21ArrayTest, AssignmentOperatorCopying) {
  s21::Array<int, 5> s21_array;
  s21_array = s21_array_for_copy;
  std::array<int, 5> std_array;
  std_array = std_array_for_copy;

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST_F(s21ArrayTest, MoveConstructor) {
  s21::Array<int, 5> s21_array(std::move(s21_array_for_copy));
  std::array<int, 5> std_array(std::move(std_array_for_copy));

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST_F(s21ArrayTest, AssignmentOperatorMoving) {
  s21::Array<int, 5> s21_array;
  s21_array = std::move(s21_array_for_copy);
  std::array<int, 5> std_array;
  std_array = std::move(std_array_for_copy);

  EXPECT_EQ(s21_array.size(), std_array.size());
  EXPECT_EQ(s21_array.front(), std_array.front());
  EXPECT_EQ(s21_array.back(), std_array.back());
  for (size_t i = 0; i < s21_array.size(); i++) {
    EXPECT_EQ(s21_array[i], std_array[i]);
  }
}

TEST_F(s21ArrayTest, Swap) {
  s21_array_for_swap_1.swap(s21_array_for_swap_2);
  std_array_for_swap_1.swap(std_array_for_swap_2);

  EXPECT_EQ(s21_array_for_swap_1.size(), std_array_for_swap_1.size());
  EXPECT_EQ(s21_array_for_swap_1.front(), std_array_for_swap_1.front());
  EXPECT_EQ(s21_array_for_swap_1.back(), std_array_for_swap_1.back());
  for (size_t i = 0; i < s21_array_for_swap_1.size(); i++) {
    EXPECT_EQ(s21_array_for_swap_1[i], std_array_for_swap_1[i]);
  }

  EXPECT_EQ(s21_array_for_swap_2.size(), std_array_for_swap_2.size());
  EXPECT_EQ(s21_array_for_swap_2.front(), std_array_for_swap_2.front());
  EXPECT_EQ(s21_array_for_swap_2.back(), std_array_for_swap_2.back());
  for (size_t i = 0; i < s21_array_for_swap_2.size(); i++) {
    EXPECT_EQ(s21_array_for_swap_2[i], std_array_for_swap_2[i]);
  }
}

TEST_F(s21ArrayTest, Fill) {
  s21_array_init.fill('o');
  std_array_init.fill('o');

  EXPECT_EQ(s21_array_init.size(), std_array_init.size());
  EXPECT_EQ(s21_array_init.front(), std_array_init.front());
  EXPECT_EQ(s21_array_init.back(), std_array_init.back());
  for (size_t i = 0; i < s21_array_init.size(); i++) {
    EXPECT_EQ(s21_array_init[i], std_array_init[i]);
  }
}

TEST_F(s21ArrayTest, Iterators) {
  char* s21_begin = s21_array_init.begin();
  char* std_begin = std_array_init.begin();
  char* s21_end = s21_array_init.end();
  char* std_end = std_array_init.end();

  while (s21_begin < s21_end && std_begin < std_end) {
    EXPECT_EQ(*s21_begin++, *std_begin++);
  }

  EXPECT_EQ(s21_array_empty.begin(), s21_array_empty.end());
  EXPECT_EQ(*s21_array_init.data(), s21_array_init[0]);
}

TEST_F(s21ArrayTest, At) {
  EXPECT_EQ(s21_array_init.at(0), s21_array_init[0]);
  s21_array_init.at(0) = 'c';
  EXPECT_EQ(s21_array_init.at(0), 'c');

  EXPECT_THROW(s21_array_init.at(-1) = 4, std::out_of_range);
  EXPECT_THROW(s21_array_init.at(s21_array_init.size() + 10) = 4,
               std::out_of_range);
}

/* ---------------------------- QUEUE ----------------------------- */

class S21QueueTest : public testing::Test {
 protected:
  class Example {
   public:
    Example() : x_(0), y_(0){};
    Example(int x, int y) : x_(x), y_(y){};
    int getX() { return x_; }
    int getY() { return y_; }
    bool operator==(const Example& other) const {
      return x_ == other.x_ && y_ == other.y_;
    }

   private:
    int x_, y_;
  };

  s21::Queue<Example> s21_queue_emplace;
  s21::Queue<int> s21_queue_empty;
  s21::Queue<char> s21_queue_init_list{'c', 'b', 'a'};
  s21::Queue<int> s21_queue_for_copy{1, 1, 2, 3, 5, 8, 13};

  std::queue<int> std_queue_empty;
  std::queue<Example> std_queue_emplace;
};

TEST_F(S21QueueTest, DefaultConstructor) {
  EXPECT_EQ(s21_queue_empty.size(), std_queue_empty.size());
  EXPECT_EQ(s21_queue_empty.empty(), std_queue_empty.empty());
}

TEST_F(S21QueueTest, InitializerListConstructor) {
  std::initializer_list<int> init_list_for_copy = {1, 1, 2, 3, 5, 8, 13};
  s21::Queue<int> s21_queue{init_list_for_copy};
  std::queue<int> std_queue{init_list_for_copy};
  EXPECT_EQ(s21_queue.size(), std_queue.size());

  while (!s21_queue.empty() && !std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue.back(), std_queue.back());
    s21_queue.pop();
    std_queue.pop();
  }
}

TEST_F(S21QueueTest, CopyConstructor) {
  std::initializer_list<int> init_list_for_copy = {1, 1, 2, 3, 5, 8, 13};
  s21::Queue<int> s21_queue_for_copy{init_list_for_copy};
  std::queue<int> std_queue_for_copy{init_list_for_copy};

  s21::Queue<int> s21_queue(s21_queue_for_copy);
  std::queue<int> std_queue(std_queue_for_copy);

  EXPECT_EQ(s21_queue.size(), std_queue.size());
  while (!s21_queue.empty() && !std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue.back(), std_queue.back());
    s21_queue.pop();
    std_queue.pop();
  }
}

TEST_F(S21QueueTest, AssignmentOperatorCopy) {
  std::initializer_list<int> init_list_for_copy = {1, 1, 2, 3, 5, 8, 13};
  s21::Queue<int> s21_queue_for_copy{init_list_for_copy};
  std::queue<int> std_queue_for_copy{init_list_for_copy};

  s21::Queue<int> s21_queue;
  std::queue<int> std_queue;
  s21_queue = s21_queue_for_copy;
  std_queue = std_queue_for_copy;

  EXPECT_EQ(s21_queue.size(), std_queue.size());
  while (!s21_queue.empty() && !std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue.back(), std_queue.back());
    s21_queue.pop();
    std_queue.pop();
  }
}

TEST_F(S21QueueTest, MoveConstructor) {
  std::initializer_list<int> init_list_for_move = {1, 1, 2, 3, 5, 8, 13};
  s21::Queue<int> s21_queue_for_move{init_list_for_move};
  std::queue<int> std_queue_for_move{init_list_for_move};

  s21::Queue<int> s21_queue(std::move(s21_queue_for_move));
  std::queue<int> std_queue(std::move(std_queue_for_move));

  EXPECT_EQ(s21_queue.size(), std_queue.size());
  while (!s21_queue.empty() && !std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue.back(), std_queue.back());
    s21_queue.pop();
    std_queue.pop();
  }
}

TEST_F(S21QueueTest, AssignmentOperatorMove) {
  std::initializer_list<int> init_list_for_move = {1, 1, 2, 3, 5, 8, 13};
  s21::Queue<int> s21_queue_for_move{init_list_for_move};
  std::queue<int> std_queue_for_move{init_list_for_move};

  s21::Queue<int> s21_queue;
  std::queue<int> std_queue;
  std_queue = std::move(std_queue_for_move);
  s21_queue = std::move(s21_queue_for_move);

  EXPECT_EQ(s21_queue.size(), std_queue.size());
  while (!s21_queue.empty() && !std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue.back(), std_queue.back());
    s21_queue.pop();
    std_queue.pop();
  }
}

TEST_F(S21QueueTest, Push) {
  s21_queue_empty.push(1);
  std_queue_empty.push(1);
  EXPECT_EQ(s21_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(s21_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(s21_queue_empty.size(), std_queue_empty.size());
  s21_queue_empty.push(1123213);
  std_queue_empty.push(1123213);

  s21_queue_empty.front() = 21;
  std_queue_empty.front() = 21;

  s21_queue_empty.back() = 42;
  std_queue_empty.back() = 42;
  EXPECT_EQ(s21_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(s21_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(s21_queue_empty.size(), std_queue_empty.size());
}

TEST_F(S21QueueTest, Pop) {
  s21_queue_empty.push(1);
  std_queue_empty.push(1);
  s21_queue_empty.push(1123213);
  std_queue_empty.push(1123213);

  s21_queue_empty.pop();
  std_queue_empty.pop();
  EXPECT_EQ(s21_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(s21_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(s21_queue_empty.size(), std_queue_empty.size());

  s21_queue_empty.pop();
  std_queue_empty.pop();
  EXPECT_EQ(s21_queue_empty.size(), std_queue_empty.size());
}

TEST_F(S21QueueTest, Swap) {
  std::initializer_list<int> init_list = {1, 1, 3, 6};
  std::initializer_list<int> init_list_for_swap = {1, 3, 5, 5, 6, 7};
  s21::Queue<int> s21_queue{init_list};
  s21::Queue<int> s21_queue_for_swap{init_list_for_swap};

  std::queue<int> std_queue{init_list};
  std::queue<int> std_queue_for_swap{init_list_for_swap};

  s21_queue.swap(s21_queue_for_swap);
  std_queue.swap(std_queue_for_swap);

  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue_for_swap.size(), std_queue_for_swap.size());

  while (!s21_queue.empty() && !std_queue.empty()) {
    EXPECT_EQ(s21_queue.front(), std_queue.front());
    EXPECT_EQ(s21_queue.back(), std_queue.back());
    s21_queue.pop();
    std_queue.pop();
  }

  while (!s21_queue_for_swap.empty() && !std_queue_for_swap.empty()) {
    EXPECT_EQ(s21_queue_for_swap.front(), std_queue_for_swap.front());
    EXPECT_EQ(s21_queue_for_swap.back(), std_queue_for_swap.back());
    s21_queue_for_swap.pop();
    std_queue_for_swap.pop();
  }
}

TEST_F(S21QueueTest, EmplaceBack) {
  s21_queue_emplace.push(Example(1, 2));
  std_queue_emplace.push(Example(1, 2));
  EXPECT_EQ(s21_queue_emplace.size(), std_queue_emplace.size());
  EXPECT_EQ(s21_queue_emplace.front(), std_queue_emplace.front());
  EXPECT_EQ(s21_queue_emplace.back(), std_queue_emplace.back());
  s21_queue_emplace.emplace_back(4, 5);
  std_queue_emplace.emplace(4, 5);
  EXPECT_EQ(s21_queue_emplace.size(), std_queue_emplace.size());
  EXPECT_EQ(s21_queue_emplace.front(), std_queue_emplace.front());
  EXPECT_EQ(s21_queue_emplace.back(), std_queue_emplace.back());
}

/* ------------------------ STACK ------------------------------ */

class S21StackTest : public testing::Test {
 protected:
  class Example {
   public:
    Example() : x_(0), y_(0){};
    Example(int x, int y) : x_(x), y_(y){};
    int getX() { return x_; }
    int getY() { return y_; }
    bool operator==(const Example& other) const {
      return x_ == other.x_ && y_ == other.y_;
    }

   private:
    int x_, y_;
  };

  s21::Stack<Example> s21_stack_emplace;
  s21::Stack<int> s21_empty;
  s21::Stack<char> s21_init_list{'c', 'b', 'a'};
  s21::Stack<int> s21_stack_for_copy{1, 1, 2, 3, 5, 8, 13};

  std::stack<int> std_empty;
  std::stack<Example> std_stack_emplace;
};

TEST_F(S21StackTest, DefaultConstructor) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
}

TEST_F(S21StackTest, InitializerListConstructor) {
  std::initializer_list<int> init_list = {1, 2, 3};
  s21::Stack<int> s21_stack{init_list};
  std::stack<int> std_stack{init_list};

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }
}

TEST_F(S21StackTest, CopyConstructor) {
  std::initializer_list<int> init_list_for_copy = {1, 1, 2, 3, 5, 8, 13};
  s21::Stack<int> s21_stack_for_copy{init_list_for_copy};
  std::stack<int> std_stack_for_copy{init_list_for_copy};

  s21::Stack<int> s21_stack(s21_stack_for_copy);
  std::stack<int> std_stack(std_stack_for_copy);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }
}

TEST_F(S21StackTest, AssignmentOperatorCopy) {
  std::initializer_list<double> init_list_for_copy = {1231.4, 1.342, 3.23, 4.4};
  s21::Stack<double> s21_stack_for_move{init_list_for_copy};
  std::stack<double> std_stack_for_move{init_list_for_copy};

  s21::Stack<double> s21_stack;
  s21_stack = s21_stack_for_move;
  std::stack<double> std_stack;
  std_stack = std_stack_for_move;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }

  EXPECT_EQ(s21_stack_for_move.size(), std_stack_for_move.size());
}

TEST_F(S21StackTest, MoveConstructor) {
  std::initializer_list<double> init_list_for_move = {1231.4, 1.342, 3.23, 4.4};
  s21::Stack<double> s21_stack_for_move{init_list_for_move};
  std::stack<double> std_stack_for_move{init_list_for_move};

  s21::Stack<double> s21_stack(std::move(s21_stack_for_move));
  std::stack<double> std_stack(std::move(std_stack_for_move));
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }

  EXPECT_EQ(s21_stack_for_move.size(), std_stack_for_move.size());
}

TEST_F(S21StackTest, AssignmentOperatorMove) {
  std::initializer_list<double> init_list_for_copy = {1231.4, 1.342, 3.23, 4.4};
  s21::Stack<double> s21_stack_for_move{init_list_for_copy};
  std::stack<double> std_stack_for_move{init_list_for_copy};

  s21::Stack<double> s21_stack;
  s21_stack = std::move(s21_stack_for_move);
  std::stack<double> std_stack;
  std_stack = std::move(std_stack_for_move);
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }

  EXPECT_EQ(s21_stack_for_move.size(), std_stack_for_move.size());
}

TEST_F(S21StackTest, Push) {
  s21_empty.push(123);
  std_empty.push(123);
  EXPECT_EQ(s21_empty.top(), std_empty.top());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  s21_empty.push(45322345);
  std_empty.push(45322345);
  EXPECT_EQ(s21_empty.top(), std_empty.top());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
}

TEST_F(S21StackTest, Pop) {
  s21_empty.push(123);
  std_empty.push(123);
  s21_empty.push(45322345);
  std_empty.push(45322345);
  EXPECT_EQ(s21_empty.top(), std_empty.top());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  s21_empty.pop();
  std_empty.pop();
  EXPECT_EQ(s21_empty.top(), std_empty.top());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  s21_empty.pop();
  std_empty.pop();
  EXPECT_EQ(s21_empty.size(), std_empty.size());
}

TEST_F(S21StackTest, Swap) {
  std::initializer_list<int> init_list = {1, 1, 3, 6};
  std::initializer_list<int> init_list_for_swap = {1, 3, 5, 5, 6, 7};
  s21::Stack<int> s21_stack{init_list};
  s21::Stack<int> s21_stack_for_swap{init_list_for_swap};

  std::stack<int> std_stack{init_list};
  std::stack<int> std_stack_for_swap{init_list_for_swap};

  s21_stack.swap(s21_stack_for_swap);
  std_stack.swap(std_stack_for_swap);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack_for_swap.size(), std_stack_for_swap.size());
  while (!s21_stack.empty() && !std_stack.empty()) {
    EXPECT_EQ(s21_stack.top(), std_stack.top());
    s21_stack.pop();
    std_stack.pop();
  }

  while (!s21_stack_for_swap.empty() && !std_stack_for_swap.empty()) {
    EXPECT_EQ(s21_stack_for_swap.top(), std_stack_for_swap.top());
    s21_stack_for_swap.pop();
    std_stack_for_swap.pop();
  }
}

TEST_F(S21StackTest, EmplaceFront) {
  s21_stack_emplace.push(Example(1, 2));
  std_stack_emplace.push(Example(1, 2));
  EXPECT_EQ(s21_stack_emplace.size(), std_stack_emplace.size());
  EXPECT_EQ(s21_stack_emplace.top(), std_stack_emplace.top());
  s21_stack_emplace.emplace_front(4, 5);
  std_stack_emplace.emplace(4, 5);
  EXPECT_EQ(s21_stack_emplace.size(), std_stack_emplace.size());
  EXPECT_EQ(s21_stack_emplace.top(), std_stack_emplace.top());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef __APPLE__
  free(__cxxabiv1::__cxa_get_globals());
#endif
  return RUN_ALL_TESTS();
}
