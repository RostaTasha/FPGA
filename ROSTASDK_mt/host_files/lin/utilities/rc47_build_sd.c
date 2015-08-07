// build_sd.cpp : Defines the entry point for the console application.
//

#include "RostaPCIeAPI.h"
#include "rc47-api.h"

/*
Rosta RC47 SD file builder

Yuri Rumyantsev <rumyantsev@rosta.ru>
*/

char *sp6_file_name_ptr;

char *v7_file_name_ptr[MAX_V7_BITFILES];
//char * v7_options[5]; 
unsigned int v7_description[MAX_V7_BITFILES]; 
char *sd_card_file;

int parse_cmd_line(int argc, char *argv[]);
void print_usage(void);






int main(int argc, char *argv[])
{
	int numrec, ret_val;

	
	printf("Start building SD file\n"); 
	printf("\n"); 

	// first get bitfiles names

	numrec = parse_cmd_line(argc, argv);

	if (numrec < 0) {
		print_usage(); 
		return 1;
	}




	ret_val = build_sd( sp6_file_name_ptr, *v7_file_name_ptr, v7_description, sd_card_file );

		if (ret_val< 0) {
		printf("Error in building SD file");
		return 1;
	}

	
	return 0;



}

int parse_cmd_line(int argc, char *argv[])
{
	int i, numrec = 0, sp6_ok = 0;
	
	
	for (i=1; i < (argc-1); i++) 
		if ( !strncmp("-sp6",argv[i],4) ) {
			sp6_file_name_ptr = argv[i+1];
			sp6_ok = 1; 

		} else if (!strncmp("-o",argv[i],2) ) {			// set output file name
			sd_card_file = argv[i+1];
		
		} else if (!strncmp("-v7",argv[i],3) ) {		// virtex 7


			if (!strncmp("485",argv[i+1],3) ) {			// 485 crystall
				
				if (!strncmp("all",argv[i+2],3) ) {		
					v7_description[numrec] = XC7VX485T_ALL; 
				} else if (!strncmp("test",argv[i+2], 4) ) {
					v7_description[numrec] = XC7VX485T_TEST;
				} else {
					printf("Error! Bad description for V7\n");
					return -4;
				}
			
			} else if (!strncmp("585",argv[i+1],3) ) {	// 585 crystall

				if (!strncmp("all",argv[i+2],3) ) {		
					v7_description[numrec] = XC7V585T_ALL;
				} else if (!strncmp("test",argv[i+2], 4) ) {
					v7_description[numrec] = XC7V585T_TEST;
				} else {
					printf("Error! Bad description for V7\n");
					return -4;
				}

			} else {
				printf("Error! Bad crystall for V7\n");
				return -3; 
			}

			v7_file_name_ptr[numrec++] = argv[i+3];		

			if (numrec > MAX_V7_BITFILES) {
				printf("Error! numrec > MAX_V7_BITFILES = %d! \n",MAX_V7_BITFILES);
				return -2;
			}
		}

	return (sp6_ok? numrec : -1);

}





void print_usage(void)
{
	printf("Command line error!\n");
	printf("\tUsage: build_sd_file -sp6 [sp6 bit file name] -v7 [crystall] [options] [v7 bit file name]\n");
	printf("\tcrystall: 485, 585\n"); 
	printf("\toptions: all, test\n"); 
}



