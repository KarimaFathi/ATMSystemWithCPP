# ATMSystemWithCPP

## Description

This is a basic ATM simulation program built in C++. It allows users to log in using their account number and pin code, and then access various banking functionalities such as:
- Checking account balance
- Withdrawing money (both normal and quick withdrawals)
- Depositing money
- Logging out

The program works by reading and writing user data from a text file (`clients.txt`), which stores information such as account number, pin code, name, phone number, and account balance.

## Features

- **Login System**: The user can log in with their account number and pin code.
- **Main Menu**: After login, the user can access a menu that allows them to choose between different banking options such as quick withdraw, normal withdraw, deposit, check balance, and log out.
- **Withdraw Options**:
  - **Quick Withdraw**: Predefined withdrawal amounts (20, 50, 100, etc.).
  - **Normal Withdraw**: Allows the user to withdraw any multiple of 5.
- **Deposit**: The user can deposit money into their account.
- **Balance Check**: The user can view their current balance.
- **Data Persistence**: User data is read from and written back to a file (`clients.txt`).


## Demonstation Video

You can view a quick video demonstration of the ATM system in action. The video showcases how the system works and walks through the core features.

https://github.com/user-attachments/assets/2f8f75a4-b952-4973-9d53-d1a3c1c6c1c9

