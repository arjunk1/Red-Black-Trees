#include <stdlib.h>
#include <stdio.h>


struct node{
	int value;
	int node_colour;
	struct node *node_parent;
	struct node *leftchild;
	struct node *rightchild;
};

struct node *NULLNODE;
struct node *TOPNODE;




void transform_tree(struct node *u, struct node *v);
void tree_print(struct node *x);
void rightchild_twist(struct node *x);
void delete_node_function_helper(struct node *x);
void insert_into_tree_helper(struct node *curr);
struct node *search_node_function(int value);
struct node *tree_minimum(struct node *x);
void insert_into_tree(int value);
void delete_node_function(struct node *curr);
void leftchild_twist(struct node *x);

#define BLACK 1
#define RED 0

void delete_node_function(struct node *curr){
	if(curr == NULLNODE || curr == NULL){
		printf("Not Possible\n");
		return;
	}
	struct node *y, *x;
	int y_previous_node_colour;

	y = curr;
	y_previous_node_colour = y->node_colour;

	if(curr->rightchild == NULLNODE){
		x = curr->leftchild;
		transform_tree(curr, curr->leftchild);
	}
	else if(curr->leftchild == NULLNODE){
		x = curr->rightchild;
		transform_tree(curr, curr->rightchild);
	}
	else{
		y = tree_minimum(curr->rightchild);
		y_previous_node_colour = y->node_colour;
		x = y->rightchild;

		if(y->node_parent != curr){
			transform_tree(y, y->rightchild);
			y->rightchild = curr->rightchild;
			y->rightchild->node_parent = y;
		}
		else{
			x->node_parent = y;
		}
		transform_tree(curr, y);
		y->leftchild = curr->leftchild;
		y->leftchild->node_parent = y;
		y->node_colour = curr->node_colour;
	}
	if(y_previous_node_colour == BLACK){
		delete_node_function_helper(x);
	}
}

void tree_print(struct node *x){
	if(x != NULLNODE){
	tree_print(x->leftchild);
	printf("%d\t", x->value);
	tree_print(x->rightchild);
	}
}

struct node *search_node_function(int value){
	struct node *x;

	x = TOPNODE;
	while(x != NULLNODE && x->value != value){
		if(value < x->value){
			x = x->leftchild;
		}
		else{
			x = x->rightchild;
		}
	}

	return x;
}

struct node *tree_minimum(struct node *x){
	while(x->leftchild != NULLNODE){
	x = x->leftchild;
	}
	return x;
}

void leftchild_twist(struct node *x){
	struct node *y;
	y = x->rightchild;
	x->rightchild = y->leftchild;
	if(y->leftchild != NULLNODE){
		y->leftchild->node_parent = x;
	}
	y->node_parent = x->node_parent;
	if(y->node_parent == NULLNODE){
		TOPNODE = y;
	}
	else if(x == x->node_parent->leftchild){
		x->node_parent->leftchild = y;
	}
	else{
		x->node_parent->rightchild = y;
	}
	
	y->leftchild = x;
	x->node_parent = y;
}

void tree_print_range(struct node *x, int lrange, int rrange){
	if(x != NULLNODE){
	tree_print_range(x->leftchild,lrange,rrange);
	if(x->value >= lrange && x->value <= rrange)
		printf("%d\t", x->value);
	tree_print_range(x->rightchild, lrange, rrange);
	}
}
void insert_into_tree_helper(struct node *curr){
	while(curr->node_parent->node_colour == RED){
		if(curr->node_parent != curr->node_parent->node_parent->leftchild){
			if(curr->node_parent->node_parent->leftchild->node_colour == BLACK){
				if(curr == curr->node_parent->leftchild){
					curr = curr->node_parent;
					rightchild_twist(curr);
				}
				curr->node_parent->node_colour = BLACK;
				curr->node_parent->node_parent->node_colour = RED;
				leftchild_twist(curr->node_parent->node_parent);
			}
			else{
				curr->node_parent->node_colour = BLACK;
				curr->node_parent->node_parent->leftchild->node_colour = BLACK;
				curr->node_parent->node_parent->node_colour = RED;
				curr = curr->node_parent->node_parent;
			}
		}
		else{
			if(curr->node_parent->node_parent->rightchild->node_colour == BLACK){
				if(curr == curr->node_parent->rightchild){
					curr = curr->node_parent;
					leftchild_twist(curr);
				}
				curr->node_parent->node_colour = BLACK;
				curr->node_parent->node_parent->node_colour = RED;
				rightchild_twist(curr->node_parent->node_parent);
			}
			else{
				curr->node_parent->node_colour = BLACK;
				curr->node_parent->node_parent->rightchild->node_colour = BLACK;
				curr->node_parent->node_parent->node_colour = RED;
				curr = curr->node_parent->node_parent;
			}

		}
	}
	TOPNODE->node_colour = BLACK;
}


void rightchild_twist(struct node *x){
	struct node *y;
	y = x->leftchild;
	x->leftchild = y->rightchild;
	if(y->rightchild != NULLNODE){
		y->rightchild->node_parent = x;
	}
	y->node_parent = x->node_parent;
	if(y->node_parent == NULLNODE){
		TOPNODE = y;
	}
	else if(x == x->node_parent->leftchild){
		x->node_parent->leftchild = y;	
	}
	else{
		x->node_parent->rightchild = y;
	}
	y->rightchild = x;
	x->node_parent = y;
}

