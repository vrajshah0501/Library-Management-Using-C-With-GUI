# Library Management with C
To run this code you need to install the development package GTK. The package name may vary depending on your Linux distribution.

Running GTK applications on Windows requires some additional setup. GTK is primarily designed for Unix-like systems, but it can be used on Windows with the help of the GTK development environment called MSYS2.

Here are the general steps to set up MSYS2 and compile the provided GTK code on Windows:

Install MSYS2:
Download the MSYS2 installer from the official website.
Follow the installation instructions on the website.

Update MSYS2:
Open the MSYS2 terminal and run the following commands to update the package database and core system components:
pacman -Syu

Install necessary packages:
Install the required development packages for GTK. In the MSYS2 terminal, run:
pacman -S mingw-w64-x86_64-gtk3

Compile the code:
Open the MSYS2 terminal in the directory containing your source code.
Compile the code using the following command:
gcc -o your_program_name your_source_code.c `pkg-config --cflags --libs gtk+-3.0`
Replace your_program_name with the desired name for the compiled executable and your_source_code.c with the name of your source code file.

Run the executable:
After successful compilation, you can run the program using:
./your_program_name

Please note that the exact steps might vary depending on your specific environment. If you encounter any issues or have further questions, feel free to ask!
