/* 
   This file contains definitions of all the functions defined in "project.h".
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "project.h"

int number = 0;
/* To find if any word is possible out of given bag of letter*/
int how_many = 0;
char word[20];

void upper(char *p)
{
    while (*p)
    {
        *p = toupper(*p);
        p++;
    }
}

int score(char string[], int s)
{
    int good, bad, a, b, i, weight = 0;
    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == '*')
            continue;
        else if (string[i] == 'E' || string[i] == 'A' || string[i] == 'I' || string[i] == 'N' || string[i] == 'O' || string[i] == 'R' || string[i] == 'T' || string[i] == 'L' || string[i] == 'S' || string[i] == 'U')
            weight = weight + 1;
        else if (string[i] == 'D' || string[i] == 'G')
            weight = weight + 2;
        else if (string[i] == 'B' || string[i] == 'C' || string[i] == 'M' || string[i] == 'P')
            weight = weight + 3;
        else if (string[i] == 'F' || string[i] == 'H' || string[i] == 'V' || string[i] == 'W' || string[i] == 'Y')
            weight = weight + 4;
        else if (string[i] == 'K')
            weight = weight + 5;
        else if (string[i] == 'J' || string[i] == 'X')
            weight = weight + 8;
        else
            weight = weight + 10;
    }
    good = (s - 1) * strlen(string);
    a = 3 * (s + 1 - strlen(string));
    b = 1;
    if (a >= b)
        bad = a;
    else
        bad = b;
    int mult = good - bad;
    int score = mult * weight;
    return score;
}

int has_star(char str[])
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '*')
        {
            count++;
        }
    }
    return count;
}

void word_maker(char str[], char bag[], int count, int p, int counter)
{
    int k, i, j;
    char ch;
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == '*')
        {
            k = i;
            while (p != count)
            {
                j = p;
                ch = bag[p];
                str[i] = bag[p];
                bag[p] = '*';
                if (str[i] == '*')
                {
                    p++;
                    continue;
                }
                if (has_star(str))
                {
                    word_maker(str, bag, count, 0, counter);
                    str[i] = '*';
                }
                else
                {
                    number++;
                    bag[j] = ch;
                    if (search(str))
                    {
                        word_for_score(str, counter);
                    }
                }
                bag[j] = ch;
                p++;
            }
        }
    }
    bag[j] = ch;
    str[k] = '*';
}

void make_hashtable()
{
    char tmp[20];
    for (int i = 0; i < 9000; i++)
        hashtable[i] = NULL;
    FILE *f1 = fopen("dict03/dic.txt", "r");
    assert(f1 != NULL);
    while (fscanf(f1, "%s", tmp) != -1)
    {
        insert(tmp);
    }
}

