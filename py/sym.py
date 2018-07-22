import os, sys

sym_dict = {}
type_dict = {}

def osf(file) :
    os.system("nm " + file + " > /tmp/ptp_sym")
    fd = open("/tmp/ptp_sym", "r")
    lines = fd.readlines()
    os.system("rm /tmp/ptp_sysm")
    for line in lines:
        addr = line[0:16].strip("\r\n")
        type = line[17:18].strip("\r\n")
        sym_name = line[19:].strip("\r\n")
        if type in type_dict :
            type_dict[type].append((sym_name, addr))
        else :
            type_dict[type] = [(sym_name, addr)]
        sym_dict[sym_name] = (addr, type)

def tell(key) :
    if key in sym_dict:
        print sym_dict[key]
    elif key in type_dict:
        for each_sym in type_dict[key] :
            print each_sym
    else :
        print "key not available"
