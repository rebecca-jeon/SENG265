#!/usr/bin/env python3
'''Assignment 4 Part 3'''
print(__doc__)

from a41 import ProEpilogue, Ellipse, Circle, Rectangle, drawCircleLine, drawEllipse, drawRectLine
from a42 import GenRandom, ArtConfig, shape_lists
from typing import IO


def making_art(f: IO[str], t: int, width, height):
    num_shapes = GenRandom(800, 1000).genInRange()
    SHAPES = shape_lists(num_shapes, width, height)
    for shape in SHAPES:
        if shape[1] == 0:
            drawCircleLine(f, t, Circle((shape[2], shape[3], shape[4]), (shape[9], shape[11], shape[10], shape[12])))
        elif shape[1] == 1:
            drawRectLine(f, t, Rectangle((shape[2], shape[3], shape[7], shape[8]), (shape[9], shape[10], shape[11], shape[12])))
        else:
            drawEllipse(f, t, Ellipse((shape[2], shape[3], shape[5], shape[6]), (shape[9], shape[10], shape[11], shape[12])))


def writeHTMLfile():
    '''writeHTMLfile method'''
    
    fnam: str = "myPart3Art.html"
    f: IO[str] = open(fnam, "w")
    width = GenRandom(500, 1000).genInRange()
    height = GenRandom(500, 1000).genInRange()
  
    ArT = ProEpilogue("My Incredible Art", width, height)
    ArT.write_Prologue(f)

    making_art(f, 2, width, height)
   
    ArT.write_epilogue(f)
    f.close()

def main():
    '''main function'''
    writeHTMLfile()

main()

