# Job Seeking Application

# Modules
This is a job seeking application written in C that allows users to login, signup, and modify their details. The application is split into several modules to maintain a clear and organized codebase. The following modules are included:

## main.c: 
This file contains the main function and displays a menu to the user with options for login, signup, and modifying user details. Based on the login type, either the job seeker module or the company module is called.

## login.h: 
This header file contains functions and data structures related to the login process. It handles user authentication and ensures that only registered users can access the application.

## signup.h: 
This header file contains functions and data structures related to the signup process. It allows users to create new accounts as either job seekers or employers.

## jobseeker.h: 
This header file contains functions and data structures specific to job seekers. It allows job seekers to give their requirements as input and receive the matching and recommended job offers as an output.

## company.h: 
This header file contains functions and data structures specific to companies or employers. It allows companies to find job seekers whose qualifications, skills, certifications, etc.. matches their requirements.

## modifydetails.h: 
This header file contains functions and data structures to modify user details, such as updating personal information, skills, or job preferences.

# Databases
The application also stores the data properly in text files. These databases are kept in a folder called 'db'.

## usernamedb.txt: 
This text file serves as a database for storing usernames of registered users. Each line in the file represents a single username. When a user signs up, their username is added to this file. During the login process, the application checks this file to authenticate users. Also, the usernames are prefixed by an index that denotes if the user is job seeker or an employer. prefix 1 denotes that the user is job seeker, prefix 2 denotes that the user is employer.

## pwdb.txt: 
This text file acts as a database for storing user passwords.

## seekerprofile.txt: 
This text file is used to store job seeker profiles. When a job seeker signs up, their profile information is stored in this file. The profile may include details such as the seeker's name, skills, qualifications etc.. The application can use this file to match job seekers with companies.

## companyprofile.txt: 
This text file functions as a database for company or employer profiles. When a company signs up, its profile information is saved in this file. The profile may contain details like the company's name, industry, and any specific job openings they have posted. The application can use this file to display company information and match job offers to the seekers.


# Compilation and Execution

## To compile the job seeking application, follow these steps:

* Ensure you have a C compiler installed on your system. 
* Download or clone the source code files to a directory on your computer.
* Open your terminal or command prompt and navigate to the directory containing the source code files.
* Compile the application using the following command:
  
`gcc main.c -o jobseekingapplication.exe`

(This command will compile all the necessary source code files and create an executable named jobseekingapplication.exe . There is no need for linking all the modules manually because they are done internally and hence compiling the 'main.c' file, compiles all the other modules as well, making user's job easier)

* Now, you can run the application by executing given executable:

`./jobseekingapplication.exe`

The application will display a menu with options for login, signup, and modify user details. Follow the on-screen instructions to navigate through the application and utilize its features.

