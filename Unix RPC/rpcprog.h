/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPCPROG_H_RPCGEN
#define _RPCPROG_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct send_data {
	double a;
	struct {
		u_int Y_len;
		int *Y_val;
	} Y;
};
typedef struct send_data send_data;

struct receive_data {
	struct {
		u_int double_arr_len;
		double *double_arr_val;
	} double_arr;
	struct {
		u_int int_arr_len;
		int *int_arr_val;
	} int_arr;
};
typedef struct receive_data receive_data;

#define AVG_PROG 0x23451111
#define AVG_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define AVG 1
extern  double * avg_1(send_data *, CLIENT *);
extern  double * avg_1_svc(send_data *, struct svc_req *);
extern int avg_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define AVG 1
extern  double * avg_1();
extern  double * avg_1_svc();
extern int avg_prog_1_freeresult ();
#endif /* K&R C */

#define MIN_MAX_PROG 0x23451112
#define MIN_MAX_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define MIN_MAX 2
extern  receive_data * min_max_1(send_data *, CLIENT *);
extern  receive_data * min_max_1_svc(send_data *, struct svc_req *);
extern int min_max_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MIN_MAX 2
extern  receive_data * min_max_1();
extern  receive_data * min_max_1_svc();
extern int min_max_prog_1_freeresult ();
#endif /* K&R C */

#define MUL_PROG 0x23451113
#define MUL_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define MUL 3
extern  receive_data * mul_1(send_data *, CLIENT *);
extern  receive_data * mul_1_svc(send_data *, struct svc_req *);
extern int mul_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MUL 3
extern  receive_data * mul_1();
extern  receive_data * mul_1_svc();
extern int mul_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_send_data (XDR *, send_data*);
extern  bool_t xdr_receive_data (XDR *, receive_data*);

#else /* K&R C */
extern bool_t xdr_send_data ();
extern bool_t xdr_receive_data ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPCPROG_H_RPCGEN */