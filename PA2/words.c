/*
 * Ted Meyer
 */

// includes
#include <stdio.h>
#include <ctype.h>
#include "tree.h"


// function declarations
void fillTree(struct node **branch, char *filename);
void write_tree(char *filename, struct node **tree);
void remove_punctuation(char *p);
int read_words(char *filename, char *words[], int max_count);



int main(int argc, char*argv[])
{	
	//define root node
	struct node *root = 0;

	//fill the tree from the text files
	int k;
	for(k = 2; k < argc; k++)
	{
		fillTree(&root, argv[k]);
	}

	//write the tree to file
	write_tree(argv[1], &root);

	// free up the mem and exit
	prune(root);
	return 0;
}



void fillTree(struct node **tree, char *filename)
{
	FILE *f = fopen(filename, "rt");
	char temp[100]; //max length word
	while(fscanf(f, "%s", temp) != -1)
	{
		remove_punctuation(temp);
		insert(strdup(temp), tree);
	}
	fclose(f);
}


void write_tree(char *filename, struct node **tree) {
	//init varibles
	FILE *file = fopen(filename,"a+");

	//print the tree (and get the total word count)
	int total = print_tree(tree, file);

	//print the footer and close file
	fprintf(file, "-------------\n%6i	Total number of different words\n",total);
	fclose(file);
}



void remove_punctuation(char *p)
{
	//create temp vars
	char *src = p, *dst = p;

	//loop over chars
	while (*src)
	{
		if (ispunct((unsigned char)*src))
		{
			src++; //dont keep it
		}
		else if (src == dst)
		{
			src++;
			dst++;
		}
		else
		{
			*dst++ = *src++;
		}
	}
	//empty temp
	*dst = 0;
}
