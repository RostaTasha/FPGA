/*
 * rc47_reset_v7.c
 *
 *  Created on: May 24, 2012
 *      Author: urock
 */


#include "RostaPCIeAPI.h"
#include "rc47-api.h"


struct cmd_params_t {
	int		board_index;
	int		chip_select;

};




void print_usage(void)
{
	printf("Command line args error!\n");
	printf("Usage: <executable name> -b [board index] -v [chip select]\n");
	printf("chip select: any combination of C0, C1, C2, C3 or all\n");

}


int process_cmd_line(int argc, char *argv[], struct cmd_params_t *cmd_p)
{
	int i,j, index, chip_select = 0;

	int got_index=0, got_cs=0, max_j=0;


	for (i=0;i<argc; i++) {

		if (!strncmp("-b",argv[i],2)) {
			sscanf(argv[i+1],"%d",&index);
			cmd_p->board_index = index;
			got_index = 1;

		}
		if (!strncmp("-v",argv[i],2)) {
			if ((i+4) < (argc-1))  //
				max_j = i+4;
			else
				max_j = argc-1;


			for(j=i;j<=max_j;j++) {
				if (!strncmp("C0",argv[j],2))
					chip_select |= CS_LD;
				if (!strncmp("C1",argv[j],2))
					chip_select |= CS_LU;
				if (!strncmp("C2",argv[j],2))
					chip_select |= CS_RD;
				if (!strncmp("C3",argv[j],2))
					chip_select |= CS_RU;
				if (!strncmp("all",argv[j],3))
					chip_select = CS_LD | CS_LU | CS_RD | CS_RU;
			}
			cmd_p->chip_select = chip_select;
			got_cs = 1;


		}

	}


	if (got_index && got_cs)
		return 1;
	else
		return -1;
}



int main(int argc, char *argv[])
{
	int r, k, ret_val, indexx;
	int chip_select = 0;

	struct cmd_params_t	cmd_p;
	struct pci_device pd[MAX_PCIE_DEVICES];
	struct rc47_board_t rc47[MAX_RC47_BOARDS];

	if (process_cmd_line(argc, argv, &cmd_p) < 0) {
		print_usage();
		return -1;
	}


	indexx = cmd_p.board_index;

	chip_select = cmd_p.chip_select;


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


	if (indexx >= k) {
		printf("\nInvalid board index! Exitting...\n\n");
		return -2;
	}



	// open SP6 device
	do_and_test(RD_OpenDevice,(rc47[indexx].SP_pd));


	ret_val = rc47_reset_v7(&rc47[indexx], chip_select);

	if (ret_val < 0)
		printf("Error resetting!\n");

	RD_CloseDevice(rc47[indexx].SP_pd);


	sleep(1);

	printf("\nRescan PCI Express bus after reset...\n");
	do_and_test(RD_RescanBus,());
	sleep(1);

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


	rc47_print_device_info(k,rc47);

	return 0;
}



