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
  TDynamicVector<int> v(3);
  v[0] = 0; v[1] = 1; v[2] = 2;
  TDynamicVector<int> p(v);
  EXPECT_TRUE(p==v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 0; v[1] = 1; v[2] = 2;
  TDynamicVector<int> p(v);
  p[0] = 1;
  EXPECT_FALSE(p[0] == v[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element) //был в комментариях
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(10);
  EXPECT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(10);
  ASSERT_ANY_THROW(v.at(11));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v(3), p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 4; p[1] = 5; p[2] = 6;
  ASSERT_NO_THROW(v = p);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(3),p(5);
  v = p;
  EXPECT_EQ(5, v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(4), p(3);
  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 0;
  p[0] = 4; p[1] = 5; p[2] = 6;
  ASSERT_NO_THROW(v = p);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v(3), p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 1; p[1] = 2; p[2] = 3;
  EXPECT_TRUE(p == v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v(3), p(4);;
  EXPECT_FALSE(p == v);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 1; v[1] = 1; v[2] = 1;
  int a = 7;
  p[0] = 8; p[1] = 8; p[2] = 8;
  EXPECT_EQ(p, v + a);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 2; v[1] = 3; v[2] = 4;
  int a = 1;
  p[0] = 1; p[1] = 2; p[2] = 3;
  EXPECT_EQ(p, v - a);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  int a = 2;
  p[0] = 2; p[1] = 4; p[2] = 6;
  EXPECT_EQ(p, v * a);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  TDynamicVector<int> res(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 1; p[1] = 2; p[2] = 3;
  res[0] = 2; res[1] = 4; res[2] = 6;
  EXPECT_EQ(res, v + p);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(4);
  ASSERT_ANY_THROW(p+v);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  TDynamicVector<int> res(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 2; p[1] = 3; p[2] = 4;
  res[0] = -1; res[1] = -1; res[2] = -1;
  EXPECT_EQ(res, v - p);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(4);
  ASSERT_ANY_THROW(p - v);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 2; p[1] = 3; p[2] = 4;
  int res = 20;
  EXPECT_EQ(res,v * p);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(4);
  ASSERT_ANY_THROW(p * v);
}

