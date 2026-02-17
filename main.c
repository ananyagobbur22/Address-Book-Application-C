#include <stdio.h>
#include <stdlib.h>
#include "contact.h"
#include "file.h"

/* Main Function:
 1. This is where the whole program starts running.
 2. Shows a menu to the user (create, search, edit, delete, etc).
 3. Calls the respective function depending on what user chooses.
 4. Keeps looping until user chooses to exit. */

int main() {
    int choice;   // stores user input for menu options
    AddressBook addressBook;  

    initialize(&addressBook); // load contacts from file at the beginning
    

    do {
        // display menu every time
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save contacts\n");		
        printf("7. Exiting\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        // run the option selected by user
        switch (choice) {
            case 1:
                createContact(&addressBook);   // add a new contact
                break;
            case 2:
                searchContact(&addressBook);   // find an existing contact
                break;
            case 3:
                editContact(&addressBook);     // edit/update details
                break;
            case 4:
                deleteContact(&addressBook);   // remove contact
                break;
            case 5:          
                listContacts(&addressBook,1);  // show contacts (default by name)
                break;
            case 6:
                printf("Saving the contacts...\n");
                saveContactsToFile(&addressBook); // write data to file
                break;
            case 7:
                printf("Exiting ...\n");
                exit(0); // end program
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (1);  // infinite loop until user exits
       
    return 0; // end of program
}