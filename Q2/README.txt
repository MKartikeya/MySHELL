Hello! to run MyShell please go through this README.txt file.


Setting the environment required:
1)I've used 'readline' libraries to make things simple for taking input and adding into history.
    To install install readline libraries run the following command in the Terminal.
    
    sudo apt- get install libreadline8 libreadline-dev

Running the code:
1)The folder has makefile which contains the set of instructions to convert files into assembly level code.
2)Run 'makefile' in terminal in the respective directory.
3)The final assembly level code is stored in myshell.o .Run './myshell' to start the program.
4)We can use 'make clean' to remove all .o files.
Note: All the files below are required for compilation.

Folder Structure:
->The assignment folder consists of :
1)README.txt: This current file.
2)main.c: It contains the main function.
3)makefile: To complile all files together.
4)myheader.h: It contains the function declarations for main.c.
5)Function files: mycp.c mygrep.c myls.c myms.c myps.c: They contain the functions to execute respective commands.
6)Help files: help.txt mycp_help.txt mygrep_help.txt myls_help.txt myms_help.txt myps_help.txt : They contain content of help of respective commands.

Commands:
The following commands have been implemented with each of atleast four-five variations.
1)ls
2)cp
3)mv
4)ps
5)grep
6)Basic 'cd' is also implemented along with 'clear'.

Note:/************ 1)More info regarding commands are present in "help.txt" or running 'help'.********************/
2)Please note that all commands may not be implemented to exact parfection as the terminal like, color,error displaying,etc.There can be few differences in the commmands. More variations can be implemented can be implemented just with few more lines the difference is only in printing. 
3)PREFER FULL SCREEN TO GET PROPER ALIGNMENT OF TEXT.

NOTE: THE ASSIGNMENT 1 CONSISTS OF SINGLE FILE AND MAKEFILE ISN'T REQUIRED.
GOOD LUCK TRYING OUT!
