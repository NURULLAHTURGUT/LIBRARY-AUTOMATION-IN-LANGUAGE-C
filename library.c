#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<locale.h>


//FUNCTION FOR BOOKS
typedef struct book{
	int barcode;
    char bookname[30];
    char author[30];
    char publishing_house[30];
    int release_date;
    int inventory;
    
}book ;                   


//FUNCTION FOR MEMBERS
typedef struct member{
   char i_n[30];                     //i_n identification number means we will use it in functions
   char name_surname[30];
   char birthdate[30];
   char phone_number[30];
   char address [30];
   int situation;          //status checker that bans a user when they delay a book return

}member;


//FUNCTION FOR LENDING BOOKS
typedef struct borrowed{                  
      char memberi_n[25];                                 
      int book_barcode;
      time_t delivery_date;
      time_t return_date;
      int to_use ;         //the number of days the user will use the book.
      int day_of_use;      //the number of days the user uses the book.
      int delay_days;
      int situation;      //status to check if the user is banned

}borrowed;


// BOOK ADDITION SCREEN
void add_book(){
	system("cls");
	printf("BOOK ADDITION SCREEN: \n");
	book k1;
	printf("BARCODE NUMBER OF THE BOOK YOU WANT TO ADD :");  scanf(" %d",&k1.barcode);  
	printf("ENTER THE TITLE OF THE BOOK YOU WANT TO ADD :");  scanf("%s",k1.bookname);
	printf("AUTHOR OF THE BOOK YOU WANT TO ADD:");  scanf("%s",k1.author);
	printf("PUBLISHER OF THE BOOK YOU WANT TO ADD :");  scanf("%s",k1.publishing_house);
	printf("PUBLICATION DATE OF THE BOOK YOU WANT TO ADD :");  scanf("%d",&k1.release_date);
	printf("BOOK STOCK NUMBER:"); scanf("%d",&k1.inventory);
	FILE * ptr = fopen("Books.data","a+b");  //creating a data file for books.
	fwrite (&k1, sizeof(book),1,ptr);  //FILE WRITING   
	fclose(ptr);   //CLOSING THE FILE.
	printf("book registration completed.");
}

//BOOK DELETION SCREEN
void delete_book(){
	system("cls");
	printf("BOOK DELETION SCREEN: \n");
	book k1;
	int bbarcode, result=0;
	printf("BARCODE NUMBER OF THE BOOK YOU WANT TO DELETE :");  scanf(" %[^\n]d",&bbarcode);
	FILE * ptr = fopen("Books.data","r+b");  //READING EXISTING BOOK DATA FILE.
	FILE * newptr = fopen("backup.data","w+b");  //CREATING A NEW DATA FILE.
	while(fread (&k1, sizeof(book), 1, ptr) != NULL)
	{
		if(bbarcode != k1.barcode)
		fwrite (&k1, sizeof(book),1,newptr);
		else
		result=1;
		
	}
	fclose(ptr);
	fclose (newptr);
	if(result==0){
		printf(" %d BOOK WITH BARCODE NUMBER NOT FOUND.", bbarcode);
	}
	else{
		remove("Books.data");
		rename("backup.data","Books.data");
		printf(" %d BOOK WITH BARCODE NUMBER DELETED.", bbarcode);
	}
	
}

//BOOK OPERATIONS MENU.
void book_transactions()
{
	system("cls");
	printf("BOOK TRANSACTIONS SCREEN: \n");
	
	int selection;
	printf(" 1-ADD BOOK: \n");
	printf(" 2-BOOK DELETE : \n");
	printf(" 3-LIST BOOKS: \n");
	printf(" 0-BACK TO MAIN MENU. \n");
	printf("YOUR CHOICE:");  scanf("%d",&selection);
	
	switch (selection){
		case 1: add_book(); break;
		case 2: delete_book(); break;
		case 3: book_list(); break;
		case 0:  break;
		default : printf(" YOU HAVE MADE AN INCORRECT SELECTION. YOU ARE REDIRECTED TO THE MAIN MENU...");  break;
	}
	
}

