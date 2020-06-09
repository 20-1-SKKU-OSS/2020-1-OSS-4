# Team 4
 * [홈페이지](#HOME_PAGE)
 * [팀소개](#Members)
 * [프로젝트 소개](#about_project)
 * [활동 방법](#how_to)
 * [활동 계획](#plan)
 * [개인별 기여방법](#contribute)

## <div id = "HOME_PAGE">홈페이지</div>
https://20-1-skku-oss.github.io/2020-1-OSS-4/

## <div id = "Members">팀소개</div>
### 팀장
**정승혁**
> 이메일: tmdgur325@gmail.com<br>
> GitHub ID: [meltingOcean](https://github.com/meltingocean)<br>
> 경력: 성균관대학교 소프트웨어학과 재학중<br>
> **Data Structure Project 담당**<br>

### 팀원
**권윤영**
> 이메일: nicesteph@naver.com<br>
> GitHub ID: [yoonyoungkwon](https://github.com/yoonyoungkwon)<br>
> 경력: 성균관대학교 소프트웨어학과 재학중<br>
> **Data Structure Project 담당**<br>

**윤태웅**
> 이메일: woongman1109@naver.com<br>
> GitHub ID: [woongman1109](https://github.com/woongman1109)<br>
> 경력: 성균관대학교 나노공학과 재학중 / 소프트웨어학과 복수 전공중<br>
> **MISC Project 담당**<br>

**이찬영**
> 이메일: ckckdud123@naver.com<br>
> GitHub ID: [ckckdud3](https://github.com/ckckdud3)<br>
> 경력: 성균관대학교 소프트웨어학과 재학중<br>
> **Data Structure Project 담당**<br>

**최영우**
> 이메일: cyw7515@naver.com<br>
> GitHub ID: [Yongware](https://github.com/yongware)<br>
> 경력: 성균관대학교 소프트웨어학과 재학중<br>
> **MISC Project 담당**<br>

## <div id = "about_project">프로젝트 소개</div>
 * Algorithms/C 프로젝트를 선정했습니다.
 * 자주 사용되는 알고리즘을 정리하고 그것에 대한 이해를 돕는 프로젝트입니다.

## 프로젝트별 진행 사항
**1. Data Structure Project**
 ## b+tree 추가<br>
        - NUM_KEYS 상수를 설정하여서 원하는 노드크기의 B+tree를 생성하여 insert 후 만들어진 b+tree를 c로 구현하는것 완료.
**2. MISC Project**
 ## bit단위 연산 라이브러리 생성 및 추가<br>
	- Subtractable_check
	- ByteSwap
	- isGreater
	- fitsBits
	- logicalShift
	- countbit
	- rotate
	- float_absolute_value
	- int_to_float_cast
	- float_twice
	
 ## Vector 구조체와 관련 연산 추가 <br>
	- Vector 구조체 및 생성자 추가 (vector, MakeVector)
	- Vector의 스칼라곱, Vector간 합 구현 (VecotrScalarMultiplication, VectorAdd)
	- Vector의 내적과 길이 구현 (InnerProduct, VectorLength)
	- 두 Vector 사이 각(cos), Vector의 사영 구현 (VectorAngleCos, VectorProjection)
	
## MIPS Architecture Operation Simulator 기능 추가 <br>
	- cmd를 이용한 shell로 명령어를 실행해 MIPS Architecture 기반 instruction을 시뮬레이션할 수 있음(.bin, .dat 등의 바이너리 파일을 이용할 수 있음)
	- read <filename>: 지정된 파일을 읽어 instruction의 형태로 출력함
	- [WIP V3] loadinst <filename>: 지정된 파일을 읽어 binary code를 instruction으로 변환해 가상 instruction data memory 영역에 저장함
	- loaddata <filename>: 지정된 파일을 읽어 binary code를 데이터로 변환해 가상 data memory 영역에 저장함
	- [WIP V3] run [number]: 가상 instruction memory에 저장된 instruction을 실행하여 가상 register에 반영
		- [number]: 지정한 숫자만큼의 명령어를 실행함(지정하지 않는 경우 instruction 끝까지 실행함)
	- registers: 현재 register 값들을 출력함($0 ~ #31, PC, HI LO)
	
 ## Matrix(행렬) 구조체와 관련 연산 추가 <br>
	- Matrix 구조체 및 생성자 추가(Matrix, MakeMatrix)
	- Matrix의 스칼라곱, Matrix간 합 구현 (MatrixScalarMulitiplication, MatrixAdd)
	- Matrix 출력 함수 구현 (PrintMatrix)
	- Matrix의 전치(Transpose) 구현 (Transpose)
	- 두 Matrix간의 곱 구현 (MatrixMultiplication)
	- 정방행렬(Square Matrix), 대칭행렬(Symmetric Matrix) 판별 함수 구현 (isSquareMatrix, isSymmetric Matrix)


## 기존 프로젝트 내용
전체 알고리즘 리스트: [DIRECTORY.md](https://github.com/20-1-SKKU-OSS-4/blob/master/C-master/DIRECTORY.md)

## LeetCode Algorithm (문제풀이 사이트 LeetCode에 올라온 문제에 대한 풀이)
- [LeetCode](https://leetcode.com/problemset/all/): LeetCode 알고리즘 문제 사이트
- [Solution](https://github.com/TheAlgorithms/C/tree/master/leetcode): 요청이 들어온 문제나 직접 푼 문제 대한 풀이

## Computer Oriented Statistical Methods (통계학 Method 라이브러리)
	- Gauss_Elimination
	- Lagrange_Theorem
	- Mean
	- Median
	- Seidal
	- Simpson's_1-3rd_rule.c
	- Variance
	- statistic (C Lib)

## Conversions (진법 변환)
	- binary_to_decimal: 2진수에서 10진수로의 변환
	- decimal_to_binary: 10진수에서 2진수로의 변환
	- decimal_to_hexa: 10진수에서 16진수로의 변환
	- decimal_to_octal: 10진수에서 8진수로의 변환
	- to_decimal: x진수에서 10진수로의 변환
	- hexa_to_octal: :16진수에서 8진수로의 변환


## Data Structures (자료구조)
	- stack
	- queue
		- singly_linked_list based queue
		- deque (double-ended queue)
	- dictionary
	- linked_list
		- singly_link_list_deletion
		- stack_using_linkedlists
	- binary_trees
		- create_node
		- recursive_traversals
	- trie
		- trie
	- heap
		- min heap
		- max heap 


## Searching (탐색 방법)
	- Linear_Search
	- Binary_Search
	- Other_Binary_Search
	- Jump_Search
	- Fibonacci_Search
	- Interpolation_Search
	- Modified_Binary_Search


## Sorting (정렬 방법)
	- BinaryInsertionSort
	- BubbleSort
	- BitonicSort
	- BucketSort
	- BogoSort
	- comb_sort
	- CountingSort
	- Cycle Sort
	- gnome_sort
	- PartitionSort
	- ShellSort
	- RadixSort
	- InsertionSort
	- MergeSort
	- OtherBubbleSort
	- PancakeSort
	- QuickSort
	- SelectionSort
	- ShakerSort
	- HeapSort
	- StoogeSort


## Hashing (해쉬 함수)
	- sdbm
	- djb2
	- xor8 (8 bit)
	- adler_32 (32 bit)


## Misc (기타 함수)
	- ArmstrongNumber	
	- Binning
	- Factorial
	- Fibonacci
	- Greatest Common Divisor	
	- isArmstrong
	- LongestSubSequence
	- palindrome
	- prime factorization	
	- QUARTILE
	- rselect
	- strongNumber
	- TowerOfHanoi
	- Greatest Common Divisor
	- Sudoku Solver
	- prime factorization
	- PID Controller

## Project Euler
	- Problem 1
	- Problem 2
	- Problem 3
	- Problem 4
	- Problem 5
	- Problem 6
	- Problem 7


## exercism
In this directory you will find (in the right order):
* hello-world
* isogram
* acronym
* word-count
* rna-transcription

## Simple Client Server Implementation (간단한 서버와 사용자 구현)
This directory contains
* client.c
* server.c


## <div id="#how_to">활동 방법</div>
* TheAlgorithms에 빠져 있는 자료구조(양방향 연결 리스트, b+ 트리 등), 알고리즘(Matrix 연산, bitwise 연산 등)을 구현</br>
* 테스트를 거쳐Pull Request를 요청하는 방식으로 프로젝트에 기여한다.</br>
* 활동 기록을 문서화하여 정리하고, 또한 ReadMe 마크다운의 번역 등을 통해서도 프로젝트에 기여하도록 한다.</br>


## <div id="plan">활동 계획</div>
20.5: 팀 프로젝트 선정 및 개인별 기여 방식 논의</br>
20.6.1주차: 프로젝트 소개 페이지, wiki, README 생성 및 작성</br>
20.6~: 프로젝트 진행</br>


## <div id="contribute">개인별 기여방법</div>
**정승혁(팀장)**
> 1. Data Structure 프로젝트<br>
>  * b-tree 등 자주 쓰이는 tree structure 구현<br>
>  * 최신 프로그래밍 동향을 파악해 그에 맞는 Data Structure 구현<br>
>  * 알고리즘적 버그가 있는 부분 수정<br>
> 2. Issue에 올라온 버그 및 요청 파악<br>
> 3. ReadMe에 기여한 내용 반영<br>
> 4. Project 정적페이지 관리<br>


**권윤영**
> 1. Data Structure 프로젝트 <br>
>  * Double LL과 관련된 라이브러리 구현 <br>
>  * 자주 쓰이나 아직 구현되지 않은 Data Structure 구현 <br>
>  * Data Structure 코드들에 한글 주석 추가 <br>
> 2. Issue에 올라온 버그 파악 <br>
> 3. Project 정적페이지 관리 <br>

**윤태웅**
> 1. MISC 프로젝트<br>
>  * 행렬 연산 등 C언어 알고리즘 라이브러리 구현<br>
>  * Bitwise Operation 관련 라이브러리 구현<br>
> 2. Wiki에 기여한 내용 반영<br>
> 3. 메모리 관리에 대한 전반적 점검<br>
>  * 동적할당 등으로 일어나는 NPE 등의 에러 제거<br>

**이찬영**
> 1. Data Structure 프로젝트<br>
>  * 바이토닝 정렬 등 Data Structur 내의 Sorting 라이브러리 구현<br>
>  * Queue 등 자주 쓰이는 대중적인 Data Structure 구현<br>
> 2. Wiki에 기여한 내용들 반영<br>
> 3. Issue 파악 및 관리<br>


**최영우**
> 1. MISC 프로젝트 <br>
>  * C언어 알고리즘 라이브러리 구현<br>
>  * 벡터 및 행렬 연산 관련 라이브러리 구현<br>
>  * Bitwise Operation 라이브러리 설계 및 구현 <br>
>  * 알고리즘상의 에러 제거 <br>
> 2. Issue 추가 및 관리 <br>
> 3. ReadMe 관리 및 기여한 내용 반영<br>
>  * MISC 프로젝트 진행 사항 및 완료 사항 정리


