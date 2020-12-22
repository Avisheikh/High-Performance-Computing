#include <stdio.h>


 void unsolvedDependecy(int *A2, int *B2, int *C2, int *D2)
 {
    int a = *A2;
    int b = *B2;
    int c = *C2;
    int d = *D2;

    b=a+c;
    b=c+d;
    c=b+d;

      printf("The value of B with unsolved the dependencies: %d\nThe value of C with unsolved the dependencies: %d \n\n", b, c);

 }



void solvedDependency(int *A1,int *B1,int *C1, int *D1, int *b_temp1,int *C11)
{
    int a = *A1;
    int b = *B1;
    int c = *C1;
    int d = *D1;
    int bTemp = *b_temp1;
    int c1 = *C11;
    // with solving the dependencies
     c1 = c;
     bTemp =  a + c;
     b = c1 + d;
     c = b + d;

    printf("The value of B with solved the dependencies: %d\nThe value of C with solved the dependencies: %d\n\n", b, c);

}

int main()
{
    int A = 1;
    int B = 2;
    int C = 3;
    int D = 4;
    int b_temp;
    int C1;



    unsolvedDependecy(&A,&B,&C,&D);
    solvedDependency(&A,&B,&C,&D,&b_temp,&C1);



    return 0;

}
