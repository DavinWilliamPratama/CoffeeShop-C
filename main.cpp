#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Davin William Pratama
//2301861296

int counter = 3;


void mainMenu(){
    printf("Hello!! Choose your role please!\n");
    printf("================================\n");
    printf("1. Admin\n");
    printf("2. Customer\n");
    printf("3. Shut down\n");
    printf("choose>> ");
}

struct data {
    int nomor;
	int qty;
	char produk[50];
	char type[15];
	int harga;
	struct data* next;
	struct data* prev;
}*head = NULL, *tail = NULL;

struct node{
    int nomor;
	int qty;
	char produk[50];
	char type[15];
	int harga;
    struct node *next;
}*front=NULL, *rear=NULL,*scan,*temp,*curr,*del;
typedef struct node N;

void viewAdmin(){
    struct data* temp = head;
    int i=1;
    printf("========================================================================================\n");
    printf("                             +++ Brew Coffee Shop +++");
    printf("\nWelcome Mr./Mrs. Admin \n");
    printf("========================================================================================\n");
    printf("No.| Menu                                 | Type       |Quantity    | Price            |\n");
    printf("----------------------------------------------------------------------------------------\n");
     while(temp != NULL) {
            printf("%d  | %-34s   |%11s |         %3d|  %10d\n", i,temp->produk, temp->type,temp->qty, temp->harga);
            temp = temp->next;
            i+=1;
        }
}

void viewCust(char nama[20]){
    struct data* temp = head;
    int i=1;
    printf("========================================================================================\n");
    printf("                             +++ Brew Coffee Shop +++");
    printf("\nWelcome Mr./Mrs. %s \n", nama);
    printf("========================================================================================\n");
    printf("No.| Menu                                 | Type       |Quantity    | Price            |\n");
    printf("----------------------------------------------------------------------------------------\n");
     while(temp != NULL) {
            printf("%d  | %-34s   |%11s |         %3d|  %10d\n", i,temp->produk, temp->type,temp->qty, temp->harga);
            temp = temp->next;
            i+=1;
        }
}

void menuAdmin(){
    viewAdmin();
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n1. Add item");
    printf("\n2. Remove item");
    printf("\n3. Exit");
    printf("\n----------------------------------------------------------------------------------------\n");
    printf("Enter your action: ");
}

void invoice(){
    int i= 1;
    struct node* temp = front;
    printf("\nYour Order:");
    printf("\n=======================================================================================\n");
    printf("No.| Menu                                 | Type       |Quantity    | Total Price      |");
    printf("\n----------------------------------------------------------------------------------------\n");
     while(temp != NULL) {
            printf("%d  | %-34s   |%11s |         %3d|  %10d\n", i,temp->produk, temp->type,temp->qty, temp->harga);
            temp = temp->next;
            i+=1;
        }
    printf("----------------------------------------------------------------------------------------\n");

}

void menuCust(char nama[20]){
    viewCust(nama);
    printf("----------------------------------------------------------------------------------------\n");
    printf("\n1. Buy item");
    printf("\n2. Cancel item");
    printf("\n3. Exit");
    printf("\n----------------------------------------------------------------------------------------");
    invoice();
    printf("Enter your action: ");

}



