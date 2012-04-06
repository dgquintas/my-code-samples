# encoding: utf-8

def manually_insert(inputPath,outputPath,conditions):
  import re
  from os.path import dirname,abspath
  from os import getcwd, chdir, remove
  from tempfile import mkstemp
  oldPWD = getcwd()
  chdir(dirname(abspath(inputPath)))
  input = open(inputPath,'r')
  output = open(outputPath, 'w')
  pragma_str = "#pragma __libmpplas_manual_include"
  for line in input.xreadlines():
    if line.strip()[:len(pragma_str)] == "#pragma __libmpplas_manual_include":
      no_condition = False
      cond_read = ""
      if len(line.split()) == 2: #no cond
        no_condition = True
      else:
        cond_read = line.split()[2]
      include_line = input.next()
      if cond_read in conditions or no_condition:
        m = re.match(r'#include "([a-zA-Z0-9\_\.]+)"', include_line.strip())
        file_to_include = m.group(1)
        #parse input file for possible substitutions as well
        tmpOutFile = mkstemp()[1]
        manually_insert( file_to_include, tmpOutFile, "")
        tmpOutFileDesc = open(tmpOutFile, 'r')
        output.write(tmpOutFileDesc.read())
        tmpOutFileDesc.close()
        remove( tmpOutFile )
    else:
      output.write(line)
  chdir(oldPWD)
  input.close()
  output.close()



if __name__ == "__main__":
  from sys import argv
  infile = argv[1]
  outfile= argv[2]
  cond1   = argv[3]
  cond2   = argv[4]

  manually_insert(infile, outfile, (cond1, cond2) )


