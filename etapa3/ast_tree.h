#include <stdlib.h>
#include <stdio.h>
#include "hash.h"


struct struct_AST
{
	nodeType node_type;
	linkedList* node;

	int numSons;
	struct struct_AST** son;
};
