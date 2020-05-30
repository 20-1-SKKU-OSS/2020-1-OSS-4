#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/* Check the struct form, 벡터 구조체 */
typedef struct vector_ {
	unsigned size;
	int *content;
}vector;

/* Vector constructor, 벡터 생성자 */
vector MakeVector(int size, const int *element) {
	vector v;
	v.size = size;
	v.content = malloc(sizeof(int)*size);
	for(int i=0; i<size; i++)
		v.content[i] = element[i];
	return v;
}

/* Vector Scalar Multiplication, 벡터 스칼라 곱 */
vector VectorScalarMultiplication(int c, vector v) {
	int *content = malloc(sizeof(int)*v.size);
	for (int i = 0; i < v.size; i++)
		content[i] = v.content[i] * c;

	vector result = MakeVector(v.size, content);
	return result;
}

/* Vector Addition, 벡터의 합 */
vector VectorAdd(vector v1, vector v2) {
	if (v1.size != v2.size) return;

	int *content = malloc(sizeof(int)*v1.size);
	for (int i = 0; i < v1.size; i++)
		content[i] = v1.content[i] + v2.content[i];

	vector result = MakeVector(v1.size, content);	
	return result;
}


/* innerProduct of two Vectors, 벡터의 내적 */
int InnerProduct(vector v1, vector v2) {
	if (v1.size != v2.size) return;
	int result = 0;
	for (int i = 0; i < v1.size; i++)
		result = v1.content[i] * v2.content[i];
	return result;
}


/* Length of vector, 벡터의 길이 */
float VectorLength(vector v) {
	float result = 0.0;
	for (int i = 0; i < v.size; i++)
		result += v.content[i] * v.content[i];
	result = sqrt(result);
	return result;
}

/* Angle between two vectors (cos A), 두 벡터 사이의 각 (코사인) */
float VectorAngleCos(vector v1, vector v2) {
	if (v1.size != v2.size) return;
	float result = 0.0;
	result = InnerProduct(v1, v2) / (VectorLength(v1)*VectorLength(v2));
	return result;
}

/* Projection of one to the other, 한 벡터의 다른 벡터로의 사영 */
float VectorProjection(vector v1, vector v2) {
	if (v1.size != v2.size) return;
	float result = 0.0;
	result = VectorLength(v1) * VectorAngleCos(v1, v2);
	return result;
}

//for example, 사용 예시 main
int main() {
	
	int size1 = 3, size2 = 3;
	int *content1 = malloc(sizeof(int)*size1);
	int *content2 = malloc(sizeof(int)*size2);
	
	for (int i = 0; i < 3; i++) {
		content1[i] = i * 3;
		content2[i] = i * -1;
	}

	vector v1 = MakeVector(size1, content1);
	vector v2 = MakeVector(size2, content2);
 	vector v3 = VectorScalarMultiplication(4, v2);
	vector v4 = VectorAdd(v1, v2);

  	printf("%d\n", InnerProduct(v3, v4));
	printf("%.3f\n", VectorAngleCos(v1, v2));
	printf("%.3f %.3f %.3f %.3f\n", VectorLength(v1), VectorLength(v2));
	printf("%.3f\n", VectorProjection(v1, v2));

	system("pause");
}
