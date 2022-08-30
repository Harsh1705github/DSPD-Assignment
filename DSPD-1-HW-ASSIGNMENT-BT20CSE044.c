#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
struct patient
{
	int patientnumber;
	int age;
	char gender;
	char firstname[20];
	char lastname[20];
	char phonenumber[10];
	char residentialcity[15];
	char email[30];
	char doctor[20];
	char problem[30];
	int servicetype;
	float totalcharge[15];
	float totaldeposited[15];
	float totalreturn[15];
	
};


int main()
{
	struct patient p[100],q[100],swap;
	int num,i,m,k,a,b,c,n,t,number,find,max,min,max_num,min_num;
	char x[15],y[15],doc_name;
	i=0;m=0;b=0;
	
	
	printf("\n\n\n--------------------------------------------------NAGPUR HOSPITAL-------------------------------------------------\nSERVICE TYPE:\n------------------------------------------------------0 FOR OPD\n------------------------------------------------------1 FOR EMERGENCY SERVICE\n\n\n ");
	printf("\n1. Add new patient record\n");
	printf("2. Search  patient record\n");
	printf("3. Edit patient record\n");
	printf("4. List record of patient\n");
	printf("5. Delete patient record \n");
	printf("6. Print outsider patient data\n");
	printf("7. Max and Min charge of treatment\n");
	printf("8. Funds return data\n");
	printf("9. Search patient by age\n");
	printf("10. Search patient by doctor\n");
	printf("11. View doctor\n\n");
	
	printf("How many patients are there? ");
	scanf("%d",&num);
	
	struct patient r[150];
	
	for(k=1;k<=num;k++)
	{
	   printf("\n\nEnter patient number: ");
	   scanf("%d",&r[k].patientnumber);
	   printf("Enter age: ");
	   scanf("%d",&r[k].age);
	   fflush(stdin);
	   printf("Enter gender[m/f]: ");
	   scanf("%c",&r[k].gender);
	   fflush(stdin);
	   printf("Enter first name: ");
	   gets(r[k].firstname);
	   fflush(stdin);
	   printf("enter last name: ");
	   gets(r[k].lastname);
	   fflush(stdin);
	   printf("Enter phone number: ");
	   gets(r[k].phonenumber);
	   fflush(stdin);
	   printf("Enter residentialcity: ");
	   gets(r[k].residentialcity);
	   printf("Enter email: ");
	   fflush(stdin);
	   gets(r[k].email);
	   printf("Enter doctor: ");
	   gets(r[k].doctor);
	   fflush(stdin);
	   printf("Enter problem: ");
	   gets(r[k].problem);
	   fflush(stdin);
	   printf("Enter service type[0/1]: ");
	   scanf("%d",&r[k].servicetype);
	   printf("Enter total charge: ");
	   scanf("%f",&r[k].totalcharge);
	   printf("Enter total deposited:");
	   scanf("%f",&r[k].totaldeposited);
	   printf("Enter total return:");
	   scanf("%f",&r[k].totalreturn);
	}
	
	for(k=1;k<=num;k++)
	 {
	 	if(r[k].servicetype==0)
	 	{
	 	i++;
	    p[i]=r[k];	
	    }
	    else
	    {
	    	m++;
	    	q[m]=r[k];
		}
	 }	
	 
	 
	printf("\n\n--------------------------------------------------------------------\n\n");
	printf("1. Add new patient record\n");
	printf("2. Search  patient record\n");
	printf("3. Edit patient record\n");
	printf("4. List record of patient\n");
	printf("5. Delete patient record \n");
	printf("6. Print outsider patient data\n");
	printf("7. Max and Min charge of treatment\n");
	printf("8. Funds return data\n");
	printf("9. Search patient by age\n");
	printf("10. Search patient by doctor\n");
	printf("11. View doctor\n\n");
	
    
		 
	printf("Enter number: ");
	scanf("%d",&number);	
	
	switch(number)
	{
	    case '1':
	    	{
			printf("enter service type: ");
			scanf("%d",&a);
			if(a==0)
		    	{      
			       i++;num++;
	               printf("enter patient number: ")	;
	               scanf("%d",&p[i].patientnumber);
	               printf("enter age: ");
	               scanf("%d",&p[i].age);
	               fflush(stdin);
	               printf("enter gender[m/f]:");
	               scanf("%c",&p[i].gender);
	               fflush(stdin);
	               printf("enter first name:");
	               gets(p[i].firstname);
	               fflush(stdin);
	               printf("enter last name:");
	               gets(p[i].lastname);
	               fflush(stdin);
	               printf("enter phone number:");
	               gets(p[i].phonenumber);
	               fflush(stdin);
	               printf("enter residentialcity:");
	               gets(p[i].residentialcity);
	               fflush(stdin);
	               printf("enter email ");
	               gets(p[i].email);
	               fflush(stdin);
	               printf("enter doctor:");
	               gets(p[i].doctor);
	               fflush(stdin);
	               printf("enter problem:");
	               gets(p[i].problem);
	               p[i].servicetype=a;
	               printf("enter total charge:");
	               scanf("%f",&p[i].totalcharge);
	               printf("enter total deposited:");
	               scanf("%f",&p[i].totaldeposited);
	               printf("enter total return:");
	               scanf("%f",&p[i].totalreturn);	
	               r[num]=p[i];
		    	}
			else
			   {    
			       num++;
			       m++;
	               printf("enter patient number: ")	;
	               scanf("%d",&q[m].patientnumber);
	               printf("enter age: ");
	               scanf("%d",&q[m].age);
	               fflush(stdin);
	               printf("enter gender[m/f]:");
	               scanf("%c",&q[m].gender);
	               fflush(stdin);
	               printf("enter first name:");
	               gets(q[m].firstname);
	               fflush(stdin);
	               printf("enter last name:");
	               gets(q[m].lastname);
	               fflush(stdin);
	               printf("enter phone number:");
	               gets(q[m].phonenumber);
	               fflush(stdin);
	               printf("enter residentialcity:");
	               gets(q[m].residentialcity);
	               fflush(stdin);
	               printf("enter email ");
	               gets(q[m].email);
	               fflush(stdin);
	               printf("enter doctor:");
	               gets(q[m].doctor);
	               fflush(stdin);
	               printf("enter problem:");
	               gets(q[m].problem);
	               q[m].servicetype=1;
	               printf("enter total charge:");
	               scanf("%f",&q[m].totalcharge);
	               printf("enter total deposited:");
	               scanf("%f",&q[m].totaldeposited);
	               printf("enter total return:");
	               scanf("%f",&q[m].totalreturn);	
	               r[num]=q[m];
		    	}
	    	for(a=0;a<i-1;a++)
	         	{
		     	for(b=0;b<i-1-a;b++)
		        	{
			    	if(p[b].patientnumber > p[b+1].patientnumber)
			        	{
				        	swap=p[b];
				        	p[b]=p[b+1];
					        p[b+1]=swap;
			    	    }
		    	    }
		    	}	
			for(a=0;a<m-1;a++)
	      	    {
		    	for(b=0;b<m-1-a;b++)
		    	    {
				        if(p[b].patientnumber > p[b+1].patientnumber)
			             	{
				            	swap=p[b];
				             	p[b]=p[b+1];
				             	p[b+1]=swap;
			             	}
		          	}
		     	}
			break;
		}
		
		
		case '2':
			{
			printf("\n\nsearch via name : press 1\nsearch via number : press 2 \n ");
			scanf("%d",&c);
			switch(c)
		    	{
			     	case '1':
				    	{
				        	fflush(stdin);
					        printf("enter first name: ");
					        scanf("%s",x);
					        fflush(stdin);
					        printf("enter last name: ");
					        scanf("%s",y);
					        
				        	for(a=1;a<=num;a++)
				            	{
					            	if((strcmp(r[a].firstname,x)==0)&&(strcmp(r[a].lastname,y)==0))
					                     	{
	                                       printf("\nage = %d",r[a].age);
	  	                                   printf("\ngender= %c",r[a].gender);
	                                       printf("\nname: ");
	                                       puts(r[a].firstname);
	                                       puts(r[a].lastname);
	                                       printf("\nphone number: ");
	                                       puts(r[a].phonenumber);
	                                       printf("\nresidential city: ");
	                                       puts(r[a].residentialcity);
	                                       printf("\nemail: ");
	                                       puts(r[a].email);
	                                       printf("\ndoctor:");
	                                       puts(r[a].doctor);
	                                       printf("\nproblem:");
	                                       puts(r[a].problem);
	                                       printf("\nservice type[0/1]:");
	                                       printf("%d",r[a].servicetype);
	                                       printf("\ntotal charge:");
	                                       printf("%f",r[a].totalcharge);
	                                       printf("\ntotal deposited:");
	                                       printf("%f",r[a].totaldeposited);
	                                       printf("\ntotal return:");
	                                       printf("%f",r[a].totalreturn);
						                 	}
						               	else
							              printf("no records available");	
					        	}
						break;
				     	}  
				 case '2':
					  {
						printf("enter patient number: ");
						scanf("%d",&n);
						for(a=1;a<=num;a++)
						{
							if(r[a].patientnumber==n)
							{
	                                       printf("\nage = %d",r[a].age);
	  	                                   printf("\ngender= %c",r[a].gender);
	                                       printf("\nname: ");
	                                       puts(r[a].firstname);
	                                       puts(r[a].lastname);
	                                       printf("\nphone number: ");
	                                       puts(r[a].phonenumber);
	                                       printf("\nresidential city: ");
	                                       puts(r[a].residentialcity);
	                                       printf("\nemail: ");
	                                       puts(r[a].email);
	                                       printf("\ndoctor:");
	                                       puts(r[a].doctor);
	                                       printf("\nproblem:");
	                                       puts(r[a].problem);
	                                       printf("\nservice type[0/1]:");
	                                       printf("%d",r[a].servicetype);
	                                       printf("\ntotal charge:");
	                                       printf("%f",r[a].totalcharge);
	                                       printf("\ntotal deposited:");
	                                       printf("%f",r[a].totaldeposited);
	                                       printf("\ntotal return:");
	                                       printf("%f",r[a].totalreturn);	  	
							}
							else
							printf("no records available");
						}
			     	}
		    	} 
			break;
			}
	    case '5':
         	{
		        printf("enter patient number: ");
		        scanf("%d",&t);
		        for(a=1;a<=num;a++)
		          {
		             	if(r[a].patientnumber==t)
			               {
			                 	find=a+1;
				                for(find;find<=num;find++)
			               {
				                	r[find-1]=r[find];
				           }
			           	num--;
			               }
	           	  }
         	break;
			}
	    case '6':
	         {
		         for(a=1;a<=num;a++)
	                 	{
		                    	if(r[a].residentialcity!="nagpur")
		                            	{
                                        	   printf("\nage = %d",r[a].age);
                                        	   printf("\ngender= %c",r[a].gender);
                                         	   printf("\nname: ");
	                                           puts(r[a].firstname);
	                                           puts(r[a].lastname);
	                                           printf("\nphone number: ");
	                                           puts(r[a].phonenumber);
	                                           printf("\nresidential city: ");
	                                           puts(r[a].residentialcity);
	                                           printf("\nemail: ");
	                                           puts(r[a].email);
	                                           printf("\ndoctor:");
	                                           puts(r[a].doctor);
	                                           printf("\nproblem:");
	                                           puts(r[a].problem);
	                                           printf("\nservice type[0/1]:");
	                                           printf("%d",r[a].servicetype);
	                                           printf("\ntotal charge:");
	                                           printf("%f",r[a].totalcharge);
	                                           printf("\ntotal deposited:");
	                                           printf("%f",r[a].totaldeposited);
	                                           printf("\ntotal return:");
	                                           printf("%f",r[a].totalreturn);	
		                               	}
	                    }
	     break;	
		 }
		   
	        case '7':
	           	{
		             	max=r[0].totalcharge;
	                    min=max;
	                    max_num=0;
	                    min_num=0;
	                    
						for(a=1;a<num;a++)
	                         {
	                              	if(r[a].totalcharge>max)
	                                     	{
		                                      max=r[a].totalcharge;
		                                      max_num=a;
	                                       	}
	                               	if(r[a].totalcharge<min)
	                                       	{
		                                    min=r[a].totalcharge;
		                                    min_num=a;
	                                        }	
                             }
	                            printf("\nhighest charge by hospital is ");
	                            puts(r[max_num].firstname);
	                            puts(r[max_num].lastname);
	                            printf("\nlowest charge by hospital is ");
	                            puts(r[min_num].firstname);
	                            puts(r[min_num].lastname);
		break;
		}
		
		
		case '8':
			{
			for(a=1;a<=num;a++)
			{
				if(r[a].totalreturn>0)
				{
					printf("\n\n");
					puts(r[a].firstname);
					printf(" ");
					puts(r[a].lastname);
					printf(" total return = %f",r[a].totalreturn);
				}
				}	
			break;			
			}
			
			
		case '9':
		{
			printf("\n patient availing emergency service within range of age 25-40 are ");
			for(a=1;a<=num;a++)
			{
				if(r[a].servicetype==1&&r[a].age<=40&&r[a].age>=25)
				{
					puts(r[a].firstname);
					printf(" ");
					puts(r[a].lastname);
					printf("\n");
				}
			}
				printf("\n patient availing emergency service within range of age 40+ are ");
			for(a=1;a<=num;a++)
			{
				if(r[a].servicetype==1&&r[a].age>40)
				{
					puts(r[a].firstname);
					printf(" ");
					puts(r[a].lastname);
					printf("\n");
				}
			}
		break;
		}	
		
		
		case '10':
			{
			printf("enter doctor name: ");
			scanf("%s",doc_name);
			for(a=1;a<=num;a++)
			{
				if(strcmp(r[a].doctor,doc_name)==0)
				{
					puts(r[a].firstname);
					printf(" ");
					puts(r[a].lastname);
					printf("\n");
				}
			}	
		break;
			}
	}
	return 0;
}
