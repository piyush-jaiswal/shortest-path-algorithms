#include "stdio.h"
#include "stdlib.h"

struct BinomialNode{
	int key;
	char data;
	int degree;
	struct BinomialNode* p;
	struct BinomialNode* child;
	struct BinomialNode* sibling;
};

struct BinomialHeap{
	struct BinomialNode* head;
};

struct BinomialNode* Make_Binomial_Node(int k);
struct BinomialHeap* Make_Binomial_Heap();
struct BinomialNode* Binomial_Heap_Minimum(struct BinomialHeap* H);
void Binomial_Link (struct BinomialNode* y, struct BinomialNode* z);
struct BinomialNode* Binomial_Heap_Merge (struct BinomialHeap* H1, struct BinomialHeap* H2);
struct BinomialNode* Binomial_Heap_Union(struct BinomialHeap* H1, struct BinomialHeap* H2);
void Binomial_Heap_Insert(struct BinomialHeap* H, struct BinomialNode* x);
struct BinomialNode* Binomial_Heap_Extract_Min(struct BinomialHeap* H);
struct BinomialNode* Binomial_Heap_Reverse(struct BinomialNode* x);

int main(){
    printf("\nPress 1. to insert into binomial heap.");
    printf("\nPress 2. to get minimum of binomial heap.");
    printf("\nPress 3. to extract minimum from binomial heap.");
    printf("\nPress 4. to get list of instructions.");
    printf("\nPress any other key to terminate operation!");
    int ch=1;int dat;
    struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H = Make_Binomial_Heap();
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
    while((ch==1)||(ch==2)||(ch==3)||(ch==4))
    {
    printf("\nEnter your choice: ");
    scanf("%d",&ch);
    if(ch==1)
    {
        printf("\nEnter element: ");
        scanf("%d",&dat);
        x = Make_Binomial_Node(dat);
        Binomial_Heap_Insert(H,x);
        printf("\n%d successfully inserted. The head is %d.\n\n",x->key,H->head->key);
    }
    else if(ch==2)
    {
        if(H->head==NULL)
            printf("\nCannot insert! Heap is empty");
        else
        {
            x=Binomial_Heap_Minimum(H);
            printf("\nMinimum is %d.",x->key);
        }
    }
    else if(ch==3)
    {
        if(H->head==NULL)
            printf("\nCannot extract minimum! Heap is empty");
        else
        {
            x = Binomial_Heap_Extract_Min(H);
				printf("\n%d is extracted\n", x->key);
				if (H->head) {
					printf("\nThe head is %d\n\n", H->head->key);
				}
        }
    }
    else if(ch==4)
    {
        printf("\nPress 1. to insert into binomial heap.");
    printf("\nPress 2. to get minimum of binomial heap.");
    printf("\nPress 3. to extract minimum from binomial heap.");
    printf("\nPress 4. to get list of instructions.");
    printf("\nPress any other key to terminate operation!");
    }
    else
        ch=ch;
    }
    return 0;
}

struct BinomialNode* Make_Binomial_Node(int k){
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	x->child = NULL;
	x->degree = 0;
	x->key = k;
	x->data = 0;
	x->p = NULL;
	x->sibling = NULL;
	return x;
}

struct BinomialHeap* Make_Binomial_Heap(){
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H -> head = NULL;
	return H;
}

struct BinomialNode* Binomial_Heap_Minimum(struct BinomialHeap* H){
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* z = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	x = H->head;
	y = NULL;
	z = NULL;
	int min = 2147483647;
	while (x){
		if (x->key < min){
			min = x->key;
			y = x;
		}
		z = x->sibling;
		x = z;
	}
	return y;
}

void Binomial_Link (struct BinomialNode* y, struct BinomialNode* z){
	y->p = z;
	y->sibling = z->child;
	z->child = y;
	z->degree++;
}

struct BinomialNode* Binomial_Heap_Merge (struct BinomialHeap* H1, struct BinomialHeap* H2){
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* z = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* buf = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	H = Make_Binomial_Heap();
	x = H1->head;
	y = H2->head;
	z = NULL;
	buf = NULL;
	if (x&&y){
	   if (x->degree <= y->degree){
		  z = x;
		  buf = x->sibling;
		  x = buf;
		  } else {
		  z = y;
		  buf = y->sibling;
		  y = buf;
		  }
	} else if (y) {
	  	   z = y;
	  	   buf = y->sibling;
		   y = buf;
	} else if (x){
	  	   z = x;
	  	   buf = x->sibling;
		   x = buf;
	}
	H->head=z;
	while (x && y){
		if (x->degree <= y->degree){
			z->sibling = x;
			buf = x->sibling;
			x = buf;
		} else {
			z->sibling = y;
			buf = y->sibling;
			y = buf;
		}
		buf=z->sibling;
		z=buf;
	}
	if (x){
		z->sibling = x;
	} else if (y){
		z->sibling = y;
	}
	return H->head;
}

struct BinomialNode* Binomial_Heap_Union(struct BinomialHeap* H1, struct BinomialHeap* H2){
	struct BinomialHeap* H = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H = Make_Binomial_Heap();
	H->head = Binomial_Heap_Merge(H1, H2);
	struct BinomialNode* prev_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* next_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	if(H->head == NULL){
		return NULL;
	}
	prev_x = NULL;
	x = H->head;
	next_x = x->sibling;
	while (next_x){
		if ((x->degree != next_x->degree) || ((next_x->sibling != NULL) && next_x->sibling->degree == x->degree)){
			prev_x = x;
			x = next_x;
		} else if (x->key <= next_x->key){
		  	   x->sibling = next_x->sibling;
			   Binomial_Link(next_x,x);
		} else {
		  	if (prev_x == NULL){
				H->head = next_x;
		    }else{
		  		prev_x->sibling = next_x;
		    }
			Binomial_Link(x,next_x);
			x = next_x;
		}
		next_x = x->sibling;
	}
	return H->head;
}

void Binomial_Heap_Insert(struct BinomialHeap* H, struct BinomialNode* x){
	struct BinomialHeap* H_ = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H_->head = x;
	H->head = Binomial_Heap_Union(H, H_);
}

struct BinomialNode* Binomial_Heap_Extract_Min(struct BinomialHeap* H){
	struct BinomialNode* x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* z = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* prev_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* prev_y = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	x = H->head;
	prev_x = NULL;
	y = NULL;
	prev_y = NULL;
	z = NULL;
	int min = 2147483647;
	while (x){
		if (x->key < min){
			prev_y = prev_x;
			min = x->key;
			y = x;
		}
		prev_x = x;
		z = x->sibling;
		x = z;
	}
	if (prev_y){
		prev_y->sibling = y->sibling;
	}else{
		H->head = y->sibling;
	}
	struct BinomialHeap* H_ = (struct BinomialHeap* )malloc(sizeof(struct BinomialHeap));
	H_ = Make_Binomial_Heap();
	H_->head = Binomial_Heap_Reverse(y->child);
	H->head = Binomial_Heap_Union(H, H_);
	return y;
}

struct BinomialNode* Binomial_Heap_Reverse(struct BinomialNode* x){
	struct BinomialNode* prev_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	struct BinomialNode* next_x = (struct BinomialNode* )malloc(sizeof(struct BinomialNode));
	prev_x = NULL;
	next_x = NULL;
	while(x){
		x->p = NULL;
		next_x = x->sibling;
		x->sibling = prev_x;
		prev_x = x;
		x = next_x;
	}
	return prev_x;
}
