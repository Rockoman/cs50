/**Marc LaRocco
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //check if n is positive
    if (n < 0)
        return false;
        
    //declare variables
    int high = n - 1;
    int low = 0;
    int index = 0;
    
    //while low is less than high....
    while (low <= high)
    {
        //find the middle
        index = (high + low)/2;
    
        //check if the current index of the array is the same as the value we're looking for.
        if(value == values[index])
            return true;       
        //if the starting point value is the same as the ending point AND the array doesn't equal value
        if (low == high && values[low] != value)
            return false;
        //if values[index] is less than the value, increase the starting point by 1    
        else if(values[index] < value)
            low = index + 1;
        //if the values[index] is greater than the value, decrease the ending point by 1.
        else
            high = index - 1;
            
    }
    
    //if no true is found...
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement an O(n^2) selection sorting algorithm
    
    int index;
    int temp;
       
    //if n is not positive, return
    if(n < 0)
        return;
    
    for(int i = 0; i < n; i++)
    {
        //declare index value
        index = i;
    
        for(int j = i; j < n; j++)
        {
            if(values[index] > values[j])
                index = j;                
        }
        
        temp = values[i];
        values[i] = values[index];
        values[index] = temp;
        
        
    }
    
    return;
}
