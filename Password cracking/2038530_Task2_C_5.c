#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

#define total_password 10

pthread_mutex_t count_mutex;
int count=0;   

char *encrypted_password = "$6$AS$bZw8vbh6g3itOiFEBPMMLC/q6w5q8SmY35FTO7EsM6LYb9R7M.dnb8YJnVDzBFH2UgEAfFJVmaYKSIrbj40MC0";

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void multi_thread()
{ 

  pthread_t thread1, thread2;

  void *kernel_function_1();
  void *kernel_function_2();

    pthread_create(&thread1, NULL,kernel_function_1, (void *)encrypted_password);
    pthread_create(&thread2, NULL,kernel_function_2, (void *)encrypted_password);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
 
}

void *kernel_function_1(char *salt_and_encrypted){

  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

 
  for(x='A'; x<='M'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);  
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	        printf("#%-8d%s %s\n", count, plain, enc);
		      //return;	
        } 

      }
    }
  }

}

void *kernel_function_2(char *salt_and_encrypted){
  int a, b, i;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='N'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
      for(i=0; i<=99; i++){
        sprintf(plain, "%c%c%02d", a, b, i); 
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
          //return;	
        } 
       
      }
    }
  }

}


int time_difference(struct timespec *start, struct timespec *finish, long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[]){
  struct timespec start, finish;   
  long long int time_elapsed;


  for(int i =0; i< total_password; i++)
  {
     clock_gettime(CLOCK_MONOTONIC, &start);
  
	    multi_thread();	

      clock_gettime(CLOCK_MONOTONIC, &finish);
      time_difference(&start, &finish, &time_elapsed);
      printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
            (time_elapsed/1.0e9));

  }
     

  return 0;
}


