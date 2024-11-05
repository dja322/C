
#include <time.h> //for random testing numbers
#include <assert.h> //for assert testing
#include <stdlib.h> //for rand()

/**
 *  @brief Moves elements in array one to the right, 
 *  overriding the element to the right and leaving
 *  a copy of the first element. Returns replaced int
 *  @param Array array to be sorted
 *  @param startIndex left most element being moved right
 *  @param endIndex Position that elements will move towards
 *  @returns [int] integer that was overwritten
 */
int moveRight(int Array[], int startIndex, int endIndex)
{
    int erasedInteger = Array[endIndex];
    for (int index = endIndex; index >= startIndex; --index)
    {
        Array[index] = Array[index-1];   
    }   
    return erasedInteger;
}

/**
 *  @brief Moves elements in array one to the left, 
 *  overriding the element to the left and leaving
 *  a copy of the first element. Returns replaced int
 *  @param Array array to be sorted
 *  @param startIndex Position that elements will move towards
 *  @param endIndex right most element being moved left
 *  @returns [int] integer that was overriden
 */
int moveLeft(int Array[], int startIndex, int endIndex)
{
    int erasedInteger = Array[endIndex];
    for (int index = startIndex; index <= endIndex; ++index)
    {
        Array[index] = Array[index+1];   
    }   
    return erasedInteger;
}

/**
 *  @brief Using binarySearch to find position of where element should be
 *  @param array array to be searched
 *  @param sortedListStartIndex starting index of the area to be searched
 *  @param sortedListEndIndex ending index of the area to be searched
 *  @returns [int] position of element or where it should be if not in array
 */
int binarySearchToFindPosition(int array[], int element,
        int sortedListStartIndex, int sortedListEndIndex)
{
    int low = sortedListStartIndex;
    int max = sortedListEndIndex;
    int mid = (max - low) / 2 + low;
    
    //loops through elements until it finds either the same element or
    //it finds the two elements it should be between and returns index of larger one
    while ( !(element >= array[mid-1] && element <= array[mid]) )
    {
        mid = (max - low) / 2 + low;
        if (element > array[mid])
        {
            low = mid + 1;
        }
        else if (element < array[mid])
        {
            max = mid - 1;
        }
        else
        {
            return mid;
        }
        
    }
    return mid;
}

/**
 *  @brief Sorting algorithm that starts with 
 *  middle elements and sorts out from the center
 *  @param Array Array that is to be sorted
 *  @param sizeOfArray size of array
 */
void MiddleSort(int Array[], int sizeOfArray)
{
    int currentSortedSize = (sizeOfArray % 2 == 0) ? 1 : 0;
    
    int startIndex = (sizeOfArray / 2) - currentSortedSize;
    int endIndex = startIndex + currentSortedSize;
    
    int replacePosition;
    int currentLarge;
    int currentLow;

    //create initial state with sorted one or two elements
    if (Array[startIndex] > Array[endIndex])
    {
        currentLarge = Array[startIndex];
        currentLow = Array[endIndex];
    }
    else
    {
        currentLow = Array[startIndex];
        currentLarge = Array[endIndex];
    }

    //set array preloop state
    Array[startIndex] = currentLow;
    Array[endIndex] = currentLarge;

    startIndex -= 1;
    endIndex += 1;

    //loop until end of array is passed
    while (startIndex >= 0 && endIndex < sizeOfArray)
    {

        //checks which of the two picks is larger/smaller
        if (Array[startIndex] > Array[endIndex])
        {
            currentLarge = Array[startIndex];
            currentLow = Array[endIndex];
        }
        else
        {
            currentLow = Array[startIndex];
            currentLarge = Array[endIndex];
        }

        //if block to determine how elements are moved around and places
            //if low is lowest
        if (currentLow < Array[startIndex+1])
        {
            Array[startIndex] = currentLow;

            //check where largeest should go
            if (currentLarge < Array[endIndex-1])
            {
                replacePosition = binarySearchToFindPosition(Array, currentLarge,
                                  startIndex, endIndex-1);
                moveRight(Array, replacePosition, endIndex);
                Array[replacePosition] = currentLarge;
            }
            else
            {
                Array[endIndex] = currentLarge;
            }
        }
        //if the lowest and larger are the biggest so far
        else if (currentLow > Array[endIndex-1])
        {
            moveLeft(Array, startIndex, endIndex-1);
            Array[endIndex-1] = currentLow;
            Array[endIndex] = currentLarge;
        }
        //if low tested value is not the largest or smallest
        else
        {
            replacePosition = binarySearchToFindPosition(Array, currentLow,
                              startIndex+1, endIndex-1);
            moveLeft(Array, startIndex, replacePosition-1);
            Array[replacePosition-1] = currentLow;

            //check where largest should go, either at end or in sorted list
            if (currentLarge < Array[endIndex-1])
            {
                replacePosition = binarySearchToFindPosition(Array, currentLarge,
                                startIndex, endIndex-1);
                moveRight(Array, replacePosition, endIndex);
                Array[replacePosition] = currentLarge; 
            }
            else
            {
                Array[endIndex] = currentLarge;
            }
        }
        
        //increment sorted array
        --startIndex;
        ++endIndex;
    }
}


/**
 * @brief tests sorting middle sort algorithm
 * @param array array to be filled and tested
 * @param arraySize size of array
 */
static void test(int array[], int arraySize)
{
    for (int index = 0; index < arraySize; ++index)
    {
        array[index] = (rand() % 100);
    }

    MiddleSort(array, arraySize);

    for (int index = 1; index < arraySize; ++index)
    {
        assert(array[index-1] <= array[index]);
    }
}

/** Main function
 *  @brief Runs main and creates test array that will be tested
 *  @returns an integer 0
 */
int main()
{
    srand(time(NULL));
    int size = 50;
    int array[size];

    test(array, size);

    return 0;
}
