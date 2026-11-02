#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	TDynamicVector<int> v1(v);
	v[0] = 100;
	EXPECT_EQ(v1[0], 1);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	EXPECT_ANY_THROW(v[-3] = 2);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	EXPECT_ANY_THROW(v[100] = 3);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	EXPECT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {4, 5, 6};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	v1 = v;
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(3), v1(4);
	v1 = v;
	EXPECT_EQ(v1.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3), v1(4);
	v1 = v;
	EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	int* a = new int[3] {1, 2, 3};
	TDynamicVector<int> v(a, 3);
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(3), v1(4);
	EXPECT_NE(v, v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {6, 7, 8};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	EXPECT_EQ(v + 5, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {-4, -3, -2};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	EXPECT_EQ(v - 5, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {5, 10, 15};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	EXPECT_EQ(v * 5, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {4, 5, 6};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	int* c = new int[3] {5, 7, 9};
	TDynamicVector<int> v2(c, 3);
	EXPECT_EQ(v + v1, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(4);
	EXPECT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {4, 5, 6};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	int* c = new int[3] {3, 3, 3};
	TDynamicVector<int> v2(c, 3);
	EXPECT_EQ(v1 - v, v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(4);
	EXPECT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {4, 5, 6};
	TDynamicVector<int> v(a, 3), v1(b, 3);
	EXPECT_EQ(v * v1, 32);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v1(4);
	EXPECT_ANY_THROW(v * v1);
}

