#!/usr/bin/env	python3

#Allan Liu
#V00806981
#SENG265

import fileinput
import sys

#dictionaries to be used to determine what format to use
#formatting is turned off by default
flags = {
    'chars' : 0,
    'LW' : 0,
    'LM' : 0,
    'LS' : 0,
    'FT' : False,
    'new_paragraph' : 0,
}

#function that formats LW, LM, LS accordingly to the flags that have been set and prints each word
def make_format(words):
    for i in range(len(words)):
        #make linespacing if exceeded the line width
        if flags['chars'] + len(words[i]) + 1 > flags['LW']:
            print()
            line_spacing()
            flags['chars'] = 0
        #adds space between words only if it is not the first word of the sentence
        elif flags['chars'] > flags['LM']:
            print (" ", end = "")
            flags['chars'] += 1
        if flags['chars'] == 0:
            if flags['new_paragraph'] == 1:
                if flags['FT'] == True:
                    line_spacing()
                flags['new_paragraph'] = 0
            margins()
            flags['chars'] += flags['LM']
        #print the words in list
        print("%s" %words[i], end="")
        flags['chars'] += len(words[i])

#function that checks for formatting and changes dictionary
#it will return whether if it has encountered a formatter command for each line
def check_format(line):
    has_format = 0
    words = line.split()
    if words[0] == ".LW":
        flags['LW'] = int(words[1])
        flags['FT'] = True
        has_format = 1
        #print(flags['LW'])
    elif words[0] == ".LM":
        if any("-" in word for word in words):
            flags['LM'] = flags['LM'] + int(words[1])
        elif any("+" in word for word in words):
            flags['LM'] = flags['LM'] + int(words[1])
        else:
            flags['LM'] = int(words[1])
        #check margins
        if flags['LM'] < 0:
            flags['LM'] = 0
        if flags['LM'] > (flags['LW'] - 20):
            flags['LM'] = (flags['LW'] - 20)
        flags['FT'] = True
        has_format = 1
    elif words[0] == ".LS":
        flags['LS'] = int(words[1])
        flags['FT'] = True
        has_format = 1
    elif words[0] == ".FT":
        if words[1] == "off":
            flags['FT'] = False
        elif words[1] == "on":
            flags['FT'] = True
        has_format = 1
    return has_format

def margins():
    for x in range(flags['LM']):
        print(" ", end = "")

def line_spacing():
    for x in range(flags['LS']):
        print()

#read input line by line and check for empty lines
def main():
    for line in fileinput.input():
        if line.strip() == '':
            print()
            if flags['FT'] == True:
                print()
                line_spacing()
            flags['new_paragraph'] = 1
            flags['chars'] = 0
        #check each line if it has a formatting command. If it does, set the flags accordingly, but don't print the format commands to stdout
        else:
            has_format = check_format(line)
            #prints the line without any formatting
            if flags['FT'] == False and has_format != 1:
                print(line, end="")
            #gets rid of all whitespace before printing each line according to formatting commands
            elif flags['FT'] == True and has_format != 1:
                words = line.split()
                make_format(words)
    #prints new line at the end of file for unix
    if flags['chars'] > 0:
        print()


if __name__ == '__main__':
    main()
