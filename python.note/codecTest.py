# coding: utf-8 
# this file will be saved by utf-8, so strS is encoded by utf-8

# the bytes are: \xe6\xb1\x89 (utf-8 by default)
strS = "汉" # <type 'str'>, this is a str object, 3 bytes
print strS, type(strS) 

# interprete the byte stream with utf-8
strU = strS.decode('utf-8') # <type 'Unicode'>, this is a Unicode object 

#strGBK = strS.decode('gbk') #error, 'gbk' codec can't decode byte seq \xe6\xb1\x89, because \xe6\xb1\x89 is not valid for gbk

strGBK = strU.encode('gbk') # encode Unicode object strU with gbk
print strGBK, type(strGBK)

# python 2.X中，会先把'\xd0\x91'转换为unicode，再encode
# 因此也会抛出UnicodeDecodeError
try:
    "\xd0\x91".encode("utf-8")
except UnicodeDecodeError as e:
    print e


 
import sys
import locale
 
def p(f):
    print '%s.%s(): %s' % (f.__module__, f.__name__, f())
 
# 返回当前系统所使用的默认字符编码
p(sys.getdefaultencoding)
 
# 返回用于转换Unicode文件名至系统文件名所使用的编码
p(sys.getfilesystemencoding)
 
# 获取默认的区域设置并返回tuple（语言, 编码）
p(locale.getdefaultlocale)
 
# 返回用户设定的文本数据编码
# 文档中提到this function only returns a guess
p(locale.getpreferredencoding)