//book listing function
void book_list(){

	system("cls");
	printf("BOOK LIST SCREEN: \n");
	book k1;
	int number_of_books=0;
	FILE * ptr = fopen("Books.data","r+b");  //READING EXISTING BOOK DATA FILE
	printf("%-20s%-20s%-20s%-20s%-20s%-20s\n","BOOK-BARCODE","BOOK-NAME", "BOOK-AUTHOR", "BOOK-PUBLISHER","BOOK-PUBLICATION DATE","BOOK-STOCK");
	while(fread (&k1, sizeof(book),1,ptr) != NULL){
		printf("%-20d%-20s%-20s%-20s%-20d%-20d\n",k1.barcode,k1.bookname,k1.author,k1.publishing_house,k1.release_date,k1.inventory);
		number_of_books+=k1.inventory;
	}
	fclose(ptr);
	printf("\n TOTAL NUMBER OF BOOKS : %d",number_of_books);
	
}

//MEMBER ADDITION FUNCTION
void ADD_MEMBER()
{

	system("cls");
	printf(" MEMBER ADDITION SCREEN: \n");
	member member1;
	printf(" MEMBER'S ID NUMBER : ");  scanf("%s",&member1.i_n);                                
	printf(" ENTER MEMBER'S NAME AND SURNAME : ");  scanf("%s",&member1.name_surname);
	printf(" MEMBER'S DATE OF BIRTH : ");  scanf("%s",&member1.birthdate);
	printf(" ENTER THE MEMBER'S TELEPHONE NUMBER : ");  scanf("%s",&member1.phone_number);
	printf(" MEMBER'S ADDRESS : ");  scanf("%s",&member1.address);
	member1.situation=0;
	FILE * ptr = fopen("members.data","a+b");  //CREATING DATA FILES FOR MEMBERS
	fwrite (&member1, sizeof(member),1,ptr);  //FILE WRITING
	fclose(ptr);   //CLOSING THE FILE
	printf("MEMBER REGISTRATION COMPLETED.");
    	
}

//MEMBER DELETION FUNCTION
void Delete_member()
{
	system("cls");
	printf("MEMBER DELETION SCREEN: \n");
	member member1;
	int result=0;
	char i_n[30];                                                                             
	printf("ID NUMBER OF THE MEMBER YOU WANT TO DELETE :");  scanf(" %[^\n]s",&i_n);
	FILE * ptr = fopen("members.data","r+b");  //READING EXISTING MEMBERS DATA FILE
	FILE * newptr = fopen("backup.data","w+b");  //CREATING A NEW DATA FILE
	while(fread (&member1, sizeof(member),1,ptr) != NULL){
		if(strcmp (i_n , member1.i_n) !=0){
			fwrite (&member1, sizeof(member),1,newptr);
		}
		else{
			result=1;
		}
	}
	fclose(ptr);
	fclose (newptr);
	if(result==0){
		printf("%d NO MEMBER WITH ID NUMBER FOUND.",i_n);
	}
	else{
		remove("members.data");
		rename("backup.data","memberler.data");
		printf("%d MEMBER WITH ID NUMBER DELETED.",i_n);
	}
	printf("MEMBER DELETION PROCESS COMPLETED.");
	
}

//MEMBER LISTING FUNCTION
void member_list()
{
	system("cls");
	printf("ÜYE LÝSTESÝ EKRANI: \n");
	member member1;
	int number_of_members=0;
	FILE * ptr = fopen("members.data","r+b");  //READING EXISTING MEMBERS DATA FILE
	printf("%-20s%-30s%-20s%-20s%-20s%-20s\n","MEMBER IDENTIFICATION NO.","MEMBER NAME-SURNAME", "MEMBER DATE OF BIRTH", "MEMBER PHONE NUMBER","MEMBER ADDRESS","MEMBER SÝTUATÝON");
	while(fread (&member1, sizeof(member),1,ptr) != NULL){
		printf("%-20s%-30s%-20s%-20s%-20s%-20d\n",member1.i_n,member1.name_surname,member1.birthdate,member1.phone_number,member1.address,member1.situation);
		number_of_members++;
	}
	fclose(ptr);
	printf("\n TOTAL NUMBER OF MEMBERS : %d",number_of_members);
}

