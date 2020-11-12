#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 43862

void clear_stdin (void){
  while ( getchar() != '\n' );
}

int is_valid(int ch, int numbers[]){

  for (int i = 0; i < 10; i++) {

    if (ch == numbers[i])
      return 1;

  }

  return 0;

}

int getData(int srv, char *data, int start_point, char *ans, char multiplier[]){

  int arr_size = 0, minus = 0, numCount = 0, cmp = 0, numbers[10]= {0,1,2,3,4,5,6,7,8,9}, valid_char = 0;
  char arr_elem = 0;

  if (*ans == '3'){

    while (1) {

      printf("Insert a number to multiply the vector.\n");
      printf("> ");
      if(fgets(multiplier,10,stdin) == NULL){
        printf("Failed to read the string!\n");
        exit(0);
      }

      if (strcmp(multiplier, "\n") == 0)
        return 0;

      if (multiplier != 0)
        break;

    }

  }

  printf("Insert vector values.\n");

  while (1){

    valid_char = 1;

    if (numCount == 0){
      printf("> ");
    }

    arr_elem = fgetc(stdin);

    if(arr_elem == '-'){

      if (numCount >= 1) {
        clear_stdin();
        return 0;
      }

      minus = 1;
      numCount = 1;
      continue;
    }

    numCount++;

    if (arr_elem != '\n'){
      cmp = arr_elem - '0';
      valid_char = is_valid(cmp, numbers);
    }

    if(valid_char == 0){
      clear_stdin();
      return 0;

    }

    if (valid_char == 1) {

      if (arr_elem == '\n') {

        if (numCount == 1)
          break;

        minus = 0;
        numCount = 0;
      }

      if (minus == 1 && numCount == 2)
        data[start_point++] = '-';

      data[start_point++] = arr_elem;

    }

    if (start_point % 10 == 0) {
			//printf("Reallocating memory.\n");
			if((data = (char *)realloc(data, (start_point + 10))) == NULL){
				printf("Realloc error\n");
				exit(0);
			}

		}

  }

  if (start_point == 2)
    return 0;

  arr_size = start_point;
  data[1] = '\n';

  return arr_size;
}


void print_intArr(int *array, int size){

  for (size_t i = 0; i < size; i++) {

    if (i == 0)
      printf("\nMIN [ ");

    printf("%d ",array[i]);

    if (i+1 == size)
      printf("] MAX\n");

  }

}


void print_doubleArr(double *array, int size){

  for (size_t i = 0; i < size; i++) {

    if (i == 0)
      printf("\nMultiplied Vector:\n\n[ ");

    printf("%.2lf ",array[i]);

    if (i+1 == size)
      printf("]\n");

  }

}


int functions(int srv, char *ans) {

  int data_arr_size = 0, start_point = 2;
  char *Data, multiplier[10];

  Data = (char *)malloc(10);
  memset(Data, 0, 10);
  memset(multiplier, '\0', 10);

  data_arr_size = getData(srv, Data, start_point, ans, multiplier);

  if (data_arr_size == 0)
    return 1;

  send(srv, &data_arr_size, sizeof(int), 0);


  if (*ans == '1') {

    double result = 0;

    Data[0] = *ans;

    send(srv, Data, data_arr_size, 0);

    recv(srv, &result, sizeof(double), 0);

    printf("\nAVG: %.2lf\n",result);

  }

  if (*ans == '2') {

    int result[2];
    int int_arr_size = 2 * sizeof(int);

    Data[0] = *ans;

    send(srv, Data, data_arr_size, 0);

    recv(srv, result, int_arr_size, 0);

    print_intArr(result, 2);
  }

  if (*ans == '3'){

    double *result = NULL;
    int double_arr_size = 0;

    result = (double *)malloc((data_arr_size - 2) * sizeof(double));
    memset(result, 0, (data_arr_size - 2) * sizeof(double));

    Data[0] = *ans;

    send(srv, Data, data_arr_size, 0);
    send(srv, multiplier, 10, 0);

    recv(srv, &double_arr_size, sizeof(int), 0);
    recv(srv, result, double_arr_size * sizeof(double), 0);

    print_doubleArr(result, double_arr_size);

    free(result);
  }

  free(Data);

  return 0;
}

int main(int argc, char const *argv[]) {

  char *answer;
  int invalid_num = 0, invalid_in = 0, server, opt = 1;
  const char *ip;

  struct sockaddr_in server_info;

  answer = (char *)malloc(10);
  memset(answer, 0, 10);

  if (argc != 2) {
    printf("Usage: client ip_address.\n");
    exit(0);
  }

  if ((server = socket(AF_INET,SOCK_STREAM,0)) == -1) {
    perror("socket");
    exit(0);
  }

  bzero(&server_info, sizeof(server_info));
  ip = argv[1];

  if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  server_info.sin_family = AF_INET;
  server_info.sin_port = htons(PORT);
  if(inet_pton(AF_INET, ip, &server_info.sin_addr)<=0){
        printf("Invalid address.\n");
        exit(0);
    }

  if (connect(server, (struct sockaddr *)&server_info, sizeof(server_info)) != 0) {
        printf("Connection failed.\n");
        exit(0);
    }


  while (1) {

    if (invalid_num == 1) {
      printf("\n\n* Invalid number! *\n");
      invalid_num = 0;
    }

    if (invalid_in == 1) {
      printf("\n\n* Please select one of the following... *\n");
      invalid_in = 0;
    }


    printf("\n----------------------------------\n");
    printf("-    1. AVG function.            -\n-    2. Min/Max function.        -\n-    3. Multiplication function. -\n- Exit. Terminate the program.   -\n");
    printf("----------------------------------\n");
    printf("Select one function (e.g 1):\n");
    printf("> ");

    if(fgets(answer,10,stdin) == NULL){
      printf("Failed to read the string!\n");
      exit(0);
    }

    if ((strcmp(answer,"exit\n") == 0) || (strcmp(answer,"e\n") == 0 || (strcmp(answer,"\n") == 0)))
      break;

    if ((strcmp(answer,"1\n") == 0) || (strcmp(answer,"2\n") == 0) || (strcmp(answer,"3\n") == 0)){
      invalid_num = functions(server, answer);
    }else{
      invalid_in = 1;
    }

  }

  printf("\nTerminated.\n");

  free(answer);
  close(server);

  return 0;
}
