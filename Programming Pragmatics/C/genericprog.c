/*
 * Mike Zeng
 * CECS 424-05
 * Assignment 3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value;
} person;
//defining compares to sort
int dcompare(const void *a,const void *b) {
    double *x = (double *) a;
    double *y = (double *) b;
    if (*x < *y) return -1;
    else if (*x > *y) return 1;
    return 0;
}
int pcomparefst(const void *a,const void *b) {
    person *x = (person *) a;
    person *y = (person *) b;
    return strcmp(x->key, y->key);
}
int pcomparesnd(const void *a,const void *b) {
    person *x = (person *) a;
    person *y = (person *) b;
    if((x->value - y->value) == 0)  //if their age is the same, go alphabetically
        return strcmp(x->key, y->key);
    else                            //order by descending age
        return y->value - x->value;
}

//data structures
char *names[] = {"Hal","Susann","Dwight","Kassandra","Lawrence","Cindy","Cory","Mac","Romana","Doretha","Danna","Zara","Rosalyn","Risa","Benny","Juan","Natalie"};
int ages[] = {20, 31, 19, 21, 25, 22, 27, 19, 27, 32, 20, 23, 26, 24, 28, 33, 25};
double numbers[] = { 645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26 };
const int num_len = (sizeof numbers/ sizeof *numbers);
const int people_len = (sizeof names/ sizeof *names);

//display lists
void display_num(double* a){
    for(int i=0;i<num_len;i++){
        printf("%.2f  ", a[i]);
    }
}
void display_people(person* p){
    for(int i=0;i<people_len;i++){
        printf("%s,%d ", p[i].key, p[i].value);
    }
}

int main(int argc, char** argv) {   
    person *people = malloc(sizeof(person) * people_len);
    if (people == NULL) {   //people error check
        perror("Malloc");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i<people_len;i++){    //generate the people list
        people[i].key = names[i];
        people[i].value = ages[i];
    }
    
    //display list of numbers
    printf("List of numbers: \n");
    display_num(numbers);
    qsort(numbers, num_len, sizeof(*numbers), dcompare);    //generic qsort to sort in ascending order
    printf("\nOrdered numbers: \n");
    display_num(numbers);
    
    //display list of people
    printf("\n\nList of people: \n");
    display_people(people);
    person *alpha_sort_people = malloc(sizeof(person) * people_len);
    for(int i = 0;i<people_len;i++){    //generate temp people list to sort alphabetically
        alpha_sort_people[i].key = people[i].key;
        alpha_sort_people[i].value = people[i].value;
    }
    qsort(alpha_sort_people, people_len, sizeof(*alpha_sort_people), pcomparefst);  //alphabetically sorted people
    printf("\nOrdered people by name alphabetically:\n");
    display_people(alpha_sort_people);
    qsort(alpha_sort_people, people_len, sizeof(*alpha_sort_people), pcomparesnd);  //age descended sort people, then by alphabetically
    printf("\nOrdered people by descending age then alphabetically:\n");
    display_people(alpha_sort_people);
    printf("\n");        
    
    free(people);
    free(alpha_sort_people);
    return (EXIT_SUCCESS);
}