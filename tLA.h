/*****************************************************************//**
 * \file   tLA.h
 * \brief
 *
 * \author JiayuTu
 * \date   June 2022
 *********************************************************************/
#ifndef TLA_H
#define TLA_H

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct Determinant {
	float** value;		// two-dimensional arrays
	int row;			// row of determinant
	int col;			// column of determinant
}Det;

typedef struct Matrix {
	float** value;		// two-dimensional arrays
	int row;			// row of Matrix
	int col;			// column of Matrix
}Mat;

/// <summary>
/// Status of return
/// </summary>
typedef enum status {
	TLA_OK = 0,			// OK
	TLA_ERR_MEM,		// Error: memory
	TLA_ERR_CARV,		// Error: Column and Row value
}Status;


/// <summary>
/// toMat
/// convert two-dimensional array to Mat
/// </summary>
/// <param name="dst">point of Mat</param>
/// <param name="var">point of two-dimensional arrays</param>
/// <param name="row">row of two-dimensional</param>
/// <param name="col">column of two-dimensional</param>
/// <returns></returns>
Status toMat(Mat* dst, float** var, int row, int col);

/// <summary>
/// toEyeMat
/// convert Mat to identity matrix
/// </summary>
/// <param name="dst">point of Mat</param>
/// <returns></returns>
Status toEyeMat(Mat* dst);

/// <summary>
/// toZeroMat
/// convert Mat to zero matrix
/// </summary>
/// <param name="dst">point of Mat</param>
/// <returns></returns>
Status toZeroMat(Mat* dst);


/// <summary>
/// eyeMat
/// create a identity matrix
/// </summary>
/// <param name="dst"></param>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns></returns>
Status eyeMat(Mat* dst, int row,int col);

/// <summary>
/// zeroMat
/// create a zero matrix
/// </summary>
/// <param name="dst"></param>
/// <param name="row"></param>
/// <param name="col"></param>
/// <returns></returns>
Status zeroMat(Mat* dst, int row, int col);

/// <summary>
/// showMat
/// print a Mat
/// </summary>
/// <param name="Matrix"></param>
/// <returns></returns>
Status showMat(Mat Matrix);

/// <summary>
/// copyMat
/// copy Mat
/// </summary>
/// <param name="dst"></param>
/// <param name="src"></param>
/// <returns></returns>
Status copyMat(Mat* dst, Mat* src);

/// /// <summary>
/// addMat
/// add src Mat to dst Mat
/// </summary>
/// <param name="dst"></param>
/// <param name="src"></param>
/// <returns></returns>
Status addMat(Mat* dst, Mat* src);

/// <summary>
/// subMat
/// 矩阵相减
/// </summary>
/// <param name="dst"></param>
/// <param name="src"></param>
/// <returns></returns>
Status subMat(Mat* dst, Mat* src);

/// <summary>
/// mulMat
/// 矩阵相乘
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="dst"></param>
/// <returns></returns>
Status mulMat(Mat* a, Mat* b, Mat* dst);

/// <summary>
/// mulnMat
/// 矩阵数乘
/// </summary>
/// <param name="src"></param>
/// <param name="a"></param>
/// <returns></returns>
Status mulnMat(Mat* src, float a);

/// <summary>
/// tranMat
/// 转置矩阵
/// </summary>
/// <param name="src"></param>
/// <returns></returns>
Status tranMat(Mat* src);

/// <summary>
/// isEqualMat
/// 判断是否为相等矩阵
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int isEqualMat(Mat* a, Mat* b);

/// <summary>
/// isSymmetricMat
/// 判断是否为对称矩阵
/// </summary>
/// <param name="src"></param>
/// <returns></returns>
int isSymmetricMat(Mat* src);

/// <summary>
/// isSkewSymmetricMat
/// 判断是否为斜对称矩阵
/// </summary>
/// <param name="src"></param>
/// <returns></returns>
int isSkewSymmetricMat(Mat* src);

/// <summary>
/// isEyeMat
/// 判断是否为单位矩阵
/// </summary>
/// <param name="src"></param>
/// <returns></returns>
int isEyeMat(Mat* src);

/// <summary>
/// isOrthogonalMat
/// 判断是否为正交矩阵
/// </summary>
/// <param name="src"></param>
/// <returns></returns>
int isOrthogonalMat(Mat* src);

/// <summary>
/// isHomeMat
/// 判断是否为同型矩阵
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int isHomeMat(Mat* a, Mat* b);

/// <summary>
/// isDiagMat
/// 判断是否为对角矩阵
/// </summary>
/// <param name="mat"></param>
/// <returns></returns>
int isDiagMat(Mat* mat);


#endif // !TLA_H