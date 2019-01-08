#!/usr/bin/env python3

#Allan Liu
#V00806981
import fileinput
import sys
import re
import argparse

class UVroff:
    def __init__(self, filename, text_in):
        self.filename = filename
        self.text_in = text_in

        #output a list to be returned
        self.output_line = []

        #data attributes (formatting turned off by default)
        self.chars = 0
        self.LW = 0
        self.LM = 0
        self.LS = 0
        self.FT = False
        self.new_paragraph = 0
        #self.check = True
        self.line_string = ""

        self.LS_old = 0
        self.LS_changed = False
        self.LS_flag = False

    def line_spacing(self):
        if self.LS_changed is True:
            for i in range(self.LS_old):
                self.output_line.append("")
            self.LS_flag = False
            self.LS_old = self.LS
        else:
            for x in range(self.LS):
                self.output_line.append("")

    def margins(self):
        for x in range(self.LM):
            self.line_string += " "

    #function that formats LW, LM, LS accordingly to the data attributes that have been set and prints each word
    def make_format(self, line):
        has_format = self.check_format(line)
        #append to output_line if it has no formatting
        if self.FT == False and has_format != 1:
            self.output_line.append(line)
        elif self.FT == True and has_format != 1:
            words = line.split()

            for i in range(len(words)):
                #make line spacing if exceeded the line width
                if self.chars + len(words[i]) + 1 > self.LW:
                    self.output_line.append(self.line_string)
                    self.line_string = ""
                    self.line_spacing()
                    self.chars= 0
                #adding space between words if it is not the first word of a line
                elif self.chars > self.LM:
                    self.line_string += " "
                    self.chars += 1
                #when it is the start of a new line, make appropriate line margins
                if self.chars == 0:
                    if self.new_paragraph == 1:
                        self.line_spacing()
                        self.new_paragraph = 0
                    self.margins()
                    self.chars += self.LM
                #print the word in the list
                self.line_string += words[i]
                self.chars += len(words[i])

    #function that checks for formatting and changes data attributes
    #it will return whether if it has encountered a formatter command for each line
    def check_format(self, line):
        has_format = 0
        words = line.split()
        if words[0] == ".LW":
            try:
                if isinstance(int(words[1]), int):
                    self.LW = int(words[1])
                    self.FT = True
                    has_format = 1
                elif words[1][0] == "-":
                    self.LW -= int(words[1][1:])
                    self.FT = True
                elif words[1][0] == "+":
                    self.LW += int(words[1][1:])
                    self.FT = True
            except ValueError:
                sys.stderr.write("\nValueError: Not a valid .LW value: %s\n\n" % (words[1]))
        elif words[0] == ".LM":
            try:
                if words[1][:1] == "-":
                    self.LM -= int(words[1][1:])
                    if self.LM < 0:
                        self.LM = 0
                        sys.stderr.write("\n.LM can't have have negative margins! It is currently: %s\n" % (words[1]))
                        sys.stderr.write("\nChanged .LM to 0\n\n")
                elif words[1][:1] == "+":
                    self.LM += int(words[1][1:])
                else:
                    self.LM = int(words[1])
                #check margins restrictions
                if self.LM > self.LW - 20:
                    self.LM = self.LW - 20
                self.FT = True
                has_format = 1
            except ValueError:
                sys.stderr.write("\nValueError: Not a valid .LM value: %s\n\n" % (words[1]))

        #LS_flag turns True only if it encounters a .LS command at least once in the file.
        #LS_flag stays True which will run the else command in the function line_spacing().
        #If while reading line by line encounters another .LS command, set LS_changed to True
        #and will copy the old line spacing values to LS_old attribute before reassigning LS to the new value.
        #Necessary to pass the harder test cases with appropriate line spacing.

        elif words[0] == ".LS":
            try:
                if self.LS_flag is True:
                    self.LS_old = self.LS
                    self.LS_changed = True
                self.LS = int(words[1])
                if self.LS < 0:
                    self.LS = 0
                    sys.stderr.write("\n.LS value must be be between 0 and 2, it is currently: %s\n" % (words[1]))
                    sys.stderr.write("\nChanged .LS to 0\n\n")
                if self.LS > 2:
                    self.LS = 2
                    sys.stderr.write("\n.LS value must be be between 0 and 2, it is currently: %s\n" % (words[1]))
                    sys.stderr.write("\nChanged .LS to 2\n\n")
                self.FT = True
                self.LS_flag = True
            except ValueError:
                sys.stderr.write("\nValueError: Not a valid .LS value %s\n\n" % (words[1]))
                #error = ["\nValueError: .LS value must be be between 0 and 2, it is currently: %s\n" % (words[1])]
                #return error
            has_format = 1
        elif words[0] == ".FT":
            if words[1] == "off":
                self.FT = False
            elif words[1] == "on":
                self.FT = True
            has_format = 1
        return has_format

    #basically, the main function in my assignment 2 that deals with the input
    def input(self, lines_text):
        for line in lines_text:
            #read input line by line and check for empty lines
            if line.strip() == "":
                if self.line_string != "":
                    self.output_line.append(self.line_string)
                    self.line_string = ""
                self.output_line.append("")
                self.line_spacing()
                self.new_paragraph = 1
                self.chars = 0

            else:
                #replace new line with nothing
                line = line.replace("\n", "")
                self.make_format(line)
        #append the rest of words to output
        if self.FT == True and self.new_paragraph != 1:
            self.output_line.append(self.line_string)
            self.line_string = ""
        return

    def get_lines(self):
        if self.filename is not None and self.text_in is None:
            #if the filename contains "stdin" take input from stdin
            if self.filename == "stdin":
                try:
                    file_in = sys.stdin.readlines()
                    self.input(file_in)
                except IOError:
                    error = ["\nIOError: Unable to read from stdin\n"]
                    return error
            #checks for valid file names to be read and opened
            else:
                try:
                    #check = re.match("\w+\.txt", self.filename)
                    check = filter(None, re.match("(\/?\w+)+\.txt", self.filename).groups())
                except AttributeError:
                    check = ""
                    error = ["\nAttributeError: The input name (%s) is not valid, please use a .txt file\n" % self.filename]
                    return error
                try:
                    file_in = open(self.filename)
                except IOError:
                    error = ["\nIOError: Unable to open (%s) file\n" % self.filename]
                    return error
                #format input if did not encounter any errors
                self.input(file_in)
                file_in.close()

        if self.filename is None and self.text_in is not None:
            try:
                #isinstance will check if the input text is a list
                #https://stackoverflow.com/questions/9759930/how-to-check-if-an-element-of-a-list-is-a-list-in-python
                isinstance(self.text_in, list)
                self.input(self.text_in)
            except TypeError:
                error = ["\nTypeError: Need to input a list\n"]
                return error
        return self.output_line
