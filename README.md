# LispCompiler

Major Sources: 
https://youtube.com/playlist?list=PLWUx_XkUoGTrXOU0pFa_OVGA-6voiIEAt&si=Z02AGeBr5tH9qy3_
https://craftinginterpreters.com/scanning.html


## START HERE
1. ### Set Up: 
    1. **GIT:** Clone the git repository into a directory of your choosing 
        1. open a terminal on your device
        2. navigate to desired directory and run following command
        3. git clone https://github.com/odcampbell/LispCompiler.git
            - if it does not allow you to clone then you follow **DOWNLOAD** 
        
    2. **DOWNLOAD:**
        1. You can download the code with the zip file "bright.zip"
        2. Unzip the code in a directory of your choosing, or unzip it and
            - copy/drag the files into the directory via file system or even some coding ide's

2. ### BUILD: (For Testing: see Step 4)
    1. move into the directory **"LispInterpreter"** and then **"bright"**
        - everything should be done from the bright directory unless the project gets reorganized
        
    2. run command **"make"**
        - I already have a make file set up in the "bright" directory so,
        - it should create an executable called **"bright.exe"**

3. ### RUN: (For Syntax and Stuff see Step 5)
    1. **To terminal:**
        1. **From File**
            - run cmd **"bright fileName.txt"** or **"bright.exe fileName.txt"**
            - this will run the cmds in the file and exit when done
            - fileName.txt is just a placeholder for whatever file is holding your code
            - **Try** with this cmd: **"bright yispTest.lisp"** to use my demo file
            - Answers are located in **"demoAnswerKey.txt"**

        2. **Interactive:**
            - run cmd **"bright"** or **"bright.exe"**
            - you can type cmds in one line continously e.g. (+ 10 (car (cdr (10 90 40)))) to output 100

    2. **To File:**
        - To send results to a file, just add the extraction operator **">>"** and a file name for your output
        - e.g., **bright yispTest.lisp >> output.txt**
        - this works best for output from a file to a file

    3. Clean:
        - Cleans executable file .exe 
        - commented out ".o" because no object files are created and stored in this build

4. ### TEST:
    I wrote a simple script to streamline testing.
    I believe these can run different on different systems so I wrote one for windows and one for linux

    1. Windows Terminal:
        - run script **windows_test.bat**
        - it will call make, run test file, and output the results to **yispResults.txt**
        - then it will run test.py on the results and output this to **testResults.txt**
        - you can also run the bash script here via: **bash linux_test.sh**

    2. Linux:
        - run script **./linux_test.sh**
        - it does the same thing

    3. If a test passed, it is labeled True and if not, then False

5. ### Syntax and Stuff
    1. **Not Implemented: (Things you can't do/use in my yisp)**
        - strings (prn function to print strings also doesn't work currently)
        - data structures (e.g., vector, map)
        - cond
        - handling commas
        - decimals (might not crash but you get unexpected behavior)
        - case sensitivy (keywords have to match implementation -> core.cpp)

    2. **Implemented:**
        - +, -, *, /, list?, nil?, count?, not? >, =>, <, <=, car, cdr, cons, if,
        - and?, or?, list
        - symbol? (only if actually set, e.g. via (def a (fn (b)b) )) (symbol? a) true
        - recursion (non optimized so be frugal)
        - user defined functions
    
    3. Built in Function Syntax:  (name arg arg)
    4. User defined function Syntax: (def name (fn (arguments) body))
    5. Files for premade functions: core.cpp

# Notes:
I started off this project using the book's scanner for parsing but didn't want to try automating classes in C, so I found a tutorial to follow from there. My code differs from the tutorial in 
- parsing implementation, 
- cons, car, and cdr implementation 
    - (which were absent from the tutorial)
    - (I also had to approximate them with vectors since I wasn't using linked lists here), 
- some naming conventions
- the repl loop because Im reading from file, which was tricky with how the rest of my code was structured.
- Unless a recent commit says otherwise, I haven't added optimization for recursion yet so don't do anything crazy when making recurssive calls
- I also am not a big fan of my make file: I love it for simplicity sake but I'm not sure if builds as efficiently in this form as it would in others.