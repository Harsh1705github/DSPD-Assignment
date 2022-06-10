#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


//structure of book list which is present in library
typedef struct book_list{
    char Title[40];
    char subject[20];
    char author[30];
    int number_of_copies_issued;
    int number_of_copies_available;
    struct book_list *next;
}book_list;


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

//globally defined pointers
book_list *first1=NULL;
book_list *last1=NULL;
request_queue *first2=NULL;
request_queue *last2=NULL;
borrower_list *first3=NULL;
borrower_list *last3=NULL;
request_queue *defaulter_list=NULL;
request_queue *defaulter_list_last=NULL;

void greetings()
{
    printf("\n\n");
    printf("\t\t\t     **********************************************\n");
    printf("\t\t\t     *                                            *\n");
    printf("\t\t\t     *                                            *\n");
    printf("\t\t\t     *     ----------------------------------     *\n");
    printf("\t\t\t     *      WELCOME TO BOOK ACCESS MANAGEMENT     *\n");
    printf("\t\t\t     *     ----------------------------------     *\n");
    printf("\t\t\t     *                                            *\n");
    printf("\t\t\t     *                                            *\n");
    printf("\t\t\t     **********************************************\n");
    printf("\n\n");
}



//creation of book list by user
void create_book_list(char title[], char subject[], char author[], int co_issued, int co_available)
{

    book_list *temp = NULL;
    if (first1 == NULL)
    {
        first1 = (book_list *)malloc(sizeof(book_list));
        strcpy(first1->Title, title);
        strcpy(first1->subject, subject);
        strcpy(first1->author, author);
        first1->number_of_copies_issued = co_issued;
        first1->number_of_copies_available = co_available;
        first1->next = NULL;
        last1 = first1;
    }

    else
    {
        temp = (book_list *)malloc(sizeof(book_list));

        strcpy(temp->Title, title);
        strcpy(temp->subject, subject);
        strcpy(temp->author, author);
        temp->number_of_copies_issued = co_issued;
        temp->number_of_copies_available = co_available;
        temp->next = NULL;
        last1->next = temp;
        last1 = temp;
    }
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
        temp2 = (request_queue *)malloc(sizeof(book_list));

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

//checks copies of book are available or not.
int is_available(char *book)
{
    book_list *temp = first1;
    while (temp)
    {
        if (strcmp(book, temp->Title) == 0 && temp->number_of_copies_available > 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

//book available in 3 days or not.
// return 1 for yes and 0 for no.
int is_available_in_3_days(char book[])
{
	
	//suppose this is present date. 16th April, 2022
    int current_date=20220416;                                      //date format yyyymmdd         .

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


//CONDITION FOR CASE 1
//a.student not borrowed more than 3 books
//b.student must returned book within 15 days
//c.book must be available in book list


//1.Display name of students who'll get books.
void display_of_students_who_get_books()
{
    request_queue *temp = first2;
    printf("\nstudents who will get the books are: \n");
    while (temp)
    {
        int t1 = is_borrow(temp->Name_of_the_student);
        int t2 = is_return(temp->Name_of_the_student);
        int t3 = is_available(temp->title_of_the_book);
        if (!(t1) && !(t2) && t3)
        {
            puts(temp->Name_of_the_student);
            printf("\n");
        }
        temp = temp->next;
    }
    printf("\n\n---------------------------------------------------\n\n");
}


//2.Function to find the most demand book.
void most_demand_books()
{
	char demand_book[40];
	
	book_list* temp = first1;
	request_queue* temp2 = first2;
	
	int max=0;
	while(temp!=NULL)
	{
		int count=0;
		temp2=first2;
		while(temp2!=NULL)
		{
		    if(strcmp(temp2->title_of_the_book,temp->Title)==0)	
			  {
			    count++;
		   	  }
		   	  temp2=temp2->next;
		}
		
		count=count+temp->number_of_copies_issued;
		if(count>max)
		{
			max=count;
			strcpy(demand_book,temp->Title);
		}
		temp=temp->next;
	}
	printf("\nThe book in most demand is: ");
	puts(demand_book);
	printf("\n\n---------------------------------------------------\n\n");
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
        int t3 = is_available(temp->title_of_the_book);
        int t4 = is_available_in_3_days(temp->title_of_the_book);
       
        
        if (!(t1) && !(t2) && (t3))
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
    printf("total books given is %d\n",count);
    printf("\n\n---------------------------------------------------\n\n");
} 


//4.Sort and display borowwer list.
void Borrow_List_Descending()
{
	struct borrower_list *p=first3;
	struct borrower_list *q;
	
	int count;
	char arr[20],arr1[20];
	
	printf("\nThe borrower_list according to the number of books issued in descending order");
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


//5.Sort and display of all books of a particular subject based on its copies.
void Sort_Display_Title_Author()
{
	char sub[20];
	printf("\nEnter subject :");
	scanf("%s",sub);
	
	struct book_list *m=first1;
	
	int max=0,i=0;
	while(m!=NULL)
	{
		if(strcmp(sub,m->subject)==0 && m->number_of_copies_available>max)
		{
			max=m->number_of_copies_available;
		}
		m=m->next;
	}
	
	printf("\n");
	while(i<=max)
	{
		m=first1;
	    while(m!=NULL)
	    {
	    	if(m->number_of_copies_available==i && strcmp(sub,m->subject)==0)
	    	{
	    		printf("\nauthor: %s",m->author);
	    		printf("\ntitle: %s",m->Title);
			}
	    	m=m->next;
	    }
		i++;
	}
	  printf("\n\n---------------------------------------------------\n\n");
}


void insert_defaulter_list(char name[],char title_book[])
{
    request_queue *temp2 = NULL;
    
    if (defaulter_list == NULL)
    {
        defaulter_list = (request_queue *)malloc(sizeof(request_queue));
        strcpy(defaulter_list->Name_of_the_student,name);
        strcpy(defaulter_list->title_of_the_book,title_book);
        defaulter_list->next = NULL;
        defaulter_list_last=defaulter_list;
    }

    else
    {
        temp2 = (request_queue *)malloc(sizeof(request_queue));

        strcpy(temp2->Name_of_the_student,name);
        strcpy(temp2->title_of_the_book,title_book);
        temp2->next = NULL;
        defaulter_list_last->next = temp2;
        defaulter_list_last = temp2;
    }	
}


void delete_node_in_request_queue(char name[])
{
	request_queue *temp=NULL;
	request_queue *prev=NULL;
	request_queue *curr=NULL;
	
	if(strcmp(name,first2->Name_of_the_student)==0)
	{
		temp=first2;
		first2=first2->next;
		free(temp);
	}
	else 
	{
		prev=first2;
		curr=first2->next;
		while(strcmp(name,curr->Name_of_the_student)==0)
		{
			prev->next=curr->next;
			free(curr);
		}
		curr=curr->next;
		prev=prev->next;
	}
}


//6.Formation and display of defaulter list.
void display_defaulter_list()
{
    borrower_list *temp = first3;
	while(temp!=NULL)
	{
		if(is_return(temp->Name_of_the_student)==1)
		{
		insert_defaulter_list(temp->Name_of_the_student,temp->title_of_the_book);
		delete_node_in_request_queue(temp->Name_of_the_student);	
		}
		temp=temp->next;
	}
	
   printf("\n\nThe list of defaulters students are:\n");
   
   request_queue *temp2=defaulter_list;
   while(temp2!=NULL)
   {
   	puts(temp2->Name_of_the_student);
   	printf("\n"); 
    temp2=temp2->next; 	
   }  	
	
	printf("\n\n---------------------------------------------------\n\n");
} 


//7.Display name of students who already borowwed books and asking for other
void display_requested_borrowed()
{
    request_queue *temp = first2;
    if (temp)
    {
        printf("students who already borrowed and requesting are\n");
        while (temp)
        {
            puts(temp->Name_of_the_student);
            temp = temp->next;
        }
    }
    else
    {
        printf("No student is there who requested a book and aslo borrowed a book\n");
    }
    
    printf("\n\n---------------------------------------------------\n\n");
}


//8.Display name of requested books whose copies are available.
void display_re_copies_available()
{
    request_queue *temp1 = first2;
    printf("names of the requested books whose copies are available:\n");
    while (temp1)
    {
        book_list *temp2 = first1;
        while (temp2)
        {
            if (strcmp(temp2->Title, temp1->title_of_the_book) == 0 && temp2->number_of_copies_available > 0)
            {
                puts(temp2->Title);
                break;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    
   	printf("\n\n---------------------------------------------------\n\n");
}


//9.Display title of books which have not been issued by anyone.
void display_not_issued()
{
    book_list *temp1 = first1;
    printf("\nBooks that not issued are\n");
    while (temp1)
    {
        borrower_list *temp2 = first3;
        while (temp2)
        {
            if (strcmp(temp1->Title, temp2->title_of_the_book) == 0)
            {
                break;
            }
            temp2 = temp2->next;
        }
        if (temp2 == NULL)
        {
            puts(temp1->Title);
        }
        temp1 = temp1->next;
    }
    
    printf("\n\n---------------------------------------------------\n\n");
}


int get_m_index(int *arr, int m)
{
    int max = arr[0];
    int i;
    for (i = 1; i < m; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

// 10. Display the name of the student who has requested for the maximum number of books.
void display_req_max_books(int m)
{
    int a[m];
    int i = 0,j;
    for (j = 0; j < m; j++)
    {
        a[j] = 0;
    }
    request_queue *p = first2;
    request_queue *q = NULL;
    while (p)
    {
        q = p->next;
        while (q)
        {
            if (strcmp(p->Name_of_the_student, q->Name_of_the_student) == 0)
            {
                a[i]++;
            }
            q = q->next;
        }
        p = p->next;
        i++;
    }
    int m_index = get_m_index(a, m);
    request_queue *temp = first2;
    request_queue *temp2 = NULL;
    int k = 0;
    printf("\nName of a students who requested a books maximum times is\n");
    while (temp)
    {
        temp2 = temp->next;
        k = 0;
        while (temp2)
        {
            if (strcmp(temp->Name_of_the_student, temp2->Name_of_the_student) == 0)
            {
                k++;
            }
            temp2 = temp2->next;
        }
        if (k == m_index)
        {
            puts(temp->Name_of_the_student);
        }
        temp = temp->next;
    }
    
    	printf("\n\n---------------------------------------------------\n\n");
}




//driver code
int main()
{
	greetings();
	int n;
	char Title[40],subject[20],author[30];
	int copies_issued,copies_available;
	int i;
	printf("\nNo of books in book_list which are available: ");
	scanf("%d",&n);
	fflush(stdin);
	for(i=0;i<n;i++)
	{
	  printf("\nEnter title: \n");
	  gets(Title);
	  printf("Enter subject: \n");
	  gets(subject);
	  printf("Enter author: \n");
	  gets(author);	
	  printf("Enter no of copies issued: \n");
	  scanf("%d",&copies_issued);
	  printf("Enter no of copies available: \n");
	  scanf("%d",&copies_available);
	  fflush(stdin);
	  create_book_list(Title,subject,author,copies_issued,copies_available);
	}
	
	int m;
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
	printf("4.Sort and display borowwer list.\n5.Sort and display of all books of a particular subject based on its copies.\n6.Remove defaulter from request list and display in new defaulter list.\n");
	printf("7.Display name of students who already borowwed books and asking for other.\n8.Display name of requested books whose copies are available.\n9.Display title of books which not been issued by anyone.\n");
	printf("10.Display name of students who has requested for maximum no. of books.\n\n");
		
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
				break;
			}
			case 2:{
				most_demand_books();
				break;
			}
			case 3:{
				books_given_students_in_3_days();
				break;
			}
			case 4:{
				Borrow_List_Descending();
				break;
			}			
			case 5:{
				Sort_Display_Title_Author();
				break;
			}
			case 6:{
				display_defaulter_list();
				break;
			}
			case 7:{
				display_requested_borrowed();
				break;
			}
			case 8:{
				display_re_copies_available();
				break;
			}
			case 9:{
				display_not_issued();
				break;
			}
			case 10:{
				display_req_max_books(m);
				break;
			}
			default:{
				printf("enter correct choice of given options.: ");
				break;
			}
		}		
		
		
	}
	return 0;
}

