#include <stdio.h>
#include <stdlib.h>
#include "indexation_image.h"





int main ()
{ 
  
   Image im;
   int * histo;
   
   decodeImage(&im,"01.txt");

  

   for(unsigned int y = 0;y < im.tailleY;y++){
      for(unsigned int x = 0;x < im.tailleX;x++){
          printf("%u  %u  %u    ", (*(im.image+(x*im.tailleY)+y)).R,(*(im.image+(x*im.tailleY)+y)).G,(*(im.image+(x*im.tailleY)+y)).B);
          }   
      printf("\n");
      }
       
      histo=histogramme(im,2);

      printf("\n");
    
   for(unsigned int y = 0;y < pow(2,3*2);y++)
      printf("%d",*(histo+y));


 return 0;
}
