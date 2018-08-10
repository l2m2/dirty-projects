#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import os
import re
import sqlite3
import time
import sys

def find_md5_files(root_path, md5_files):
    for f in os.listdir(root_path):
        path = os.path.join(root_path, f)
        if (os.path.isdir(path)):
            find_md5_files(path, md5_files)
        elif (os.path.isfile(path)):
            if (re.match(r"([a-fA-F\d]{32})", f)):
                md5_files.append(path)
        else:
            print "do nothing"

print "begin."
print "traverse the md5 folder."
path = "/toplinker/topibd-http/data/topibd_client_files"
md5_files = []
find_md5_files(path, md5_files)
try:
    con = sqlite3.connect("/toplinker/topibd-http/data/fileinfo.db")
except Exception, e:
    print e
    exit()
cursor = con.cursor()
now = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
count = len(md5_files)
for i, f in enumerate(md5_files):
    sys.stdout.write("repair(%d/%d)..." % (i, count))
    sys.stdout.flush()
    base_name = os.path.basename(f)
    cursor.execute("SELECT * FROM files_topibd_client_files WHERE md5=?", (base_name, ))
    values = cursor.fetchall()
    if (len(values) == 0):
        cursor.execute("INSERT INTO files_topibd_client_files(md5, create_time) VALUES(?,?)", (base_name, now))
        
con.commit()
con.close()
