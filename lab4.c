//  Mohammed Ahmed
//  1001655176
//  Lab 4
//  gcc lab4.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



//function to extract digit from a number
int isolateDigit(int pos, int num)
{
    int digit=num;
    int dividend=1000000000/pow(10,pos);
    
    digit = num%dividend;

    //prevents dividing by 0
    if(dividend/10!=0)
    {
        digit = digit/(dividend/10);
    } 
    return digit;
}

//function to read input
void readInput(int* n,int* k,int** S, int** digitTable)
{
  
  // Loads all input and allocates space
  int i;

  scanf("%d",n);
  scanf("%d",k);

  //creates digitTable array based on size of input set
  *digitTable = (int*) malloc((*n+1)*sizeof(int));

  //creates array to store input set based on n (input size)
  *S=(int*) malloc((*n+1)*sizeof(int));

  //fills input set array
  for (i=0;i<=*n;i++)
    scanf("%d",*S+i);

}

//counting sort function
void countingSort(int *n, int*k, int *S, int digitSpot, int *slot,int *count, int *digitTable)
{

  int keep; //index we want to keep
  int tempSize; //temporarily store the size when we reduce the array

  //PHASE 1 - Clear count table
  int i;
  for(i=0; i < 10; i++)
  {
    count[i] = 0;
  }

  //PHASE 2 - Count the input table
  for(i = 0; i < *n; i++)
  {

    if(digitTable[i] != -1)
    {
      count[digitTable[i]]++;
    }

    
  }

  //PHASE 3 - Create the slot table

  //initial starting value is 0
  slot[0] = 0;

  //loops through slot table and adds values
  for (i=1; i < 10; i++)
  {
    //fills slot table
    slot[i]=slot[i-1]+count[i-1];
  }



  int max;  //upper bound of slot value
  int min;  //lower bound of slot value
  int found = 0;


  //PHASE 4 - Update input table, k, and n
  for(i = 1; i < 10; i++)
  {
    max = slot[i];
    
    //checks if slot value is greater than k (whether it is actually the max)
    //found checks if we have already found the max (so we don't set it to a larger value)
    if(max >= *k && found == 0)
    {
      //max value found
      found = 1;
      

      //sets min value
      min = slot[i-1];

      //sets keep (index of the min value)
      if(i > 0)
      {
        keep = i - 1;
      }
      else
      {
        keep = i;
      }
      
    }
  }

  

  //setting new k value
  *k = *k - min;
  

  //setting temporary size
  tempSize = count[keep];


  //throw away useless values and output new array

  int tempArray[tempSize];
  int counter = 0;
  int check = 0;
  int value;

  //first extract values we want
  for(i = 0; i < *n; i++)
  {
    value = S[i];
    check = isolateDigit(digitSpot, value);
      
    //checks if the value has the digit we want
    if(check == keep)
    {
      //takes value from input array into the temp array
      //counter keeps track of index of tempArray
      tempArray[counter] = S[i];
      counter++;

    }
  }


  //second we overwrite the input array with tempArray
  for(i = 0; i < tempSize; i++)
  {
    S[i] = tempArray[i];
    
  }
  
  //setting new size
  *n = count[keep];
  





 

}

int main(void) 
{
  int n;    // Size of input set
  int k;    // Target value (kth element in the set)
  int *S;   // Input set

  int digitSpot = 0;
  int slot[10];
  int count[10];
  int *digitTable;  //table with all the digits from a certain column (ex. tens place)

  //read input file
  readInput(&n, &k, &S, &digitTable);

  //stores initial k value
  int kInitial = k;

  //stores initial n value
  int nInitial = n;


  do
  {

    //clear digit table (set all the values to -1)
    int i;
    for(i = 0; i < nInitial; i++)
    {
      digitTable[i] = -1;
    }

    //fill up digitTable based on digitSpot
    for(i = 0; i < n; i++)
    {
      //fills digitTable with values from the input at a certain spot
      digitTable[i] = isolateDigit(digitSpot, S[i]);
    }

    //OFFICIAL OUTPUT
    printf("position %d n %d\n",(9-digitSpot),n);

    //count sort
    countingSort(&n, &k ,S, digitSpot, slot, count, digitTable);


    //increment digit position
    digitSpot++;



  }
  while(digitSpot < 9 && n > 1);

  //count sort
  countingSort(&n, &k ,S, digitSpot, slot, count, digitTable);

  //checks if size is 0 (impossible)
  if(n == 0)
  {
    n++;
  }

  //OFFICIAL OUTPUT
  printf("position %d n %d\n",(9-digitSpot),n);

  //FINAL OUTPUTss
  printf("\nMSD 10 radix: The value with rank %d is %d\n\n",kInitial,S[0]);
  

  //free memory
  free(S);

  return 0;
}




