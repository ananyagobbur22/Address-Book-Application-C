/*-------------------------------------------------------
 Project  : Address Book
 Name     : Ananya Gobbur
 Date     : 25-09-2025

 Description:
   A simple Address Book program where we can 
   add, search, edit, delete, and list contacts. 
   It also saves the contacts to a file.

Sample Input:
Aditya,2222222222,aditya@gmail.com
Ambika,0987654321,alice@example.com
Ananya,1234567890,ananya@gmail.com
Bob Johnson,1112223333,bob@company.com
Carol White,4445556666,carol@company.com
David Miller,2223334444,david.miller@example.com
Eve Adams,5556667777,eve.adams@example.com
Frank Harris,9998887777,frank.harris@company.com
Grace Lee,3334445555,grace.lee@example.com
Harshi,9480378044,hvhn@gmail.com
Henry Clark,7778889999,henry.clark@company.com
Ivy Wilson,6667778888,ivy.wilson@example.com
John,1234567890,john@example.com

Sample Output: 
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exiting
Enter your choice: 1
Enter the details:
Enter the Name: Gururaj
Enter the phonenumber: 9797979797
Enter the mailid: gururajgobbur@gmail.com
Contact added successfully

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exiting
Enter your choice: 6
Saving the contacts...

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exiting
Enter your choice: 7
Exiting ...
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

/* listContacts()
 Shows contacts sorted by name/phone/email
 Makes a temp copy so original order won’t get messed
 Uses bubble sort for sorting (simple approach)
 Finally prints the sorted list*/

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    int sort;
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available.\n");  // if empty
        return;
    }

    // ask the user on what basis to sort
    printf("List contacts by:\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &sort);

    // make a copy of contacts 
    Contact temp[100];
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        temp[i] = addressBook->contacts[i];
    }

    // use bubble sort logic
    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) 
        {
            int cmp = 0;

            if (sort == 1) 
            {
                cmp = strcmp(temp[j].name, temp[j + 1].name); // comparing by name
            } 
            else if (sort == 2) 
            {
                cmp = strcmp(temp[j].phone, temp[j + 1].phone); // comparing by phone
            } 
            else if (sort == 3) 
            {
                cmp = strcmp(temp[j].email, temp[j + 1].email); // comparing by email
            }

            // swap if not in order
            if (cmp > 0) 
            {
                Contact t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    // printing the sorted list
    printf("\nContacts:\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%d. %s %s %s\n", i + 1,
               temp[i].name, temp[i].phone, temp[i].email);
    }
}

/* saveAndExit()
 Saves all contacts into the file
 Then exits the program safely */
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);   // saving the contact
    exit(EXIT_SUCCESS);                // exiting from the program
}

/* initialize()
 Initializes the contact book
 Sets initial count to 0
 Loads any existing contacts from file*/
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;     // start with zero contactCount
    loadContactsFromFile(addressBook); // load contacts
}

/* createContact()
 Takes input of name, phone, email
 Validates each one
 If valid, adds it to the list */
void createContact(AddressBook *addressBook)
{
    char name[50];
    char phonenumber[20];
    char mail[50];

    printf("Enter the details: \n");
    printf("Enter the Name: ");
    getchar();  // clear buffer
    scanf(" %[^\n]", name);

    // validate name
    int validation = validate_name(name);
    if(!validation)
    {
        printf("Invalid name\n");
        return;
    }

    // phone number input
    printf("Enter the phonenumber: ");
    scanf("%s", phonenumber);   
    validation = validate_phonenumber(phonenumber, addressBook);
    if(!validation)
    {
        printf("Invalid phone number\n");
        return;
    }

    // email id input
    printf("Enter the mailid: ");
    scanf("%s", mail);
    validation = validate_email(mail, addressBook);
    if(!validation)
    {
        printf("Invalid email\n");
        return;  
    }

    // storing the new contact into the struct
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phonenumber);
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    printf("Contact added successfully\n");
    addressBook->contactCount++;  // count increments
}

/* searchContact()
 Allows user to search by name/phone/email
 Prints details if found
 Returns 1 if success, -1 if not found */
