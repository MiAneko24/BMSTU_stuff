
#include "../inc/matrix_templates.h"
#include "../inc/iterator_template.h"
#include "../inc/const_iterator_templates.h"
#include <check.h>

START_TEST(test_summmary_of_two_double_matrix_normal_case)
{
    Matrix<double> mat_1 = Matrix<double>({{6, -1, 3, -5, 2.2}, {-4, 9, 3.1, -2.2, -4}, {3, 7, 3.5, 1, 5}});
    Matrix<double> mat_2 = Matrix<double>({{1.6, 7, 8.3, 7, 5.8}, {9, -3, -0.1, 4.2, 8}, {-4, -9, 4.5, -0.4, 1}});
    Matrix<double> res_exp = Matrix<double>({{7.6, 6, 11.3, 2, 8}, {5, 6, 3, 2, 4}, {-1, -2, 8, 0.6, 6}});
    Matrix<double> res = mat_1 + mat_2;

    ck_assert(res == res_exp);
}
END_TEST

START_TEST(test_substitution_of_two_double_matrix_normal_case)
{
    Matrix<double> mat_1 = Matrix<double>({{6, -1, 3, -5, 2.2}, {-4, 9, 3.1, -2.2, -4}, {3, 7, 3.5, 1, 5}});
    Matrix<double> mat_2 = Matrix<double>({{1.6, 7, 8.3, 7, 5.8}, {9, -3, -0.1, 4.2, 8}, {-4, -9, 4.5, -0.4, 1}});
    Matrix<double> res_exp = Matrix<double>({{4.4, -8, -5.3, -12, -3.6}, {-13, 12, 3.2, -6.4, -12}, {7, 16, -1, 1.4, 4}});
    Matrix<double> res = mat_1 - mat_2;
    ck_assert(res == res_exp);
}
END_TEST


START_TEST(test_multiplication_of_two_double_matrix_normal_case)
{
    Matrix<double> mat_1 = Matrix<double>({{6, -1, 3, -5, 2.2}, {-4, 9, 3.1, -2.2, -4}, {3, 7, 3.5, 1, 5}});
    Matrix<double> mat_2 = Matrix<double>({{1.6, 7}, {8.3, 5.8}, {9, -3}, {4.2, 8}, {-1, 0.6}});
    Matrix<double> res_exp = Matrix<double>({{5.1, -11.48}, {90.96, -5.1}, {93.6, 62.1}});
    Matrix<double> res = mat_1 * mat_2;

    ck_assert(res == res_exp);
}
END_TEST

START_TEST(test_transpose_square_string_matrix)
{
    int n = 4;
    Matrix<std::string> mat_1 = Matrix<std::string>(n, n);
    for (int i = 0; i < mat_1.getRows(); i++)
        for (int j = 0; j < mat_1.getColumns(); j++)
            mat_1[i][j] = std::to_string(i - j);
    Matrix<std::string> mat_exp = Matrix<std::string>(n, n);
    for (int i = 0; i < mat_exp.getRows(); i++)
        for (int j = 0; j < mat_exp.getColumns(); j++)
            mat_exp[i][j] = std::to_string(j - i);
    mat_1.transpose();
    ck_assert(mat_1 == mat_exp);
}
END_TEST

START_TEST(test_det_null_double_matrix)
{
    Matrix<double> mat_1 = Matrix<double>(7, 7);
    int cnt = 1;
    for (int i = 0; i < mat_1.getRows(); i++)
        for (int j = 0; j < mat_1.getColumns(); j++)
        {
            mat_1[i][j] = cnt;
            cnt++;
        }
    double det = mat_1.det();
    ck_assert(abs(det - 0) < 1e-8);
}
END_TEST

START_TEST(test_det_non_null_double_matrix)
{
    Matrix<double> mat_1 = Matrix<double>(3, 3);
    int cnt = 1;
    for (int i = 0; i < mat_1.getRows(); i++)
        for (int j = 0; j < mat_1.getColumns(); j++)
        {
            mat_1[i][j] = cnt;
            cnt++;
        }
    mat_1[mat_1.getRows() - 1][mat_1.getRows() - 1]++;
    double det = mat_1.det();
    ck_assert(abs(det - (-3)) < 1e-8);
}
END_TEST

START_TEST(test_reverse_matrix_usual_case)
{
    Matrix<double> mat_1 = Matrix<double>(3, 3);
    int cnt = 1;
    for (int i = 0; i < mat_1.getRows(); i++)
        for (int j = 0; j < mat_1.getColumns(); j++)
        {
            mat_1[i][j] = cnt;
            cnt++;
        }
    mat_1[2][2] += 3;

    Matrix<double> mat_exp = Matrix<double>(3, 3);
    mat_exp[0][0] = -4 / 3;
    mat_exp[0][1] = 0;
    mat_exp[0][2] = 1 / 3;
    mat_exp[1][0] = 2 / 3;
    mat_exp[1][1] = 1;
    mat_exp[1][2] = -2 / 3;
    mat_exp[2][0] = 1 / 3;
    mat_exp[2][1] = -2 / 3;
    mat_exp[2][2] = 1 / 3;
    mat_1.reverse_matrix();
    ck_assert(mat_1 == mat_exp);
}
END_TEST

