#import csv
from collections import Counter



def readFile():
    """
    Read file into list and count occurences 
    Return:
         Dictionary of counted list items
    """
    filepath = "U:\\CornerGrocer\\Release\\groceries.csv"
    groceries = []
    with open(filepath) as f:
        for line in f:
            groceries.append(line.strip('\n'))
    counted = Counter(groceries)
    return counted


def countAll():
    """
    Print counted items from grocery file 
    """
    
    counted = readFile()
    for key, value in counted.items():
        print(key, value)

def countItem(item):
    """
    Print number of times a specific item was purchased
    Args:
        string item    item of interest to display counted value 
    """
    counted = readFile()
    return counted[item]

def writeSummary():
    """
    Write counted grocery items to file after reading initial raw list and counting items
    """
    
    # file path to write data to
    filepath = "U:\\CornerGrocer\\Release\\frequency.dat"

    # call function to read grocery file and count items
    counted = readFile()

    # covert dictionary to list
    ls_counted = list(counted.items())

    # iterate over list and write each element to a new line
    f = open(filepath, 'a')
    for i in range(len(ls_counted)):    
        f.write(ls_counted[i][0] + ' ' + str(ls_counted[i][1]) + '\n')
            