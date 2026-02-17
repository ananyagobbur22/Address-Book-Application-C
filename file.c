#include <stdio.h>
#include <string.h>
#include "file.h"
#include "contact.h"

/* saveContactsToFile()
Saves all contacts from AddressBook into a CSV file.
Sorts contacts by name before saving (for neatness).
First line of file stores the number of contacts.
Each line stores name, phone, email separated by commas. */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *ptr = fopen("contact.csv", "w");  // open file for writing
    if (ptr == NULL)                        
    {
        printf("Error opening file\n");
        return;
    }

    fprintf(ptr, "%d\n", addressBook->contactCount);  // write count first

    // copy contacts into a temp array for sorting
    Contact temp[100];
    for (int i = 0; i < addressBook->contactCount; i++) {
        temp[i] = addressBook->contacts[i];
    }

    // bubble sort contacts by name
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (strcmp(temp[j].name, temp[j+1].name) > 0) {
                Contact t = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = t;
            }
        }
    }

    // write sorted contacts to file
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(ptr, "%s,%s,%s\n",
                temp[i].name,
                temp[i].phone,
                temp[i].email);
    }

    fclose(ptr); // close the file
}

/* loadContactsFromFile()
Reads contacts from the CSV file into AddressBook.
First line of file should have the number of contacts.
Each subsequent line contains name, phone, email separated by commas.
If file doesn’t exist or format is wrong, sets contactCount to 0. */
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contact.csv", "r");  // open file for reading
    if (fptr == NULL)                        
    {
        addressBook->contactCount = 0;     // no file, so start empty
        return;
    }

    int count;

    // read the number of contacts from first line
    if (fscanf(fptr, "%d\n", &count) != 1)
    {
        printf("Error: invalid file format\n");
        fclose(fptr);
        addressBook->contactCount = 0;
        return;
    }

    addressBook->contactCount = count;  // set count

    // read each contact line
    for (int i = 0; i < count; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fptr); // close the file
}
