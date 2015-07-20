/*
 * rc47_program_sdio.c
 *
 *  Created on: Mar 19, 2013
 *      Author: urock
 */



#include "RostaPCIeAPI.h"
#include "rc47-api.h"


// defines and variables





struct cmd_params_t {
	int		board_index;
	int 	verify;
	char 	*bit_file_path;

};

int rc47_programm_sdio(struct rc47_board_t *rc47, char *bit_file_path, int verify);


void print_usage(void)
{
	printf("Command line args error!\n");
	printf("Usage: <executable name> -b [board index] -f [sd card file name] [-verify]\n");

}


int process_cmd_line(int argc, char *argv[], struct cmd_params_t *cmd_p)
{
	int i, index;

	int got_index=0, got_file_name=0;

	cmd_p->verify = 0;

	for (i=0;i<argc; i++) {

		if (!strncmp("-b",argv[i],2)) {
			sscanf(argv[i+1],"%d",&index);
			cmd_p->board_index = index;
			got_index = 1;

		}
		if (!strncmp("-f",argv[i],2)) {
			cmd_p->bit_file_path = argv[i+1];
			got_file_name = 1;
		}

		if (!strncmp("-verify",argv[i],7))
			cmd_p->verify = 1;

	}


	if (got_index && got_file_name)
		return 1;
	else
		return -1;
}


int main(int argc, char *argv[])
{
	int k, index;

	struct cmd_params_t	cmd_p;

	struct pci_device pd[MAX_PCIE_DEVICES];
	struct rc47_board_t rc47[MAX_RC47_BOARDS];


	if (process_cmd_line(argc, argv, &cmd_p) < 0) {
		print_usage();
		return -1;
	}


	index = cmd_p.board_index;


	printf("\nSearching for RC47 boards\n");

	k = rc47_search_for_boards(pd,rc47);

	if (k<0) {
		printf("No boards in system!\n\n");
		return 0;
	} else 
		if (k==1)		
			printf("Found %d board\n",k);
		else
			printf("Found %d boards\n",k);


	if (index >= k) {
		fprintf(stderr,"\nInvalid board index! Exitting...\n\n");
		return -2;
	}



	if (rc47_programm_sdio(&rc47[index], cmd_p.bit_file_path, cmd_p.verify) != 0) {
		fprintf(stderr,"Error in rc47_programm_sdio\n");
		return -2; 
	}



	return 0;
}



