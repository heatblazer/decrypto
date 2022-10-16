#!/usr/bin/python

import subprocess
import os
import sys
import re

def cleanhtml(raw_html):
  cleanr = re.compile('<.*?>')
  cleantext = re.sub(cleanr, '', raw_html)
  cleantext = cleantext.replace(' ', '').replace('\n', '').replace('\t', '').replace('.', '')
  return cleantext

nodes = [] # per word count

HISTOGRAM = {}

def donwload(url):
    txt = str()
    dataout = []
    fp = subprocess.check_output("curl -s {}".format(url), shell=True)
    tf = fp.decode('utf-8')
    for line in tf:
        txt += line
    cleantxt = cleanhtml(txt)
    dataout = cleantxt.split(" ")
    return cleantxt 



#usage decrypto.py -n <number of downloads>
# if none it will download once

if __name__ == "__main__":
    count = 1
    for i in range(len(sys.argv)):
        if sys.argv[i] == "-n":
            count = int(sys.argv[i+1])

    for i in range(0, count):
        data= donwload("http://magadans22.org")
        print(data)
    pass
