#!/usr/bin/env python3
import re

input("\nRun re.search() - Example 1");
print("Example 1: re.search()")
#This is the haystack we want to search
haystack = 'an example word:cat!!'
#This is the needle (or search pattern)
# word: - Exactly match
# \w\w\w - 3 word characters [0-9a-zA-Z_] in a row
needle=r'word:\w\w\w'

#Search for first occurance in string
match = re.search(needle, haystack)

#On success 
if match:                      
    print('Found', match.group()) 
else: # Returns None if no matches are found
    print("No {} in {}".format(needle, haystack))

input("\nRun re.search() - Example 2");
print()
print("Example 2: re.search() and group()")
haystack = 'purple alice-b@google.com monkey dishwasher'

#Look for
#[\w.-]+ - A word (\w) OR any char but newline (.) OR - exactly,  1 or more (+) times
#@ - Match exactly
needle = r'([\w.-]+)@([\w.-]+)'
match = re.search(needle, haystack)
    
if match:
    print("Group 0 (whole match): ", match.group())  
    print("Group 1: ", match.group(1))  
    print("Group 2: ", match.group(2))  

input("\nRun re.findall() - Example 3");
print()
print("Example 3: re.findall()")
haystack = 'purple alice@google.com, blah monkey   bob@abc.com blah dishwasher'
# [\w\.-] - Match a word (\w) OR . exactly (not the special dot) or -, 1 or more (+) times
needle=r'[\w\.-]+@[\w\.-]+'
emails = re.findall(needle, haystack) 
for email in emails:
    print(email)

input("\nRun re.findall() - Example 4");
print()
print("Example 4: re.findall() and groups")
haystack = 'purple alice@google.com, blah monkey bob@abc.com blah dishwasher'
needle=r'([\w\.-]+)@([\w\.-]+)'
matches = re.findall(needle, haystack)
for (username,host) in matches:
    print("Username: {}\t\tHost: {}".format(username, host))

input("\nRun re.sub() - Example 5");
print()
print("Example 5: Substitution (re.sub)")
haystack = 'purple alice@google.com, blah monkey bob@abc.com blah dishwasher'
needle = r'([\w\.-]+)@([\w\.-]+)'
# \1 is group(1), \2 group(2) in the replacement
# Keep group 1 match and replace rest of match
substr = r'\1@yo-yo-dyne.com'
new_string = re.sub(needle, substr, haystack)
print(haystack)
print(new_string)
print()
print("All done!")



