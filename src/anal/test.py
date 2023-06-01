import os
from ctypes import *
from lxml import etree

class Morpheus:
    def __init__(self):
        self.lib = cdll.LoadLibrary("./libmorpheus.so")
        self.lib.freeme.argtypes = c_void_p,
        self.lib.freeme.restype = None
        #lib.teststring.argtypes = []
        self.lib.teststring.restype = c_void_p


    def ask(self, latin):
        """Ask morpheus for latin word, returns xml.etree.ElementTree answer."""
        res = self.lib.teststring(bytes(latin, "utf-8"))
        ans = cast(res, c_char_p)
        ans = ans.value if ans != None else None
        ans = ans.decode("ascii") if ans != None else ""
        self.lib.freeme(res)
        return ans

if __name__ == "__main__":
    w = Morpheus()
    res = w.ask("deo")
    print(f"Answer: »{res}«")
    #print(etree.tounicode(res))

