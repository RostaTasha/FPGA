/********************************************
* rc47_rand_test.c
*
*
*
*
*******************************************/
#include "add_test.h"



struct cmd_params_t {
	int		board;
	int		v7;
};

									
void print_usage(char *argv[]);
int fpga_init(int argc, char *argv[], int *dev);
int process_cmd_line(int argc, char *argv[], struct cmd_params_t *cmd_p);
int fpga_write_user_reg(int dev, unsigned int addr, unsigned int value);
int fpga_read_user_reg(int dev, unsigned int addr, unsigned int *value);
int fpga_reg_test(int cur_it, int dev);
int fpga_summ_test(int cur_it, int dev);

struct pci_device pd[MAX_PCIE_DEVICES];
struct rc47_board_t rc47[MAX_RC47_BOARDS];
struct pci_device *pd_ptr;







int main(int argc, char *argv[])
{
	int dev, ret_val;

	
	
	// find and init FPGA device
	ret_val = fpga_init(argc, argv, &dev);
	
	
	for (int i =0; i< NUM_ITER; i++){
	
	if (fpga_reg_test(i, dev)<0) break;
	
	}
	
	for (int i =0; i< NUM_ITER; i++){
	
	if (fpga_summ_test(i, dev)<0) break;
	
	}
	
	
	
	
	RD_CloseDevice(pd_ptr);
	
	return 0; 

}






//##########################command line parser#####################################################
int process_cmd_line(int argc, char *argv[], struct cmd_params_t *cmd_p)
{
	int i,j=0, k ;

	unsigned int board, v7, v7_, plx;
	int lend, mode, num_it, hls_size, addr;

	int got_brd=0, got_len=0, got_v7=0, got_size = 0, got_addr=0;
	for (i=0;i<argc; i++) {
		
		if ((strlen(argv[i])>=6) && !strncmp("--help",argv[i],6) ){
			print_usage(argv);
			return -2;
		}	
		
		if ((strlen(argv[i])>=2)&& !strncmp("-b",argv[i],2)) {
			if (i!=(argc-1) && sscanf(argv[i+1],"%d",&board)>0){
				cmd_p->board = board;
				got_brd = 1;
			}
		}
		
		if ((strlen(argv[i])>=2)&& !strncmp("-v",argv[i],2)) {
			if (i <argc && (strlen(argv[i+1])>=2)&& !strncmp("C0",argv[i+1],2)) {
				cmd_p->v7 = CS_C0; got_v7 = 1; 
			} else if (i <argc  && (strlen(argv[i+1])>=2)&&  !strncmp("C1",argv[i+1],2)) {
				cmd_p->v7 = CS_C1;  got_v7 = 1;
			} else if (i <argc  && (strlen(argv[i+1])>=2)&&  !strncmp("C2",argv[i+1],2)) {
				cmd_p->v7 = CS_C2; got_v7 = 1;
			} else if (i <argc && (strlen(argv[i+1])>=2)&&  !strncmp("C3",argv[i+1],2)) {
				cmd_p->v7 = CS_C3;  got_v7 = 1; 
				
			}

		}
		
	}

	/////////////////////////////////////////////////////		
	if (got_brd && got_v7){
		return 0;
	}
	else{
		printf("\n %s: missing or invalid operand\n Try 'sudo %s --help' for more information\n\n", argv[0], argv[0]);
		return -1;
	}

}


