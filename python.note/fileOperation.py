# coding: utf-8
import os

print "The current working directory (os.getcwd()): ", os.getcwd()
print "All files and dirs in a given dir: (os.listdir) ", os.listdir( os.getcwd() )
print "Remove file: (os.remove)"
print "Remove dirs: (os.removedirs)"
print "Check whether it is a file (os.path.isfile)"
print "Check whether it is a dir(os.path.isdir)"
print "Check whether it is an absolute path (os.path.isabs)"
print "Check whether the path exists (os.path.exists)"
print "Slipt file and dir (os.path.split)", os.path.split('/home/zhuj7/poem') 
print "os.path.splitext(), os.path.dirname(), os.path.basename()"
print "Get and set environment variable: os.getenv() os.putenv()"
print "Line seperator: os.linesep"
print "os name:os.name"

"""
os.rename(old, new)
os.makedirs
os.mkdir
os.stat
os.chmod
os.exit
os.path.getsize("file") get the file size
os.mknod("text") create a filesystem node
os.chdir("path") change directory 
os.rmdir("dir") remove empty dir
shutil.copyfile("oldfile","newfile") 
shutil.copy("oldfile","newfile")      
shutil.copytree("olddir","newdir")        
shutil.move("oldpos","newpos")   
shutil.rmtree("dir")    
"""
