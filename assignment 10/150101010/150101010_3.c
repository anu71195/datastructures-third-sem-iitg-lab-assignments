//NAME = ANURAG RAMTEKE
//ROLL NO = 150101010
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
	int *ISBN;
	node*left;
	node*right;
	char *title;
	char *author;
	int year;
	int  cost;
	int number;	
};

node*create_heap()//creates emtpy heap
{
	node*temp;
	temp=NULL;
	return temp;
}
node*create_node(int*ISBN,char * title,char*author,int year, int cost,int number)//creates node with certaiin alues as indicated
{
	node*temp;
	temp=(node*)malloc(sizeof(node));
	temp->ISBN=ISBN;
	temp->left=NULL;
	temp->right=NULL;
	temp->title=title;
	temp->author=author;
	temp->year=year;
	temp->cost=cost;
	temp->number=number;

}
int comparison(node*a,node*b)//comparison nodes a and b if a is greater then 0 and if b is greater than 1 and if equal then return 2
{
	int i; 
	for(i=0;i<5;i++)	
	{
		if((a->ISBN[2-i])>(b->ISBN[2-i])) return 0;
		else if((a->ISBN[2-i])<(b->ISBN[2-i])) return 1;
	}
	return 2;
}
node*insert(node*head,node*a)//inserts the node a in to the heap head in its correct places according to the ISBN No
{
	if(head==NULL) head=a;
	else if(comparison(head,a)==0) head->left=insert(head->left,a);
	else if(comparison(head,a)==1) head->right=insert(head->right,a);
	else if(comparison(head,a)==2) 
	{
		printf("ERROR - DUBLICATE ENTRY\n");
		return head;
	}
	return head; 
}
void print_heap(node*head)//prints the heap of book with its detials
{
	if(head==NULL) return;
	int dn;
	dn=no_digits(head->ISBN[1])+no_digits(head->ISBN[2])+no_digits(head->ISBN[3]);
	print_heap(head->left);
	
	printf("%.3d-%d-%d-%d-%.1d    %.4d    %d    %d\t\t%s\t\t%s\n",head->ISBN[0],head->ISBN[1],head->ISBN[2],head->ISBN[3],head->ISBN[4],head->year,head->cost,head->number,head->author,head->title);
	print_heap(head->right);
}
node*input(node*head,int a,int b, int c,int d, int e ,char*title,char*author,int year,int cost,int number)//gets the inbut for every book and set its value
{
	node*temp;
	int*ISBN;
	ISBN=(int*)malloc(sizeof(int)*3);
	ISBN[0]=a;
	ISBN[1]=b;
	ISBN[2]=c;
	ISBN[3]=d;
	ISBN[4]=e;
	temp=create_node(ISBN,title,author,year,cost,number);
	head=insert(head,temp);	
	return head;
}
void increase_10_percent(node * head)//increases the cost of each book by 10%
{
	if(head==NULL) return;
	increase_10_percent(head->left);
	head->cost+=(head->cost)/10;
	increase_10_percent(head->right);
	
}
int search(node*head,node*temp)//searches temp node in head
{
	int t;
	if(head==NULL) return -1;
	if(comparison(head,temp)==2) return head->number;//does the comparison 2 means equal
	t=search(head->left,temp);
	if(t>=0) return t;
	t=search(head->right,temp);	
	if(t>=0) return t;
	return -1;
}
int no_digits(int number)//calculates the no of digits in a number
{
	int k=1,length=0;
	while(1)
	{
		if(k>number) return length;
		else 
		{
			k*=10;
			length++;
		}
	}
}
int power(int a, int b)//powering terms i.e. a^b
{
	int i,powe=1;
	for(i=0;i<b;i++) powe*=a;
	return powe;
}
int checksum(int*isbn)//checksum i.e. the last single digit in the ISBN
{
	int d,checksum,even,odd,i,powe,j=1,flag=0,temp,divide=10;//even means even sum and odd means odd sum
	even=7;
	odd=9+isbn[0]%10;
	for(i=1;i<4;i++)
	{
		d=no_digits(isbn[i]);//returns the no of digits in a number
		while(1)
		{
			powe=power(10,d-j);//returns the power such that 10^(d-j)
			temp=isbn[i]/powe;//to get the digit required first divide it by continouoysly increasing power and then divide it by 10;
			temp=temp%divide;
			if(flag==0)
			{

				even+=temp;//even terms added
				flag=1;//to add next time in odd
			}
			else if(flag==1)
			{
				odd+=temp;//odd terms added
				flag=0;//to add next time in even
			}
			j++;
			if(j>d)break;
		}
		j=1;
	}
	even*=3;//multiplying even terms by 3
	checksum=even+odd;//calculating checcksum
	checksum=checksum%10;//getting final checksum 
	checksum=10-checksum;
	return checksum;
}
int main()
{
	system("clear");
	node*head,*temp;
	char *title,*author;
	int option,*isbn,i,j,number,cost,year,flag=0 , sum,dn;//dn stands for digits numbers as in number of digits
	title=(char*)malloc(sizeof(char)*100);
	author=(char*)malloc(sizeof(char)*100);
	isbn=(int*)malloc(sizeof(int)*5);
	head=create_heap();//creates empty heap
	head=input(head,978,93,32573,90,1,"Computer Systems: A Programmer's Perspec","Hallaron Bryant",2016,682,7);//takes input for the books
	head=input(head,978,12,59004,61,2,"PROGRAMMING IN ANSI C 6TH EDITION","E BALAGURUSWAMY",2013,310,23);
	head=input(head,978,93,80931,91,3,"Data Mining: Concepts and Techniques","Jiwaei Han",2007,434,83);
	head=input(head,978,81,76561,26,6,"Let Us C++","Yashavant P. ",2003,218,97);
	head=input(head,978,93,52301,67,6,"Hadoop: The Definitive Guide","Tom White",2015,700,45);
	system("clear");
	printf("ISBN code\t     year    cost sold no.   author \t\ttitle\n\n");
	print_heap(head);//prints the book details
	printf("\n");
	while(1)
	{
		printf("\n0/1/2/3/4	:	insert/increase-10-percent/search/print/break	:	");
		scanf("%d",&option);//options takes the input for the action to take plae as instruted by user
		while(option>4)//in case of wrong input
		{
			printf("\nERROR - WRONG INPUT - GIVE THE INPUT AGAIN\n\n");
			printf("0/1/2/3	:	insert/increase-10-percent/search/break	:	");
			scanf("%d",&option);
		}
		if(option==4) break;//break input
		else if (option==3) //printing option
		{
			printf("\nISBN code\t     year    cost sold no.   author \t\ttitle\n\n");
			print_heap(head);
		}
		else if (option==2)//to search a particular ISBN
		{	
			printf("\nGive the ISBN number in the format of 5 difference groups x x x x x where each x represents a number of varying length	:	");
			for(i=0;i<5;i++) scanf("%d",&isbn[i]);
			temp=create_node(isbn,"dg "," sdfg",0, 0,0);//dummy node to search it
			j=search(head,temp); 
			if(j==-1) printf("BOOK FOUND\n");
			else printf("\nnumber of copies sold is %d\n",j);//gives the no of copies sold
		}
		else if(option==1) increase_10_percent(head);//increase cost by 10 percent
		else if(option==0)//insert a book
		{
			printf("\nGive the isbn no. in the format of 5 difference groups x x x x x where each x represents a number of varying length	:	");
			while(flag==0)
			{
				for(i=0;i<5;i++) 
				{
					scanf("%d",&isbn[i]);//takes the input of isbn and followed by conditions in case of wrong input
					if(i==4) 
					{

						 sum=checksum(isbn); 
						 
					}	
					if(isbn[0]!=978&&isbn[0]!=979&&i==0)
					{
						printf("ERROR - WRONG INPUT - FIRST NUMBER SHOULD BE EITHER 978 OR 979	- GIVE THE ISBN AGAIN 	:	");
						break;
					}
					if((isbn[1]>99999||isbn[1]<0)&&(i==1))
					{
						printf("ERROR - WRONG INPUT - SECOND NUMBER SHOULD BE BETWEEN 1 AND 99999	- GIVE THE ISBN AGAIN	:	");
						break;

					}
					if((isbn[2]>9999999||isbn[2]<0)&&(i==2))
					{
						printf("ERROR - WRONG INPUT - THIRD NUMBER SHOULD BE BETWEEN 1 AND 9999999	- GIVE THE ISBN AGAIN	:	");
						break;

					}
					if((isbn[3]>999999||isbn[3]<0)&&(i==3))
					{
						printf("ERROR - WRONG INPUT - FOURTH NUMBER SHOULD BE BETWEEN 1 AND 999999	- GIVE THE ISBN AGAIN	: 	");
						break;
					}
					if((isbn[4]!=sum)&&(i==4))
					{
						printf("ERROR - WRONG INPUT - FIFTH NUMBER IS WRONG - GIVE HTE ISBN AGAIN	:	");
						break;
					} 
					else if(i==4) flag=1;//if all the conditions are passed that is no error in the input
				}
			}
			flag=0;//takes the input from the user for books
			printf("Give the name of the author	:	");
			scanf("%s",author);
			printf("Give the name of the title of the book	:	");	
			scanf("%s",title);
			printf("Give the year of the book published	:	");
			scanf("%d",&year);
			printf("Give the cost of the book	:	");
			scanf("%d",&cost);
			printf("Give the number of books sold	:	");
			scanf("%d",&number);
			head=input(head,isbn[0],isbn[1],isbn[2],isbn[3],isbn[4],title,author,year,cost,number);//putting the book in the heap
		}
	}
}
