from Tkinter import *

class App(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.grid()
        self.createWidgets()

    def createWidgets(self):
        self.quitButton = Button(self, text='LOL!!1', command=self.quit)
        self.quitButton.grid()

app = App()
app.master.title("Hola mundo cruel")
app.mainloop()
