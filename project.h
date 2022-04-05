/* 
   This file have the declaration of the functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bag of letter */
char bag[1000];
char bag2[1000];
char *str1;

/* To calculate score of the word */
int score(char string[], int s);

/* To convert word to dictionary compatible word */
void upper(char *p);

/* To make all the word possible from the bag of letters */
void word_maker(char str[], char bag[], int count, int p, int counter);

#define SIZE 9000

/* For Hashing*/
struct node
{
   char word[16];
   struct node *next;
};
struct node *hashtable[SIZE];
int hash_func(char ch[]);
void insert(char ch[]);
int search(char ch[]);
void make_hashtable();

/*For maximum score*/
int word_for_score(char ch[], int counter);

/* For the linked list i.e. bag of letter */
struct ls
{
   char data;
   struct ls *next;
};

extern struct ls *head;
void in(char d);
char out(char d);
void makebagEmpty();

/*To ignite search*/
void search_cat_without_star(int counter, int i);
void search_cat_with_star(int counter, int i);
