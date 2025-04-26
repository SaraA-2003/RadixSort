/* Sara Adnan Mahmoud Al-Lahaleh
ID: 1211083
Section:1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<ctype.h>

#define MAX_LENG 30//Declare a constant representing the length of a string.

/** @brief Define a structure "node" ,that consist of two pointers and data
*and that is the structure of the nodes that will build a doubly linked list.
*
*  @param prev pointer of type Node.
*  @param next pointer of type Node.
*  @param data it is an array of characters that will store a string inside it.
*/
struct node;
typedef struct node *Node;// another name 'Node' for the pointer struct node*,and if i want to declare pointer
struct node
{
    Node prev;
    char data[MAX_LENG];//I add plus 1 for the string terminate "\0"

    Node next;

};
typedef Node List;//double pointer (if i want to declare list)
/////////////////////////////

/** @brief Define a structure "node1" ,that consist of two pointers and data
*and that is the structure of the nodes that will build a doubly linked list.
*
*  @param prev pointer of type Node1.
*  @param next pointer of type Node1.
*  @param data it is a character data type that will store a character inside it.
*/
struct node1;
typedef struct node1 *Node1;// another name 'Node' for the pointer struct node*,and if i want to declare pointer
struct node1
{
    Node1 prev;
    char data;
    Node1 next;

};
typedef Node1 List1;//double pointer (if i want to declare list)

/////////////Global variables////////////
List1 characters[63];/*Declare a global array of doubly linked lists with the first index for '*', the second 10 indexs
for numbers [0-9],the second 26 indexes for uppercase letters, and the last 26 indexes for lower case letters.*/

List unsortedList;//Declare a list for unsorted strings
List extenUnsortedList;//Declare a list for extended unsorted strings
List extenSortedList;//Declare a list for extended sorted strings

int isRead=0;//checks if the input file has been read or not
int isSorted=0;//checks if the strings have been stored or not

///////program's functions///////
void displayMenu();

List CreateList();
List1 CreateList1();

void DeleteList(List L);
void DeleteList1(List1 L);

int IsEmpty(List L);
int IsEmpty1(List1 L);

void printList(List L);

void insertLast(List L, char  s[MAX_LENG]);
void insertLast1(List1 L, char s [MAX_LENG]);

List readInputFile();
void printToOutputFile(List L);

int MaxLengString(List L);
void extendedString(List Ls, List Ld);
void copyTwoLists(List Ls, List Ld);
void deletepadding(List L);

void radixSort(List L);
void sortList(List L);

int deleteNode (char word[MAX_LENG]);
void deleteNode1(List L,char word[MAX_LENG]);

int wordLength ( char word[MAX_LENG]);
int getSize(List L);
int isLetDig(char word[MAX_LENG]);





