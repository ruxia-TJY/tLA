#include"tLA.h"

Status toMat(Mat* dst, float** var, int row, int col)
{

	dst->row = row;
	dst->col = col;
	
	float** Rmatrix = (float**)malloc(sizeof(float*) * row);
	if (Rmatrix == NULL)goto err_mem;

	for (int i = 0; i < row; i++) {
		Rmatrix[i] = (float*)malloc(sizeof(float) * col);
		if (Rmatrix[i] == NULL)goto err_mem;
	}

	// set value
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Rmatrix[i][j] = *((float*)var + col * i + j);
		}
	}

	dst->value = Rmatrix;
	return TLA_OK;

err_mem:
	free(Rmatrix);
	return TLA_ERR_MEM;
}

Status toEyeMat(Mat* dst)
{
	if (dst->row != dst->col)goto err;

	for (int i = 0; i < dst->row; i++) {
		for (int j = 0; j < dst->col; j++) {
			dst->value[i][j] = (i == j) ? 1 : 0;
		}
	}
	return TLA_OK;

err:
	return TLA_ERR_CARV;
}

Status toZeroMat(Mat* dst)
{
	for (int i = 0; i < dst->row; i++) {
		for (int j = 0; j < dst->col; j++) {
			dst->value[i][j] = 0;
		}
	}
	return TLA_OK;
}

Status eyeMat(Mat* dst, int order)
{
	dst->row = order;
	dst->col = order;

	float** matrix = (float**)malloc(sizeof(float*) * order);
	for (int i = 0; i < order; i++) {
		matrix[i] = (float*)malloc(sizeof(float) * order);
	}

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			matrix[i][j] = i == j ? 1 : 0;
		}
	}
	dst->value = matrix;

	return TLA_OK;
}

Status zeroMat(Mat* dst, int row, int col)
{
	dst->row = row;
	dst->col = col;
	float** matrix = (float**)malloc(sizeof(float*) * row);
	for (int i = 0; i < row; i++) {
		matrix[i] = (float*)malloc(sizeof(float) * col);
	}

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix[i][j] = 0;

	dst->value = matrix;
	return TLA_OK;
}

/**
 * showMat
 * ´òÓ¡Mat.
 *
 * \param Matrix
 * \return
 */
Status showMat(Mat Matrix)
{
	for (int i = 0; i < Matrix.row; i++) {
		for (int j = 0; j < Matrix.col; j++) {
			printf("\t%f\t", Matrix.value[i][j]);
		}
		printf("|\n");
	}
	return TLA_OK;
}

Status copyMat(Mat* dst, Mat* src)
{
	dst->row = src->row;
	dst->col = src->col;

	float** matrix = (float**)malloc(sizeof(float*) * dst->row);
	for (int i = 0; i < dst->row; i++) {
		matrix[i] = (float*)malloc(sizeof(float) * dst->col);
	}

	for (int i = 0; i < dst->row; i++)
		for (int j = 0; j < dst->col; j++)
			matrix[i][j] = src->value[i][j];

	dst->value = matrix;
	return TLA_OK;
}

Status addMat(Mat* dst, Mat* src)
{
	if ((dst->row != src->row) || (dst->col != src->col))
		goto Err;

	for (int i = 0; i < dst->row; i++) {
		for (int j = 0; j < dst->col; j++) {
			dst->value[i][j] += src->value[i][j];
		}
	}

	return TLA_OK;
Err:
	return TLA_ERR_CARV;
}

Status subMat(Mat* dst, Mat* src)
{
	if ((dst->row != src->row) || (dst->col != src->col))
		goto Err;

	for (int i = 0; i < dst->row; i++) {
		for (int j = 0; j < dst->col; j++) {
			dst->value[i][j] -= src->value[i][j];
		}
	}
	return TLA_OK;
Err:
	return TLA_ERR_CARV;
}

Status mulMat(Mat* a, Mat* b, Mat* dst)
{

	if (a->col != b->row)goto Err;

	dst->row = b->row;
	dst->col = a->col;

	float** Rmatrix = (float**)malloc(sizeof(float*) * dst->row);
	for (int i = 0; i < dst->row; i++) {
		Rmatrix[i] = (float*)malloc(sizeof(float) * dst->col);
	}

	for (int i = 0; i < dst->row; i++) {
		for (int j = 0; j < dst->col; j++) {
			float f = 0;
			for (int x = 0; x < a->col; x++) {
				f += a->value[i][x] * b->value[x][j];
			}

			Rmatrix[i][j] = f;
		}
	}
	dst->value = Rmatrix;

	return TLA_OK;
Err:
	return TLA_ERR_CARV;
}

Status mulnMat(Mat* src, float a)
{
	for (int i = 0; i < src->row; i++) {
		for (int j = 0; j < src->col; j++) {
			src->value[i][j] *= a;
		}
	}
	return TLA_OK;
}

Status tranMat(Mat* src)
{
	if (src->row != src->col) {
		int temp = src->row;
		src->row = src->col;
		src->col = temp;
	}

	float** Rmatrix = (float**)malloc(sizeof(float*) * src->row);
	for (int i = 0; i < src->row; i++) {
		Rmatrix[i] = (float*)malloc(sizeof(float) * src->col);
	}

	for (int i = 0; i < src->row; i++) {
		for (int j = 0; j < src->col; j++) {
			Rmatrix[i][j] = src->value[j][i];
		}
	}

	free(src->value);
	src->value = Rmatrix;
	return TLA_OK;
}

int isEqualMat(Mat* a, Mat* b)
{
	if ((a->col != b->col) || (a->row != b->row)) return 0;

	for (int i = 0; i < a->row; i++) {
		for (int j = 0; j < a->col; j++) {
			if (a->value[i][j] != b->value[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}

int isSymmetricMat(Mat* src)
{
	if (src->row != src->col)return 0;

	for (int i = 0; i < (src->row / 2); i++) {
		for (int j = 0; j < src->col; j++) {
			if (src->value[i][j] != src->value[j][i]) {
				return 0; break;
			}
		}
	}
	return 1;
}


int isSkewSymmetricMat(Mat* src)
{
	Mat m;
	Mat t;
	copyMat(&m, src);
	copyMat(&t, src);

	mulnMat(&m, -1);
	tranMat(&t);

	if (!isEqualMat(&m, &t))return 0;

	return 1;
}

int isEyeMat(Mat* src)
{
	if (src->row != src->col)return 0;

	for (int i = 0; i < src->row; i++) {
		for (int j = 0; j < src->col; j++) {
			if (i == j) {
				if (src->value[i][j] != 1)return 0;
			}
			else {
				if (src->value[i][j] != 0)return 0;
			}
		}
	}
	return 1;
}

int isOrthogonalMat(Mat* src)
{
	Mat dst;
	copyMat(&dst, src);
	tranMat(&dst);

	mulMat(&src, &dst, &dst);

	if (isEyeMat(&dst))return 0;

	return 1;
}

int isHomeMat(Mat* a, Mat* b)
{
	return !((a->col != b->col) || (a->row != b->row));
}

int isDiagMat(Mat* mat)
{
	for (int i = 0; i < mat->row; i++) {
		for (int j = 0; j < mat->col; j++) {
			if (i != j) {
				if (mat->value[i][j] != 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

