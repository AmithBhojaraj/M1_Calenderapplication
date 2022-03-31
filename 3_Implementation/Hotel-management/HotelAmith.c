#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void enter_guest_name();
void find_guest_name();
void find_room();
void checkout_guest();
void view_bookings();


FILE* view;
FILE *fp;
FILE* enter;
char AdminEntry[20] = {'y'};
char user_entry[20] = {'y'};


struct HotelAmith
{
    char name[20];
    char room[20];
    char food[20];
    char internet[20];

}h;

int main(){ 

    int a,b,c;

	printf("\t\t       -----------------------------           \n");
	printf("\t\t          WELCOME TO HOTEL AMITH               \n");
	printf("\t\t       -----------------------------           \n");


    printf("\n\tFor ADMIN access Enter 1 \t\t\t");
    printf("\n\tFor USER access Enter 2 \t\t\t");
    printf("\n>> ");
     scanf("%d",&a);

        switch(a){
            case 1:{
                char password[10];
                char filepassword[10];
                int i;

                FILE *passw;
                passw = fopen("password.txt","r");

                printf("\n Welcome ADMIN!\n Please enter the password to continue: ");

                for(i=0; i<8; i++){
                    scanf("%s",password);
                    fscanf(passw,"%s",filepassword);
                    if (strcmp(filepassword,password) == 0) {
                        printf("\n\nYou can now access ADMIN portal \n");
                        fclose(passw);
                        break;
                    }
                    else{
                     printf("\nIncorrect password, please try again.");
                     printf("\nYou have %d trys left ",5-i-1);
                     printf("\n\nEnter password >> ");
                    }
                    if(i==4){
                        fclose(passw);
                        return 0;
                    }

               
                }

                 //re-entry if
                while(AdminEntry[0] =='y'){

                printf("\n\tTo view booking requests Enter 1 \t\t\t");
                printf("\n\tTo view booked guests details Enter 2 \t\t\t");
                printf("\n\tTo add new guest Enter 3 \t\t\t");
   	            printf("\n\tTo locate room number of existing guest Enter 4 \t");
                printf("\n\tTo find guest of occupied room Enter 5 \t");
                printf("\n\tTo checkout a guest with existing room number Enter 6 \n");
                printf(">> ");
                scanf("%d",&b);

                switch(b){
                    case 1:{
                        view_bookings();
                        break;
                    }
                    case 2:{
                        FILE* fpi;
                        fpi = fopen("NewGuestDetails.txt","r");	

                        while(fscanf(fpi,"%s %s %s",h.name,h.room,h.internet) != -1){	
                          fgets(h.food, 255, (FILE*)fpi);
                          printf("%s %s %s %s \n",h.name,h.room,h.internet,h.food);
                         }
                         break;
                    }
                    case 3:{
                        enter_guest_name();
                        break;
                    }
                    case 4:{
                        find_guest_name();
                        break;
                    }
                    case 5:{
                        find_room();
                        break;
                    }
                case 6:{
                    checkout_guest();
                    break;
                    }
                    default:{
                        printf("\n Wrong entry!");
                    }
                }
                //enter again?
                printf("Would you like to continue? (y/n)\n");
                scanf("%s",AdminEntry);

                }
                if(strcmp(AdminEntry,"n") == 0){
                    printf("Exiting...\n");
                    printf("\e[1;1H\e[2J");
                    printf("\n >Exited<\n\n");
                    //system("clear");
                    return 0;
                }
                else{
                    printf("Wrong entry!\nExiting...\n");
                    return 0;
                }
                break;
            }
            
                     
            case 2:{
                while(user_entry[0] =='y'){
                printf("\nHello user and welcome to Amith's Hotel!");
                printf("\n\tTo view available rooms Enter 1 \t\t\t");
   	            printf("\n\tTo request booking of a room Enter 2 \t");
                printf("\n>> ");
                scanf("%d",&c);
                switch(c){
                    case 1:{
                        FILE* view;
                        view = fopen("RoomNumbers.txt","r");
                        printf("Rpoms available are:\n");
                        while(fscanf(view,"%s",h.room) != -1){	
                        printf("%s \n",h.room);
                        }
                        fclose(view);
                        break;
                    }

                    case 2:{
                        printf("Please enter your name: ");
                        scanf("%s",h.name);
                        printf("Enter room number to book: ");
                        scanf("%s",h.room);
                        printf("Do you need Internet? (yes/no): ");
                        scanf("%s",h.internet);
                        printf("Do you need food? (yes/no): ");
                        scanf("%s",h.food);

                        enter = fopen("bookings.txt","a");

                        fprintf(enter,"%s %s %s %s",h.name,h.room,h.internet,h.food);
                        fprintf(enter,"\n");

                        printf("Booking Succesfull !!\n");
                        fclose(enter);

                    }
                }
                    
                printf("Would you like to continue? (y/n)\n");
                scanf("%s",user_entry);

                }
                if(strcmp(user_entry,"n") == 0){
                    printf("Exiting...\n");
                    printf("\e[1;1H\e[2J");
                    printf("\n >Exited<\n\n");

                    return 0;
                }
                else{
                    printf("Wrong entry!\nExiting...\n");
                    return 0;
                }
                break;
            }
        }
}

