#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
//#include<conio.h>
#include "trie.h"

void load(trie *root)
{
    int i; 

    //initializing trie for dictionary
    (*root) = (trie)malloc(sizeof(node));
    if((*root) == NULL)
    {
        printf("OUT OF MEMORY!\nDictionary cannot be loaded\n");
        
    }
    for(i = 0 ; i < NUM_CHAR ; i++)
    {
        (*root)->child[i] = NULL;
    }
    (*root)->terminal = false;  //initialized
    
    int index;
    trie temp = (*root);

    //dictionary begins
    FILE *fp = fopen("dictionary.txt","r+");

    // fp null means not file opened
    if(fp == NULL)
    {
        printf("ERROR!\n");
        
    }

    //file opened storing words in trie
    char word_str[20];
    char meaning[200];

    while((fscanf(fp,"%s",word_str)) != EOF)           //fscanf reads until any blank space but doesnt store 
    {
        fgets(meaning, 200, fp);                       //fgets reads until a newline but also stores it
        int word_len = strlen(word_str);               // fscanf is at the end of the first word and fgets at the end of the first line
        for(i = 0 ; i < word_len ; i++)
        {
            //handling letters of the word
            if(isalpha(word_str[i]))                         // checking if the character is an alphabet or not
                index = (int)tolower(word_str[i]) - 'a';      // changing it to lower case and storing index        
            
            if(index > 25 || index < 0)
            {
                continue;                                   //skipping the current character
            }

            // now insert that character read from dictionary to the trie structure
            if(temp->child[index] == NULL)
            {
                //create and initialize new next nodes for the subsequent letters
                temp->child[index] = (trie)malloc(sizeof(node));
                if(temp->child[index] == NULL)
                {
                    printf("OUT OF MEMORY!");
                   
                }
                temp = temp->child[index];
                int j;
                for(j = 0 ; j < 26 ; j++)
                {
                    temp->child[j] = NULL;
                    
                }
                temp->terminal = false;


            }
            else{
                temp = temp->child[index];
                //marking word as present in the dictionary
                if(i == word_len - 1)
                {
                    temp->terminal = true ; 
                    int mean_len = strlen(meaning);
                    temp->mean=(char*)malloc(sizeof(char)*mean_len);
                    strcpy(temp->mean,meaning);
                }
            }
        }
        temp = (*root);
    }
    fclose(fp);
    
}

void unload(trie *dict_rem)
{
    trie temp = (*dict_rem);
    //recursively free allocated memory
    int i ;
    for(i = 0 ; i < NUM_CHAR ; i++)
    {
        if(temp->child[i] != NULL)
        {
            unload(&(temp->child[i]));
        }
    }
    free(temp);
    temp = NULL;
}

int search(trie root, char* key)
{
    trie temp = root;
    int i,status=0;
    int length = strlen(key);
    for(i = 0 ; i < length ; i++)
    {
        int index = (int)tolower(key[i]) - 'a';
        if(temp->child[index] != NULL)
        {
           temp = temp->child[index];
           if( i == length - 1)
           {
                if(temp->terminal == true)
                {
                    printf("\nThe meaning of the word is : %s\n",temp->mean);
                   
                }
                 status = 1;
           }
        }
        else{
            printf("\n The word is not present in the Dictionary \n");
            status = 0;
            break;
        }
        
    }
    return status;
    
}

char* search_for(trie root, char* key)
{
    trie temp = root;
	int length = strlen(key);
    for (int i = 0; i < length ; i++)
    {
        int index = (int)tolower(key[i]) - 'a';
        if (temp->child[index] == NULL)
            return NULL;

        temp = temp->child[index];
    }

    if((temp->terminal == true))
    {
        return temp->mean;
        }
    else {
    return NULL;
    }
}

void view()
{   

    printf("\t\t\t ------ VIEWING THE CONTENTS OF DICTIONARY ------\n\n\n");
    FILE *fp = fopen("dictionary.txt","r");
    if (fp == NULL)
    {
        printf("Error opening the dictionary\n");
    }
    char word_str[20];
    char meaning[200];
    while(fscanf(fp,"%s",word_str) != EOF)
    {
        printf(" -- %s\n",word_str);
        fgets(meaning,200,fp);
    } 
    fclose(fp);
}