int main()
{
//create the lists that i will use in this program
    extenUnsortedList=CreateList();
    extenSortedList=CreateList();



    int op;
    displayMenu();
    scanf("%d",&op);

    while(op!= 8) //If the user selects operation 8, the program will terminate.
    {

        switch(op)
        {
        case 1://read the input file
        {
            int choice;
            if(isRead==1) //if the user wants to load a strings from other file
            {
                printf("Do you want to load a list of strings from a new file?if yes enter 1,if no enter 0:\t");
                scanf("%d",&choice);
                if(choice==0)//not loading from another file
                    break;
                else //loading from another file
                {
                    unsortedList = readInputFile();
                    printf("\nThe file has been effectively loaded, and the strings are now ready for use.\n\n");
                    isSorted=0;
                    isRead=1;
                    break;
                }
            }
            unsortedList = readInputFile();
            printf("\nThe file has been effectively loaded, and the strings are now ready for use.\n\n");


            isRead=1;


            break;
        }

        case 2://print the unsorted list
        {

            if(isRead==0)
            {
                printf("The strings are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }
            printList(unsortedList);

            break;
        }
        case 3://sort the list
        {

            if(isRead==0)
            {
                printf("The strings are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }
            if((IsEmpty(unsortedList)))
            {
                printf("The strings list is empty ,there is nothing to sort.\n\n");

                break;
            }
            if(isSorted==1)
            {
                printf("The list of strings has already been arranged in a sorted order.\nPlease select option 4 to display the sorted list.\n\n ");
                break;
            }
            DeleteList(extenSortedList);
            DeleteList(extenUnsortedList);

            extendedString(unsortedList,extenUnsortedList);//add padding (*) to the strings

            if(extenUnsortedList->next->next==NULL)  //has only one node
            {
                insertLast(extenSortedList, extenUnsortedList->next->data);
                printf("The list contains only one string; therefore, the sorted version will be identical to the original.\n\n");
                isSorted=1;
                break;
            }

            radixSort(extenUnsortedList);
            printf("The strings have been successfully sorted..\n\n");
            isSorted=1;



            break;
        }

        case 4://print the sorted list
        {

            if(isRead==0)
            {
                printf("The strings are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }
            if((IsEmpty(extenSortedList))&&(IsEmpty(unsortedList)))  //lists are empty
            {
                printf("The sorted strings list is empty; there is nothing to print. You can add new strings and sort them in operation 5.\n\n");
                break;
            }

            if(isSorted==0)
            {
                printf("The list is currently unsorted; please execute operation 3 to sort it.\n\n");
                break;
            }

            printf("The sorted list of strings:\n\n");
            printList(extenSortedList);
            printf("\n");


            break;
        }

        case 5://add a new string and sort it
        {

            if(isRead==0)
            {
                printf("The strings are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }

            if((isSorted==0)&&(!IsEmpty(unsortedList)))
            {
                printf("The list is currently unsorted; please execute operation 3 to sort it.\n\n");
                break;
            }

            //add new string
            char newString[100];//I set the size to 100 to handle strings longer than 30 characters,for checking purpose.
            int length;
            printf("\nPlease input the string you want to add to the list:\t");
            scanf("%s",newString);
            length=strlen(newString);
            newString[length]='\0';


            while((length>MAX_LENG)||(!isalpha(newString[0]))||(isLetDig(newString)==0)) //if the input string dos not adhere to the specified strings rules
            {
                if(length >MAX_LENG) //checks if the string exceeds 30 or not
                {
                    printf("\nThe input string does not adhere to the specified string rules;it should not exceed 30 characters.\n\n");
                    printf("Please enter a new string of 30 characters or less:\t");
                    scanf("%s",newString);
                    length=strlen(newString);
                    newString[length]='\0';
                }
                if(!isalpha(newString[0])) //checks if the first char is letter or not
                {
                    printf("\nThe input string does not adhere to the specified string rules; it should starts with a character.\n\n");
                    printf("Please enter a new string that starts with a letter:\t");
                    scanf("%s",newString);
                    length=strlen(newString);
                    newString[length]='\0';
                }
                if(isLetDig(newString)==0) //checks if the string char is letter or digit or both
                {
                    printf("\nThe input string does not adhere to the specified string rules; it should not have any symbols.\n\n");
                    printf("Please provide a new string without any symbols:\t");
                    scanf("%s",newString);
                    length=strlen(newString);
                    newString[length]='\0';
                }
            }


            if(IsEmpty(extenSortedList))  //checks if the extendSortedList is empty or not
            {
                insertLast(extenSortedList, newString);
                insertLast(unsortedList,newString);//add the new string to the unsorted list

                isSorted=1;
                printf("\nThe new string has been added and successfully sorted.\nYou can print the list using operation 4.\n\n");
                break;
            }


            insertLast(unsortedList,newString);//add the new string to the unsorted list

            //delete lists to reuse them
            DeleteList(extenSortedList);
            DeleteList(extenUnsortedList);

            extendedString(unsortedList,extenUnsortedList);//add padding (zero) to the strings

            radixSort(extenUnsortedList);

            isSorted=1;

            printf("\nThe new string has been added and successfully sorted.\nYou can print the list using operation 4.\n\n");

            break;
        }

        case 6://delete a string from the sorted list
        {
            if(isRead==0)
            {
                printf("The strings are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }
            if((IsEmpty(extenSortedList))&&(IsEmpty(unsortedList)))  //list is empty
            {
                printf("The Strings list is empty; there is nothing to delete. You can add new strings and sort them in operation 5.\n\n");
                break;
            }


            if(isSorted==0)
            {
                printf("The list is currently unsorted; please execute operation 3 to sort it.\n\n");
                break;
            }



            //delete word
            char removeString[100];//I set the size to 100 to handle strings longer than 30 characters,for checking purpose.
            int length;
            printf("\nPlease input the string you want to delete from the list:\t");
            scanf("%s",removeString);
            length=strlen(removeString);
            removeString[length]='\0';

            while((length>MAX_LENG)||(!isalpha(removeString[0]))||(isLetDig(removeString)==0)) //if the input string dos not adhere to the specified strings rules
            {
                if(length >MAX_LENG) //checks if the string exceeds 30 or not
                {
                    printf("\nThe input string does not adhere to the specified string rules;it should not exceed 30 characters.\n");
                    printf("Please enter a new string of 30 characters or less to delete:\t");
                    scanf("%s",removeString);
                    length=strlen(removeString);
                    removeString[length]='\0';

                }
                else if(!isalpha(removeString[0])) //checks if the first char is letter or not
                {
                    printf("\nThe input string does not adhere to the specified string rules; it should starts with a character.\n");
                    printf("Please enter a new string that starts with a letter to delete:\t");
                    scanf("%s",removeString);
                    length=strlen(removeString);
                    removeString[length]='\0';
                }
                if(isLetDig(removeString)==0) //checks if the string char is letter or digit or both
                {
                    printf("\nThe input string does not adhere to the specified string rules; it should not have any symbols.\n\n");
                    printf("Please provide a new string without any symbols to delete:\t");
                    scanf("%s",removeString);
                    length=strlen(removeString);
                    removeString[length]='\0';
                }
            }


            int isExist=0; //checks if the string has been found in the list or not

            isExist=deleteNode(removeString); //delete the entered string from the extended sorted list

            //the entered string is not found
            if(isExist==0)
            {
                printf("\nThe entered string was not found.\nTo perform another deletion, select operation 6.\n\n");
                break;

            }
            //the entered string is exist

            deleteNode1(unsortedList,removeString);//update the unsorted list after deletion operation

            isSorted=1;

            printf("\nThe specified string has been successfully removed from the sorted list.\n\n");

            break;
        }

        case 7://print the lists in the output file
        {
            if(isRead==0)
            {
                printf("The strings are not currently loaded from the file.\nPlease execute operation 1 to load them before proceeding.\n\n");
                break;
            }

            if((isSorted==0)&&(!IsEmpty(unsortedList)))
            {
                printf("The list is currently unsorted.\nPlease execute operation 3 to sort the list before printing the string to the output file.\n\n");
                break;
            }
            if(IsEmpty(unsortedList)) //list is empty
            {
                printf("The sorted strings list is currently empty,hence there is nothing to print in the output file.\n");
                printf("You can add new strings to the sorted list and sort them in operation 5.\n\n");
                break;

            }



            printToOutputFile(extenSortedList);
            printf("The sorted strings have been successfully stored in the 'output.txt' file.\n\n");

            break;
        }
        default :
            printf("The operation entered is not valid. Please choose again..\n\n");//if the user input non valid op
        }
        displayMenu();
        scanf("%d",&op);

    }
    printf("\nYou have exited my program. Thank you for using it!!\n");

//Free the memory occupied by the doubly linked list upon program termination
    DeleteList(unsortedList);
    free(unsortedList);
    DeleteList(extenUnsortedList);
    free(extenUnsortedList);
    DeleteList(extenSortedList);
    free(extenSortedList);
    Node ptr;
    int i;

    for(i=0; i<63; i++)
    {
        ptr=characters[i]->next;
        if(ptr==NULL)
            continue;
        if(ptr!=NULL)
        {
            DeleteList1(characters[i]);
            free(characters[i]);

        }
    }


    return 0;
}

//////////CreateList//////////
/** @brief This Function creates the head of the doubly linked list.
 *
 *it creates the head (double pointer) using malloc ,then it checks if the head is exist.
 *then we assign NULL to its previous and next pointers.
 *
 *  @param L  double pointer of type List ,it will be the head of the doubly LL.
 *  @return double pointer (List).
 */
List CreateList()
{
    List L = (List)malloc(sizeof(struct node));

    if (L == NULL)
    {
        printf("The creation of a list is not possible due to insufficient memory space..\n");
        return NULL;
    }


    L->prev=NULL;
    L->next = NULL;

    return L;
}

//////////CreateList1//////////
/** @brief This Function creates the head of the doubly linked list.
 *
 *it creates the head (double pointer) using malloc ,then it checks if the head is exist.
 *then we assign NULL to its previous and next pointers.
 *
 *  @param L  double pointer of type List ,it will be the head of the doubly LL.
 *  @return double pointer (List).
 */
List1 CreateList1()
{
    List1 L = (List1)malloc(sizeof(struct node1));

    if (L == NULL)
    {
        printf("The creation of a list is not possible due to insufficient memory space..\n");
        return NULL;
    }

    L->prev=NULL;
    L->next = NULL;

    return L;
}

//////////Delete List//////////
/** @brief This Function removes the nodes from the doubly linked list.
 *
 *it checks if the list that we want to delete is exist and not empty
 *then we delete every node from the linked list using free function

 *  @param p pointer of type Node ,it points to a node within the linked list.
 *  @param temp pointer of type Node ,it points to a node within the linked list.
 *  @return Void.
 */
void DeleteList(List L)
{
    if(L== NULL)
    {
        printf("The linked list was not found..\n");
        return;
    }
    else if(IsEmpty(L))
    {
        //printf("The linked list is devoid of elements; hence,there's nothing to delete..\n");
        return;
    }

    Node p,temp;
    p=L->next;
    L->next= NULL;

    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p=temp;

    }
    return;

}

//////////DeleteList1//////////
/** @brief This Function removes the nodes from the doubly linked list.
 *
 *it checks if the list that we want to delete is exist and not empty
 *then we delete every node from the linked list using free function

 *  @param p pointer of type Node ,it points to a node within the linked list.
 *  @param temp pointer of type Node ,it points to a node within the linked list.
 *  @return Void.
 */
void DeleteList1(List1 L)
{


    if(L== NULL)
    {
        printf("The linked list was not found..\n");
        return;
    }
    else if(IsEmpty1(L))
    {
        //printf("The linked list is devoid of elements; hence,there's nothing to delete..\n");
        return;
    }

    Node p,temp;
    p=L->next;
    L->next= NULL;

    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p=temp;

    }
    return;
}
//////////isEmpty//////////
/** @brief This boolean Function checks if the linked list is empty.
 *
 *it checks if the head is pointing to a NULL or to a node , if it points to
 *a NULL then it's empty and return 1 ,otherwise it's not and return 0 .

 *  @return int.
 */
int IsEmpty(List L)
{
    return(L->next == NULL);
}

//////////isEmpty1//////////
/** @brief This boolean Function checks if the linked list is empty.
 *
 *it checks if the head is pointing to a NULL or to a node , if it points to
 *a NULL then it's empty and return 1 ,otherwise it's not and return 0 .

 *  @return int.
 */
int IsEmpty1(List1 L)
{
    return(L->next == NULL);
}
//////////printList//////////
/** @brief This Function prints the contents of a doubly linked list.
 *
 *it checks if the list that we want to print is exist and not empty

 *  @param temp pointer of type Node ,it points to a node within the linked list.
 *  @return Void.
 */
void printList(List L)
{

    if(L==NULL)
    {
        printf("The linked list was not found..\n");
        return;
    }
    else if(IsEmpty(L))
    {
        printf("The linked list is empty..\n");
        return;
    }

    Node temp;
    temp=L->next;
    while(temp != NULL)
    {
        printf("%s\n",temp->data);
        temp=temp->next;
    }
    printf("\n");


}
//////////insertLast//////////
/** @brief This Function adds nodes to the back of the string doubly LL.
 *
 *it checks if the list that we want to print is exist ,and checks if the new node we created is exists.
 *it also check if the list is empty or not for the purpose of adding a node to an empty list.

 *  @param ptr pointer of type Node ,it points to a node within the linked list.
 *  @return Void.
 */
void insertLast(List L, char s [MAX_LENG])
{


    Node ptr;
    Node newNode = (Node)malloc(sizeof(struct node));
    strcpy(newNode->data,s);
    newNode->prev=NULL;
    newNode->next=NULL;

    if(L== NULL)
    {
        printf("The linked list was not found..\n");
        return;
    }
    else if (newNode == NULL)
    {
        printf("There is no memory space remaining..\n");
        return;
    }
    else if(IsEmpty(L))
    {
        L->next= newNode;
        newNode->prev = L;
        newNode->next = NULL;
        return;
    }
    ptr= L->next;

    while(ptr->next != NULL)
    {
        ptr=ptr->next;

    }
    ptr->next = newNode;
    newNode->prev=ptr;
    newNode->next=NULL;

}

//////////insertLast1//////////
/** @brief This Function adds nodes to the back of the character doubly LL.
 *
 *it checks if the list that we want to print is exist ,and checks if the new node we created is exists.
 *it also check if the list is empty or not for the purpose of adding a node to an empty list.

 *  @param ptr pointer of type Node1 ,it points to a node within the linked list.
 *  @return Void.
 */
void insertLast1(List1 L, char s[MAX_LENG])
{

    Node ptr;
    Node newNode = (Node)malloc(sizeof(struct node));
    strcpy(newNode->data,s);
    newNode->prev=NULL;
    newNode->next=NULL;

    if(L== NULL)
    {
        printf("The linked list was not found..\n");
        return;
    }
    else if (newNode == NULL)
    {
        printf("There is no memory space remaining..\n");
        return;
    }
    else if(IsEmpty1(L))
    {
        L->next= newNode;
        newNode->prev = L;
        newNode->next = NULL;
        return;
    }
    ptr= L->next;

    while(ptr->next != NULL)
    {
        ptr=ptr->next;

    }

    ptr->next = newNode;
    newNode->prev=ptr;
    newNode->next=NULL;

}
//////////readInputFile//////////
/** @brief This Function read the strings line by line that are inside the file and store them in a doubly linked list.
 *
 *it also checks if the file is exist or not.
 *

 *  @param in pointer to input file.
 *  @param fileName[100] String to store file name.
 *  @param str[31] string with maximum length (30)+ the string terminate '\0'
 *  @return List.
 */

List readInputFile()
{

    FILE* in;
    char fileName[100];
    printf("Please provide the name of the input file:\t");
    scanf("%s",fileName);

    in= fopen(fileName,"r");
    while(in==NULL) //If the file does not exist
    {

        printf("Unable to open the file. The file does not exist.\n\n");
        printf("Please provide the name of the input file:\t");
        scanf("%s",fileName);
        in= fopen(fileName,"r");
    }
    List L = CreateList();
    DeleteList(L);

    char str[100];//I set the size to 100 to handle strings longer than 30 characters,for checking purpose.
    int length;
    while(fgets(str,sizeof(str),in)) //Read lines one by one and store each string in the list "L"
    {

        if(isLetDig(str)) //checks if the string is only numbers or letters or both
        {

            length=wordLength(str);

            if((length <=30))  // checks if the strings is 30 char or less
            {
                if((isalpha(str[0])))//checks if the first char is a letter or not
                {
                    str[length]='\0';
                    insertLast(L,str);

                }
            }
        }
    }

    return L;
    fclose(in);
}


//////////printToOutputFile//////////
/** @brief This Function print the sorted strings list to the output file.
 *
 *  @param out pointer to input file.
 *  @param ptr pointer of type Node , points to the head of the requested list
 *  @return Void.
 */
void printToOutputFile(List L)
{
    FILE * out;
    out=fopen("output.txt","w");

    Node ptr=L->next;
    while(ptr!=NULL)
    {
        fprintf(out,"\n\n");
        fflush(out);

        fprintf(out,"%s\n",ptr->data);
        fflush(out);
        ptr=ptr->next;

    }


}


//////////displayMenu//////////
/** @brief This function presents a menu of operations.
 *
 *  @return Void.
 */
void displayMenu()
{
    printf("\n\nPlease select the option number for the action you wish to perform:\n\n");
    printf("1- Load the strings from a file\n");
    printf("2- Print the strings before sorting\n");
    printf("3- Sort the strings\n");
    printf("4- Print the sorted strings\n");
    printf("5- Add a new word to the list of sorted strings [and sort it]\n");
    printf("6- Delete a word from the sorted strings\n");
    printf("7- Save the output file\n");
    printf("8- Exit\n");
    printf("\n");
}

//////////MaxLengString//////////
/** @brief This function locates the longest string.
 *
 *  @param max integer ,store the max length of strings.
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @return Void.
 */
int MaxLengString(List L)
{
    if(L== NULL)
    {
        printf("The linked list was not found..\n");
        return;
    }
//    else if(IsEmpty(L))
//    {
//        printf("The linked list is devoid of elements; hence,there's nothing to delete..\n");
//        return;
//    }
    int max=-1, index=0;
    Node ptr=L->next;
    while(ptr !=NULL)
    {
        while((isalpha(ptr->data[index]))||(isdigit(ptr->data[index]))) //while the char is letter or number
        {
            index++;
        }
        if(max<=index)
        {
            max=index;
        }
        index=0;
        ptr=ptr->next;
    }


    return max;

}

//////////extendedString//////////
/** @brief This function appends (*) to strings that are shorter than the maximum length string,
 * ensuring uniform string length for the sorting process.
 *
 *  @param length integer ,store the max length of strings.
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @param i integer ,to use in the for loop
 *  @return Void.
 */
void extendedString(List Ls,List Ld)
{

    copyTwoLists(Ls,Ld);//makes copy of the unsorted list to add the zeros to it and use it on the sorting process

    Node ptr = Ld-> next;
    int max = MaxLengString(Ld);

    int length,i;
    while(ptr != NULL)
    {
        length = wordLength(ptr->data);//get the length of the string

        if(length != max)
        {
            for(i=length; i<max; i++)
            {
                ptr->data[i]='*';
            }
            ptr->data[max]='\0';//adds null terminate at the end of the string

        }
        ptr=ptr->next;
    }


}

//////////copyTwoLists//////////
/** @brief This function duplicates the contents of the source list and stores them in the destination list.
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @return Void.
 */
void copyTwoLists(List Ls, List Ld)
{


    DeleteList(Ld);//make the destination list empty to add the contents of the source list in it
    Node ptr=Ls->next; //pointer to the first string

    while(ptr!=NULL)
    {
        insertLast(Ld,ptr->data);//adds the strings
        ptr=ptr->next;
    }

}



//////////deletepadding//////////
/** @brief This function removes the stars (that were added in the extendedString function)after the sorting process
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @param max integer ,store the max length of strings.
 *  @param i integer ,to use it in the for loop
 *  @return Void.
 */
void deletepadding(List L)
{

    int max=MaxLengString(L);

    int count=0,i;

    Node ptr=L->next; //pointer to the first string in the sorted list
    while(ptr!=NULL)
    {
        for(i=0; i<=max; i++)
        {
            if(ptr->data[i]!='*')
            {
                ptr->data[count]=ptr->data[i];
                count++;
            }
            else//if ptr-> data == '0'
                break;
        }

        ptr->data[count]='\0';//adds the null terminate

        count=0;
        ptr=ptr->next;
    }


}

//////////radixSort//////////
/** @brief This function employs the radix sort algorithm to sort a list of strings.
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @param max integer ,store the max length of strings.
 *  @param j,i integer , use it in the for loop.
 *  @param letter character, store the character of a string.
 *  @param Sindex integer, use it as an index for a string(array of char).
 *  @param Cindex integer, use it as an index for the character array.
 *  @return Void.
 */
void radixSort(List L)
{


    if(L==NULL)
    {
        printf("The specified linked list for sorting could not be located..\n\n");
        return;
    }
    else if(IsEmpty(L))
    {
        //printf("No elements were found in the linked list you intend to sort..\n\n");
        return;
    }
    else if(L->next->next==NULL)   //has one element
    {

        //printf("The linked list you desire to sort contains only one element, making it already in sorted order..\n\n");
        return;
    }

    //If the List has at least two strings

    //initialize the character list -alphabet-
    characters[0]=CreateList1();
    characters[0]->data='*';

//ASCII ordering
    int j;
    char digit='0';
    for(j=1; j<11; j++)
    {
        characters[j]=CreateList1();
        characters[j]->data=digit;
        digit+=1;
    }

    char let='A';

    for( j=11; j<37; j++)
    {
        characters[j]=CreateList1();
        characters[j]->data=let;
        let+=1;


    }
    let='a';
    for(j=37; j<63; j++)
    {
        characters[j]=CreateList1();
        characters[j]->data=let;
        let+=1;


    }



    Node ptr=L->next; //pointer to the first string


    int max=MaxLengString(L);//get the maximum length of the string lists for the sorting process


    char letter;
    int Sindex=max-1; //starts at the LS character of the string
    int Cindex=0, i=0;

    for( i=0; i<max; i++)
    {

        while(ptr!=NULL)
        {
            letter=ptr->data[Sindex];

            while((letter != characters[Cindex]->data))
            {
                Cindex++;

            }

            insertLast1(characters[Cindex], ptr->data);//Inserts the string at the appropriate position in the characters array list.

            Cindex=0;
            ptr=ptr->next;
        }



        Sindex--;//decrease the string index by one
        sortList(L);

        ptr=L->next; //pointer to the first string

    }

    copyTwoLists(L, extenSortedList); //sorted strings will be stored in extendedSortedList
    deletepadding(extenSortedList);//Remove the padding (zeros) after completing the sorting process.

}
//////////sortList//////////
/** @brief Function to transfer the strings from the characters array list to list L for re-sorting.
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @param i integer , use it in the for loop.
 *  @return Void.
 */
void sortList(List L)
{


    Node ptr;
    int i;

    for( i=0; i<63; i++)
    {
        ptr=characters[i]->next;

        if(ptr==NULL)  //empty list
        {
            continue;
        }
        while(ptr!=NULL)
        {
            insertLast(extenSortedList, ptr->data);
            ptr=ptr->next;
        }
        DeleteList1(characters[i]);//to make the characters[i] empty to reuse it again

    }

    copyTwoLists(extenSortedList, L);//strings list will be stored in L
    DeleteList(extenSortedList);//to reuse it again
}

//////////deleteNode//////////
/** @brief Boolean function for removing a specified string from the sorted list,
 * and indicating whether it was successfully deleted or not.
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @param isRemoved integer , use it as a flag to store if the node was successfully removed or not.
 *  @return int.
 */
int deleteNode (char word[MAX_LENG])
{
    int isRemoved=0;//checks if the specified word has been deleted or not
    if(extenSortedList== NULL)
    {
        printf("The specified linked list for deletion could not be located..\n\n");
        return isRemoved;
    }
    else if(IsEmpty(extenSortedList))
    {
        //printf("The linked list is devoid of elements; hence,there's nothing to delete..\n");
        return isRemoved;
    }

    Node ptr=extenSortedList->next;
    while(ptr != NULL)
    {
        if((strcmp(ptr->data,word))==0)  //checks if the requested word for deletion equal the data from the sorted list
        {
            if(ptr->prev == NULL)//first node
            {
                extenSortedList->next=ptr->next;
                ptr->next->prev=extenSortedList;
                free(ptr);
                isRemoved=1;//successfully removed
                return isRemoved;
            }
            if(ptr->next== NULL)//last node
            {
                ptr->prev->next=NULL;
                free(ptr);
                isRemoved=1;

                return isRemoved;
            }

            ptr->prev->next= ptr->next;
            ptr->next->prev=ptr->prev;
            free(ptr);
            isRemoved=1;
            return isRemoved;
        }
        ptr=ptr->next;
    }
    return isRemoved;

}

//////////wordLength//////////
/** @brief Function that calculates the length of a provided string.
 *
 *  @param index integer, use it as an index for the string word
 *  @param count integer, use it to count the number of string's characters
 *  @return int.
 */
int wordLength ( char word[MAX_LENG])
{
    int index=0, count=0;
    while((isalpha(word[index]))|| (isdigit(word[index]))) //if the char is a letter or number
    {
        count++;
        index++;
    }
    return count;
}

//////////deleteNode1//////////
/** @brief  Function for removing a specified string from a list.
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @return void.
 */
void deleteNode1(List L,char word[MAX_LENG+1])
{


    if(L== NULL)
    {
        printf("The linked list was not found..\n\n");
        return;
    }
    else if(IsEmpty(L))
    {
        //printf("The linked list is devoid of elements; hence,there's nothing to delete..\n\n");
        return;
    }

    Node ptr=L->next;
    while(ptr != NULL)
    {
        if((strcmp(ptr->data,word))==0)
        {
            if(ptr->prev == NULL)//first node
            {
                L->next=ptr->next;
                ptr->next->prev=L;
                free(ptr);
                return;
            }
            if(ptr->next== NULL)
            {
                ptr->prev->next=NULL;
                free(ptr);
                return;
            }

            ptr->prev->next= ptr->next;
            ptr->next->prev=ptr->prev;
            free(ptr);
            return;
        }
        ptr=ptr->next;
    }

}
//////////getSize//////////
/** @brief Function that calculates the size of a provided list.
 *
 *  @param ptr pointer of type Node , points to the nodes of the doubly LL.
 *  @param count integer, use it to count the number of the list's nodes
 *  @return int.
 */
int getSize(List L)
{
    if(L== NULL)
    {
        printf("The linked list was not found..\n\n");
        return;
    }
    else if(IsEmpty(L))
    {
        printf("The linked list is empty..\n\n");
        return 0;
    }
    int count=0;
    Node ptr=L;
    while(ptr->next != NULL)
    {
        count++;
        ptr=ptr->next;
    }
    return count;

}

//////////isLetDig//////////
/** @brief Boolean function that checks if the string contains only letters or numbers or both.
 *
 *  @param i integer, use it in the for loop.
 *  @return int.
 */
int isLetDig(char word[MAX_LENG])
{
    int i;

    for(i=0; i<(strlen(word)-1); i++)
    {

        if(!isalnum(word[i])) //if the char is not letter or digit
        {
            return 0;
        }
    }


    return 1;

}
