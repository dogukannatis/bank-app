#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <stdbool.h>
#include <ctype.h>
#define _id 1
#define registered 5

/*  Author: Doðukan ATÝÞ
	Date: 01/03/2021 - started
		  08/03/2021 - finished
*/

FILE *sum;

int currentTime(){
	time_t s, val = 1; 
    struct tm* current_time; 
  
    // time in seconds 
    s = time(NULL); 
  
    // to get current time 
    current_time = localtime(&s); 
  
   /* printf("%02d:%02d:%02d", 
           current_time->tm_hour, 
           current_time->tm_min, 
           current_time->tm_sec);*/
           
    int time = current_time->tm_hour;
	return time;
  
}

//delay effect
void delay(int number_of_seconds){ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds); 
} 

// STRUCT
struct user{
	char name[15];
	char surname[15];
	struct account{
		int number;
		int pin;
		float balance;
		bool summary;
	}info;
     enum accountid{ id }key;
	
};

struct user users[registered];

int invalidInput(){

	int i;
	system("cls");
	printf("You've entered an invalid value!");
	for (i = 0; i < 2; i++) { 
        	delay(1); 
			printf(".", i + 1); 
		} 
	return 1;
}
int inputControl(const char *const message){
    int value;

    printf("%s > ", message);
    while (scanf("%d", &value) != 1)
    {
        int chr;
        printf("\tinvalid input...\n");
        do {
            chr = getchar();
        } while ((chr != EOF) && (chr != '\n'));
        printf("%s > ", message);
    }
    return value;
}
float inputControlFloat(const char *const message){
    float value;

    printf("%s > ", message);
    while (scanf("%f", &value) != 1)
    {
        int chr;
        printf("\tinvalid input...\n");
        do {
            chr = getchar();
        } while ((chr != EOF) && (chr != '\n'));
        printf("%s > ", message);
    }
    return value;
}
int loginScreen(int accountno,int pin, char *accountname){
	int i;
	char sat, *kark;
	char invalid;
	int enterAccountNum,enterAccountPin;
	int current_time = currentTime();
	
//	printf("\nPlease enter your account number: ");
	enterAccountNum = inputControl("\nPlease enter your account number:");
//	printf("\nPlease enter your account number: ");
	enterAccountPin = inputControl("\nPlease enter your pin:");

	// check informations
	if(enterAccountNum==accountno && enterAccountPin==pin){
		system("cls");
		printf("\n###########################################\n");
		printf("	Login successfull!");
		printf("\n###########################################\n");
		if( (currentTime < 17) && (currentTime > 5) ){
			printf("Have a good day, %s",accountname);
		}else{
			printf("Have a good evening, %s",accountname);
		}
		// delay effect for routing	
		for (i = 0; i < 2; i++) { 
        	delay(2); 
			printf(".", i + 1); 
			} 
		return 1;
	}else{	
		system("cls");
		printf("\n###########################################################\n");
		printf("	Invalid account number or pin! Please try again.");
		printf("\n###########################################################\n");
		// delay effect for routing		
		for (i = 0; i < 2; i++) { 
        	delay(2); 
			printf(" ", i + 1); // !*
			} 
		return 0;
	}
}


int menu(int accountno,int pin, char *accountname, char *accountsurname, bool *summary, float *balance){
	system("cls");
	printf("Account balance: %.2f TL\n\n",*balance);
	printf("1-> Show account informations\n");
	printf("2-> Write account summary to txt\n");
	printf("3-> Money Transfer\n");
	printf("4-> Deposit\n"); // yatýrma
	printf("5-> Withdraw\n");
//	printf("X-> Main menu\n");
	printf("6-> Logout \n");
	printf("-------------------------------\n");
		
	int code = inputControl("Please enter a code: \n");
	
	switch(code){
		case 1:
			showAccountInformations(accountno,pin,accountname,accountsurname,summary,balance);			
		case 2:
			accountSummary(accountno,pin,accountname,accountsurname,summary,balance);
		case 3:
			transferMoney(accountno,pin,accountname,accountsurname,summary,balance);
		case 4:
			deposit(accountno,pin,accountname,accountsurname,summary,balance);
		case 5:
			withdraw(accountno,pin,accountname,accountsurname,summary,balance);
		case 6:
			logOut(accountname);
		default:
			menu(accountno,pin,accountname,accountsurname,summary,balance);
			break;
	}

}