int searchContact(AddressBook *addressBook) 
{
    int input, flag = 0, found = 0;
    char inputname[50];
    char inputphone[20];
    char inputmail[50];

    // menu to choose search 
    printf("1.Search by Name:\n2.Search by Phone:\n3.Search by Mail:\n");
    scanf("%d", &input);
    getchar();

    if(input == 1)
    {
        flag = 1;
        printf("Enter the name to be searched: ");
        scanf("%[^\n]", inputname);

        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(inputname, addressBook->contacts[i].name) == 0)
            {
                printf("%d %s %s %s\n", i,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    }
    else if(input == 2)
    {
        flag = 1;
        printf("Enter the phone number to be searched: ");
        scanf("%s", inputphone);

        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(inputphone, addressBook->contacts[i].phone) == 0)
            {
                printf("%d %s %s %s\n", i,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    }
    else if(input == 3)
    {
        flag = 1;
        printf("Enter the mail to be searched: ");
        scanf("%s", inputmail);

        for(int i=0; i<addressBook->contactCount; i++)
        {
            if(strcmp(inputmail, addressBook->contacts[i].email) == 0)
            {
                printf("%d %s %s %s\n", i,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
                found = 1;
            }
        }
    }

    // if invalid option or empty data
    if(flag == 0 || addressBook->contactCount == 0)
    {
        printf("Data not found\n");
        return -1;
    }

    // if nothing matches
    if(found == 0)
    {
        printf("Contact not found\n");
        return -1;
    }

    return 1; 
}

/* editContact()
 First searches for contact
 Then asks which field (name/phone/email) to edit
 Validates new value before updating */
int editContact(AddressBook *addressBook)
{
    int ret = searchContact(addressBook); 
    if(ret == -1)
    {
        return 0; // didn't find contact to edit
    }

    int i, input1;
    char name1[50], phone1[20], email1[50];

    printf("Enter the index of the contact you want to edit: ");
    scanf("%d", &i);
    getchar();

    // check if the given index is valid
    if(i < 0 || i >= addressBook->contactCount)
    {
        printf("Invalid index\n");
        return 0;
    }

    // menu to choose 
    printf("What do you want to edit: 1.name\n2.phonenumber\n3.email\n");
    scanf("%d", &input1);
    getchar();

    if(input1 == 1)
    {
        printf("Enter the new name: ");
        scanf("%[^\n]", name1);
        if(validate_name(name1) == 1)
        {
            strcpy(addressBook->contacts[i].name, name1);
        }
        else
        {
            printf("Edit failed, invalid name\n");
        }
    }
    else if(input1 == 2)
    {
        printf("Enter the new phone number: ");
        scanf("%s", phone1);
        if(validate_phonenumber(phone1, addressBook) == 1)
        {
            strcpy(addressBook->contacts[i].phone, phone1);
        }
        else
        {
            printf("Edit failed, invalid phone number\n");
        }
    }
    else if(input1 == 3)
    {
        printf("Enter the new email: ");
        scanf("%s", email1);
        if(validate_email(email1, addressBook) == 1)
        {
            strcpy(addressBook->contacts[i].email, email1);
        }
        else
        {
            printf("Edit failed, invalid email\n");
        }
    }
    else
    {
        printf("Invalid choice\n");
        return 0;
    }

    printf("Contact updated successfully\n");
    return 1;
}

/* deleteContact()
 Searches for the contact to delete
 Asks for index
 Shifts all contacts after it to fill gap
 Decreases total count */
void deleteContact(AddressBook *addressBook)
{
    int ret = searchContact(addressBook); 
    if(ret == -1)
    {
        return; // if there is no contact to delete
    }

    int i;
    printf("Enter the index of the contact you want to delete: ");
    scanf("%d", &i);
    getchar();

    // invalid index
    if(i < 0 || i >= addressBook->contactCount)
    {
        printf("Invalid index\n");
        return;
    }

    // shifting contacts left
    for(int j=i; j<addressBook->contactCount-1; j++)
    {
        addressBook->contacts[j] = addressBook->contacts[j+1];
    }
    addressBook->contactCount--; 

    printf("Contact deleted successfully\n");
}