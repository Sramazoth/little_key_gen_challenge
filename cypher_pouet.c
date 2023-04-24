/*
==========================================
 Title:  Cypher and uncipher program which goes with the little program to reverse
 Author: Pouet Pouet
 Date:   11 Mars 2023
==========================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

unsigned char* cipher_key = "æìüþ÷ðØÝÐÅ¾¶¦£©"; // yep ... unreadable ... as all things should be
// unsigned char cipher_key[] = {0x10, 0xAA, 0x67, 0xA1, 0xFF};

/*
 * Explicit.
 * cipher_mode = 1 -> ciphering
 * cipher_mode = -1 -> unciphering
 */
void cipher_uncipher_file(int cipher_mode, char* filename)
{
	FILE *fps, *fpt;
	unsigned char ch;
	fps = fopen(filename, "rb");
	if(fps == NULL)
	{
		printf("Can't open file \033[1m%s\033[0m.\n", filename);
		return;
	}

	char* ciph_file_end;
	if (cipher_mode == 1) ciph_file_end = ".ciph";
	else ciph_file_end = ".unciph";
	strcat(filename, ciph_file_end);

	fpt = fopen(filename, "wb");
	if(fpt == NULL)
	{
		printf("Can't create an output file, verify permission.\n");
		return;
	}
	int cpt = 0;
	ch = fgetc(fps);
	int value;
	while(ch != 255)
	{
		// J'ai du mal à lire mon propre c, en espérant que le reverse
		// soit encore moins compréhensible
		value = ch + cipher_mode * cipher_key[cpt % strlen(cipher_key)];
        if (value < 0) ch = value + 254;
        else if (value > 254) ch = value - 254;
        else ch = value;
		fputc(ch, fpt);
		ch = fgetc(fps);
		cpt += 1;
	}
	fclose(fps);
	fclose(fpt);
	if (cipher_mode == 1) printf("Done ciphering, output: \033[32m%s\033[0m\n", filename);
	else printf("Done unciphering, output: \033[32m%s\033[0m\n", filename);
}


/*
 * Explicit. 
 */
void show_help()
{
	printf("Program is able to cipher and uncipher a file (basic cesar),\n");
	printf("output is always filename with extension as .unciph or .ciph.\nOptions:\n");
	printf("	-h, --help      	show this menu\n");
	printf("	-f, --file      	select which file to use\n");
	printf("	-c, --cipher    	cipher mode\n");
	printf("	-u, --uncipher  	uncipher mode\n");
}

/*
 * Explicit. 
 */
int main(int argc, char *argv[], char **envp)
{
	char filename[256];
	bool filename_defined = false;
	int cipher_mode = 0;

	if (argc == 1)
	{
		show_help();
		return 0;
	}

	if (argc != 1) 
	{
		for (int i = 1; i < argc; ++i)
		{
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
			{
				show_help();
				return 0;
			}
			else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
			{
				if (i+1 < argc) {
					filename_defined = true;
					strcpy( filename, argv[i+1] );
					i++;
				}
			}
			else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--cipher") == 0)
			{
				cipher_mode++;
			}
			else if (strcmp(argv[i], "-u") == 0 || strcmp(argv[i], "--uncipher") == 0)
			{
				cipher_mode--;
			}
		}
	}

	if (cipher_mode == 0)
	{
		printf("Please select exactly one mode: --uncipher or --cipher).\n");
		return 0;		
	}

	if (filename_defined) {
		cipher_uncipher_file(cipher_mode, filename);
	} 
	else
	{
		printf("Missing file: %s [--uncipher/--cipher] --file [filename]\n", argv[0]);
	}
	return 0;
}