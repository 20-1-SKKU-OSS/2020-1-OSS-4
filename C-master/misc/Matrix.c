#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef enum _boolean { 
	FALSE,
	TRUE
}boolean;

#define FALSE 0
#define TRUE 1

//Vector, 벡터 구조체
typedef struct Vector_ {
	unsigned size;
	int *content;
}Vector;


//Matrix, 행렬 구조체
typedef struct Matrix_ {
	unsigned row;
	unsigned column;
	Vector *content;
}Matrix;

/* Vector constructor, 벡터 생성자 */
Vector MakeVector(int size, const int *element) {
	Vector v;
	v.size = size;
	v.content = malloc(sizeof(int)*size);
	for (int i = 0; i<size; i++)
		v.content[i] = element[i];
	return v;
}


/* Matrix constructor, 행렬 생성자 */
Matrix MakeMatrix(unsigned row, unsigned column, Vector *contents) {
	Matrix M;
	M.row = row;
	M.column = column;

	M.content = malloc(sizeof(contents->content)*row);
	for (int i = 0; i < row; i++)
		M.content[i].content = malloc(sizeof(int)*column);
	

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			M.content[i].content[j] = contents[i].content[j];
		}
	}
		
	return M;
}


/* Matrix Scalar Multiplication, 행렬 스칼라 곱 */
Matrix ScalarMultiplication(int c, Matrix m) {
	int row = m.row;
	int column = m.column;
	Vector *content = malloc(sizeof(m.content->content)*row);
	for (int i = 0; i < row; i++)
		content[i].content = malloc(sizeof(int)*column);
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			content[i].content[j] = m.content[i].content[j] * c;
		}
	}

	Matrix result = MakeMatrix(row, column, content);
	return result;
}


/* Matrix Addition, 두 행렬의 합 */
Matrix MatrixAdd(Matrix m1, Matrix m2) {
	if ((m1.row != m2.row) || (m1.column != m2.column)) return MakeMatrix(0, 0, NULL);
	int row = m1.row;
	int column = m1.column;
	Vector *content = malloc(sizeof(m1.content->content)*row);
	for (int i = 0; i < row; i++)
		content[i].content = malloc(sizeof(int)*column);
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			content[i].content[j] = m1.content[i].content[j] + m2.content[i].content[j];
		}
	}
	Matrix result = MakeMatrix(row, column, content);
	return result;
}

/* Transpose of Matrix, 행렬 전치(행렬을 90도 돌림), 미완성 */
Matrix Transpose(Matrix m) {
	int row = m.row;
	int column = m.column;
	Vector tmp;
	tmp.content = malloc(sizeof(int)*row);
	Vector *content = malloc(sizeof(tmp)*column);
	for (int i = 0; i < column; i++)
		content[i].content = malloc(sizeof(int)*row);

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			content[j].content[i] = m.content[i].content[j];
		}
	}
	Matrix result = MakeMatrix(column, row, content);
	return result;
}



Matrix MatrixMultiplication(Matrix m1, Matrix m2) {
	int row = m1.row;
	int column = m2.column;
	if ((m1.column != m2.row) && (m1.row != m2.column)) MakeMatrix(0, 0, NULL);
	int i = 0, j = 0;
	Vector tmp;

	//initialize, 만들 행열 초기화
	tmp.content = malloc(sizeof(int) * column);
	Vector *content = malloc(sizeof(tmp) * row);
	
	for (i = 0; i < row; i++)
		content[i].content = malloc(sizeof(int)*row);

	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			content[i].content[j] = 0;
	
	//곱셈 값 넣어주기
	i = 0, j = 0;
	while (i < row) {
		while (j <= column) {
			for (int k = 0; k < m1.column; k++) {
				content[i].content[j] += m1.content[i].content[k] * m2.content[k].content[j];
			}
			j++;
		}
		i++;
		j = 0;
	}

	return MakeMatrix(row, column, content);
}


/* isSquareMatrix, 정방행렬 여부 반환 */
boolean isSquareMatrix(Matrix m) {
	return m.row == m.column;
}


/* isSymmetricMatrix, 대칭행렬 여부 반환 */
boolean isSymmetricMatrix(Matrix m) {
	if (!isSquareMatrix(m)) return FALSE;
	for (int i = 0; i < m.row; i++)
		for (int j = 0; j < m.column; j++)
			if (m.content[i].content[j] != m.content[j].content[i])
				return FALSE;
	return TRUE;
}


/* print Matrix, 행렬을 출력함 */
void PrintMatrix(Matrix m) {
	if (m.row == 0) return;

	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.column; j++) {
			printf("%2d ", m.content[i].content[j]);
		}
		printf("\n");
	}
	printf("\n");
}


/* example of use, 용례 */
int main() {
	int a[3] = { 7, 0, -3 }, b[3] = { 2, 1, 4 };
	int c[2] = { 3, -1 }, d[2] = { 2, 4 }, e[2] = { 1, -1};

	Vector v1 = MakeVector(3, a);
	Vector v2 = MakeVector(3, b);
	Vector v3 = MakeVector(2, c);
	Vector v4 = MakeVector(2, d);
	Vector v5 = MakeVector(2, e);

	Vector C1[2] = { v1, v2 };
	Vector C2[3] = { v3, v4 , v5};
	
	Matrix m1 = MakeMatrix(2, 3, C1);
	Matrix m2 = MakeMatrix(3, 2, C2);

	PrintMatrix(m1);
	PrintMatrix(m2);

	PrintMatrix(MatrixAdd(m1, m2));
	PrintMatrix(ScalarMultiplication(3, m1));
	PrintMatrix(Transpose(m1));
	PrintMatrix(MatrixMultiplication(m1, m2));

	system("pause");
}