void insert(trie *root)
{
    
    system("clear");
    char word[20];
    char meaning[200];
    char temp_meaning[20];
    printf("\n\t\t\t--------------- INSERTION OF A WORD IN THE DICTIONARY ---------------\n\n\n");
    printf(" Enter the word you wish to add: ");
    scanf("%s",word);
    printf("\n");
    printf(" Enter the meaning: ");
    scanf("%s",meaning);
    int word_len = strlen(word);
    int index,i;
    trie temp = (*root);
    for(i = 0 ; i < word_len ; i++)
    {
        //handling letters of the words
        if(isalpha(word[i]))
        {
            index = (int)tolower(word[i]) - 'a';
        }
        if(index > 25 || index < 0)
        {
            continue;
        }
         
         // inserting the character from the word read from dictionary to trie
         if(temp->child[index] == NULL)
         {
            // create and initialize new next nodes for subsequent letters
            temp->child[index] = (trie)malloc(sizeof(node));
            if(temp->child[index] == NULL)
            {
                printf("OUT OF MEMORY!");
                return;
            }
            temp= temp->child[index];
            int j ;
            for(j = 0 ; j < NUM_CHAR ; j++)
            {
                temp->child[j]=NULL;
                
            }
            temp->terminal = false;
         }
         else {
             temp = temp->child[index];
             //set word as present in the dictionary
         }
         if(i == word_len - 1)
         {
            temp->terminal = true ;
            int mean_len = strlen(meaning);
            temp->mean=(char*)malloc(sizeof(char)*mean_len);
            strcpy(temp->mean,meaning);
        }

    }
    FILE *fp = fopen("dictionary.txt","a");
    fprintf(fp,"\n%s ",word);
    fprintf(fp,"%s",meaning);
    //fputs("\n",fp);
    fclose(fp);
    

}

int haveChildren(trie curr)
{
	for (int i = 0; i < 26; i++)
		if (curr->child[i])
			return 1;	// child found

	return 0;
}

int deletion(trie*curr, char* str)
{
	// return if Trie is empty
	if (*curr == NULL)
		return 0;

	// if we have not reached the end of the string
	if (*str)
	{
		// recur for the node corresponding to next character in
		// the string and if it returns 1, delete current node
		// (if it is non-leaf)
        int index = (int)tolower(*str) - 'a';
		if (*curr != NULL && (*curr)->child[index] != NULL &&
			deletion(&((*curr)->child[index]), str + 1) &&
			(*curr)->terminal == false)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	// if we have reached the end of the string
	if (*str == '\0' && (*curr)->terminal == true)
	{
		// if current node is a leaf node and don't have any children
		if (!haveChildren(*curr))
		{
			free(*curr); // delete current node
			(*curr) = NULL;
			return 1; // delete non-leaf parent nodes
		}

		// if current node is a leaf node and have children
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			(*curr)->terminal = false;
			return 0;	   // don't delete its parent nodes
		}
	}

	return 0;
}

/*void del_from_dict(trie root,char *key)
{

    FILE* fp1 = fopen("dictionary.txt","r");
    FILE* fp2 = fopen("temp.txt","w");
    char buffer[200];
    char* mean = search(root,key);
    char str2[10] = " ";
    strcat(key,str2);
    strcat(key,mean);
    printf("%s",key);
   
    while(fgets(buffer,200,fp1))
    {
       
        if(strcmp(buffer,key) == 0)
        {
            continue;
        }
        fprintf(fp2,"\n%s",buffer);
    }
    
  
    
        fclose(fp1);
        fclose(fp2);
        remove("dictionary.txt");
        rename("temp.txt","dictionary.txt");

}*/

void del_from_dict(char *key)
{   
    char word[20],meaning[200];
    FILE *fp1,*fp2;
    fp1 = fopen("dictionary.txt","r");
    fp2 = fopen("temp.txt","w");

    //rewind(fp1);
    while(fscanf(fp1,"%s",word) != EOF)
    {
        if(strcmp(key,word) != 0)
        {
            fprintf(fp2,"%s ",word);
            fgets(meaning,200,fp1);
            fprintf(fp2,"%s",meaning);
        }
        else
        {
            fgets(meaning,200,fp1);
        }

    }
    fclose(fp2);
    fclose(fp1);
    remove("dictionary.txt");
    rename("temp.txt","dictionary.txt");

}




