#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define matrix_size 1024


            typedef struct parameters {
                        int x;// starting row
                        int y;// finishing row
            }state;

            // Return a random number between 0 and 50
            int random_num() {
                return rand() % 50;
            }


            //Initializing variable
            int firstMatrix[matrix_size][matrix_size];
            int secondMatrix[matrix_size][matrix_size];
            int result [matrix_size][matrix_size]; //calculate multiplied Matrix

            int i,j,k;


            void initialize_zero()
            {
                  //Defining matrices By 0

                for(int x=0;x<10;x++)
                {
                    for(int y=0;y<10;y++){
                        firstMatrix[x][y] = 0;
                        secondMatrix[x][y] = 0;
                        result[x][y] = 0;
                    }
                 }

            }

            void initialize_random()
            {
                 //Getting firstMatrix And secondMatrix
             printf("\n First Matrix \n\n");



            // Getting Row And Column
            printf("Enter number of rows for matrix one: ");
            scanf("%d",&i);
            printf("Enter number of columns for matrix one: ");
            scanf("%d",&j);

            printf("Variable are automatically initialized  with random number. \n\n");
            for(int x=0;x<i;x++){
                for(int y=0;y<j;y++){

                    firstMatrix[x][y] = random_num();
                }
            }

            printf("\n Second Matrix \n\n");
            // Getting Column Number For secondMatrix
            printf("Number of rows for matrix 2 : %d\n",j);
            printf("Enter number of columns for matrix 2: ");
            scanf("%d",&k);

             printf("Variable are automatically initialized  with random number. \n\n");
             for(int x=0;x<j;x++){
                for(int y=0;y<k;y++){

                    secondMatrix[x][y]= random_num();
                }
            }



            printf("\n --- Matrix 1 ---\n\n");
            for(int x=0;x<i;x++){
                for(int y=0;y<j;y++){
                    printf("%5d",firstMatrix[x][y]);
                }
                printf("\n\n");
            }

            printf(" --- Matrix 2 ---\n\n");
            for(int x=0;x<j;x++){
                for(int y=0;y<k;y++){
                    printf("%5d",secondMatrix[x][y]);
                }
                printf("\n\n");
            }
            }

            //Calculate Each Element
            void* calculateElement(void* argument){

                state* p = argument;

                //Calculating Each Element Using Passed Arguments
                for(int a=0;a<j;a++){
                    result[p->x][p->y] += firstMatrix[p->x][a]*secondMatrix[a][p->y];
                }
                sleep(3);

                //End Of Thread
                pthread_exit(0);
            }


        int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
        {
              long long int ds =  finish->tv_sec - start->tv_sec;
              long long int dn =  finish->tv_nsec - start->tv_nsec;

              if(dn < 0 ) {
                ds--;
                dn += 1000000000;
              }
              *difference = ds * 1000000000 + dn;
              return !(*difference > 0);
        }


        int main(){


            struct timespec start, finish;
            long long int time_elapsed;


            //Get Max number of threads from user.
            int MAX_THREADS;
            printf("\nEnter number of threads to use.\n");
            scanf("%d", &MAX_THREADS);

            if(MAX_THREADS < 1)
            {
              printf("Invalid number of threads.\n");
              return(1);
            }
            printf("Starting calculations.\n\n");


            initialize_zero();
            initialize_random();

             //Start Timer
            clock_gettime(CLOCK_MONOTONIC, &start);
            //Defining Threads
            pthread_t thread[MAX_THREADS];
            int thread_number = 0;
            state p[i*k];

            // Performing threads multiplication
            for(int x=0;x<i;x++){
                for(int y=0;y<k;y++){


                    p[thread_number].x=x;
                    p[thread_number].y=y;

                    //Checking Errors
                    int status;

                    //Create Specific Thread For Each Element
                    status = pthread_create(&thread[thread_number], NULL, calculateElement, (void *) &p[thread_number]);

                    //Check For Error
                    if(status!=0){
                        printf("Error In Threads");
                        exit(0);
                    }

                    thread_number++;
                }
            }


            for(int z=0;z<(i*k);z++)
                pthread_join(thread[z],NULL );

            printf(" Multiplied Matrix \n\n");
            for(int x=0;x<i;x++){
                for(int y=0;y<k;y++){
                    printf("%5d",result[x][y]);
                }
                printf("\n\n");
            }


            //Calculate Total Time
            clock_gettime(CLOCK_MONOTONIC, &finish);
              time_difference(&start, &finish, &time_elapsed);
              printf("Time elapsed for blocked matrix multiplication was %lldns or %0.3lfs\n", time_elapsed,(time_elapsed/1.0e9));


//            printf(" ---> Used Threads : %d \n\n",thread_number);
//                for(int z=0;z<thread_number;z++)
//                printf(" - Thread %d ID : %d\n",z+1,(int)thread[z]);


            //Start Timer
            clock_gettime(CLOCK_MONOTONIC, &start);
            // naive matrix multiplication
            for(int x=0; x<i; x++)
            {
                for(int y=0; y<j; y++)
                {
                      result[x][y]=0;

                      for(int z=0; z <  matrix_size; z++)
                      {
                        result[x][y]=result[x][y] + firstMatrix[x][z] * secondMatrix[z][y];
                       }
                      }
                    }
                    printf("\nNaive matrix multiplication\n");
                    for(int x=0; x<i; x++) {
                     for(int y=0; y<j; y++) {
                       printf("%d  ", result[x][y]=result[x][y]);
                      }
                    printf("\n");
                    }


                 //Calculate Total Time
              clock_gettime(CLOCK_MONOTONIC, &finish);
              time_difference(&start, &finish, &time_elapsed);
              printf("\nTime elapsed for naive matrix multiplication was %lldns or %0.3lfs\n", time_elapsed,(time_elapsed/1.0e9));

            return 0;
        }
