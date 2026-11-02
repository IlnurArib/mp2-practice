#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);
  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	int x = 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			m[i][j] = x++;
		}
	}
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	int x = 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			m[i][j] = x++;
		}
	}
	TDynamicMatrix<int> m1(m);
	m1[0][0] = 100;
	EXPECT_NE(m[0][0], 100);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[1][0] = 0;
	EXPECT_TRUE(m[1][0] == 0);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW(m[-2][-3] = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW(m[10][3] = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	EXPECT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	EXPECT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	m = m1;
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(5);
	EXPECT_NO_THROW(m = m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) m[i][j] = i + j + 2;
	}
	TDynamicMatrix<int> m1(3);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) m1[i][j] = i + j + 2;
	}
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(3), m1(5);
	EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) m[i][j] = i + j + 2;
	}
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) m1[i][j] = i + j + 10;
	}

	TDynamicMatrix<int> m2(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) m2[i][j] = 2 * (i + j) + 12;
	}
	EXPECT_EQ(m + m1, m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3), m1(5);
	EXPECT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) m[i][j] = i + j + 2;
	}
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) m1[i][j] = i + j + 10;
	}

	TDynamicMatrix<int> m2(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) m2[i][j] = -8;
	}
	EXPECT_EQ(m - m1, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(3), m1(5);
	EXPECT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector) {
	TDynamicMatrix<int> m(3);
	int* a = new int[3] {1, 2, 3};
	int* b = new int[3] {14, 23, 18};
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3 - i; j++) m[i][j] = ++cnt;
	}
	TDynamicVector<int> v(a, 3), v1(b, 3);
	EXPECT_EQ(m * v, v1);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_different_size) {
	TDynamicMatrix<int> m(5);
	TDynamicVector<int> v(3);
	EXPECT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_matrix) {
	TDynamicMatrix<int> m(2), m1(2), m2(2);
	int cnt = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2 - i; j++) m[i][j] = ++cnt;
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2 - i; j++) m1[i][j] = ++cnt;
	}
	m2[0][0] = 4; m2[0][1] = 17;
	m2[1][0] = 18;
	EXPECT_EQ(m * m1, m2);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_matrix_different_size) {
	TDynamicMatrix<int> m(3), m1(5);
	EXPECT_ANY_THROW(m * m1);
}