//MEMBER TRANSACTIONS SCREEN
void member_transactions()
{
	system("cls");
	printf("MEMBER TRANSACTIONS SCREEN: \n");
	
	int selection;
	printf(" 1-ADD MEMBER: \n");
	printf(" 2-DELETE MEMBER : \n");
	printf(" 3-LIST MEMBERS: \n");
	printf(" 0-BACK TO MAIN MENU. \n");
	printf("YOUR CHOICE:");  scanf("%d",&selection);
	
	switch (selection){
		case 1: ADD_MEMBER(); break;
		case 2: Delete_member(); break;
		case 3: member_list(); break;
		case 0:  break;
		default : printf(" YOU HAVE MADE AN INCORRECT SELECTION. YOU ARE REDIRECTED TO THE MAIN MENU...");  break;
	}
	
}

//STOCK UPDATE FUNCTION
void update_stock(int barcode,int number){

	book k1;
	int Counter=0;
	FILE * ptr = fopen("Books.data","r+b");  //READING EXISTING BOOK DATA FILE
	while(fread (&k1, sizeof(book),1,ptr) != NULL){
		if(barcode ==k1.barcode){
			break;
			Counter++;
		}
	}
	rewind(ptr);
	fseek(ptr,(Counter)*sizeof(book),0);
	
	k1.inventory+=number;
	
    fwrite (&k1, sizeof(book),1,ptr);
    fclose(ptr);
    printf(" STOCK UPDATED.");
}

//book lending screen
void Lendbook()
{
	system("cls");
	printf("BOOK LENDING SCREEN: \n");
	borrowed o;
	member member1;
	book k1;
	int uresult=0,kresult=0;
	printf("MEMBER IDENTIFICATION NO. :"); scanf("%s",o.memberi_n);
	//getchar();
	printf("BOOK BARCODE : "); scanf("%d",&o.book_barcode);
	FILE * uptr = fopen("members.data","r+b");
		while(fread (&member1, sizeof(member),1,uptr) != NULL)
		{
			if (strcmp(o.memberi_n,member1.i_n)==0){
				uresult=1;
				break;
				
			}
		}
		fclose(uptr);
		if (uresult==0){
			printf("%s MEMBER WITH ID NUMBER NOT FOUND, YOU ARE REDIRECTED TO THE MAIN MENU...\n",o.memberi_n);
			return;
		}
		if (member1.situation<-1){
			printf("\n%s NUMBERED MEMBER BANNED, YOU WILL BE REDIRECTED TO THE MAIN MENU...\n",o.memberi_n);
			return;
		}
		FILE * kptr = fopen("Books.data","r+b");
		while(fread (&k1, sizeof(book),1,kptr) != NULL)
		{
			if (o.book_barcode==k1.barcode){
				kresult=1;
				break;
			}
			
		}
		fclose(kptr);
		if (kresult==0){
			printf("\n %d BOOK WITH BARCODE NOT FOUND, YOU ARE REDIRECTED TO THE MAIN MENU...\n",o.book_barcode); 
			return;
		}
		if (k1.inventory<1){
			printf("\n%d THE BOOK WITH BARCODE IS OUT OF STOCK, YOU ARE REDIRECTED TO THE MAIN MENU...\n",o.book_barcode);
			return;
		}
			FILE * ptr = fopen("lending_books.data","a+b");                                                  //!!!!!!!!
			printf("HOW MANY DAYS THE MEMBER WILL USE THE BOOK :"); scanf("%d",&o.to_use );
			o.delivery_date=time(0);
			fwrite (&o, sizeof(borrowed),1,kptr) ;
			fclose(ptr);
			printf("ESCROW REGISTRATION COMPLETED.");
			update_stock(o.book_barcode,-1);
			
} 

//PERSON STATUS UPDATE FUNCTION     
void update_contact(char *i_nptr)
{

	member member1;
	int result=0,Counter=0;
	
	FILE * ptr = fopen("members.data","r+b");  
	
	while(fread (&member1, sizeof(member),1,ptr) != NULL){
		if(strcmp (i_nptr , member1.i_n) ==0){
			result=1;
			break;
		}	
			
		Counter++;
		
	}
	if(result==1){
	rewind(ptr);
	fseek (ptr, sizeof(member),0);
	member1.situation=-1;  //member1.situation
	fwrite (&member1, sizeof(member),1,ptr);
	printf("MEMBER STATUS UPDATED. \n");
	}

	fclose(ptr);
	
}

