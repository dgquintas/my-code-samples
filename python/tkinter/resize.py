from tkinter import *

class app( Frame ):
    def __init__( self, master=None ):
        Frame.__init__( self, master )
        self.grid( sticky='nswe' )
        top = self.winfo_toplevel()
        top.rowconfigure( 0, weight=1 )
        top.columnconfigure( 0, weight=1 )

        self.rowconfigure( 0, weight=1 )
        self.columnconfigure( 0, weight=1 )
        
        self.b = Canvas( self, bg='gray' )
        self.b.grid( row=0, column=0, sticky='nswe' )
        self.b.create_line( 1,1, 10, 10)
if __name__ == "__main__":
    root = Tk()
    appl = app( master=root )
    appl.mainloop()

