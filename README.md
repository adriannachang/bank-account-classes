# bank-account-classes
Virtual banking program made for my ICS4U class, making use of reading/writing to binary and classes. It was coded in Dev C++.

This program stores banking account information for two users, Rob and Shirley King. 

UPON INITIATION, PROGRAM WILL ASK FOR ACCOUNT NUMBER AND PASSWORD. User must enter following information:
Account number: 56897-2225678
Account password: W5tr@43

After being granted access, the user may select what they would like to do from a list of options: they may view the account information (read from the binary file), perform a transaction, or change the account information.

Accepted values:
Account #: char array (size 14)
Account Password (char size 8)
Owner Name (char size 20)
Joint Owner Name (char size 20)
Owner SSN (char size 12)
Joint Owner SSN (char size 12)
Account Balance (double)

CHALLENGES FACED:
This was our first project dealing with classes in ICS4U; I struggled with the concept initially, especially in terms of deriving classes from other classes. Although it took me a little while to sort out dealing with classes and having functions inside classes, this program was definitely a great learning experience for me.

MOST PROUD OF:
Making use of reading/writing information to binary files to increase the functionality of the program. Although it wasn't required for the assignment, I modified the program so that the user could alter the program's banking information and have it all saved to a binary file.
