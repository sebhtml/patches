/* 
 * 2012-09-27
 * Sébastien Boisvert
 *
 * Test to see if MPI can handle negative tags 
 * or very large tags.
 * This test is for 2 processes only.
 * If the test runs without errors with
 *
 * 	mpiexec -n 2 ./any-tag-test
 *
 * then it is successful.
 */


#include <mpi.h>
#include <stdlib.h>

#define SENDER 0
#define RECEIVER 1
#define PROCESSES 2

#define NEGATIVE_TAG -2147483648
#define POSITIVE_TAG 2147483647

typedef void (*SlaveModeHandler)();

void sender(){
/*
 * Requests should be freed with MPI_Test
 */
	MPI_Request request1;
	MPI_Isend(NULL,0,MPI_BYTE,RECEIVER,NEGATIVE_TAG,MPI_COMM_WORLD,&request1);
	MPI_Request request2;
	MPI_Isend(NULL,0,MPI_BYTE,RECEIVER,POSITIVE_TAG,MPI_COMM_WORLD,&request2);
}

void receiver(){
	MPI_Recv(NULL,0,MPI_BYTE,SENDER,NEGATIVE_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	MPI_Recv(NULL,0,MPI_BYTE,SENDER,POSITIVE_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}

void registerHandler(SlaveModeHandler*table,int handle,SlaveModeHandler handler){
	table[handle]=handler;
}

SlaveModeHandler getHandler(SlaveModeHandler*table,int rank){
	if(rank<PROCESSES)
		return table[rank];
	return NULL;
}

int main(int argc,char**argv){
	MPI_Init(&argc,&argv);

	int rank=-1;
	int size=-1;

	SlaveModeHandler handlers[PROCESSES];
	
	registerHandler(handlers,SENDER,sender);
	registerHandler(handlers,RECEIVER,receiver);

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	SlaveModeHandler code=getHandler(handlers,rank);
	
	code();

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();

	return EXIT_SUCCESS;
}
