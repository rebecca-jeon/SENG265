#!/usr/bin/env python3
'''Assignment 4 Part 2'''
if __name__ == "__doc__":
    print(__doc__)


import random
import numpy as np

class GenRandom:
    '''GenRandom class'''
    def __init__(self, start = 0, stop = 0):
        self.start = start
        self.stop = stop

    def genInRange(self):
        '''generating integers in given range method'''
        num = random.randrange(self.start, self.stop)
        return num

    def genFloatRange(self):
        '''generating floats in given range method'''
        num = round(random.uniform(self.start, self.stop), 1)
        return num


class ArtConfig:
    '''ArtConfig class
    For Shape:
        0: circles
        1: rectangles
        2: ellipse
    '''
    def __init__(self, svg_w = 0, svg_h = 0):
        self.width = svg_w
        self.height = svg_h
        self.SHA = GenRandom(0, 3).genInRange()
        self.X = GenRandom(10, self.width).genInRange()
        self.Y = GenRandom(10, self.height).genInRange()
        self.RAD = GenRandom(0, 100).genInRange()
        self.RX = GenRandom(10, 30).genInRange()
        self.RY = GenRandom(10, 30).genInRange()
        self.W = GenRandom(10, 100).genInRange()
        self.H = GenRandom(10, 100).genInRange()
        self.R = GenRandom(0, 255).genInRange()
        self.B = GenRandom(0, 255).genInRange()
        self.G = GenRandom(0, 155).genInRange()
        self.OP = GenRandom(0, 1).genFloatRange()


def shape_lists(count, width, height):
    '''creating shape lists method'''
    shape_list = []
    for CNT in range(0, count):
        S = ArtConfig(width, height)
        S_list = [CNT, S.SHA, S.X, S.Y, S.RAD, S.RX, S.RY, S.W, S.H, S.R, S.B, S.G, S.OP]
        shape_list.append(S_list)
    
    return shape_list

def write_table(shape_list):
    '''writing the table of shapes method'''
    print(("{:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5}".format('CNT', 
        'SHA', 'X', 'Y', 'RAD', 'RX', 'RY', 'W', 'H', 'R', 'B', 'G', 'OP')))
    for shape in shape_list:
        CNT, SHA, X, Y, RAD, RX, RY, W, H, R, B, G, OP = shape
        print("{:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5} {:>5}".format(CNT, 
        SHA, X, Y, RAD, RX, RY, W, H, R, B, G, OP))


def main():
    '''main function'''
    LLL = shape_lists(10, 500, 300)
    write_table(LLL)

main()