int search(char ch[])
{
    int key;
    key = hash_func(ch);
    struct node *temp = hashtable[key];
    while (temp != NULL)
    {
        if (strcmp(temp->word, ch) == 0)
        {

            //printf("Word Found: %s\n", ch);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void insert(char ch[])
{
    int key;
    key = hash_func(ch);
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->word, ch);
    temp->next = hashtable[key];
    hashtable[key] = temp;
}

int hash_func(char ch[])
{
    int key = 0;
    for (int i = 0; i < strlen(ch) - 1; i++)
    {
        key = key + (int)ch[i] * (i + 1);
    }
    return key;
}

/*Linked List for bag of letter related work*/
struct ls *head = NULL;

void in(char d)
{
    struct ls *new_node, *ptr;
    new_node = (struct ls *)malloc(sizeof(struct ls));
    new_node->data = d;
    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        ptr = head;
        head = new_node;
        new_node->next = ptr;
    }
}

char out(char d)
{
    struct ls *ptr, *temp;
    ptr = head;
    char item;
    if (head == NULL)
        return '@';
    if (ptr->data == d)
    {
        item = head->data;
        head = ptr->next;
        free(ptr);
        return item;
    }
    while (ptr->next != NULL)
    {
        if (ptr->next->data == d)
        {
            temp = ptr->next;
            ptr->next = temp->next;
            item = temp->data;
            free(temp);
            return item;
        }
        ptr = ptr->next;
    }
    if (d == 'A' || d == 'E' || d == 'I' || d == 'O' || d == 'U')
        return out('*');
    return '@';
}

void makebagEmpty()
{
    struct ls *ptr, *temp;
    ptr = head;
    while (ptr != NULL)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    head = NULL;
}

/* Find a word whose score can be calculated */
int max_score = -10000;
int word_for_score(char ch[], int counter)
{
    //Approach 1
    char dupb[1000];
    int flag, indicator, i, j, x = 0;
    strcpy(dupb, bag2);
    str1 = (char *)malloc(strlen(ch) * sizeof(char));
    for (i = 0; i < strlen(ch); i++)
    {
        flag = 1;
        indicator = 1;
        for (j = 0; j < strlen(dupb); j++)
        {

            if (ch[i] == dupb[j])
            {
                flag = 0;
                indicator = 0;
                sprintf(&str1[x++], "%c", dupb[j]);
                dupb[j] = '@';
                break;
            }
        }
        if (indicator)
        {
            for (j = 0; j < strlen(dupb); j++)
            {
                if ((ch[i] == 'A' || ch[i] == 'E' || ch[i] == 'I' || ch[i] == 'O' || ch[i] == 'U') && dupb[j] == '*')
                {
                    flag = 0;
                    sprintf(&str1[x++], "%c", dupb[j]);
                    dupb[j] = '@';
                    break;
                }
            }
        }
        if (flag == 1)
        {
            return 0;
        }
    }
    int score_word = 0;
    if (flag == 0)
    {
        score_word = score(str1, counter);
        if (score_word > max_score)
        {
            strcpy(word, ch);
            max_score = score_word;
            //printf("Possible word: %s || Score: %d\n", ch, score_word);
            how_many++;
            return 1;
        }
        else
            return 1;
    }
    return 0;
}

void search_cat_without_star(int counter, int i)
{

    char ss[20];
    int flag;
    FILE *w;
    int cases;
    if (counter >= 15)
        cases = 15;
    else
        cases = counter;
    switch (cases)
    {
    case 15:
        w = fopen("dict03/w15.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 14:
        w = fopen("dict03/w14.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 13:
        w = fopen("dict03/w13.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 12:
        w = fopen("dict03/w12.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 11:
        w = fopen("dict03/w11.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 10:
        w = fopen("dict03/w10.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 9:
        w = fopen("dict03/w9.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 8:
        w = fopen("dict03/w8.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 7:
        w = fopen("dict03/w7.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 6:
        w = fopen("dict03/w6.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 5:
        w = fopen("dict03/w5.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 4:
        w = fopen("dict03/w4.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 3:
        w = fopen("dict03/w3.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
    case 2:

        w = fopen("dict03/w2.txt", "r");
        assert(w != NULL);
        while (fscanf(w, "%s", ss) != -1)
        {
            flag = word_for_score(ss, counter);
            if (flag)
                break;
        }
        fclose(w);
        break;

    default:
        break;
    }

    if (how_many)
        printf("\nWord with maximum score is %s with score %d.\n", word, max_score);
    else
        printf("\nNo word is possible from the given letters in 'BAG OF LETTERS'.\n");
}

void search_cat_with_star(int counter, int i)
{
    char ch8[] = {"********"};
    char ch7[] = {"*******"};
    char ch6[] = {"******"};
    char ch5[] = {"*****"};
    char ch4[] = {"****"};
    char ch3[] = {"***"};
    char ch2[] = {"**"};
    if (i <= 8)
    {
        //Approach 1
        if (counter >= 2)
            word_maker(ch2, bag, i, 0, counter);
        if (counter >= 3)
            word_maker(ch3, bag, i, 0, counter);
        if (counter >= 4)
            word_maker(ch4, bag, i, 0, counter);
        if (counter >= 5)
            word_maker(ch5, bag, i, 0, counter);
        if (counter >= 6)
            word_maker(ch6, bag, i, 0, counter);
        if (counter >= 7)
            word_maker(ch7, bag, i, 0, counter);
        if (counter >= 8)
            word_maker(ch8, bag, i, 0, counter);
    }
    else
    {
        //Approach 2
        char ss[20];
        FILE *w;
        int cases;
        if (counter >= 15)
            cases = 15;
        else
            cases = counter;
        switch (cases)
        {
        case 15:
            w = fopen("dict03/w15.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 14:
            w = fopen("dict03/w14.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 13:
            w = fopen("dict03/w13.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 12:
            w = fopen("dict03/w12.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 11:
            w = fopen("dict03/w11.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 10:
            w = fopen("dict03/w10.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 9:
            w = fopen("dict03/w9.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 8:
            w = fopen("dict03/w8.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 7:
            w = fopen("dict03/w7.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 6:
            w = fopen("dict03/w6.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 5:
            w = fopen("dict03/w5.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 4:
            w = fopen("dict03/w4.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 3:
            w = fopen("dict03/w3.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
        case 2:

            w = fopen("dict03/w2.txt", "r");
            assert(w != NULL);
            while (fscanf(w, "%s", ss) != -1)
            {
                word_for_score(ss, counter);
            }
            fclose(w);
            break;

        default:
            break;
        }
    }

    if (how_many)
        printf("\nWord with maximum score is %s with score %d.\n", word, max_score);
    else
        printf("\nNo word is possible from the given letters in 'BAG OF LETTERS'.\n");
}