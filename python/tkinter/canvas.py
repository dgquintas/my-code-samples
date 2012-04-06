from Tkinter import *

class App(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.grid()
        self.createWidgets()

    def createWidgets(self):
        self.canvas = Canvas(width=1000, height=600)
        self.canvas.grid()

    def addSegment(self, (x0, y0), (x1, y1) ):
        DOT_SIZE = 5.0
        # source point: oval around (x0,y0)
        self.canvas.create_oval( x0-DOT_SIZE/2, y0-DOT_SIZE/2, x0+DOT_SIZE/2, y0+DOT_SIZE/2 )
        self.canvas.create_line( x0, y0, x1, y1 )
        self.canvas.create_oval( x1-DOT_SIZE/2, y1-DOT_SIZE/2, x1+DOT_SIZE/2, y1+DOT_SIZE/2, fill='black' )

app = App()
app.addSegment( (10, 20), (456, 484) )
app.mainloop()

print("foo")
