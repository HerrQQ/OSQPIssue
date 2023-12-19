#include <stdlib.h>
#include "osqp/osqp.h"
#include "OsqpEigen/OsqpEigen.h"
#include <Eigen/Dense>
#include <iostream>

int main(int argc, char **argv) {
    Eigen::SparseMatrix<double> hessian;
    Eigen::VectorXd gradient;
    Eigen::SparseMatrix<double> linearMatrix;
    Eigen::VectorXd lowerBound;
    Eigen::VectorXd upperBound;

    short int num_var=2,num_contrains=3;
    hessian.resize(num_var,num_var);
    hessian.insert(0,0) = 1;
    hessian.insert(1,0) = -1;
    hessian.insert(0,1) = -1;
    hessian.insert(1,1) = 2;
    std::cout << "hessian:" << std::endl << hessian << std::endl;
    gradient.resize(2);
    gradient << -2, -6;
    std::cout << "gradient:" << std::endl << gradient << std::endl;
    linearMatrix.resize(3,2);
    linearMatrix.insert(0,0) = 1;
    linearMatrix.insert(0,1) = 1;
    linearMatrix.insert(1,0) = -1;
    linearMatrix.insert(1,1) = 2;
    linearMatrix.insert(2,0) = 2;
    linearMatrix.insert(2,1) = 1;
    std::cout << "linearMatrix:" << std::endl << linearMatrix << std::endl;

    lowerBound.resize(3);
    lowerBound << -OsqpEigen::INFTY, -OsqpEigen::INFTY, -OsqpEigen::INFTY;
    std::cout << "lowerBound:" << std::endl << lowerBound << std::endl;

    upperBound.resize(3);
    upperBound << 2, 2, 3;
    std::cout << "upperBound:" << std::endl << upperBound << std::endl;

    OsqpEigen::Solver solver;

    solver.settings()->setWarmStart(true);

    solver.data()->setNumberOfVariables(num_var); //设置A矩阵的列数，即n
    solver.data()->setNumberOfConstraints(num_contrains); //设置A矩阵的行数，即m
    if(!solver.data()->setHessianMatrix(hessian)) return 1;//设置P矩阵
    if(!solver.data()->setGradient(gradient)) return 1; //设置q or f矩阵。当没有时设置为全0向量
    if(!solver.data()->setLinearConstraintsMatrix(linearMatrix)) return 1;//设置线性约束的A矩阵
    if(!solver.data()->setLowerBound(lowerBound)) return 1;//设置下边界
    if(!solver.data()->setUpperBound(upperBound)) return 1;//设置上边界

    if (!solver.initSolver()) return 1;

    if (!solver.solve()) return 1;

    auto QPSolution=solver.getSolution();
    std::cout <<"size of QP solution: " << QPSolution.size()<<std::endl;
    std::cout << "Solution for x[0]: " << QPSolution(0) << std::endl;
    std::cout << "Solution for x[1]: " << QPSolution(1) << std::endl;




};