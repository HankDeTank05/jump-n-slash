import os
import os.path
import re
from functools import partial
from tkinter import *
from tkinter.ttk import *

class App:

    def __init__(self):
        self.readLocation = os.path.join("..","jumpnslash-cpp","Jump-n-Slash","assets","textures")

        self.spriteFolders = os.listdir(self.readLocation)
        if "leveltiles" in self.spriteFolders:
            self.spriteFolders.remove("leveltiles")

        self.currentFolder = self.spriteFolders[1]

        self.spriteNamingConvention = "[a-z]+(_){1}[0-9]+([.]png){1}"

        self.usingFolder = os.path.join(self.readLocation, self.currentFolder)

        self.dirItems = os.listdir(self.usingFolder)
        sprites=[]

        # variables that the gui reads
        self.anims={}

        # populate the anims dict
        for i in range(len(self.dirItems)):
            item = self.dirItems[i]
            if re.match(self.spriteNamingConvention, item):
                animName = re.split("[_.]",item)[0]
                if animName not in self.anims:
                    self.anims[animName]=[]
                self.anims[animName].append(item)

        # variable that affect the gui
        self.animListSelection = None # the variable that controls which frames show up in the frame selector

        # 1. main application
        self.root = Tk()
        self.root.title("Connector Editor")
        # self.root.minsize(width=1280, height=720)

        ''' animation selector '''

        # 1.1. animation selector
        self.animSel = LabelFrame(self.root, text="Animation Selector")
        self.animSel.grid(column=0, row=0, sticky=[N,S,E,W])

        # 1.1.1. animation selector title box
        self.animSelTitleBox = Label(self.animSel, text="Animations")
        self.animSelTitleBox.grid(column=0, row=0, columnspan=2)

        # 1.1.2. animation list
        self.animList = Canvas(self.animSel)
        self.animList.grid(column=0, row=1)
        self.animListBtns = []
        for i in range(len(self.anims.keys())):
            btnText = list(self.anims.keys())[i]
            self.animListBtns.append(Button(self.animList, text=btnText, command=partial(self.SelectAnimation, list(self.anims.keys())[i])))
            self.animListBtns[i].grid(column=0,row=i)
        # TODO: create a command for the above buttons that sets this variable

        """
        # 1.1.2.2. animation list scrollbar
        self.animListScroll = Scrollbar(self.animSel, orient="vertical", command=self.animList.yview)
        self.animListScroll.grid(column=1, row=1, sticky=[N,S])
        # TODO: make the scroll bar span the height of the parent widget
        # TODO: make the scroll bar work
        """

        ''' animation editor '''

        # 1.2. animation editor
        self.animEdit = LabelFrame(self.root, text="Animation Editor")
        self.animEdit.grid(column=1, row=0, sticky=[N,S,E,W])

        # 1.2.1. frame selector
        self.frameSel = LabelFrame(self.animEdit, text="Frame Selector")
        self.frameSel.grid(column=0, row=1, sticky=[N,S,E,W])

        # 1.2.1.1. frame list
        self.frameList = Canvas(self.frameSel)
        self.frameList.grid(column=0, row=0)
        self.frameListBtnImgs = {}
        self.frameListBtns = {} # TODO: make it so that the buttons in this list change based on ANIM_LIST_SELECTION
        # populate frameListBtns and frameListBtnImgs
        for key in self.anims.keys():
            self.frameListBtnImgs[key] = []
            self.frameListBtns[key] = []
            for i in range(len(self.anims[key])):
                btnText = self.anims[key][i]
                imgPath = os.path.join(self.usingFolder, btnText)
                self.frameListBtnImgs[key].append(PhotoImage(file=imgPath)) # TODO: create the photoimage here
                self.frameListBtns[key].append(Button(self.frameList, text=btnText, image=self.frameListBtnImgs[key][i], compound=TOP)) # TODO: create the button here

        """
        # 1.2.1.2. frame list scroll bar
        self.frameListScroll = Scrollbar(self.frameSel, orient="horizontal", command=self.frameList.xview)
        self.frameListScroll.grid(column=0, row=1, sticky=[E,W])
        """

        # 1.2.2. frame editor
        self.frameEdit = LabelFrame(self.animEdit, text="Frame Editor")
        self.frameEdit.grid(column=0, row=0)

        # 1.2.2.1. frame viewer
        self.frameView = Canvas(self.frameEdit)
        self.frameView.grid(column=0, row=0)
        # TODO: add stuff to the frame viewer

        # 1.2.2.2. point editor
        self.pointEdit = LabelFrame(self.frameEdit, text="Point Editor")
        self.pointEdit.grid(column=1, row=0, sticky=[N,S,E,W])

        # 1.2.2.2.1. point editor title box
        self.pointEditTitleBox = Label(self.pointEdit, text="Points")
        self.pointEditTitleBox.grid(column=0, row=0, columnspan=2)

        # 1.2.2.2.2. point list
        self.pointList = Canvas(self.pointEdit)
        self.pointList.grid(column=0, row=1)
        self.pointListBoxes = []
        pointBox = Frame(self.pointList)
        pointBox.grid(column=0, row=0)
        pointBoxTitle = Label(pointBox, text="Connector Name")
        pointBoxTitle.grid(column=0, row=0, columnspan=3)
        x = 0
        y = 0
        xEntry = Entry(pointBox, textvariable=x)
        xEntry.grid(column=0, row=1)
        yEntry = Entry(pointBox, textvariable=y)
        yEntry.grid(column=1, row=1)
        setBtn = Button(pointBox, text="Set")
        setBtn.grid(column=2, row=1)

        """
        # 1.2.2.2.3. point list scroll bar
        self.pointListScroll = Scrollbar(self.pointEdit, orient="vertical", command=self.pointList.yview)
        self.pointListScroll.grid(column=1, row=1, sticky=[N,S])
        """


    def SelectAnimation(self, anim: str) -> None:
        # if there are already buttons there, remove them from the list
        if self.animListSelection is not None:
            for i in range(len(self.frameListBtns[self.animListSelection])):
                self.frameListBtns[self.animListSelection][i].grid_remove()
        self.animListSelection = anim
        # add the new buttons to the list
        for i in range(len(self.frameListBtns[self.animListSelection])):
            self.frameListBtns[self.animListSelection][i].grid(column=i,row=0)

    def Run(self) -> None:
        self.root.mainloop()

app = App()
app.Run()
