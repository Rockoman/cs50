/*Marc LaRocco
 *Pset 2 Initials
 */

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main (void)
{
    //declare variables
    string name = GetString();
    int len = strlen(name);
    
    
    for (int i = 0; i < len; i++)
    {
        //change first letter to uppercase and print
        if(i == 0)
            printf("%c", toupper(name[i]));
        
        //find a space, increment index by 1, uppercase value and print.    
        if (name[i] == ' ')
        {
            i++;
            printf("%c", toupper(name[i]));
        }   
        
    }
    //print new line
    printf("\n");
    return 0;
}