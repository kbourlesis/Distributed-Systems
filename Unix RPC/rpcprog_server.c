/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpcprog.h"

double *avg_1_svc(send_data *argp, struct svc_req *rqstp){

	static double  result;
	result = 0;

	printf("\n*** AVG function ***\n");

	for (int i = 0; i < argp->Y.Y_len; i++) {
		//printf("Y[%d]: %d\n", i,argp->Y.Y_val[i]);
		result += argp->Y.Y_val[i];
	}

	result /= argp->Y.Y_len;
	//printf("AVG: %lf\n", result);

	return &result;

}

receive_data *min_max_1_svc(send_data *argp, struct svc_req *rqstp){

	static receive_data result;

	result.int_arr.int_arr_len = 2;
	result.int_arr.int_arr_val = (int *)malloc(2 * sizeof(int));

	int min = argp->Y.Y_val[0];
	int max = argp->Y.Y_val[0];

	printf("\n*** Min/Max function ***\n");

	for (int i = 1; i < argp->Y.Y_len; i++) {
		//printf("Y[%d]: %d\n", i,argp->Y.Y_val[i]);
		if (min > argp->Y.Y_val[i]) {
			 min = argp->Y.Y_val[i];
		}

		if (max < argp->Y.Y_val[i] ) {
			max = argp->Y.Y_val[i];
		}

	}

	//printf("Min: %d\nMax: %d\n", min,max);

	result.int_arr.int_arr_val[0] = min;
	result.int_arr.int_arr_val[1] = max;

	return &result;
}

receive_data *mul_1_svc(send_data *argp, struct svc_req *rqstp){

	static receive_data  result;

	printf("\n*** Multiplication function ***\n");

	result.double_arr.double_arr_len = argp->Y.Y_len;
	result.double_arr.double_arr_val = (double *)malloc(argp->Y.Y_len * sizeof(double));

	//printf("multiplier: %lf\n", argp->a);
	/*for (int i = 0; i < argp->Y.Y_len; i++)
		printf("Y_val[%d]: %d\n", i, argp->Y.Y_val[i]);*/

	for (int i = 0; i < argp->Y.Y_len; i++)
		result.double_arr.double_arr_val[i] = argp->a * argp->Y.Y_val[i];


	/*for (int i = 0; i < argp->Y.Y_len; i++)
		printf("double_arr[%d]: %lf\n", i, result.double_arr.double_arr_val[i]);*/


	return &result;
}
