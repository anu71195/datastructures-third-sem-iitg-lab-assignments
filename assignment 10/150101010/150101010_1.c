//NAME = ANURAG RAMTEKE
//ROLL NO = 150101010
#include <stdio.h>
#include <stdlib.h>

void print(int*table,int m)//printing the table(array)
{
	int i;
	printf("INDEX	LOCATION\n");
	for(i=0;i<m;i++) printf("%d\t%d\n",i,table[i]);
	printf("\n");
}

int linear_probing(int m,int x,int*array,int*collision)//linear probing
{
	int index;
	index = x % m;			//offset
	while(1)
	{
		if(array[index]==0||array[index]==32000) 
		{
			array[index]=x;
			return index;
		}
		index+=1;
		index=index%m;
		(*collision)+=1;
	}
}
int doubl_hashing(int m,int x,int*array,int*collision)//double hashing
{
	int index,jump;
	index=x%m;
	jump=(x%(m-1))+1;			//offset
	while(1)
	{
		if(array[index]==0||array[index]==32000) 
		{
			array[index]=x;
			return index;
		}
		index+=jump;		//offseet
		index=index%m;
		(*collision)+=1;
	}
}
int quadratic_probing(int m,int x,int*array,int*collision) //quadratic probing
{
	int index,jump=0,i=0;
	index=x%m+ i + i*i*3;				//offset
	while (1)
	{
		if(array[index]==0||array[index]==32000) 
		{
			array[index]=x;
			return index;
		}
		i++;
		index=x%m + i + i*i*3;			//offset
		index=index%m;
		(*collision)+=1;
	}
	 
}
int search_linear_probing(int * array, int m, int x)//search by linear probing
{
	int index,j;
	index = x % m;			//offset
	for(j=0;j<m;j++)
	{
		if(array[index]==x)
		{
			printf("\nKEY FOUND\n");
			return index;
		}
		else if(array[index]==0) 
		{
			printf("\nKEY NOT FOUND\n");
			
			return  m+1;
		}
		index+=1;
		index=index%m;
	}
	printf("\nKEY NOT FOUND\n\n");
	return (m+1);
}
int search_quadratic_probing(int * array, int m, int x)//search by quadratic probing
{
	int index,jump=0,i=0,j;
	index=x%m+ i + i*i*3;	//offset
	for(j=0;j<m;j++)
	{
		if(array[index]==x)
		{
			printf("\nKEY FOUND\n");
			return index;
		}
		else if(array[index]==0) 
		{
			printf("\nKEY NOT FOUND\n");
			return  m+1;
		}
		i++;
		index=x%m + i + i*i*3; //offset
		index=index%m;
	}
	 
	printf("\nKEY NOT FOUND\n\n");
	return (m+1);	
}
int search_double_hashing(int * array, int m, int x)//searching in double hashing
{
	int index,jump,j;
	index=x%m;
	jump=(x%(m-1))+1;			//offset
	for(j=0;j<m;j++)
	{
		if(array[index]==x)
		{
			printf("\nKEY FOUND\n");
			return index;
		}
		else if(array[index]==0) 
		{
			printf("\nKEY NOT FOUND\n");
			return  m+1;
		}
		index+=jump;
		index=index%m;
	}
		printf("\nKEY NOT FOUND\n\n");
		return (m+1);
}

