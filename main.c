#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "project.h"

int main()
{
    clock_t t;
    t = clock();
    char b;
    int x = 0;
    int counter = 0, star=0;
    int i = 0, j = 0;

    /* To take the bag of letter*/
    printf("Enter charcters to fill bag of letter(Press enter to stop entering): ");
    scanf(" %c", &b);
    while (b != '\n')
    {
        if (b != ' ')
        {
            if (b == '*')
            {
                star++;
                bag[i++] = 'A';
                bag[i++] = 'E';
                bag[i++] = 'I';
                bag[i++] = 'O';
                bag[i++] = 'U';
                bag2[j++] = '*';
                counter++;
            }
            else
            {
                if (islower(b))
                    b = toupper(b);
                bag[i++] = b;
                bag2[j++] = b;
                counter++;
            }
        }
        scanf("%c", &b);
    }
     /* Entry to bag ends here */
    
    if (counter <= 8)
        make_hashtable();
    if(star)
        search_cat_with_star(counter, i);
    else   
        search_cat_without_star(counter, i);
    
    printf("*****************************************************************************\n");
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("TIME TAKEN: %f seconds. \n", time_taken);
    return 0;
}
