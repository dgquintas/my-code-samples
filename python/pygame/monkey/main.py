import pygame, sys

from pygame.locals import *

pygame.init()

window = pygame.display.set_mode( (468, 60) )
pygame.display.set_caption('El monooooo')
screen = pygame.display.get_surface()

monkey_img_file = './chimp.bmp'
monkey_img = pygame.image.load(monkey_img_file)

screen.blit(monkey_img, (0,0) )
pygame.display.flip()

def input(events):
    for event in events:
        if event.type == QUIT:
            sys.exit(0)
        else:
            print event

while True:
    input(pygame.event.get())