void accountSummary(int accountno,int pin,char *accountname,char *accountsurname,bool *summary,float *balance){
	int i;
	*summary = 1;
	system("cls");
	sum = fopen("account_summary.txt","w");
	if(sum!=NULL){
	// write to the txt-----------------------------------
		fprintf(sum,"ACCOUNT NUMBER: %d\n",accountno);
		//	fprintf(sum,"ACCOUNT PIN: %d\n",pin);  it shouldd be private
		fprintf(sum,"NAME: %s\n",accountname);
		fprintf(sum,"SURNAME: %s\n",accountsurname);
		fprintf(sum,"ACCOUNT BALANCE: %f\n",*balance);
	
		fclose(sum);
	//----------------------------------------------------
		printf("###################################\n");
		printf("Summary has written to the txt file!\n");
		printf("###################################\n");
		printf("You are routing to menu.");
		for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(" ", i + 1); // !* "."
		}
		menu(accountno,pin,accountname,accountsurname,summary,balance);
	}else{
		system("cls");
		printf("###################################\n");
		printf("           AN ERROR OCCURED    \n");
		printf("###################################\n");
		for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(" ", i + 1); // !* "."
		} 
	main();
	}
}

void logOut(char *accountname){
	int i;
	system("cls");
	printf("###################################\n");
	printf("           SEE YOU! %s         \n",accountname);
	printf("###################################\n");
	for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(" ", i + 1); // !* "."
		} 
	main();
}
void withdraw(int accountno,int pin,char *accountname,char *accountsurname, bool *summary, float *balance){
	system("cls");
	float amount;
	char confirm_amount;
	int confirm_pw;
	int i;
	system("cls");
	printf("           WITHDRAW SCREEN         \n");
	printf("###################################\n");
	confirm_pw = inputControl("Please enter your pin: \n");
	if(confirm_pw == pin){
		system("cls");
		printf("           WITHDRAW SCREEN         \n");
		printf("###################################\n");
		printf("Account No: %d\n",accountno);
		printf("Name: %s\n",accountname);
		printf("Surname: %s\n",accountsurname);
		printf("Balance: %.2f\n",*balance);
		printf("###################################\n");
		//printf("Please enter to amount: \n");
		amount = inputControlFloat("Please enter to amount: \n");
		//scanf("%f",&amount);
		printf("###################################\n");
		// balance check
		if(amount>*balance){
			amount = *balance;
			printf("You are withdrawing full amount %.2fTL Do you confirm? y/n",amount);
			goto chk;
		}
		printf("You are withdrawing %.2fTL Do you confirm? y/n",amount);
	chk:
		scanf("\n%c",&confirm_amount);
	
		if(confirm_amount=='y'){
			if(*balance!=confirm_amount)
				*balance-=amount; // new balance value
							
			system("cls");
			printf("           WITHDRAW SCREEN          \n");
			printf("###################################\n");
			printf("Withdrawing.");			
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
		system("cls");
		printf("           WITHDRAW SCREEN          \n");
		printf("###################################\n");
		printf("Withdraw process is succesfull!\n");
		printf("You are routing to menu.");
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
		menu(accountno,pin,accountname,accountsurname,summary,balance);
	}else{
		system("cls");
		printf("           WITHDRAW SCREEN          \n");
		printf("###################################\n");
		printf("Withdrawing process was cancelled.\n");
		printf("You are routing to menu.");
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
		menu(accountno,pin,accountname,accountsurname,summary,balance);
	}
		
	}else{
		system("cls");
		printf("           WITHDRAW SCREEN          \n");
		printf("###################################\n");
		printf("Invalid pin!");
		printf("You are routing to menu.");
		for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
		menu(accountno,pin,accountname,accountsurname,summary,balance);
	}
	
}
void deposit(int accountno,int pin,char *accountname,char *accountsurname,bool *summary,float *balance){
	system("cls");
	float amount;
	char confirm;
	int i;
	printf("           DEPOSIT SCREEN          \n");
	printf("###################################\n");
	printf("Account No: %d\n",accountno);
	printf("Name: %s\n",accountname);
	printf("Surname: %s\n",accountsurname);
	printf("###################################\n");
	//printf("\nPlease enter to amount: \n");
	amount = inputControlFloat("\nPlease enter to amount: \n");
	//	scanf("%f",&amount);
	printf("###################################\n");
	printf("You are depositing %.2fTL Do you confirm? y/n",amount);
	scanf("\n%c",&confirm);
	
	if(confirm=='y'){
		*balance+=amount; // new balance value
		system("cls");
		printf("           DEPOSIT SCREEN          \n");
		printf("###################################\n");
		printf("Depositing.");
			
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
		system("cls");
		printf("           DEPOSIT SCREEN          \n");
		printf("###################################\n");
		printf("Deposit process is succesfull!\n");
		printf("You are routing to menu.");
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
			menu(accountno,pin,accountname,accountsurname,summary,balance);
	
	}else{
		system("cls");
		printf("           DEPOSIT SCREEN          \n");
		printf("###################################\n");
		printf("Deposit process was cancelled.\n");
		printf("You are routing to menu.");
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
			menu(accountno,pin,accountname,accountsurname,summary,balance);
		
	}
}
void transferMoney(int accountno,int pin, char *accountname, char *accountsurname, bool *summary, float *balance){
	system("cls");
	float amount;
	int to; // should be account number
	char confirm;

	amount = inputControlFloat("Amount:");
	to = inputControl("To: ");
	
	// Balance check
	if(amount>*balance){
		printf("\n###################################\n");
		printf("Error: You don't have enough money!");
		printf("\n###################################\n");
		printf("\nYou are routing to menu.");
		int i;
			for (i = 0; i < 2; i++) { 
   		    	delay(3); 
				printf(".", i + 1); 
			} 
		
	}// if balance enough
	else{
		printf("\n########################################################\n");
		printf("You are sending to %d - %.2fTL | Do you confirm? y/n",to,amount);

		scanf("\n%c",&confirm);
	
		
		if(confirm == 'y'){
			*balance-=amount;
			system("cls");
			printf("Successfull!\n");
			printf("You sent: %.2fTL TO %d\n",amount,to);
			printf("\nYour new balance: %.2f",*balance);
			printf("\n########################################################\n");
			printf("You are routing to menu.");
			int i;
				for (i = 0; i < 2; i++) { 
   		    	 	delay(4); 
					printf(".", i + 1); 
				} 
			menu(accountno,pin,accountname,accountsurname,summary,balance);
		}
		else{
			system("cls");
			printf("\n########################################################\n");
			printf("Process was canceled! You are routing to menu.");
			int i;
			for (i = 0; i < 2; i++) { 
        		delay(2); 
				printf(".", i + 1); 
			} 
			menu(accountno,pin,accountname,accountsurname,summary,balance);
		}
	}	
}


