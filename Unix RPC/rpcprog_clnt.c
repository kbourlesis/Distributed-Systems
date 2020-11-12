/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rpcprog.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

double *
avg_1(send_data *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, AVG,
		(xdrproc_t) xdr_send_data, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

receive_data *
min_max_1(send_data *argp, CLIENT *clnt)
{
	static receive_data clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MIN_MAX,
		(xdrproc_t) xdr_send_data, (caddr_t) argp,
		(xdrproc_t) xdr_receive_data, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

receive_data *
mul_1(send_data *argp, CLIENT *clnt)
{
	static receive_data clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MUL,
		(xdrproc_t) xdr_send_data, (caddr_t) argp,
		(xdrproc_t) xdr_receive_data, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
