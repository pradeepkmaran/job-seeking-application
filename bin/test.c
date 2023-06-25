// C program for writing
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// a struct to be read and written
struct person {
	int id;
	char fname[20];
	char lname[20];
};

int main()
{
	FILE* outfile;

	// open file for writing
	outfile = fopen("person.txt", "w");
	if (outfile == NULL) {
		fprintf(stderr, "\nError opened file\n");
		exit(1);
	}
	char name1[] = "rohan";
	char name2[] = "sharma";
	struct person input1;

	strcpy(input1.fname, name1);
	strcpy(input1.lname, name2);
	input1.id = 1;


	// write struct to file
	int flag = 0;
	flag = fwrite(&input1, sizeof(struct person), 1,
				outfile);
	if (flag) {
		printf("Contents of the structure written "
			"successfully");
	}
	else
		printf("Error Writing to File!");

	// close file
	fclose(outfile);

	return 0;
}
