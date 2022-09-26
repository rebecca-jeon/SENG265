#!/usr/bin/env python3
'''Assignment 4 Part 1 template'''
if __name__ == "__doc__":
    print(__doc__)

from typing import IO

class ProEpilogue:
    '''ProEpilogue class'''
    def __init__(self, title="", width = 0, height = 0 ):
        self.title = title
        self.width = width
        self.height = height

    def write_Prologue(self, f: IO[str]):
        '''writing prologue method'''
        s: str = "   "
        f.write(f"<html>\n")
        f.write(f"<head>\n")
        f.write(f"{s}<title>{self.title}</title>\n")
        f.write(f"</head>\n")
        f.write(f"<body>\n")
        f.write(f"{s}<!--Define SVG drawing box-->\n")
        f.write(f'{s}<svg width= "{self.width}" height="{self.height}">\n')

    def write_epilogue(self, f: IO[str]):
        '''writing epilogue method'''
        s: str = "   "
        f.write(f"{s}</svg>\n")
        f.write(f"</body>\n")
        f.write(f"</html>")

class Ellipse:
    '''Elipse class'''
    def __init__(self, elipse: tuple, col: tuple):
        self.cx: int = elipse[0]
        self.cy: int = elipse[1]
        self.rx: int = elipse[2]
        self.ry: int = elipse[3]
        self.red: int = col[0]
        self.blue: int = col[1]
        self.green: int = col[2]
        self.op: float = col[3]

def drawEllipse(f: IO[str], t:int, e: Ellipse):
    '''draw Ellipse method'''
    ts: str = "   " * t
    line: str = f'<ellipse cx="{e.cx}" cy="{e.cy}" rx="{e.rx}" ry="{e.ry}" fill="rgb({e.red}, {e.green}, {e.blue})" fill-opacity="{e.op}"></ellipse>'
    f.write(f"{ts}{line}\n")


class Rectangle:
    '''Rectangle class'''
    def __init__(self, rec: tuple, col: tuple):
        self.x: int = rec[0]
        self.y: int = rec[1]
        self.width: int = rec[2]
        self.height: int = rec[3]
        self.red: int = col[0]
        self.blue: int = col[1]
        self.green: int = col[2]
        self.op: float = col[3]

def drawRectLine(f: IO[str], t:int, r: Rectangle):
    '''draw Rectangle method'''
    ts: str = "   " * t
    line: str = f'<rect x = "{r.x}" y = "{r.y}" width="{r.width}" height="{r.height}" fill="rgb({r.red}, {r.green}, {r.blue})" fill-opacity="{r.op}"></rect>'
    f.write(f"{ts}{line}\n")


class Circle:
    '''Circle class'''
    def __init__(self, cir: tuple, col: tuple):
        self.cx: int = cir[0]
        self.cy: int = cir[1]
        self.rad: int = cir[2]
        self.red: int = col[0]
        self.green: int = col[1]
        self.blue: int = col[2]
        self.op: float = col[3]
        
def writeHTMLcomment(f: IO[str], t: int, com: str):
    '''writeHTMLcomment method'''
    ts: str = "   " * t
    f.write(f'{ts}<!--{com}-->\n')
        
def drawCircleLine(f: IO[str], t: int, c: Circle):
    '''drawCircle method'''
    ts: str = "   " * t
    line: str = f'<circle cx="{c.cx}" cy="{c.cy}" r="{c.rad}" fill="rgb({c.red}, {c.green}, {c.blue})" fill-opacity="{c.op}"></circle>'
    f.write(f"{ts}{line}\n")
        
def genArt(f: IO[str], t: int):
   '''genART method'''
   drawCircleLine(f, t, Circle((50,50,50), (255,0,0,1.0)))
   drawCircleLine(f, t, Circle((150,50,50), (255,0,0,1.0)))
   drawCircleLine(f, t, Circle((250,50,50), (255,0,0,1.0)))
   drawCircleLine(f, t, Circle((350,50,50), (255,0,0,1.0)))
   drawCircleLine(f, t, Circle((450,50,50), (255,0,0,1.0)))
   drawCircleLine(f, t, Circle((50,250,50), (0,0,255,1.0)))
   drawCircleLine(f, t, Circle((150,250,50), (0,0,255,1.0)))
   drawCircleLine(f, t, Circle((250,250,50), (0,0,255,1.0)))
   drawCircleLine(f, t, Circle((350,250,50), (0,0,255,1.0)))
   drawCircleLine(f, t, Circle((450,250,50), (0,0,255,1.0)))
   drawRectLine(f, t, Rectangle(( 30, 50, 80, 50), (150, 100, 50, .5)))
   drawRectLine(f, t, Rectangle(( 69, 69, 150, 89), (120, 50, 100, .5)))
   drawRectLine(f, t, Rectangle((80, 11, 100, 100), (100, 100, 0, .5)))
   drawEllipse(f, t, Ellipse((200, 50, 60, 35), (150, 20, 69, .5)))
   drawEllipse(f, t, Ellipse((450, 200, 50, 45), (100, 80, 20, .7)))
        
def openSVGcanvas(f: IO[str], t: int, canvas: tuple):
     '''openSVGcanvas method'''
     ts: str = "   " * t
     writeHTMLcomment(f, t, "Define SVG drawing box")
     f.write(f'{ts}<svg width="{canvas[0]}" height="{canvas[1]}">\n')

def closeSVGcanvas(f: IO[str], t: int):
    '''closeSVGcanvas method'''
    ts: str = "   " * t
    f.write(f'{ts}</svg>\n')
    f.write(f'</body>\n')
    f.write(f'</html>\n')

def writeHTMLline(f: IO[str], t: int, line: str):
     '''writeLineHTML method'''
     ts = "   " * t
     f.write(f"{ts}{line}\n")

def writeHTMLHeader(f: IO[str], winTitle: str):
    '''writeHeadHTML method'''
    writeHTMLline(f, 0, "<html>")
    writeHTMLline(f, 0, "<head>")
    writeHTMLline(f, 1, f"<title>{winTitle}</title>")
    writeHTMLline(f, 0, "</head>")
    writeHTMLline(f, 0, "<body>")

def writeHTMLfile():
    '''writeHTMLfile method'''
    
    fnam: str = "a41.html"
    f: IO[str] = open(fnam, "w")
    """
    winTitle = "My Art"
    f: IO[str] = open(fnam, "w")
    writeHTMLHeader(f, winTitle)
    openSVGcanvas(f, 1, (800,500))
    """
    sweet = ProEpilogue("My Art", 500, 300 )
    sweet.write_Prologue(f)

    genArt(f, 2)
    """
    closeSVGcanvas(f, 1)
    """
    sweet.write_epilogue(f)
    f.close()


def main():
    '''main method'''
    writeHTMLfile()

main()

                                                                                                                                                                                                                                                                                                        
