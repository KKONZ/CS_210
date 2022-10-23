# CS_210


* ## Summarize the project and what problem it was solving.

This program takes a file in which each line represents a grocery item that was sold at a store on a particular day. The program displays a menu of options to select to the user that include listing each item in the file with the number of times it was sold, searching for a specific item and showing how many times it was sold, displaying a text based histogram of the items sold, and an option to exit the program. The functions to preform each of the options in the menu are written in python and the menu and histogram generation are written in c++.

* ## What did you do particularly well?

Using the built in counter functionality to count the items in the file helps with keeping the program simple and easy to maintain.

* ## Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?

The starter code was not built using an object oriented based approach. I could have used classes, beyond the main class, and mutators and accessors. For a simple program such as this though, that might be a bit excessive. 

* ## Which pieces of the code did you find most challenging to write, and how did you overcome this? What tools or resources are you adding to your support network?

Debugging the python code was a bit tricky because errors from visual studio code were output from c++. This made finding simple errors in the code a bit more tricky. In hindsight I could have debugged the python code on it's own before attempting to run it from within the c++ code.

* ## What skills from this project will be particularly transferable to other projects or course work?

Incorporating multiple languages into a single application or framework is a fairly common occurance. This project has helped me get a basic understanding of how to do so.
 
* ## How did you make this program maintainable, readable, and adaptable?

The biggest thing I did in this area was creating docstrings for each of the functions.