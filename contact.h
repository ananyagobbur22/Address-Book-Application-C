#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100  // max number of contacts we can store

/*  Contact struct
Stores details of a single contact
name, phone, email */
typedef struct {
    char name[50];   // contact name
    char phone[20];  // contact phone number
    char email[50];  // contact email
} Contact;

/* AddressBook struct
Stores multiple contacts
Keeps track of how many contacts we have */
typedef struct {
    Contact contacts[100];  // array of contacts
    int contactCount;       // number of contacts currently stored
} AddressBook;

/* validate_name()
Checks if the name has only letters and spaces
Returns 1 if valid, 0 if invalid */
int validate_name(char name[]);

/* validate_phonenumber()
Checks if phone is exactly 10 digits and unique
Returns 1 if valid, 0 if invalid */
int validate_phonenumber(char phone[], AddressBook *addressBook);

/* validate_email()
Checks email format and uniqueness 
Returns 1 if valid, 0 if invalid */
int validate_email(char email[], AddressBook *addressBook);

/* createContact()
Adds a new contact to the address book
Asks user for name, phone, email */
void createContact(AddressBook *addressBook);

/* searchContact()
Searches for a contact by name, phone, or email
Returns 1 if found, -1 if not */
int searchContact(AddressBook *addressBook);

/* editContact()
 Lets user edit name, phone, or email of a contact
 Returns 1 if edited successfully, 0 if failed */
int editContact(AddressBook *addressBook);

/* deleteContact()
 Deletes a contact by index */
void deleteContact(AddressBook *addressBook);

/* listContacts()
 Displays all contacts
 Can sort by name, phone, or email */
void listContacts(AddressBook *addressBook, int sortCriteria);

/* initialize()
Sets contact count to 0
Loads contacts from file if available */
void initialize(AddressBook *addressBook);

/* saveContactsToFile()
Saves all contacts to a file */
void saveContactsToFile(AddressBook *AddressBook);

#endif
