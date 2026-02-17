## Address-Book-Application-C

# Overview

A console-based Address Book application developed using structured C programming. The program enables persistent storage of contact records using file handling techniques.

# Features

Add new contacts

Search contact by name

Edit existing records

Delete contact

Persistent storage using file I/O

# Project Structure
main.c        – Program entry point  
contact.c     – Contact-related operations  
file.c        – File handling logic  
validate.c    – Input validation functions  
Makefile      – Build configuration  

# Technical Concepts Used

Structures

Dynamic memory allocation (malloc, free)

File handling (fopen, fread, fwrite)

Modular programming

String manipulation

Build & Run

Using Makefile:

make
./a.out


Or manually:

gcc main.c contact.c file.c validate.c -o addressbook
./addressbook

# Learning Outcomes

Practical implementation of persistent storage

Memory management in C

Structured modular program design
