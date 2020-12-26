#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>

#define total_password 10

int count=0;    

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void crack(char *salt_and_encrypted){
  
  int x, y, z, w;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z='A'; z<='Z'; z++){
        for(w=0; w<=99; w++)
        {
          sprintf(plain, "%c%c%c%02d", x, y, z, w);
          enc = (char *) crypt(plain, salt);
          count++;
          if(strcmp(salt_and_encrypted, enc) == 0){
            printf("#%-8d%s %s\n", count, plain, enc);
          } 				
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

  for(int i = 0 ; i < total_password;i++)
  {
      clock_gettime(CLOCK_MONOTONIC, &start);
      
      crack("$6$AS$KZtvsGBQyAiojo4VpfUGl6pM6k6qTBVJoxHL0hamlb2jCrKeAF0YFDgiisYHk6fwEERWhbmjPO01Es/vEQfSM/"); 
      
      clock_gettime(CLOCK_MONOTONIC, &finish);
      time_difference(&start, &finish, &time_elapsed);
      printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
            (time_elapsed/1.0e9));	
    
  }
  
  return 0;
}
