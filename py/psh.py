#! /usr/bin/env python

import readline, os, sys, subprocess, re, shlex
 
# Constants

operators = [ '+', '-', '*', '**', '/', '//', '%', \
              '<<', '>>', '&', '|', '^', '~', \
              '<', '>', '<=', '>=', '==', '!=', '<>' ]

delimiters = [ '(', ')', '[', ']', '{', '}', '@', \
               ',', ':', '.', '?', '=', ';', '+=', '-=', '*=', '/=', '//=', \
               '%=', '&=', '|=', '?=', '>>=', '<<=', '**=' ]

keyword = [ 'and', 'del', 'from', 'not', 'while', 'as', 'elif', 'global',
            'or', 'with', 'assert', 'else', 'if', 'pass', 'yield', 'break',
            'except', 'import', 'print', 'class', 'exec', 'in', 'raise',
            'continue', 'finally', 'is', 'return', 'def', 'for', 'lambda', 
            'try' ]


# Global Variables

history_file = os.path.expanduser("~/.psh_history")
host = os.environ["HOSTNAME"]
user = os.environ["USER"]
home = os.environ["HOME"]
cwd = os.environ["PWD"]
line_buffer = ""
sh_paths = re.split(r":", os.environ["PATH"])


# Module Functions

def psh_tab_completer(text, state) :
    '''
    Tab completer for the shell.
    '''
    line_buffer = readline.get_line_buffer()
    sh_list = re.split(r"^[\t ]*%", line_buffer)
    if not sh_list[0] :                 # Shell command line
        sh_list = re.split(r"\|", sh_list[1])
        for each in sh_list :           # Each piped command
            each_list = shlex.split(each)
            if each_list[0] == text :   # Shell program name
                completed = None
                completed_list = re.findall(r"(?=[ '\"\t])" + text + r".*?[ '\"\t]", sh_hash[0])
                if state < len(completed_list) :
                    completed = completed_list[state]
    else :                              # Python expansion
        pass 
    print state, completed, completed_list
    return completed


# Modules's main thread

# Save History

import atexit

def save_history(path) :
    '''
    Save the current sessions history into the history file
    '''
    print "\nsaving history to ", history_file
    readline.write_history_file(path)

if os.path.exists(history_file) :
    readline.read_history_file(history_file)

atexit.register(save_history, history_file)

# collect the list of executable programs under PATH 

import dircache, stat

# The main data structure to manage the shell programs
#       [<string of programs>, {prog : [<path>, count]}]

sh_hash = ["",{}]

for path in sh_paths :                      # per path
    if os.path.exists(path) :
        file_list = dircache.listdir(path)
        for file in file_list :
            if file in sh_hash[1] :
                continue
            # Check for executable-ness
            if os.lstat(os.path.join(path,file))[stat.ST_MODE] & stat.S_IEXEC :
                sh_hash[0] = sh_hash[0] + " " + file    
                sh_hash[1].setdefault(file,  [path, 0]) 


# Readline settings

    # Editing
readline.parse_and_bind("set bell-style             audible")
readline.parse_and_bind("set comment-begin          #")
readline.parse_and_bind("set editing-mode           vi")
readline.parse_and_bind("set keymap                 vi")

    # Moving
readline.parse_and_bind("\"\C-e\": end-of-line");

    # Visual
readline.parse_and_bind("set horizontal-scroll-mode off")
readline.parse_and_bind("set mark-directories       on")
readline.parse_and_bind("set mark-modified-lines    off")
readline.parse_and_bind("set mark-symlinked-directories on")
readline.parse_and_bind("set mark-hidden-files      on")
readline.parse_and_bind("C-L : clear-screen")

    # History
readline.parse_and_bind("set isearch-terminators     C-s")

    # Completion
readline.set_completer(psh_tab_completer)
readline.parse_and_bind("set completion-ignore-case off")
readline.parse_and_bind("set completion-query-items 20")
readline.parse_and_bind("set disable-completion     off")
readline.parse_and_bind("set expand-tilde           on")
readline.parse_and_bind("set page-completions       on")
readline.parse_and_bind("set show-all-if-ambiguous  on")
readline.parse_and_bind("tab: complete")
readline.parse_and_bind(r"\"\C-t\": complete")

# Command loop

#def cmd_substitution(cmd_line)

#prompt = user + '@' + host + ':' + os.path.basename(cwd)  + ' \273 '
prompt = "> "
cmp_st = ""
while 1 :
    try :
        line_buffer = raw_input(prompt)

        if line_buffer == "exit" :      # Quite the shell
            break

        if cmp_st :                     # Compound statements
            if line_buffer:  
                cmp_st += line_buffer + "\n"
            else:
                try :
                    exec(cmp_st)
                except:
                    print "Wrong statement !"
                readline.parse_and_bind("tab : complete")
                cmp_st = ""
                prompt = "> "
            continue

        if re.match(r".*:[\t ]*$", line_buffer):  # Initiat a compound statement
            prompt = ". " 
            cmp_st = line_buffer + "\n"
            readline.parse_and_bind("tab: tab-insert")
            continue

        sh_list = re.split(r"^[\t ]*%", line_buffer)
        if not sh_list[0]:              # A complete shell command
            os.system(sh_list[1])
            continue
        exec(line_buffer)
    except :
        print "\nUnexpected Exception : ", sys.exc_info()