void insert(char produk[50], char type [20], int qty, int harga) {
	struct data* node = (struct data*) malloc(sizeof(struct data));

	if(strcmp(type, "yes")==0){
        strcpy(node->type, "Coffee");
    }
    else if(strcmp(type, "no")==0){
        strcpy(node->type, "Non-Coffee");
    }
	node->qty = qty;
	strcpy(node->produk, produk);
	node->harga = harga;
	node->next = NULL;
	node->prev = NULL;

	if(head == NULL) {
		head = tail = node;
	}
	else {
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void removeProduct(){
    int nomor;
    viewAdmin();
    do{
        printf("Input number that wants to be removed [available item only]: ");
        scanf(" %d", &nomor);
    }while(nomor > counter || nomor < 0);

	struct data *temp = head;
    for(int i=1; i<nomor; i++) {
		temp = temp->next;
	}
        if(temp == head && head == tail) {
            head = tail = NULL;
            free(temp);
        }
        else if(temp == head) {
            head = head->next;
            head->prev = NULL;
            free(temp);
        }
        else if(temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
        }
        printf("Product has been removed!!\n");
}


//CUSTOMER

void buyItem(){
    int nomor;
    int total;
    int qty;

    struct data *temp = head;
    do{
        printf("choose your menu [1 - %d]: ", counter);
        scanf("%d", &nomor);
    }while(nomor < 0 || nomor > counter);

    for(int i=1; i<nomor; i++) {
		temp = temp->next;
	}

	do{
        printf("enter the quantity [1 - %d]: ", temp->qty);
        scanf("%d", &qty);
	}while(qty < 0 || qty > temp->qty);

    total = qty * temp->harga;

    struct node* curr = (struct node*) malloc(sizeof(struct node));

    strcpy(curr->type, temp->type);
	curr->qty = qty;
	strcpy(curr->produk, temp->produk);
	curr->harga = total;
	curr->next = NULL;

	if(front == NULL) {
		front = rear = curr;
	}
	else {
		rear->next=curr;
		rear = curr;
	}

	temp->qty -= curr->qty;

}

void cancel(){
    struct data *temp = head;
    scan = front;

    for(int i=1; i<=counter; i++){
            scan = front;
        while(scan->next != NULL && strcmp(temp->produk, scan->produk)!=0){
            scan = scan->next;
        }
        if(strcmp(temp->produk, scan->produk)==0 ){
            temp->qty += scan->qty;
        }

            temp = temp->next;

    }

    del = front;
    while(front != NULL) {
		del = front;
		front = front->next;
		free(del);
	}
	front = NULL;
}

void freeAll() {
	struct data* temp;
	while(head != NULL) {
		temp = head;
		head = head->next;
		free(temp);
	}
	head = tail = NULL;

	del = front;
    while(front != NULL) {
		del = front;
		front = front->next;
		free(del);
	}
	front = NULL;
}

int main(){
    int flag = -1;
    int len=0;
    int qty;
    int harga;
    int choose = 0;
    int choose1 = 0;
    int choose2 = 0;
    char produk[50];
    char type[20];
    char nama[20];


    insert("Americano", "yes", 24, 19000);
    insert("Chocolate Baked", "no", 15, 24000);
    insert("Alberto", "yes", 7, 44000);

    do{
        system("cls");getch;
        mainMenu();
        scanf("%d", &choose1);
        switch(choose1){
            case 1: system("cls");getch;
                    do{
                        menuAdmin();
                        scanf("%d", &choose);
                        switch(choose){
                            case 1: system("cls");getch;
                                    do{
                                        printf("Insert item name [ 5 < name < 20]: ");
                                        scanf(" %[^\n]", produk); getchar();
                                        len = strlen(produk);
                                     }while(len > 20 || len < 5);

                                    do{
                                        printf("Type of coffee [yes or no]:     ");
                                        scanf(" %[^\n]", type); getchar();
                                        if(strcmp(type, "yes")==0){
                                            flag = 1;
                                        }
                                        else if(strcmp(type, "no")==0){
                                        flag = 1;
                                        }
                                    }while(flag != 1);

                                    do{
                                        printf("Insert the quantity of the item [ 1 < Quantity < 100]: ");
                                        scanf("%d", &qty);getchar();
                                    }while(qty > 99 || qty < 2);

                                    do{
                                        printf("Insert the price of the item [ 10000 < price < 200000]: ");
                                        scanf("%d", &harga);
                                    }while(harga > 199999 || harga < 10001);
                                    insert(produk, type, qty, harga);
                                    counter +=1;
                                    break;
                            case 2: removeProduct();
                                    counter -=1;
                                    break;
                        }
                    } while(choose!=3);
                    break;
            case 2 :    system("cls");getch;
                        printf("Please enter your name: ");
                        scanf(" %[^\n]", nama);
                        system("cls");getch;
                        do{
                            system("cls");getch;
                            menuCust(nama);
                            scanf("%d", &choose2);
                            switch(choose2){
                                case 1: system("cls");getch;
                                        viewCust(nama);
                                        buyItem();

                                        break;
                                case 2: cancel();
                                        break;
                            }
                        }while(choose2 !=3);
                        break;
            case 3 : freeAll();
                     printf("All data has been clear!!");
                     choose1 = 4;
                     break;
        }
    }while(choose1 !=4);
}