START_TEST(test_mul_eq_int_matrix_on_number)
{
    Matrix<int> mat_1 = Matrix<int>(3, 7);
    int cnt = 1;
    for (int i = 0; i < mat_1.getRows(); i++)
        for (int j = 0; j < mat_1.getColumns(); j++)
        {
            mat_1[i][j] = cnt;
            cnt++;
        }
    cnt = 1;
    int num = 9;
    Matrix<int> res = Matrix<int>(3, 7);
       for (int i = 0; i < res.getRows(); i++)
        for (int j = 0; j < res.getColumns(); j++)
        {
            res[i][j] = cnt * num;
            cnt++;
        }
    mat_1 *= num;
    ck_assert(mat_1 == res);
}
END_TEST


START_TEST(test_div_eq_int_matrix_on_number)
{
    Matrix<int> mat_1 = Matrix<int>(3, 7);
    int cnt = 1;
    for (int i = 0; i < mat_1.getRows(); i++)
        for (int j = 0; j < mat_1.getColumns(); j++)
        {
            mat_1[i][j] = cnt;
            cnt++;
        }
    cnt = 1;
    int num = 3;
    Matrix<int> res = Matrix<int>(3, 7);
       for (int i = 0; i < res.getRows(); i++)
        for (int j = 0; j < res.getColumns(); j++)
        {
            res[i][j] = cnt / num;
            cnt++;
        }
    mat_1 /= num;
    ck_assert(mat_1 == res);
}
END_TEST


START_TEST(test_iterator)
{
    
    Matrix<std::string> mat = Matrix<std::string>(9, 2);
    int cnt = 1;
    for (int i = 0; i < mat.getRows(); i++)
        for (int j = 0; j < mat.getColumns(); j++)
        {
            mat[i][j] = std::to_string(cnt);
            cnt++;
        }

    Iterator<std::string> it = mat.begin();
    for (size_t i = 0; it != mat.end(); i++, it++)
    {
        std::cout << *it <<" ";
    }
    std::cout << std::endl;
}
END_TEST


START_TEST(test_const_iterator)
{
    
    const Matrix<char> mat = Matrix<char>({{'d', '3', '$', '=', '^', ';', 's'}, {'d', '3', '$', '=', '^', ';', 's'}, {'d', '3', '$', '=', '^', ';', 's'}});
  
    for (constIterator<char> it = mat.begin(); it != mat.end(); it++)
    {
        std::cout << *it <<" ";
    }
    std::cout << std::endl;
}
END_TEST

START_TEST(test_catch_throw)
{
    Matrix<int> mat_1 = Matrix<int>(4, 4);

    Matrix<int> mat_2 = Matrix<int>(7, 1);

    Matrix<char> mat_3 = Matrix<char>(3, 4);
    int i = 0;
    
    try
    {
        i = mat_1[6][7];

    }
    catch(IndexError &e)
    {
        std::cout << "IndexError caught"<< std::endl; 
        std::cout << e.what() << '\n';
    }

    try
    {
        mat_1 += mat_2;
    }
    catch(DimensionMatrixError &e)
    {
        std::cout << "DimensionMatrixError after summary caught" << std::endl;
        std::cout << e.what() << '\n';
    }
    try
    {
        mat_3.reverse_matrix();
    }
    catch(TypeMatrixError &e)
    {
        std::cout << "TypeMatrixError after reverse of char matrix caught" << std::endl; 
        std::cout << e.what() << '\n';
    }
    try
    {
        double j = mat_3.det();
    }
    catch(TypeMatrixError & e)
    {
        std::cout << "TypeMatrixError after attempt of getting determinant of char matrix caught" << std::endl; 
        std::cout << e.what() << '\n';
    }
    try
    {
        i = 0;
        mat_1 /= i;
    }
    catch(DivisionByZeroError &e)
    {
        std::cout << "DivisionByZeroError caught" << std::endl; 
        std::cout << e.what() << '\n';
    }
    
    
}
END_TEST



Suite* summary_of_two_matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;
    s = suite_create("summary_of_two_matrix");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_pos, test_summmary_of_two_double_matrix_normal_case);

    tcase_add_test(tc_pos, test_multiplication_of_two_double_matrix_normal_case);
    tcase_add_test(tc_pos, test_substitution_of_two_double_matrix_normal_case);
    tcase_add_test(tc_pos, test_transpose_square_string_matrix);
    tcase_add_test(tc_pos, test_det_null_double_matrix);
    tcase_add_test(tc_pos, test_det_non_null_double_matrix);
    tcase_add_test(tc_pos, test_reverse_matrix_usual_case);
    tcase_add_test(tc_pos, test_mul_eq_int_matrix_on_number);
    tcase_add_test(tc_pos, test_div_eq_int_matrix_on_number);
    tcase_add_test(tc_pos, test_iterator);
    tcase_add_test(tc_pos, test_const_iterator);
    tcase_add_test(tc_neg, test_catch_throw);
    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);
    return s;
}

int main(void)
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = summary_of_two_matrix_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);


    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}