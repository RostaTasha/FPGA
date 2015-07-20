/*
 * monitor.c
 *
 *  Created on: Oct 5, 2012
 *      Author: urock
 *
 *
 *      RC47 Monitor
 *
 *      Opens SP6 device of selected RC47 board and 
 *      reads temperature of chips
 *
 */


#include "RostaPCIeAPI.h"
#include "rc47-api.h"


struct cmd_params_t {
	int		board_index;

};

max_status_t	max_status;
stm_status_t	stm_status;


void print_usage(void)
{
	printf("Command line args error!\n");
	printf("Usage: <executable name> -b [board index]\n");

}


int process_cmd_line(int argc, char *argv[], struct cmd_params_t *cmd_p)
{
	int i, index;

	int got_index=0;


	for (i=0;i<argc; i++) {

		if (!strncmp("-b",argv[i],2)) {
			sscanf(argv[i+1],"%d",&index);
			cmd_p->board_index = index;
			got_index = 1;

		}
	}


	if (got_index)
		return 1;
	else
		return -1;
}


int main(int argc, char *argv[])
{
	int r, k, index,  dev;

	struct cmd_params_t	cmd_p;
	struct pci_device pd[MAX_PCIE_DEVICES];
	struct rc47_board_t rc47[MAX_RC47_BOARDS];



	if (process_cmd_line(argc, argv, &cmd_p) < 0) {
		print_usage();
		return -1;
	}


	index = cmd_p.board_index;


	printf("\nSearching for RC47 boards... \n");

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
		fprintf(stderr,"\nInvalid board index! Exitting...\n");
		return -2;
	}



	// open SP6 device
	do_and_test(RD_OpenDevice,(rc47[index].SP_pd));


	dev = rc47[index].SP_pd->intfd;



	if (rc47_read_stm_status(dev, &stm_status) != 0) {
		fprintf(stderr,"Error in rc47_read_stm_status\n");
		return -1;
	}

	printf("\nGot Status:  \n");

	printf("\t STM firmware version = %2.1f\n\n",((float)stm_status.fversion/10));

	printf("RDM-03 MAC Address is %x:%x:%x:%x:%x:%x\n", stm_status.mac0, stm_status.mac1, stm_status.mac2,
														  stm_status.mac3, stm_status.mac4, stm_status.mac5);
	if (stm_status.i2c_error)
		printf("\t i2c_error = %d\n",stm_status.i2c_error);
	if (stm_status.cpld_error)
		printf("\t cpld_error = %d\n",stm_status.cpld_error);
	if (stm_status.sdio_error)
		printf("\t sdio_error = %d\n",stm_status.sdio_error);
	if (stm_status.sdio_card_vaild_code == 0)
		printf("\t sdio_card_vaild_code = %d\n",stm_status.sdio_card_vaild_code);
	if (stm_status.plx_error)
		printf("\t plx_error = %d\n",stm_status.plx_error);

	printf("\n");


	if (rc47_read_max_status(dev, &max_status) != 0) {
		fprintf(stderr,"Error in rc47_read_stm_status\n");
		return -1;
	}

		printf("Temp PLX\t\t = %d\n\n", max_status.u40_Text1);

		printf("Temp Virtex-7 C0\t = %d\n", max_status.u38_Text1);
		printf("Temp Virtex-7 C1\t = %d\n", max_status.u38_Text2);

		printf("Temp Virtex-7 C2\t = %d\n", max_status.u39_Text1);
		printf("Temp Virtex-7 C3\t = %d\n\n", max_status.u39_Text2);


		//sleep(5);




	RD_CloseDevice(rc47[index].SP_pd);



	return 0;
}