void delete_linear_probing(int * array, int m, int x)//delete by linear probing
{
	int index;
	index = search_linear_probing(array, m, x);//searching the index
	if(index==(m+1)) return;
	else array[index]=32000;
}
void delete_quadratic_probing(int * array, int m, int x)//delete by quadratic probing
{
	int index;
	index = search_quadratic_probing(array, m, x);//searching the index
	if(index==(m+1)) return;
	else array[index]=32000;
}
void  delete_double_hashing(int * array, int m, int x)//delete by double hashing
{
	int index;
	index = search_double_hashing(array, m, x);//searching the index
	if(index==(m+1)) return;
	else array[index]=32000;
}
int main()
{
	system("clear");	
	int m,*linear_probing_array,*quadratic_probing_array,*double_hashing_array,collision1=0,collision2=0,collision3=0,number=0,x,option,out,temp,iopt;
	//m is for the size of the hash table, collision1,2,3 respectively is for linear probing,quadratic probing,double hashing	
	printf("\n0/1 	:	userinput/random:");//option whether to have random generator or userinput entirely
	scanf("%d",&option); system("clear");
	while (1)
	{
		if (option<2) 	break;//in case of wrong input
		printf("\nERROR - WRONG INPUT - GIVE INPUT AGAIN:\n\n");
		printf("0/1 	:	userinput/random:");	
		scanf("%d",&option);
	}
	
	if(option==0)//user input
	{
		printf("\ngive the size of hash table:");
		scanf("%d",&m);	system("clear");
		linear_probing_array=(int*)malloc(sizeof(int)*m);
		quadratic_probing_array=(int*)malloc(sizeof(int)*m);
		double_hashing_array=(int*)malloc(sizeof(int)*m);
		
		while(1)
		{
			printf("0/1/2/3	:	insert/delete/break/status");
			scanf("%d",&iopt); system("clear");//iopt is for the action to take
			if(iopt==0)
			{
	
				printf("Give an elements to insert : ");
				scanf("%d",&x);	system("clear");
				number++;//counts the number of input given
				if(number>m) 
				{
					printf("OVERFLOW");
					return 0;
				}
				linear_probing(m,x,linear_probing_array,&collision1);//insert by linear probing
				doubl_hashing(m, x,double_hashing_array,&collision3);//insert by double hasihing
				quadratic_probing( m, x,quadratic_probing_array,&collision2);//insert by quadratic probing
				
			}
			else if(iopt==1)
			{
				printf("Give an element to delete : ");
				scanf("%d",&x);system("clear");number--;
				delete_linear_probing(linear_probing_array ,m,x);//delete by linear probing
				delete_double_hashing(double_hashing_array,m, x );//delete by double hashing
				delete_quadratic_probing( quadratic_probing_array,m, x );//delete by quadratic probing

				
			}
			else if(iopt==2) break;
			else if(iopt==3)
			{
				
				printf("\nFOR LINEAR PROBING\n");
				print(linear_probing_array,m);//printing
				printf("No of collisions in linear probing are %d\n\n",collision1);
				printf("FOR QUADRATIC PROBING\n");
				print(quadratic_probing_array,m);
				printf("No of collisions in quadratic probing are %d\n\n",collision2);
				printf("FOR DOUBLE HASHING\n");
				print(double_hashing_array,m);
				printf("No of collisions in double hashing are   %d\n\n",collision3);
				printf("\n");
			}
		}
		
	}
	else if (option==1)//random generator
	{
		m=rand()%100;//m randomly generator below 100
		printf("size of array generated is =%d\n",m);
		linear_probing_array=(int*)malloc(sizeof(int)*m);
		quadratic_probing_array=(int*)malloc(sizeof(int)*m);
		double_hashing_array=(int*)malloc(sizeof(int)*m);
		while(1)
		{
			x=rand();
			number++;
			if(number>m)//overflowing condition 
			{
				break;
			}
			linear_probing(m,x,linear_probing_array,&collision1);//insert by linear probing
			doubl_hashing(m, x,double_hashing_array,&collision3); //insert by double hashing
			quadratic_probing( m, x,quadratic_probing_array,&collision2); //insert by quadratic probing
			 
			 
		}
		while(1)
		{
			printf("0/1/2/3	:	insert/delete/break/status");
			scanf("%d",&iopt); system("clear");
			if(iopt==0)
			{
	
				printf("Give an elements to insert : ");
				scanf("%d",&x);	system("clear");
				number++;
				if(number>m) 
				{
					printf("OVERFLOW");
					return 0;
				}
				linear_probing(m,x,linear_probing_array,&collision1);//insert by linear probing
				doubl_hashing(m, x,double_hashing_array,&collision3);//insert by double hashing
				quadratic_probing( m, x,quadratic_probing_array,&collision2);//insert by quadratic probing
				
			}
			else if(iopt==1)
			{
				printf("Give an element to delete : ");
				scanf("%d",&x);system("clear");number--;
				delete_linear_probing(linear_probing_array ,m,x);//delete by linear probing
				delete_double_hashing(double_hashing_array,m, x );//delete by duble hashing
				delete_quadratic_probing( quadratic_probing_array,m, x );//delete by quadratic probing

				
			}
			else if(iopt==2) break;
			else if(iopt==3)
			{
				
				printf("\nFOR LINEAR PROBING\n");
				print(linear_probing_array,m);//printing
				printf("No of collisions in linear probing are %d\n\n",collision1);
				printf("FOR QUADRATIC PROBING\n");
				print(quadratic_probing_array,m);
				printf("No of collisions in quadratic probing are %d\n\n",collision2);
				printf("FOR DOUBLE HASHING\n");
				print(double_hashing_array,m);
				printf("No of collisions in double hashing are   %d\n\n",collision3);
				printf("\n");
			}
		}
		
	}
}