//FUNCTION THAT TAKES BACK THE LENT BOOK
void borrowkback()
{
	system("cls");
	printf("LOAN BOOK RETURN SCREEN: \n");
	borrowed o;
	member member1;
	book k1;
	char memberi_n[30];
	int book_barcode;
	int result=0,Counter=0;
	printf("MEMBER ID NUMBER:"); scanf("%s",&memberi_n);
	printf("BOOK BARCODE : "); scanf("%d",&book_barcode);
	FILE * ptr = fopen("lending_books.data","r+b");                        
		while(fread (&o, sizeof(borrowed),1,ptr) != NULL)
		{
			if (strcmp(o.memberi_n,memberi_n) ==0 &&  book_barcode == o.book_barcode ){   
				result=1;
				break;
				
			}
			Counter++;
		}
	
		
		
		if (result==0){
			fclose(ptr);
			printf("%s WITH ID NUMBER OR %d REGISTRATION WITH BARCODE NUMBER NOT FOUND, YOU ARE DIRECTED TO THE MAIN MENU...\n",memberi_n,book_barcode);  
			return;
		}
		else{
			rewind(ptr);
			o.return_date=time(0);
			float seconds,minutes,hours,days;
			seconds=difftime(o.return_date,o.delivery_date);
			minutes=seconds/60;
			hours=minutes/60;
			days=hours/24;
			o.day_of_use= days;
			printf("NUMBER OF DAYS USED: %f",days);
			o.delay_days=o.to_use -o.day_of_use;
			if(o.delay_days>5)
			o.situation=-1;  
			else
			o.situation=1;
		    
		    
		    fseek (ptr,(Counter)*sizeof(borrowed),0);
			fwrite (&o, sizeof(borrowed),1,ptr) ;
			fclose(ptr);
			printf("BORROWED BOOK TAKEN BACK.");
			update_stock(o.book_barcode,1);
			
			if(o.situation==-1) 
			update_contact(memberi_n);
		}
	
			
			
			
}

//BORROWED BOOKS LISTING SCREEN
void lend_list()
{
	system("cls");
	printf("BOOK LISTING SCREEN. \n");
	borrowed o;
	int Counter=0;
    FILE * ptr=fopen("lending_books.data","r+b");                              
    printf("%-20s%-20s%-20s\n","IDENTIFICATION NO.","BARCODE","SÝTUATÝON");
    while(fread(&o,sizeof(borrowed),1,ptr) !=NULL)
    {
    //if(o.situation==0){
    printf("%-20s%-20d%-20d\n",o.memberi_n,o.book_barcode,o.situation);
    Counter++;
   // }
    	
	}
	fclose(ptr);
	printf("NUMBER OF BORROWED BOOKS: %d\n",Counter);
}

// borrowed_operations FUNCTION
void borrowed_operations()
{
	system("cls");
	printf("LOAN BOOK TRANSACTIONS SCREEN: \n");
	
	int selection;
	printf(" 1-LEND A BOOK: \n");
	printf(" 2-TAKE BACK THE BORROWED BOOK : \n");
	printf(" 3-LIST BORROWED BOOKS: \n");
	printf(" 0-BACK TO MAIN MENU. \n");
	printf("YOUR CHOICE:");  scanf("%d",&selection);
	
	switch (selection){
		case 1: Lendbook(); break;
		case 2: borrowkback(); break;
		case 3: lend_list(); break;
		case 0:  break;
		default : printf(" YOU HAVE MADE AN INCORRECT SELECTION. YOU ARE REDIRECTED TO THE MAIN MENU...");  break;
	}
}



int menu()
{
	int selection;
	printf("\n ***** LIBRARY AUTOMATION ***** \n");
	printf("\n 1- BOOK PROCESSING :\n");
	printf("\n 2- MEMBER TRANSACTIONS :\n");
	printf("\n 3- BOOK BORROWING PROCEDURES :\n");
	printf("\n 0- EXÝT :\n");
	printf("\n YOUR CHOICE :");
	scanf("%d",&selection);
	return selection;
}

int main(){
	setlocale(LC_ALL, "Turkish"); 
	int selection=menu();
	
	while( selection!= 0 ){
		switch(selection){
			case 1: book_transactions(); break;
			case 2: member_transactions(); break;
			case 3: borrowed_operations(); break;
			case 0: break;
			default :{
				printf("YOU MADE A WRONG CHOICE .");
				
				break;
			}
		
		}
		selection=menu();
	}
	
	return 0 ;
}