//method declaration to enter name of the guest
void enter_guest_name(){ 

    FILE *temp1; 
    FILE *temp2;

    printf("\nEnter name of the guest: ");
    scanf("%s",h.name);
    printf("\nEnter their room number: ");
    scanf("%s",h.room);
    printf("\n Plese specify if you need Internet? (yes/no): ");
    scanf("%s",h.internet);
    printf("\nEnter if you need food (yes/no): ");
    scanf("%s",h.food);
    
    //entering guests
    fp = fopen("NewGuestDetails.txt","a");

    if( fp == NULL){
        printf("\nFile not found");
        exit(1);
    }
    else{
        fprintf(fp,"%s %s %s %s",h.name,h.room,h.internet,h.food);
        printf("\nDone\n");
    }
    fprintf(fp,"\n");

    char remove_guest[20];
    strcpy(remove_guest,h.name);
    char remove_room[20];
    strcpy(remove_room,h.room);

    //remove booking of a guest
    temp1 = fopen("temp1.txt","a");
    enter = fopen("bookings.txt","r");
 
    while(fscanf(enter,"%s %s %s",h.name,h.room,h.internet) != -1){
            fgetc(enter);	
		    fgets(h.food, 20, (FILE*)enter);
			    if(strcmp(h.name,remove_guest) != 0){
                    fprintf(temp1,"%s %s %s %s",h.name,h.room,h.internet,h.food);
                }
        }
    fclose(enter);
    fclose(temp1);
    remove("bookings.txt");
    rename("temp1.txt","bookings.txt");
    fclose(fp);

    //removing room
    temp2 = fopen("temp2.txt","a");
    view = fopen("rooms.txt","r");

    
    while(fscanf(view,"%s",h.room) != -1){
			    if(strcmp(h.room,remove_room) != 0){
                    fprintf(temp2,"%s",h.room);
                    fprintf(temp2,"\n");
                }
        }
    fclose(view);
    fclose(temp2);
    remove("rooms.txt");
    rename("temp2.txt","rooms.txt");


    fclose(fp);
}

//method declaration to find name of the guest
void find_guest_name(){
    char buffer[20];
    char entered_name[20];
    int guestFound =0;

    printf("\nEnter guest name to find -->");
    scanf("%s",entered_name);   
  
    fp = fopen("NewGuestDetails.txt","r");	
    while(fscanf(fp,"%s %s %s",h.name,h.room,h.internet) != -1){	
    fgets(h.food, 255, (FILE*)fp);
    if(strcmp(h.name,entered_name) == 0){
                     guestFound = 1;
                    printf("\n Guest found!");
                    printf("\n Name  is %s",h.name);
                    printf("\n Room number is %s",h.room);
                    printf("\n Internet included %s",h.internet);
                    printf("\n Food included %s",h.food);

      }
   }
   if(guestFound == 0){
         printf("\nGuest %s not found!\n", entered_name);
      }
   fclose(fp);
}

//method definition for checking out a guest
void checkout_guest(){
    char buffer2[20];
    char checkout_name[20];
    char add_room[20];

    FILE *temp;

    printf("Enter guest name to checkout ");
    scanf("%s",checkout_name);

    fp = fopen("NewGuestDetails.txt","r");
    temp = fopen("temp.txt","w");

    if(fp == NULL){
    printf("File not found");
    exit(1);
    }
	else{
        while(fscanf(fp,"%s %s %s",h.name,h.room,h.internet) != -1){
            fgetc(fp);	
		    fgets(h.food, 20, (FILE*)fp);
			    if(strcmp(h.name,checkout_name) != 0){
                    fprintf(temp,"%s %s %s %s",h.name,h.room,h.internet,h.food);
                }
                else{
                   strcpy(add_room,h.room);
                }
        }
        printf("Room checked out!");
    }

    fclose(fp);
    fclose(temp);
    remove("NewGuestDetails.txt");
    rename("temp.txt","NewGuestDetails.txt");

    //enter room back into available rooms list
    view = fopen("RoomNumbers.txt","a");
    printf(" add is %s",add_room);
    fprintf(view,"%s",add_room);
    fclose(view);

}

//method definition for finding rooms avalaible
void find_room(){
    char buffer[20];
    char entered_room[20];
    int roomFound =0;
    FILE *fp;
    printf("\nEnter room number to find -->");
    scanf("%s",entered_room);   
  
    fp = fopen("NewGuestDetails.txt","r");	
    while(fscanf(fp,"%s %s %s",h.name,h.room,h.internet) != -1){	
    fgets(h.food, 255, (FILE*)fp);
    if(strcmp(h.room,entered_room) == 0){
                     roomFound = 1;
                    printf("\n Room found!");
                    printf("\n Name  is %s",h.name);
                    printf("\n Room number is %s",h.room);
                    printf("Internet Included  %s",h.internet);
                    printf("\n Food included %s",h.food);
      }
    }
    if(roomFound == 0){
         printf("\nRoom %s not found!\n", entered_room);
      }
   fclose(fp);
}

//method defined to view bookings
void view_bookings(){

    enter = fopen("bookings.txt","r");	

    while(fscanf(enter,"%s %s %s",h.name,h.room,h.internet) != -1){	
        fgets(h.food, 255, (FILE*)enter);
        printf("%s %s %s %s \n",h.name,h.room,h.internet,h.food);
    }
}