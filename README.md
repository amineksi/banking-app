# Simple Banking Application in C

## Overview

This is a simple banking application written in C that operates through the terminal. It supports basic banking functionalities like creating accounts, depositing and withdrawing money, and checking account balances. The application is designed to provide a straightforward interface for managing bank accounts using standard terminal input and output.

## Features

- **Create Accounts:** Register new user accounts.
- **Login:** Secure login functionality for users.
- **Deposit Money:** Add funds to your account.
- **Send Money:** Send funds to other users accounts.
- **Check Balance:** View the current balance of your account.

## Requirements

- GCC Compiler (for compiling the C source code)
- Terminal (for running the application)

## Compilation and Running

To compile the program, open your terminal and navigate to the directory containing the source code files. Run the following commands to compile:

```sh
cc main.c connected.c login.c accounts.c welcome.c register.c -o banking_app
```
This will compile the source files and create an executable file named banking_app.

## Running the Application

Once the program is compiled, you can run the application by executing the following command in your terminal:

```sh
./banking_app
```

## File Structure

- **main.c:** The main entry point for the application. Handles initial program execution.
- **connected.c:** Manages operations available after a user has logged in.
- **login.c:** Handles user login functionality.
- **accounts.c:** Manages account-related operations like creating accounts and checking balances.
- **welcome.c:** Displays the welcome message.
- **register.c:** Manages the user registration process.

## Contributing

If you wish to contribute to this project, please fork the repository and submit a pull request. Your contributions are greatly appreciated!

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contact
For any questions or feedback, please contact me at [amine.kass35@gmail.com].