unsigned int print_number_of_leaves(struct node* node)  
{  
    if(node == NULLNODE)      
        return 0;  
    if(node->leftchild == NULLNODE && node->rightchild == NULLNODE)  
        return 1;          
    else
        return print_number_of_leaves(node->rightchild) + print_number_of_leaves(node->leftchild);  
}

void insert_into_tree(int value){
	struct node *curr, *x, *y;
	curr = malloc(sizeof(struct node));
	y = NULLNODE;
	x = TOPNODE;

	curr->value = value;
	curr->node_colour = RED;
	curr->leftchild = NULLNODE;
	curr->rightchild = NULLNODE;


	while(x != NULLNODE){
		y = x;
		if(curr->value > x->value){
			x = x->rightchild;
		}
		else{
			x = x->leftchild;
		}
	}

	if(y == NULLNODE){
		TOPNODE = curr;
	}
	else if(curr->value <= y->value){
		y->leftchild = curr;
	}
	else{
		y->rightchild = curr;
	}
	curr->node_parent = y;
	insert_into_tree_helper(curr);
}

void transform_tree(struct node *u, struct node *v){
	if(u->node_parent == NULLNODE){
	TOPNODE = v;
	}
	else if(u == u->node_parent->leftchild){
	u->node_parent->leftchild = v;
	}
	else{
	u->node_parent->rightchild = v;
	}

	v->node_parent = u->node_parent;
}

int maxDepth(struct node* node)  
{ 
   if (node==NULLNODE)  
       return 0; 
   else 
   { 
       int lDepth = maxDepth(node->leftchild); 
       int rDepth = maxDepth(node->rightchild); 
  
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}

void delete_node_function_helper(struct node *x){
	struct node *w;	
	while(x != TOPNODE && x->node_colour == BLACK){
		if(x == x->node_parent->rightchild){
			w = x->node_parent->leftchild;
			if(w->node_colour == RED){
				w->node_colour = BLACK;
				x->node_parent->node_colour = BLACK;
				rightchild_twist(x->node_parent);
				w = x->node_parent->leftchild;
			}
			if(w->leftchild->node_colour == BLACK && w->rightchild->node_colour == BLACK){
				w->node_colour = RED;
				x->node_parent->node_colour = BLACK;
				x = x->node_parent;
			}
			else{
				if(w->leftchild->node_colour == BLACK){
					w->node_colour = RED;
					w->rightchild->node_colour = BLACK;
					leftchild_twist(w);
					w = x->node_parent->leftchild;
				}
				w->node_colour = x->node_parent->node_colour;
				x->node_parent->node_colour = BLACK;
				w->leftchild->node_colour = BLACK;
				rightchild_twist(x->node_parent);
				x = TOPNODE;
			}
		}
		else{
			w = x->node_parent->rightchild;
			if(w->node_colour == RED){
				w->node_colour = BLACK;
				x->node_parent->node_colour = RED;
				leftchild_twist(x->node_parent);
				w = x->node_parent->rightchild;
			}
			if(w->leftchild->node_colour == BLACK && w->rightchild->node_colour == BLACK){
				w->node_colour = RED;
				x->node_parent->node_colour = BLACK;
				x = x->node_parent;
			}
			else{
				if(w->rightchild->node_colour == BLACK){
					w->node_colour = RED;
					w->leftchild->node_colour = BLACK;
					rightchild_twist(w);
					w = x->node_parent->rightchild;
				}
				w->node_colour = x->node_parent->node_colour;
				x->node_parent->node_colour = BLACK;
				x->rightchild->node_colour = BLACK;
				leftchild_twist(x->node_parent);
				x = TOPNODE;	
			}
		}
	}
	x->node_colour = BLACK;
}


int main(){
	int lrange, rrange;
	NULLNODE = malloc(sizeof(struct node));
	NULLNODE->node_colour = BLACK;

	TOPNODE = NULLNODE;

	printf("RED-BLACK TREES \n\n");
	int num_of_values, value;
	printf("Number of values: ");
	scanf("%d", &num_of_values);
	while(num_of_values--){
		printf("Enter value: ");
		scanf("%d", &value);
		insert_into_tree(value);
	}

	printf("PRINT TREE\n\n");
	tree_print(TOPNODE);
	printf("\n");

	printf("HEIGHT OF TREE\n\n");
	printf("%d\n", maxDepth(TOPNODE));

	printf("NUMBER OF LEAVES IN THE TREE \n\n");
	printf("%d\n", print_number_of_leaves(TOPNODE));

	printf("DELETE NODE\n\n");
	printf("Enter value to delete: ");
	scanf("%d", &value);
	delete_node_function(search_node_function(value));
	
	printf("PRINT TREE\n\n");
	tree_print(TOPNODE);
	printf("\n");

	printf("TREE RANGE PRINT TEST\n\n");
	printf("Enter range of values:\n\n");
	scanf("%d %d", &lrange, &rrange);
	tree_print_range(TOPNODE, lrange, rrange);
	printf("\n");
	return 0;
}