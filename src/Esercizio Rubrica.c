#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define ADDRESS_BOOK_SIZE 256
#define NAME_LEN 64
#define PHONE_LEN 20

typedef struct {
	int id; // id numerico del contatto (valore univoco)
	char name[NAME_LEN + 1]; // nome della persona
	char phone[PHONE_LEN + 1]; // numero di telefono
} contact_type;
/*-------------------------------------------------------*/
contact_type* create_contact(char *name, char *phone);
int add_to_address_book(contact_type *c);
int search_in_address_book(contact_type *c);
int compare_contacts(contact_type *c1, contact_type *c2);
int remove_from_address_book(contact_type *c);
void print_contact(contact_type *person);
void sort_by_name();
void swap(int x, int y);

/*-------------------------------------------------------*/
int id = 0;
contact_type *address_book[ADDRESS_BOOK_SIZE];

/*-------------------------------------------------------*/
int main(int argc, char *argv[]) {
	contact_type *dino = create_contact("dino", "+391237");
	if (dino == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(dino);

	contact_type *filippo = create_contact("filippo", "+391239");
	if (filippo == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(filippo);

	contact_type *barbara = create_contact("barbara", "+391235");
	if (barbara == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(barbara);

	contact_type *antonio = create_contact("antonio", "+391234");
	if (antonio == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(antonio);

	contact_type *enrico = create_contact("enrico", "+391238");
	if (enrico == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(enrico);

	contact_type *chiara = create_contact("chiara", "+391236");
	if (chiara == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(chiara);

	printf("Rubrica :\n");
	for (int j = 0; j < ADDRESS_BOOK_SIZE; j++) {
		if (address_book[j] != NULL)
			print_contact(address_book[j]);
	}
	printf("\n--------------RIMUOVI CONTATTO--------------\n");
	contact_type *contatto = create_contact("antonio", "+391234");
	int res = search_in_address_book(contatto);
	if (res > 0) {
		remove_from_address_book(contatto);
		printf("Il contatto (%s) è stato trovato e rimosso\n", contatto->name);
	} else
		printf("Il contatto non è stato trovato\n");

	printf("Rubrica :\n");
	for (int j = 0; j < ADDRESS_BOOK_SIZE; j++) {
		if (address_book[j] != NULL)
			print_contact(address_book[j]);
	}

	printf("\n--------------AGGIUNGI CONTATTO--------------\n");
	contatto = create_contact("pino", "+399999");
	if (contatto == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(contatto);
	printf("Rubrica :\n");
	for (int j = 0; j < ADDRESS_BOOK_SIZE; j++) {
		if (address_book[j] != NULL)
			print_contact(address_book[j]);
	}

	printf("\n--------------AGGIUNGI ANTONIO--------------\n");
	contatto = create_contact("antonio", "+391234");
	if (contatto == NULL) {
		printf("error in create contact");
		return EXIT_FAILURE;
	}
	add_to_address_book(contatto);
	printf("Rubrica :\n");
	for (int j = 0; j < ADDRESS_BOOK_SIZE; j++) {
		if (address_book[j] != NULL)
			print_contact(address_book[j]);
	}

	printf("\n--------------SORT--------------\n");
	sort_by_name();

	/*-------------------PRINT RUBRICA-----------------*/
	printf("\n*********** RUBRICA ***********\n");
	printf("Rubrica :\n");
	for (int j = 0; j < ADDRESS_BOOK_SIZE; j++) {
		if (address_book[j] != NULL)
			print_contact(address_book[j]);
	}

	/*--------------------------------------------*/
	free(dino);
	free(filippo);
	free(barbara);
	free(antonio);
	free(enrico);
	free(chiara);
	free(contatto);

	return 0;
}
/*------------------Funzioni------------------*/
contact_type* create_contact(char *name, char *phone) {
	contact_type *contatto = malloc(sizeof(contact_type));
	strcpy(contatto->name, name);
	strcpy(contatto->phone, phone);
	contatto->id = id++;
	return contatto;
}

int add_to_address_book(contact_type *c) {
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
		if (address_book[i] == NULL) {
			address_book[i] = c;
			return i;
		}
	}
	return -1;
}

int search_in_address_book(contact_type *c) {
	for (int i = 0; i < ADDRESS_BOOK_SIZE; i++) {
		if (address_book[i] != NULL) {
			if (compare_contacts(c, address_book[i]) == 0)
				return i;
		}
	}
	return -1;
}

int compare_contacts(contact_type *c1, contact_type *c2) {
	if (c1 == NULL || c2 == NULL)
		return -1;

	if (strcmp(c1->name, c2->name) == 0) {
		if (strcmp(c1->phone, c2->phone) == 0) {
			return 0;
		}
	}
	if (c1->id < c2->id)
		return -2;
	else
		return 2;
}

int remove_from_address_book(contact_type *c) {
	int index = search_in_address_book(c);
	if (index != 0) {
		address_book[index] = NULL;
		return index;
	}
	return -1;
}

void print_contact(contact_type *person) {
	printf(" id=%d, name='%s', phone='%s' \n", person->id, person->name,
			person->phone);

}

void swap(int x, int y) {
	contact_type *t = address_book[x];
	address_book[x] = address_book[y];
	address_book[y] = t;
}

void sort_by_name() {
	for (int i = 0; i < ADDRESS_BOOK_SIZE - 1; i++) {
		for (int j = 0; j < ADDRESS_BOOK_SIZE - i - 1; j++) {
			if (address_book[j] == NULL && address_book[j + 1] != NULL)
				swap(j, j + 1);
			else if (address_book[j] != NULL && address_book[j + 1] != NULL)
				if (strcmp(address_book[j]->name, address_book[j + 1]->name)>0)
					swap(j, j + 1);
		}
	}
}

