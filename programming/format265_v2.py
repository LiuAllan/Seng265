#!/usr/bin/env python3
import fileinput
import sys
import os

# Global tags
current = {
    'length' : 0,
    #'last_was_new' : False
}
tags = { 
    'format'     : False,      # Is formatting on or off? [0]
    'width'  : 0,          # The Maximum width of any given line. May change throughout processing. [1]
    'margin'    : 0,          # Desired page margin. Cannot be less then or equal to width-20 [2]
    'space'   : 0,          # Linespacing [3]
}

def main ():
    """
    Process line by line. Return none if there is a tag on the line, and add a new line if empty.
	Else check margins and width and gradually add onto the output.
    """
    output = "" #the current output is empty in the beginning. read the line and join to the output.
    lines =  [ line for line in fileinput.input() ]
    processed = [ processor(line) for line in lines]
    has_line = [ line for line in processed if line != None ]
    
    if len(has_line) == 0:
        return None
    else:
        output = "".join(has_line) #slides 87
        print (output)
    
def processor (line):
    """ 
	This function will check for the formatting tags by splitting into chunks, and format the file.
    """
    chunk = line.split() #split the entire line into chunks of words
    if len(chunk) is not 0: #check which tags
        if chunk[0] == ".FT":
            if chunk[1] == "off":
                tags['format'] = False
            elif chunk[1] == "on":
                tags['format'] = True
            return None
        elif chunk[0] == ".LW": #if it has a .LW, it will also turn "on" format
            if isinstance(int(chunk[1]), int):
                tags['width'] = int(chunk[1])
                tags['format'] = True
            elif chunk[1][0] == '-':
                tags['width'] -= int(chunk[1][1:])
                tags['format'] = True
            elif chunk[1][0] == '+':
                tags['width'] += int(chunk[1][1:])
                tags['format'] = True
            return None
        elif chunk[0] == ".LM":
            if chunk[1][:1] == "-":
                tags['margin'] -= int(chunk[1][1:])
                if tags['margin'] < 0:
                    tags['margin'] = 0
            elif chunk[1][:1] == "+":
                tags['margin'] += int(chunk[1][1:])
            else:
                tags['margin'] = int(chunk[1])
            if tags['margin'] > tags['width'] - 20: #margin restrictions
                tags['margin'] = tags['width'] - 20
            return None


        #elif chunk[0] == ".LS":
           #if tags['space'] = int(chunk[1])

    if tags['format']: #output the current line
	    """
        # Special case for empty lines.
        if chunk == []:
            current['length'] = 0
            if current['last_was_new']:
                return '\n'
            else:
                current['last_was_new'] = True
                return '\n\n'
        current['last_was_new'] = False
        """
		
        if current['length'] == 0: #check if a margin is needed for the current length
            out = "".join( [" " for i in range(tags['margin']) ] ) #add spaces for margin and join together with output
            current['length'] = tags['margin']


        #if current['length'] == 0:
            #out = out + '\n'
        else:
            out = ""
            
        for word in chunk: #add word one by one and check if it exceeds .LW
            if current['length'] + len(word) >= tags['width']: #check if a new line is needed
                margin = "".join( [" " for i in range(tags['margin']) ] )
                out = out + '\n' + margin
                current['length'] = tags['margin']
            elif current['length'] != tags['margin']: #it does not exceed .LW so just add a space
                current['length'] += 1
                out = out + ' '
            out = out + word #concatenate the output
            current['length'] += len(word)
        return out
    else:
        print (line, end="") #print the line as is without a new line if no formating tag is initiated or found in file
    
if __name__ == "__main__":
    main()
