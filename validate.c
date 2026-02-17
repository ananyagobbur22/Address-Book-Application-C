#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

/* validate_name()
Checks if the name contains only letters and spaces
Returns 1 if valid, 0 if invalid
Helps avoid weird characters in contact names */
int validate_name(char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        // if not a letter and not a space, fail
        if (!(isalpha(name[i]) || name[i] == ' '))
        {
            return 0;  
        }
    }
    return 1;  // when passes all validations
}

/* validate_phonenumber()
 Checks if phone has only digits
 Must be exactly 10 digits
 Also ensures no duplicate phone in address book
 Returns 1 if valid, 0 if invalid */
int validate_phonenumber(char *phone, AddressBook *addressBook)
{
    int i, len = 0;

    // check each character
    for (i = 0; phone[i] != '\0'; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return 0;  // invalid char
        }
        len++;
    }

    // checks length
    if (len != 10) 
    {
        return 0;  // if not 10 digits
    }
    
    // checks duplicates
    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 0; // if phone already exists
        }
    }

    return 1;  // when it passes all
}

/* validate_email()
 Ensures email has no uppercase letters or spaces
 Checks for '@' and '.' in correct positions
 Makes sure no duplicate email exists
 Returns 1 if valid, 0 if invalid */
int validate_email(char *email, AddressBook *addressBook)
{
    // check for uppercase letters or spaces in mail
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (isupper(email[i]) || email[i] == ' ')
        {
            return 0;  
        }
    }

    // basic email structure to check
    char *at = strchr(email, '@');
    char *dot = strrchr(email, '.');

    if (at == NULL || dot == NULL) return 0;      // must have @ and .
    if (dot < at) return 0;                       // dot must be after @
    if (at == email) return 0;                    // can't start with @
    if (*(dot + 1) == '\0') return 0;            // something after dot

    // checks duplicates
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0)
        {
            return 0;  // if email already exists
        }
    }

    return 1;  // when email is valid
}