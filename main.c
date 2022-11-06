#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//#include<conio.h>
#include<ctype.h>
#include<time.h>
#include "trie.h"


int main()
{
    system("clear");
    trie root;
    root = NULL;
    load(&root);
    int ch ;
    char word[50] ;
    char meaning[200] ;
    int p;
    
    while(1)
    {   system("clear");
        printf("\n                            ---------------Welcome to the Dictionary---------------\n") ;
        printf("\n                            ---------------*************************---------------\n\n\n") ;
        printf(" Enter your choice: \n\n 1.View the contents of dictionary\n\n 2.Add a word to dictionary\n\n 3.Search for the meaning of the word\n\n 4.Delete a word from the dictionary\n\n 0.EXIT\n") ;
        printf("\n");
        scanf("%d",&ch);
        system("clear");
        
        if(ch == 0)
        {
        	 unload(&root);
                printf("UNLOADING DICTIONARY...\n");
                system("clear");
                exit(0);
             } 
         else if(ch == 1)
         {
         	view();
         	printf("please enter 1:\n");
         	int c;
         	scanf("%d",&c);
         	/*char c;
         	printf("Enter space to continue");
         	scanf("%c",&c);
         	getchar();
                system("clear");*/

              }
         else if(ch == 2)
         {
          	insert(&root);
                /*char c;
         	printf("Enter space to continue");
         	scanf("%c",&c);*/
                system("clear");
         }
         else if(ch ==3)
         {
          	      view();
                     printf("Enter the word: \n");
                     scanf("%s",word);
                     char* meaning = search_for(root,word);
                    
                     
                     printf("The meaning of the word is: %s\n",meaning);
                     
                     
                     printf("please enter 1:\n");
         	     int c;
         	     scanf("%d",&c);
                     
                     /*char c;
         	      printf("Enter space to continue");
         	      scanf("%c",&c);
                     system("clear");*/
                    
               }
           else if(ch == 4)
           {
           
                    system("clear");
                    printf("\t\t\t ---- DELETION OF A WORD ----\n\n\n");
                    printf(" Enter the word to be deleted: ");
                     //printf("\n");
                     scanf("%s",word);
                    // printf("%s\n",word);
                     
                    if(search(root,word) == 1)
                    {
                     
                        deletion(&root,word);
                        del_from_dict(word);
                        /*char c;
         	         printf("Enter space to continue");
         	         scanf("%c",&c);
                        system("clear");*/
                    }
                    else{
                        printf("\n\n ----- Word is not present in the dictionary!!!!!-----\n");
                        /*char c;
         	         printf("Enter space to continue");
         	         scanf("%c",&c);
                        system("clear");*/
                    }
              }
            else{
            printf("\n Enter a valid option!\n");
                        /*char c;
         	         printf("Enter space to continue");
         	         scanf("%c",&c);
                        system("clear");*/
                        }
                     
        }
    

    return 0;
}