int fpga_init(int argc, char *argv[], int *dev_out) {
	
	int k, r;
	struct cmd_params_t	cmd_p;
	
	unsigned int reg_val;

	if (process_cmd_line(argc, argv, &cmd_p) < 0) {
		return -1;
	}

	printf("\nSearching for RC47 boards\n");

	k = rc47_search_for_boards(pd,rc47);

	if (k<0) {
		fprintf (stderr,"No boards in system!\n\n");
		return 0;
	} else 
	if (k==1)		
	printf("Found %d board\n",k);
	else
	printf("Found %d boards\n",k);


	rc47_print_device_info(k,rc47);


	if (cmd_p.board >= k) {
		fprintf (stderr,"Invalid selected board number\n");
		return -2;
	} else {
		printf("\nSelected:\n");
		printf("Board number\t:::\t%d\n", cmd_p.board);
	}



	if ((cmd_p.v7 == CS_C0) && (rc47[cmd_p.board].LD_pd != NULL)) {
		pd_ptr = rc47[cmd_p.board].LD_pd;
		printf("Virtex Chip\t:::\t%s\n", "C0");
	} else if ((cmd_p.v7 == CS_C1) && (rc47[cmd_p.board].LU_pd != NULL)) {
		pd_ptr = rc47[cmd_p.board].LU_pd;
		printf("Virtex Chip\t:::\t%s\n", "C1");
	} else if ((cmd_p.v7 == CS_C2) && (rc47[cmd_p.board].RD_pd != NULL)) {
		pd_ptr = rc47[cmd_p.board].RD_pd;
		printf("Virtex Chip\t:::\t%s\n", "C2");
	} else if ((cmd_p.v7 == CS_C3) && (rc47[cmd_p.board].RU_pd != NULL)) {
		pd_ptr = rc47[cmd_p.board].RU_pd;
		printf("Virtex Chip\t:::\t%s\n", "C3");
	} else {
		fprintf (stderr,"Invalid selected virtex chip\n");
		return -2;
	}




	// open pcie device

	do_and_test(RD_OpenDevice,(pd_ptr));		

	int dev = pd_ptr->intfd;


	// reset user part
	if (fpga_user_reset(dev) < 0)
	return -1;
	
	if (fpga_release_user_reset(dev) < 0) 
	return -1; 		
	
	// set interconnection 
	RD_ReadDeviceReg32m(dev, CNTRL_BAR, 0x4, reg_val);
	
	reg_val |= (1<<5);
	
	RD_WriteDeviceReg32m(dev, CNTRL_BAR, 0x4, reg_val);
	



	/////////////////////////////////////set all counters to zero///////////////////
	
	RD_WriteDeviceReg32m(dev, CNTRL_BAR, MasterMemRdTotalCnt, 0);
	RD_WriteDeviceReg32m(dev, CNTRL_BAR, FifoMemRdTotalCnt, 0);
	RD_WriteDeviceReg32m(dev, CNTRL_BAR, FifoMemWrTotalCnt, 0);
	RD_WriteDeviceReg32m(dev, CNTRL_BAR, MasterMemWrTotalCnt, 0);
	
	///////////////////////////////////////////////////////////////////////////////
	
	srand(time(0));
	
	*dev_out = dev; 
	

	return 0;
}


void print_usage(char *argv[])
{
	printf("Usage:\n");
	printf("\n--------------------------------------------------------------------------\n");
	printf("To run \\\\\\\\ADD TEST:\nsudo %s -b [board] -v [chip_select]\n", argv[0]);	
	printf("chip_select: C0 or C1 or C2 or C3\n");
	printf("\n--------------------------------------------------------------------------\n");
}




int fpga_reg_test(int cur_it, int dev)
{

	unsigned short write_value = 0, read_value = 0;
	unsigned int 	read_flag_and_value;
	int RunCycles = 10000,t;
	int ret_val, numErrors = 0;

	write_value = (short)((rand() << 16) | rand());
	if(fpga_write_user_reg(dev, TESTREGIN, (unsigned int)write_value) < 0)
	return -1;

	// read data and valid status
	t=0; 
	while(t++<3) {
		if(fpga_read_user_reg(dev, TESTREGOUT, &read_flag_and_value) < 0)
		return -1;
		if (read_flag_and_value & 0x80000000) 
		break;
	}
	if (t>2) { // timeout
		printf("Timeout error in Reg test\n"); 
		return -6;
	} 

	read_value = (unsigned short)read_flag_and_value;
	
	if (write_value + 1 != read_value) {
		printf("Data error in Reg test, write = %d, read = %d\n",write_value,read_value); 
		return -10;
	}

	

	printf("\n\nREG BASE TEST on iteration %d completed successfully!\n\n", cur_it);

	return 0;
}


int fpga_summ_test(int cur_it, int dev)
{

// WRITE YOUR CODE HERE


	printf("\n\nSUMM TEST on iteration %d completed successfully!\n\n", cur_it);

	return 0;
}


int fpga_write_user_reg(int dev, unsigned int addr, unsigned int value)
{	
	int ret_val;

	ret_val = RD_WriteDeviceReg32(dev, CNTRL_BAR, addr, value);
	if (ret_val < 0) {
		printf("fpga_write_user_reg: Error writting to user reg 0x%x!\n",addr);
		return -1;
	}
	return 0;
}

int fpga_read_user_reg(int dev, unsigned int addr, unsigned int *value)
{	
	int ret_val;

	ret_val = RD_ReadDeviceReg32(dev, CNTRL_BAR, addr, value);
	if (ret_val < 0) {
		printf("fpga_read_user_reg: Error reading from user reg 0x%x!\n",addr);
		return -1;
	}
	return 0;
}