void showAccountInformations(int accountno,int pin, char *accountname, char *accountsurname, bool *summary, float *balance){

	char e;
	system("cls");
	printf("Your Informations: \n");
	printf("###################\n\n");
	
	printf("Name: %s\n",accountname);
	printf("Surname: %s\n",accountsurname);
	printf("Account Number: %d\n",accountno);
	printf("Account Balance: %.2fTL\n\n",*balance); 
	if(*summary==1) 
		printf("Account Summary: it is avaliable on file\n");
	else{
		printf("Account Summary: No found record\n");
	}
	printf("-------------------------------\n");
		
back: ;

	int a = inputControl("Please enter 0 for previous menu...");
	if(a==0){
		menu(accountno,pin,accountname,accountsurname,summary,balance);
	}
	else{
		printf("\tinvalid key!\n");
		goto back;
	}	
}

int main() {
	system("cls");
	
	users[1].key = _id;
		strcpy(users[_id].name,"dogukan");
		strcpy(users[_id].surname,"atis");
		users[_id].info.number = 19000129;
		users[_id].info.pin=1234;
		users[_id].info.summary = NULL;
		users[_id].info.balance = 1000.00;
	
	
	printf("Welcome to dodoBANK...\n");
	printf("-----------------------\n");
	
	// login
	
	bool isLogin = loginScreen(
	users[_id].info.number,
	users[_id].info.pin,
	users[_id].name
	);
	
	if(isLogin == 1){
		system("cls");
		menu(
			users[_id].info.number,
			users[_id].info.pin,
			users[_id].name,
			users[_id].surname,
			&users[_id].info.summary,
			&users[_id].info.balance
		);
	}else{
		system("cls");
		main();
	}	
	return 0;

}

	













