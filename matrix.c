#include <stdio.h>
#include <stdlib.h> //rand 사용 위한 전처리기
#include <time.h>   //time 사용 위한 전처리기

/* Method Declaration */
int** create_matrix(int row, int col); //행렬 생성 함수
void print_matrix(int** matrix, int row, int col); //행렬 출력함수
int free_matrix(int** matrix, int row, int col);   //행렬 동적할당 함수
int fill_data(int** matrix, int row, int col);     //행렬 데이터 입력 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);    //행렬 a+b 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //행렬 a-b 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);  // 전치행렬 구현 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 행렬 a*t 함수

int main()
{
    printf("[----- [이찬]  [2019038029] -----]\n");
    char command; 
    int row, col;
    srand(time(NULL)); // 난수생성기
    printf("Input row and col : ");
    scanf("%d %d", &row, &col);   //행개수, 열개수 입력
    int** matrix_a = create_matrix(row, col);  //행렬 a 생성(동적할당)
    int** matrix_b = create_matrix(row, col);  //행렬 b 생성(동적할당)
    int** matrix_a_t = create_matrix(col, row);
    //행렬 a의 전치 행렬 생성 전치행렬은 원래 행과 열의 반대가 됨 ex) 2x3행렬 ->3x2행렬
    //그러므로 입력받은 row,col 를 함수호출시 거꾸로 대입해줌
    printf("Matrix Created.\n");
    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //생성된 행렬이 비어있을 시-오류발생

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //사용자에게 입력받음

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col);  //생성된 배열에 값을 집어넣는 함수
            fill_data(matrix_b, row, col);  //행렬 a,b 초기화 해줌
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //행렬 a 출력함수
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //행렬 b 출력함수
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //행렬 a+b 함수
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //행렬 a-b 함수
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            //행렬a를 주대각선 기준으로 뒤집은 전치행렬 a_t 생성
            //행과 열의 크기가 반대가 되기때문에 col, row를 반대로 보내줌
            print_matrix(matrix_a_t, col, row);
            //출력도 마찬가지로 col x row 크기 행렬을 출력해야하기 때문에 반대로 보내줌
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //a의 전치행렬 a_t 생성
            multiply_matrix(matrix_a, matrix_a_t, row, col);  //행렬 a와 a_t의 곱 구하기 함수
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");   
            free_matrix(matrix_a_t, col, row); //행렬 a_t동적 메모리 해제
            free_matrix(matrix_a, row, col);   //행렬 a동적 메모리 해제
            free_matrix(matrix_b, row, col);   //행렬 b동적 메모리 해제
            break; //스위치문 탈출
        default: //잘못 입력했을 시
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break; //스위치문 탈출
        }

    }while(command != 'q' && command != 'Q'); //q입력되면서 반복문 종료

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* Check pre conditions */ //반복되기 때문에 한번만 주석으로 설명
	if (row <= 0 || col <= 0) { 
    //입력된 row,col 무언가 하나라도 0보다 작거나 같은때 = 입력이 안됐을때
		printf("Check the size of row and col!\n");
		return -1; // 오류발생!
	}
    int **matrix = (int**)malloc(sizeof(int*)*row); 
    //행크기만큼의 공간에 포인터 변수들을 담을 이중포인터변수 선언 & 공간 동적할당 
    for (int i=0;i<row;i++){
        matrix[i]=(int*)malloc(sizeof(int)*col);
    } // 한 행마다 열크기만큼의 int형 주소들을 담을 공간 동적 할당
    //이 결과 row를 행크기로, col을 열크기로 하는 행렬 생성한다고 할 수 있다.

	/* Check post conditions */ //반복되기 때문에 한번만 주석으로 설명
	if (matrix == NULL) { //행렬이 생성(동적할당)되지 않았다면
		printf("Memory Allocation Failed.\n"); //동적할당 실패
		return -1;// 오류발생!
    }
    return matrix; //만든 행렬(이중포인터)를 리턴해줌
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return; //void 함수이기 때문에 반환 x
	}
    for (int i=0;i<row;i++){ //행들 반복
        for (int j=0;j<col;j++){ // 각 열들 반복
            printf("%5d",matrix[i][j]); 
        }
        printf("\n"); //한 행 출력하고 줄 바꿈
    }    
    printf("\n");
    /* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return; //void 함수이기 때문에 반환 x
	}
}
/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i=0;i<row;i++){ // 행들이 가리키는 내부 열들 먼저 동적메모리 해제 
        free(matrix[i]);
    }
    free(matrix); //처음 동적할당한 1칸짜리 행들의 동적메모리 해제
	return 0; // 함수 종료
}
/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            matrix[i][j]=(rand()%20);//0~19사이 난수생성해 행렬 각 자리에 더해줌.
        }
    }    
	/* Check post conditions */
	if(matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    return 0; //함수 종료
}
/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int **SUMmtx= create_matrix(row, col); //행렬각 요소의 합을 받을 행렬 생성(동적할당)
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            SUMmtx[i][j]=matrix_a[i][j]+matrix_b[i][j];
        } //행렬 a+b한 각 요소들을 생성된 행렬 각 요소에 넣어줌
    }    
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL||SUMmtx == NULL) {
        //행렬 a,b,a+b 가 생성(동적할당) 되지 않았다면
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    print_matrix(SUMmtx, row, col); //a+b 행렬 출력
	free_matrix(SUMmtx, row, col);  //a+b 행렬 동적 메모리 해제
    return 0; // 함수 종료
}
/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int **DIFmtx= create_matrix(row, col); //행렬각 요소의 차를 받을 행렬 생성(동적할당)
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            DIFmtx[i][j]=matrix_a[i][j]-matrix_b[i][j];
        } //행렬 a-b한 각 요소들을 생성된 행렬 각 요소에 넣어줌
    }    
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL||DIFmtx == NULL) {
        //행렬 a,b,a-b 가 생성(동적할당) 되지 않았다면
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    print_matrix(DIFmtx, row, col); //a-b 행렬 출력
	free_matrix(DIFmtx, row, col);  //a-b 행렬 동적 메모리 해제
    return 0; //함수 종료
}
/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{  //함수에서 매개변수로 받아온 row = 입력된 col, col = 입력된 row 임
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            matrix_t[i][j]=matrix[j][i]; 
        } //행렬a를 주대각선 기준으로 뒤집은 전치행렬 a_t이기 때문에 대각선 기준 반대편의 값이 a_t에 들어감
    }     //ex) 행렬a가 2x3이라면 3x2 행렬a_t로 각 요소들의 값이 들어감 
	/* Check post conditions */
	if (matrix == NULL||matrix_t == NULL) { //행렬과 전치행렬이 생성(동적할당)되지 않았다면
		printf("Memory Allocation Failed.\n");
		return -1; //오류발생
    }
    return 0; //함수종료
}
/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
      /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int **MULmtx= create_matrix(row, row);
    //ex) 크기가2x3 행렬a 와 크기가 3x2인 전치 행렬a_t를 곱할시 2*2크기의 행렬이 만들어짐 
    //새로 만들어지는 행렬곱의 결과인 행렬은 행렬과 그 전치행렬의 곱이므로 행과 열이 처음생성한 행렬의 행과 같다. 

    for (int k=0;k<row;k++){ //행렬 a의 행크기만큼 반복
        for (int i=0;i<row;i++){ // 행렬 a_t의 열크기 만큼 반복  
            int sum=0; //행렬곱 중간 계산값 저장할 sum
            for (int j=0;j<col;j++){ //행렬 a의 열크기 만큼 반복
                sum+=matrix_a[k][j]*matrix_t[j][i];
            }       //행렬곱의 정의에 따라 계산
            MULmtx[k][i]=sum; 
        }
    }
	/* Check post conditions */
	if (matrix_a == NULL || matrix_a == NULL||MULmtx == NULL) {
        //행렬 ,전치행렬, 행렬곱 행렬이 생성(동적할당)되지 않았다면 
		printf("Memory Allocation Failed.\n");
		return -1; //오류 발생
    }
    print_matrix(MULmtx, row, row); //a x t행렬 출력
	free_matrix(MULmtx, row, col);  //a x t행렬 동적 메모리 해제
    return 0; //함수종료
 }