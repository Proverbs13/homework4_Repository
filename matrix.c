#include <stdio.h>
#include <stdlib.h> //rand ��� ���� ��ó����
#include <time.h>   //time ��� ���� ��ó����

/* Method Declaration */
int** create_matrix(int row, int col); //��� ���� �Լ�
void print_matrix(int** matrix, int row, int col); //��� ����Լ�
int free_matrix(int** matrix, int row, int col);   //��� �����Ҵ� �Լ�
int fill_data(int** matrix, int row, int col);     //��� ������ �Է� �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);    //��� a+b �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //��� a-b �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);  // ��ġ��� ���� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // ��� a*t �Լ�

int main()
{
    printf("[----- [����]  [2019038029] -----]\n");
    char command; 
    int row, col;
    srand(time(NULL)); // ����������
    printf("Input row and col : ");
    scanf("%d %d", &row, &col);   //�ళ��, ������ �Է�
    int** matrix_a = create_matrix(row, col);  //��� a ����(�����Ҵ�)
    int** matrix_b = create_matrix(row, col);  //��� b ����(�����Ҵ�)
    int** matrix_a_t = create_matrix(col, row);
    //��� a�� ��ġ ��� ���� ��ġ����� ���� ��� ���� �ݴ밡 �� ex) 2x3��� ->3x2���
    //�׷��Ƿ� �Է¹��� row,col �� �Լ�ȣ��� �Ųٷ� ��������
    printf("Matrix Created.\n");
    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //������ ����� ������� ��-�����߻�

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
        scanf(" %c", &command); //����ڿ��� �Է¹���

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n"); 
            fill_data(matrix_a, row, col);  //������ �迭�� ���� ����ִ� �Լ�
            fill_data(matrix_b, row, col);  //��� a,b �ʱ�ȭ ����
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //��� a ����Լ�
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col); //��� b ����Լ�
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //��� a+b �Լ�
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //��� a-b �Լ�
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            //���a�� �ִ밢�� �������� ������ ��ġ��� a_t ����
            //��� ���� ũ�Ⱑ �ݴ밡 �Ǳ⶧���� col, row�� �ݴ�� ������
            print_matrix(matrix_a_t, col, row);
            //��µ� ���������� col x row ũ�� ����� ����ؾ��ϱ� ������ �ݴ�� ������
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //a�� ��ġ��� a_t ����
            multiply_matrix(matrix_a, matrix_a_t, row, col);  //��� a�� a_t�� �� ���ϱ� �Լ�
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");   
            free_matrix(matrix_a_t, col, row); //��� a_t���� �޸� ����
            free_matrix(matrix_a, row, col);   //��� a���� �޸� ����
            free_matrix(matrix_b, row, col);   //��� b���� �޸� ����
            break; //����ġ�� Ż��
        default: //�߸� �Է����� ��
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break; //����ġ�� Ż��
        }

    }while(command != 'q' && command != 'Q'); //q�ԷµǸ鼭 �ݺ��� ����

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    /* Check pre conditions */ //�ݺ��Ǳ� ������ �ѹ��� �ּ����� ����
	if (row <= 0 || col <= 0) { 
    //�Էµ� row,col ���� �ϳ��� 0���� �۰ų� ������ = �Է��� �ȵ�����
		printf("Check the size of row and col!\n");
		return -1; // �����߻�!
	}
    int **matrix = (int**)malloc(sizeof(int*)*row); 
    //��ũ�⸸ŭ�� ������ ������ �������� ���� ���������ͺ��� ���� & ���� �����Ҵ� 
    for (int i=0;i<row;i++){
        matrix[i]=(int*)malloc(sizeof(int)*col);
    } // �� �ึ�� ��ũ�⸸ŭ�� int�� �ּҵ��� ���� ���� ���� �Ҵ�
    //�� ��� row�� ��ũ���, col�� ��ũ��� �ϴ� ��� �����Ѵٰ� �� �� �ִ�.

	/* Check post conditions */ //�ݺ��Ǳ� ������ �ѹ��� �ּ����� ����
	if (matrix == NULL) { //����� ����(�����Ҵ�)���� �ʾҴٸ�
		printf("Memory Allocation Failed.\n"); //�����Ҵ� ����
		return -1;// �����߻�!
    }
    return matrix; //���� ���(����������)�� ��������
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return; //void �Լ��̱� ������ ��ȯ x
	}
    for (int i=0;i<row;i++){ //��� �ݺ�
        for (int j=0;j<col;j++){ // �� ���� �ݺ�
            printf("%5d",matrix[i][j]); 
        }
        printf("\n"); //�� �� ����ϰ� �� �ٲ�
    }    
    printf("\n");
    /* Check post conditions */
	 if (matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return; //void �Լ��̱� ������ ��ȯ x
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
    for (int i=0;i<row;i++){ // ����� ����Ű�� ���� ���� ���� �����޸� ���� 
        free(matrix[i]);
    }
    free(matrix); //ó�� �����Ҵ��� 1ĭ¥�� ����� �����޸� ����
	return 0; // �Լ� ����
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
            matrix[i][j]=(rand()%20);//0~19���� ���������� ��� �� �ڸ��� ������.
        }
    }    
	/* Check post conditions */
	if(matrix == NULL) {
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    return 0; //�Լ� ����
}
/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int **SUMmtx= create_matrix(row, col); //��İ� ����� ���� ���� ��� ����(�����Ҵ�)
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            SUMmtx[i][j]=matrix_a[i][j]+matrix_b[i][j];
        } //��� a+b�� �� ��ҵ��� ������ ��� �� ��ҿ� �־���
    }    
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL||SUMmtx == NULL) {
        //��� a,b,a+b �� ����(�����Ҵ�) ���� �ʾҴٸ�
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    print_matrix(SUMmtx, row, col); //a+b ��� ���
	free_matrix(SUMmtx, row, col);  //a+b ��� ���� �޸� ����
    return 0; // �Լ� ����
}
/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    int **DIFmtx= create_matrix(row, col); //��İ� ����� ���� ���� ��� ����(�����Ҵ�)
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            DIFmtx[i][j]=matrix_a[i][j]-matrix_b[i][j];
        } //��� a-b�� �� ��ҵ��� ������ ��� �� ��ҿ� �־���
    }    
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL||DIFmtx == NULL) {
        //��� a,b,a-b �� ����(�����Ҵ�) ���� �ʾҴٸ�
		printf("Memory Allocation Failed.\n");
		return -1;
    }
    print_matrix(DIFmtx, row, col); //a-b ��� ���
	free_matrix(DIFmtx, row, col);  //a-b ��� ���� �޸� ����
    return 0; //�Լ� ����
}
/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{  //�Լ����� �Ű������� �޾ƿ� row = �Էµ� col, col = �Էµ� row ��
     /* Check pre conditions */
	if (row <= 0 || col <= 0) {
		printf("Check the size of row and col!\n");
		return -1;
	}
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            matrix_t[i][j]=matrix[j][i]; 
        } //���a�� �ִ밢�� �������� ������ ��ġ��� a_t�̱� ������ �밢�� ���� �ݴ����� ���� a_t�� ��
    }     //ex) ���a�� 2x3�̶�� 3x2 ���a_t�� �� ��ҵ��� ���� �� 
	/* Check post conditions */
	if (matrix == NULL||matrix_t == NULL) { //��İ� ��ġ����� ����(�����Ҵ�)���� �ʾҴٸ�
		printf("Memory Allocation Failed.\n");
		return -1; //�����߻�
    }
    return 0; //�Լ�����
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
    //ex) ũ�Ⱑ2x3 ���a �� ũ�Ⱑ 3x2�� ��ġ ���a_t�� ���ҽ� 2*2ũ���� ����� ������� 
    //���� ��������� ��İ��� ����� ����� ��İ� �� ��ġ����� ���̹Ƿ� ��� ���� ó�������� ����� ��� ����. 

    for (int k=0;k<row;k++){ //��� a�� ��ũ�⸸ŭ �ݺ�
        for (int i=0;i<row;i++){ // ��� a_t�� ��ũ�� ��ŭ �ݺ�  
            int sum=0; //��İ� �߰� ��갪 ������ sum
            for (int j=0;j<col;j++){ //��� a�� ��ũ�� ��ŭ �ݺ�
                sum+=matrix_a[k][j]*matrix_t[j][i];
            }       //��İ��� ���ǿ� ���� ���
            MULmtx[k][i]=sum; 
        }
    }
	/* Check post conditions */
	if (matrix_a == NULL || matrix_a == NULL||MULmtx == NULL) {
        //��� ,��ġ���, ��İ� ����� ����(�����Ҵ�)���� �ʾҴٸ� 
		printf("Memory Allocation Failed.\n");
		return -1; //���� �߻�
    }
    print_matrix(MULmtx, row, row); //a x t��� ���
	free_matrix(MULmtx, row, col);  //a x t��� ���� �޸� ����
    return 0; //�Լ�����
 }