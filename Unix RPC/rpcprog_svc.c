/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpcprog.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
avg_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		send_data avg_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case AVG:
		_xdr_argument = (xdrproc_t) xdr_send_data;
		_xdr_result = (xdrproc_t) xdr_double;
		local = (char *(*)(char *, struct svc_req *)) avg_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

static void
min_max_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		send_data min_max_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case MIN_MAX:
		_xdr_argument = (xdrproc_t) xdr_send_data;
		_xdr_result = (xdrproc_t) xdr_receive_data;
		local = (char *(*)(char *, struct svc_req *)) min_max_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

static void
mul_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		send_data mul_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case MUL:
		_xdr_argument = (xdrproc_t) xdr_send_data;
		_xdr_result = (xdrproc_t) xdr_receive_data;
		local = (char *(*)(char *, struct svc_req *)) mul_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (AVG_PROG, AVG_VERS);
	pmap_unset (MIN_MAX_PROG, MIN_MAX_VERS);
	pmap_unset (MUL_PROG, MUL_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, AVG_PROG, AVG_VERS, avg_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (AVG_PROG, AVG_VERS, udp).");
		exit(1);
	}
	if (!svc_register(transp, MIN_MAX_PROG, MIN_MAX_VERS, min_max_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (MIN_MAX_PROG, MIN_MAX_VERS, udp).");
		exit(1);
	}
	if (!svc_register(transp, MUL_PROG, MUL_VERS, mul_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (MUL_PROG, MUL_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, AVG_PROG, AVG_VERS, avg_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (AVG_PROG, AVG_VERS, tcp).");
		exit(1);
	}
	if (!svc_register(transp, MIN_MAX_PROG, MIN_MAX_VERS, min_max_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (MIN_MAX_PROG, MIN_MAX_VERS, tcp).");
		exit(1);
	}
	if (!svc_register(transp, MUL_PROG, MUL_VERS, mul_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (MUL_PROG, MUL_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
