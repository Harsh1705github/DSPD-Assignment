#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


//structure of book database which is present in library
typedef struct book_DB
{
    int book_ID;
    char Title[20];
    char Author[20];
    char subject[20];
    int number_of_copies_issued;
    int number_of_copies_available;
    int demand;                                                  // For q2..
    struct book_DB *left;
    struct book_DB *right;
    int height;
}book_DB;


int height(book_DB *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


//structure of request list asked by students
typedef struct request_queue{
    char Name_of_the_student[20];
    char title_of_the_book[40];
    struct request_queue *next;
}request_queue;


//structure of already borrowed books by students
typedef struct borrower_list{
	char Name_of_the_student[20];
	char title_of_the_book[40];
	int date_of_issue;
	int date_of_return;
	struct borrower_list *next;
}borrower_list;


//strucuture of faulters 
typedef struct faulter_list
{
    char Name_of_student[20];
    struct faulter_list *next;
} faulter_list;


// structure of node used in q5 
typedef struct Node
{
    int data;
    char name[20];
    char title[20];
    struct Node *next;
} Node;


// structure of node used in q4 
typedef struct Node_q4
{
    int data;
    char name[20];
    struct Node_q4 *next;
} Node_q4;


//globally defined pointers
book_DB *root = NULL;
faulter_list *fptr = NULL;
request_queue *first2=NULL;
request_queue *last2=NULL;
borrower_list *first3=NULL;
borrower_list *last3=NULL;
Node *num_list = NULL;
Node_q4 *num_list_q4 = NULL;


int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

// Code for AVL tree 
// Right rotate
book_DB *rightRotate(book_DB *y)
{
    book_DB *x = y->left;
    book_DB *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
book_DB *leftRotate(book_DB *x)
{
    book_DB *y = x->right;
    book_DB *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

//getting balace factor of tree
int getBalance(book_DB *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

//insertion of tree node in tree 
book_DB *insertNode(book_DB *node, book_DB *nptr)
{
    // Find the correct position to insertNode the node and insertNode it
    if (node == NULL)
        return nptr;

    if (nptr->book_ID < node->book_ID)
        node->left = insertNode(node->left, nptr);
    else if (nptr->book_ID > node->book_ID)
        node->right = insertNode(node->right, nptr);
    else
        return node;

    // Update the balance factor of each node and
    // Balance the tree
    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && nptr->book_ID < node->left->book_ID)
        return rightRotate(node);

    if (balance < -1 && nptr->book_ID > node->right->book_ID)
        return leftRotate(node);

    if (balance > 1 && nptr->book_ID > node->left->book_ID)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && nptr->book_ID < node->right->book_ID)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


void greetings()
{
    printf("\n\n");
    printf("\t\t\t\t\t\t \t\t\t      **********************************************\n");
    printf("\t\t\t\t\t\t \t\t\t      *                                            *\n");
    printf("\t\t\t\t\t\t \t\t\t      *                                            *\n");
    printf("\t\t\t\t\t\t \t\t\t      *     ----------------------------------     *\n");
    printf("\t\t\t\t\t\t \t\t\t      *      WELCOME TO BOOK ACCESS MANAGEMENT     *\n");
    printf("\t\t\t\t\t\t \t\t\t      *     ----------------------------------     *\n");
    printf("\t\t\t\t\t\t \t\t\t      *                                            *\n");
    printf("\t\t\t\t\t\t \t\t\t      *                                            *\n");
    printf("\t\t\t\t\t\t \t\t\t      **********************************************\n");
    printf("\n\n");
}


// Used to initialise library with books 
book_DB *make_library()
{
    int n;
    printf("Enter number of books\n");
    scanf("%d", &n);
    fflush(stdin);
    while (n--)
    {
        book_DB *nptr = (book_DB *)malloc(sizeof(book_DB));
        printf("Enter The ID of book: \n");
        scanf("%d", &nptr->book_ID);
        fflush(stdin);
        printf("Enter the Title of Book: \n");
        gets(nptr->Title);
        fflush(stdin);
        printf("Enter the name of Author of Book: \n");
        gets(nptr->Author);
        fflush(stdin);
        printf("Enter the subject of book: \n");
        gets(nptr->subject);
        fflush(stdin);
        printf("Enter the number of copies issued of this book: \n");
        scanf("%d", &nptr->number_of_copies_issued);
        nptr->demand = 0;
        printf("Enter the number of copies avaliable of this book: \n");
        scanf("%d", &nptr->number_of_copies_available);
        fflush(stdin);
        nptr->left = NULL;
        nptr->right = NULL;
        nptr->height = 1;
        root = insertNode(root, nptr);
        printf("\n");
    }
    return root;
}


//creation of request queue by user
void create_request_queue(char name[],char title_book[])
{
    request_queue *temp2 = NULL;
    if (first2 == NULL)
    {
        first2 = (request_queue *)malloc(sizeof(request_queue));
        strcpy(first2->Name_of_the_student,name);
        strcpy(first2->title_of_the_book,title_book);
        first2->next = NULL;
        last2 = first2;
    }

    else
    {
        temp2 = (request_queue *)malloc(sizeof(request_queue));

        strcpy(temp2->Name_of_the_student,name);
        strcpy(temp2->title_of_the_book,title_book);
        temp2->next = NULL;
        last2->next = temp2;
        last2 = temp2;
    }	
}


//creation of borrowed list by user
void create_borrower_list(char title[],char name[],int issue_date,int return_date)
{
	borrower_list *temp3 = NULL;
    if (first3 == NULL)
    {
        first3 = (borrower_list *)malloc(sizeof(borrower_list));
        strcpy(first3->title_of_the_book, title);
        strcpy(first3->Name_of_the_student,name);
        first3->date_of_issue =issue_date;
        first3->date_of_return =return_date;
        first3->next = NULL;
        last3 = first3;
    }

    else
    {
        temp3 = (borrower_list *)malloc(sizeof(borrower_list));

        strcpy(temp3->title_of_the_book, title);
        strcpy(temp3->Name_of_the_student,name);
        temp3->date_of_issue =issue_date;
        temp3->date_of_return =return_date;
        temp3->next = NULL;
        last3->next = temp3;
        last3 = temp3;
    }
}


//Function checks student has already 3 books borrowed or not.
int is_borrow(char *s)
{
    borrower_list *temp = first3;
    int i = 0;
    while (temp)
    {
        if (strcmp(s, temp->Name_of_the_student) == 0)
        {
            i++;
        }
        temp = temp->next;
    }
    if (i >= 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// checks student returned book on time(within 15 days)or not.
int is_return(char *s)
{
    borrower_list *temp = first3;
    while (temp)
    {
        if (strcmp(s, temp->Name_of_the_student) == 0)
        {
            if ((temp->date_of_return - temp->date_of_issue) > 15)
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}


int found;                                            //global varialble to find copies are available or not.

//checks copies of book are available or not.
void inorder_q1(book_DB *curr, char book[])
{
	if(curr!=NULL)
	{
	if (strcmp(book, curr->Title) == 0 && curr->number_of_copies_available > 0)
        {
            found=1;
        }
		inorder_q1(curr->left,book);
		inorder_q1(curr->right,book);	
	}
}

int book_checking(char book[])
{
	found = 0;
	inorder_q1(root,book);
	
	if(found==1)
	return 1;
	else
	return 0;	
}


//CONDITION FOR CASE 1
//a.student not borrowed more than 3 books
//b.student must returned book within 15 days
//c.book must be available in book list

//1.Display student who get books.
void display_of_students_who_get_books()
{
	request_queue *temp = first2;
    printf("\nstudents who will get the books are: \n");
    while (temp)
    {
        int t1 = is_borrow(temp->Name_of_the_student);
        int t2 = is_return(temp->Name_of_the_student);
        int t3 = book_checking(temp->title_of_the_book);
        
        if (!(t1) && !(t2) && t3)
        {
            puts(temp->Name_of_the_student);
            printf("\n");
        }
        temp = temp->next;
    }

}

int max_demand=0;
char demand_book[40];

//2.Function to find most demanded book..
void most_demand_books(book_DB *curr)
{
	book_DB* temp = curr;
	
	if(temp!=NULL)
	{
		int count=0;
		request_queue* temp2 = first2;
		
		while(temp2!=NULL)
		{
		    if(strcmp(temp2->title_of_the_book,temp->Title)==0)	
			  {
			    count++;
		   	  }
		   	  temp2=temp2->next;
		}
		
		temp->demand=count + temp->number_of_copies_issued;
		if(temp->demand > max_demand)
		{
			max_demand=temp->demand;
			strcpy(demand_book,temp->Title);
		}
		
	most_demand_books(curr->left);
	most_demand_books(curr->right);
	}
}


//suppose this is present date. 16th April, 2022
int current_date=20220416;                                      //date format yyyymmdd         .

//book available in 3 days or not.
// return 1 for yes and 0 for no.
int is_available_in_3_days(char book[])
{
	
	borrower_list *temp=first3;
    while (temp)
    {
        if (strcmp(book, temp->title_of_the_book) == 0 && (temp->date_of_return-current_date)<=3)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


//3.Within first 3 days how many books can be given to students.
void books_given_students_in_3_days()
{
   request_queue *temp=first2;
   int count=0;
   printf("Books can be given to students within 3 days are: \n");
   while (temp!=NULL)
    {  
        int t1 = is_borrow(temp->Name_of_the_student);
        int t2 = is_return(temp->Name_of_the_student);
        int t3 = book_checking(temp->title_of_the_book);
        int t4 = is_available_in_3_days(temp->title_of_the_book);
       
        
        if (!(t1) && !(t2) && t3)
        {
        	
            puts(temp->title_of_the_book);
            count++;
            printf("\n");
        }
        else if(!(t1) && !(t2) && (t4))
        {
        	puts(temp->title_of_the_book);
            count++;
            printf("\n");    	
		}
        temp = temp->next;
    }
    printf("Total books given is %d\n",count);
} 


//4.Sort and display borowwer list.
void Borrow_List_Descending()
{
	struct borrower_list *p=first3;
	struct borrower_list *q;
	
	int count;
	char arr[20],arr1[20];
	
	printf("\nThe borrower_list according to the number of books issued in descending order: ");
	while(p!=0)
	{
		q=p->next;
		count=0;
		while(q!=0)
		{
			if(strcmp(q->Name_of_the_student,p->Name_of_the_student)==0)
			{
				count++;
			}
			q=q->next;
		}
		if(count==2)
		{
			strcpy(arr,p->Name_of_the_student);
			printf("\n");
			puts(p->Name_of_the_student);
		}
		p=p->next;
	}
	
	p=first3;
	while(p!=0)
	{
		q=p->next;
		count=0;
		while(q!=0)
		{
			if(strcmp(q->Name_of_the_student,p->Name_of_the_student)==0)
			{
				count++;
			}
			q=q->next;
		}
		if(count==1 && strcmp(arr,p->Name_of_the_student)!=0)
		{
			strcpy(arr1,p->Name_of_the_student);
			printf("\n");
			puts(p->Name_of_the_student);
		}
		p=p->next;
	}
	
	p=first3;
	while(p!=0)
	{
		q=p->next;
		count=0;
		while(q!=0)
		{
			if(strcmp(q->Name_of_the_student,p->Name_of_the_student)==0)
			{
				count++;
			}
			q=q->next;
		}
		if(count==0 && strcmp(arr,p->Name_of_the_student)!=0 && strcmp(arr1,p->Name_of_the_student)!=0)
		{
			printf("\n");
			puts(p->Name_of_the_student);
		}
		p=p->next;
	}
	  printf("\n\n---------------------------------------------------\n\n");
}


void free_list_author()
{
    while(num_list!=NULL)
	{
	Node *temp = num_list;
	num_list = num_list->next;
	temp->next = NULL;
	free(temp);	
	}	
}

void create_node(char Title[], char Author[], int num_copies)
{
	Node *temp=NULL;
	
	if(num_list==NULL)
	{
		num_list = (Node *)malloc(sizeof(Node));
        strcpy(num_list->name, Author);
        strcpy(num_list->title, Title);
        num_list->data = num_copies;
        num_list->next = NULL;
	}
	else
	{
		temp=(Node *)malloc(sizeof(Node));
        strcpy(temp->name, Author);
        strcpy(temp->title, Title);
        temp->data = num_copies;
        temp->next = num_list;
        num_list=temp;
        
	}
}


int max_q5=0;                       //global variable for storing maximum copies of particular given subject.

//5.Sort and display of all books of a particular subject based on its copies.
void Sort_Title_Author(book_DB *curr, char subject[])
{
	
	book_DB *m=curr;
	
	if(m!=NULL)
	{
		if(strcmp(subject,m->subject)==0)
		{
		create_node(m->Title,m->Author,m->number_of_copies_available);
		if(m->number_of_copies_available>max_q5)
		{
			max_q5=m->number_of_copies_available;
		}
	    }
	Sort_Title_Author(curr->left, subject);
	Sort_Title_Author(curr->right, subject);	
	}
		
}

//Display of author and title..
void Display_Title_Author()
{
  Node *temp=NULL;
  int i=max_q5;
  while(i>=0)
  {
  	temp=num_list;
    while(temp!=NULL)
    {
    	if(temp->data==i)
  	     {
  	          printf("\nAuthor: %s",temp->name);
	          printf("\tTitle: %s",temp->title);
		      printf("\n");	
         }
    temp=temp->next;
    }
    i=i-1;
  }
}


//6.Display requested books whose copies are available
void display_re_copies_available()
{
	request_queue *temp1 = first2;
	int a;
    printf("Names of the requested books whose copies are available: \n");
    while (temp1!=NULL)
    {
    	a=book_checking(temp1->title_of_the_book);
    	if(a==1)
    	{
    		printf("\nBook Title: ");
    		puts(temp1->title_of_the_book);
    		
		}
        temp1 = temp1->next;
    }
}

int not_issued_q7=0;                      //global variable to check if atleast 1 book is not issued by anyone or not..

void visit_q7(book_DB *temp)
{
	if(temp->number_of_copies_issued==0)
	{
		puts(temp->Title);
		printf("\n");
		not_issued_q7=1;	
	}
}
//7.Display of books which are not issued by anyone
void display_not_issued(book_DB *curr)
{
	if(curr!=NULL)
	{
	visit_q7(curr);
	display_not_issued(curr->left);
	display_not_issued(curr->right);	
	}
}


int check_q8 = 0;                 //global variable to check if atleast one book_id is within range or not..
//8.Display of books within given range..
void display_book_range(book_DB *curr, int start, int end)
{
	if(curr!=NULL)
	{
	      if(curr->book_ID < start)
	        {
	            display_book_range(curr->right, start, end);	
	        }
	      else if(curr->book_ID > end)
	        {
	            display_book_range(curr->left, start, end);	
	        }
	      else
	        {
	        	check_q8 = 1;
	            printf("\nBook Title: ");
	            puts(curr->Title);
	            display_book_range(curr->left,start,end);
	            display_book_range(curr->right,start,end);
	        }
    }
}

//formation of defaulter list..
void formation_defaulter_list()
{
	borrower_list *temp = first3;
	faulter_list *temp2 = NULL;
	
	while(temp)
	{
		if(temp->date_of_return - temp->date_of_issue > 15)
		{
			if(fptr==NULL)
			{
			fptr=(faulter_list *)malloc(sizeof(faulter_list));
			strcpy(fptr->Name_of_student,temp->Name_of_the_student);
			fptr->next = NULL;			
			}
			else
			{
			temp2=(faulter_list *)malloc(sizeof(faulter_list));
			strcpy(temp2->Name_of_student,temp->Name_of_the_student);
			temp2->next = fptr;
			fptr=temp2;
	    	}
		}
		temp=temp->next;
	}
}


//function to display defaulter list..
void display_defaulter_list()
{
	faulter_list *temp = fptr;
	printf("Name of defaulters: \n");
	while(temp!=NULL)
	{	
		puts(temp->Name_of_student);
		printf("\n");
		temp=temp->next;
	}
}


//driver code
int main()
{
	greetings();                            //greetings function
	int i,m;

    root=make_library();                    //formation of book database
    printf("\n");
    
	char name[20],title_book[40];
	printf("\n\nNo of students asking for books: ");
	scanf("%d",&m);
	fflush(stdin);
	for(i=0;i<m;i++)
	{
	  printf("\nEnter name of student: \n");
	  gets(name);
	  printf("Enter title of book asking: \n");
	  gets(title_book);
	  fflush(stdin);
	  create_request_queue(name,title_book);
	}
	
    int p;
	char title[40],name_student[20];
	int issue_date,return_date;
	printf("\nNo of borrower: ");
	scanf("%d",&p);
	fflush(stdin);
	for(i=0;i<p;i++)
	{
	  printf("\nEnter title: \n");
	  gets(title);
	  printf("Enter name: \n");
	  gets(name_student);
	  printf("Enter issued date(yyyymmdd): \n");
	  scanf("%d",&issue_date);
	  printf("Enter return date(yyyymmdd): \n");
	  scanf("%d",&return_date);
	  fflush(stdin);
	  create_borrower_list(title,name_student,issue_date,return_date);
	}	
    
	printf("\n\n");
    printf("\t\t\t**********************************************\n\n\n");
	printf("\n0.Exit program.\n1.Display name of students who'll get books.\n2.To find the most demand book.\n3.Within first 3 days how many books can be given to students.\n");
	printf("4.Sort borowwer list according to number of books issued in descending order.\n5.Sort and display of all books of a particular subject based on its copies.\n6.Display name of requested book whose copies are available.\n");
	printf("7.Display title of bookch are not issued by anyone.\n8.Given from boook-id to boook-id display all their book in range.\n9.Display of defaulters.\n\n");
		
	int flag=1;
	int choice;
	while(flag==1)
	{
		printf("\nEnter your choice: ");
		scanf("%d",&choice);
			
		switch(choice){
			
			case 0:{
				printf("_______Exit the program_________");
				flag=0;
				break;
			}			
			case 1:{
				display_of_students_who_get_books();
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			case 2:{
				most_demand_books(root);
				printf("\nThe book in most demand is: ");
	            puts(demand_book);
	            printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			case 3:{
				books_given_students_in_3_days();
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			case 4:{
				Borrow_List_Descending();
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}			
			case 5:{
				char sub[20];
	            printf("Enter subject :");
	            scanf("%s",sub);
				Sort_Title_Author(root,sub);
				Display_Title_Author();
				free_list_author();
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			case 6:{
				display_re_copies_available();
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			case 7:{
				printf("\nBooks which are not issued by anyone: \n");
				display_not_issued(root);
				if(not_issued_q7=0)
				{
					printf("Every book present in book database is issued.");					
				}
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			case 8:{
				int id_start,id_end;
				printf("\nEnter starting book_id: ");
				scanf("%d",&id_start);
				printf("Enter ending book_id: ");
				scanf("%d",&id_end);
				printf("Books whose book_ID is between %d and %d are: \n",id_start,id_end);
				check_q8 = 0;
				display_book_range(root,id_start,id_end);
				if(check_q8==0)
				{
					printf("NONE");
				}
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			
			case 9:{
				formation_defaulter_list();
				display_defaulter_list();
				printf("\n\n---------------------------------------------------\n\n");
				break;
			}
			default:{
				printf("Enter correct choice of given options.: ");
				break;
			}
		}				
		
	}
	return 0;
}




