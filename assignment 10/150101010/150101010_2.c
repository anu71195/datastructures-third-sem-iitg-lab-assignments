//NAME = ANURAG RAMTEKE
//ROLL NO=150101010
#include <stdio.h>
#include <stdlib.h>
typedef struct node node;
struct node
{
	int coefficient;
	int exponent;
	node * next;
};
node * create_ll()	//create empty linked list
{
	node*temp;
	temp=NULL;
	return temp;
}
node * create_node(int coefficient,int exponent)//create node with vaule coefficient and exponent
{
	node*temp;
	temp=(node*)malloc(sizeof(node));
	temp->coefficient=coefficient;
	temp->exponent=exponent;
	temp->next=NULL;
	return temp;
}
node * insert(node * head,int coefficient,int exponent)//inserts the node with coefficient and exponent
{
	if(head==NULL) head=create_node(coefficient,exponent);
	else if(head->exponent==exponent)		head->coefficient+=coefficient;
	else 	head->next=insert(head->next,coefficient,exponent);
	return head;
}
void print_ll(node * head)//print linked list
{
	if(head==NULL) return;
	printf("%d\t\t%d\n",head->coefficient,head->exponent);
	print_ll(head->next);
}
int input(node**head)//takes the inputfor polynomials and returns the degreeof polynomial
{
	int option,co,ex,max=0;//ex is for exponent and co is for coefficient
	while(1)
	{	
		printf("\n0/1	:	insert/break	:	");
		scanf("%d",&option);
		while(option>1) 
		{
			printf("\nERROR - WRONG INPUT - GIVE INPUT AGAIN\n");
			printf("\n0/1	:	insert/break	:	");
			scanf("%d",&option);
		}
		system("clear");
		if(option==1) break;
		printf("give the coefficient 	:	");
		scanf("%d",&co);
		system("clear");
		printf("Give the exponent	:	"); 
		scanf("%d",&ex);
		if(max<ex) max=ex;
		*head=insert(*head,co,ex);
		system("clear");
		printf("linked list formed is:\n");
		printf("coefficient\texponent\n");
		print_ll(*head);
	}
	return max;
}
node** multiply(node*a,node*b,int size)	//multiply two polynomials a and b
{
	
	int i,ex,co;	//ex is for exponent and co is for coefficient
	node*temp,**head;
	head=(node**)malloc(sizeof(node)*10);
	if(a==NULL && b!=NULL) // one of the polynomial is empty
	{
		head[0]=b;	
		return head;
	}
	else if(a!=NULL && b==NULL)
	{
		head[0]=a;	
		 return head;
	}
	else if(a==NULL && b==NULL) return NULL; //if obth are null
	node* x=a;
	node* y=b;
	while(1)
	{
		if(x==NULL) break;
		while(1)
		{
			if(y==NULL) break;
			ex=(x->exponent)+(y->exponent);
			co=(x->coefficient)*(y->coefficient);
			head[ex%10]=insert(head[ex%10],co ,ex );//multiplied node goes in here
			y=y->next;			
		}
		y=b;
		x=x->next;
	}
	return head;	
		
}
void print_ll_array(node**head)//print array of linked list
{
	int i=0;
	for(i=0;i<10;i++) print_ll(head[i]);
}
int main()
{
	system("clear");
	node * P1,*P2,**head;//p1 is for polynomial 1 and p2 is for polynomial 2 and head is for to store multiplication of both polynomials
	int max1,max2,array_size;
	P1=create_ll();
	P2=create_ll();
	printf("give the data for first polynomial\n");
	max1=input(&P1);//takes teh inputfor first polynomails
	printf("linked list 1 formed is:\n");
	printf("coefficient\texponent\n");
	print_ll(P1);//prints the first polynomails
	printf("\ngive the data for second polynomial\n");
	max2=input(&P2);//takes the input for second polynomial
	printf("linked list 1 is:\n");
	printf("coefficient\texponent\n");
	print_ll(P1);//prints the first polynomial
	printf("\nlinked list 2 is:\n");
	printf("coefficient\texponent\n");
	print_ll(P2);//prints teh second polynomial
	array_size=max1+max2;
	head=multiply(P1,P2,array_size);//multiplicatino fo both polynomials
	if(head==NULL)
	{
		printf("\nERROR - EMPTY LISTS\n\n");
		return 0;
	}
	printf("\n");
	printf("The multiplied linked list formed is \n");
	printf("coefficient\texponent\n");
	print_ll_array(head);//prints the multiplied polynomials
}
