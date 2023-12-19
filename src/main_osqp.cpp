// #include <stdlib.h>
// #include "osqp/osqp.h"
// #include <string>

// int main(int argc, char **argv) {
//     /* Load problem data */
//     OSQPFloat P_x[3] = {4.0, 1.0, 2.0, };
//     OSQPInt P_nnz = 3;
//     OSQPInt P_i[3] = {0, 0, 1, };
//     OSQPInt P_p[3] = {0, 1, 3, };
//     OSQPFloat q[2] = {1.0, 1.0, };
//     OSQPFloat A_x[4] = {1.0, 1.0, 1.0, 1.0, };
//     OSQPInt A_nnz = 4;
//     OSQPInt A_i[4] = {0, 1, 0, 2, };
//     OSQPInt A_p[3] = {0, 2, 4, };
//     OSQPFloat l[3] = {1.0, 0.0, 0.0, };
//     OSQPFloat u[3] = {1.0, 0.7, 0.7, };
//     OSQPInt n = 2;
//     OSQPInt m = 3;



//     // P_x[3]： 这是矩阵 P 的非零元素的数组。在这个例子中，P 是一个 2x2 的对称矩阵，由于是对称的，只需要存储上三角或下三角的元素。这里 {4.0, 1.0, 2.0} 表示的是上三角的元素。

//     // P_nnz： 这是矩阵 P 的非零元素的数量。在这个例子中，P_nnz 等于 3。

//     // P_i[3]： 这是矩阵 P 的非零元素的行索引数组。对应于 P_x 中的每个非零元素，P_i 存储其行索引。在这里，{0, 0, 1} 表示 {4.0, 1.0, 2.0} 对应的行索引。

//     // P_p[3]： 这是矩阵 P 的列指针数组。它指示每一列的起始位置在 P_x 和 P_i 数组中的索引。在这个例子中，{0, 1, 3} 表示第一列从索引 0 开始，第二列从索引 1 开始，第三列从索引 3 开始。

//     // q[2]： 这是目标函数的线性项。在这个例子中，目标函数是一个二次函数，q 中存储的是线性项的系数。

//     // A_x[4]： 这是约束矩阵 A 的非零元素的数组。在这个例子中，A_x 存储了矩阵 A 的所有非零元素，即 {1.0, 1.0, 1.0, 1.0}。

//     // A_nnz： 这是矩阵 A 的非零元素的数量。在这个例子中，A_nnz 等于 4。

//     // A_i[4]： 这是矩阵 A 的非零元素的行索引数组。对应于 A_x 中的每个非零元素，A_i 存储其行索引。在这里，{0, 1, 0, 2} 表示 {1.0, 1.0, 1.0, 1.0} 对应的行索引。

//     // A_p[3]： 这是矩阵 A 的列指针数组，指示每一列的起始位置在 A_x 和 A_i 数组中的索引。

//     // l[3]： 这是约束的下界。在这个例子中，l 存储了每个约束的下界，即 {1.0, 0.0, 0.0}。

//     // u[3]： 这是约束的上界。在这个例子中，u 存储了每个约束的上界，即 {1.0, 0.7, 0.7}。

//     // n： 问题的变量数，也就是优化问题中的变量维度。在这个例子中，n 等于 2。

//     // m： 问题的约束数。在这个例子中，m 等于 3。


//     /* Exitflag */
//     OSQPInt exitflag = 0;

//     /* Solver, settings, matrices */
//     OSQPSolver   *solver;
//     OSQPSettings *settings;
//     OSQPCscMatrix* P = static_cast<OSQPCscMatrix*>(std::malloc(sizeof(OSQPCscMatrix)));
//     OSQPCscMatrix* A = static_cast<OSQPCscMatrix*>(std::malloc(sizeof(OSQPCscMatrix)));

//     /* Populate matrices */
//     csc_set_data(A, m, n, A_nnz, A_x, A_i, A_p);
//     csc_set_data(P, n, n, P_nnz, P_x, P_i, P_p);

//     /* Set default settings */
//     settings = (OSQPSettings *)malloc(sizeof(OSQPSettings));
//     if (settings) {
//         osqp_set_default_settings(settings);
//         settings->alpha = 1.0; /* Change alpha parameter */
//     }

//     /* Setup solver */
//     exitflag = osqp_setup(&solver, P, q, A, l, u, m, n, settings);

//     /* Solve problem */
//     if (!exitflag) exitflag = osqp_solve(solver);

//     /* Cleanup */
//     osqp_cleanup(solver);
//     if (A) std::free(A);
//     if (P) std::free(P);
//     if (settings) free(settings);

//     return (int)exitflag;
// };