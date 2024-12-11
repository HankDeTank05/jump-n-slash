import os
import os.path
import re
from tkinter import *
from tkinter.ttk import *

readLocation = os.path.join("..","jumpnslash-cpp","Jump-n-Slash","assets","textures")

spriteFolders = os.listdir(readLocation)

spriteNamingConvention = "[a-z]+(_){1}[0-9]+([.]png){1}"

usingFolder = os.path.join(readLocation, "player")

dirItems = os.listdir(usingFolder)
sprites=[]
anims={}
for i in range(len(dirItems)):
    item = dirItems[i]
    if re.match(spriteNamingConvention, item):
        animName = re.split("[_.]",item)[0]
        if animName not in anims:
            anims[animName]=[]
        anims[animName].append(item)
        print(item)

# 1. main application
root = Tk()
root.title("Connector Editor")
#root.minsize(width=1280, height=720)

''' animation selector '''

# 1.1. animation selector
animSel = LabelFrame(root, text="Animation Selector")
animSel.grid(column=0, row=0)

# 1.1.1. animation selector title box
animSelTitleBox = Label(animSel, text="Animations")
animSelTitleBox.grid(column=0, row=0, columnspan=2)

# 1.1.2. animation list
animList = Canvas(animSel)
animList.grid(column=0, row=1)
animListBtns = []
for i in range(len(anims.keys())):
    btnText = list(anims.keys())[i]
    animListBtns.append(Button(animList, text=btnText))
    animListBtns[i].grid(column=0,row=i)
ANIM_LIST_SELECTION = list(anims.keys())[4] # the variable that controls which frames show up in the frame selector
# TODO: create a command for the above buttons that sets this variable

# 1.1.2.2. animation list scrollbar
animListScroll = Scrollbar(animSel, command=animList.yview)
animListScroll.grid(column=1, row=1)
# TODO: make the scroll bar span the height of the parent widget
# TODO: make the scroll bar work

''' animation editor '''

# 1.2. animation editor
animEdit = LabelFrame(root, text="Animation Editor")
animEdit.grid(column=1, row=0)

# 1.2.1. frame selector
frameSel = LabelFrame(animEdit, text="Frame Selector")
frameSel.grid(column=0, row=1)

# 1.2.1.1. frame list
frameList = Canvas(frameSel)
frameList.grid(column=0, row=0)
frameListBtns = [] # TODO: make it so that the buttons in this list change based on ANIM_LIST_SELECTION
frameListBtnImgs = []
if ANIM_LIST_SELECTION is not None:
    for i in range(len(anims[ANIM_LIST_SELECTION])):
        btnText = anims[ANIM_LIST_SELECTION][i]
        imgPath = os.path.join(usingFolder, btnText)
        print(type(imgPath))
        print(imgPath)
        frameListBtnImgs.append(PhotoImage(file=imgPath))
        frameListBtns.append(Button(frameList, text=btnText, image=frameListBtnImgs[i], compound=TOP))
        frameListBtns[i].grid(column=i, row=0)

# 1.2.1.2. frame list scroll bar
frameListScroll = Scrollbar(frameSel, orient="horizontal", command=frameList.xview)
frameListScroll.grid(column=0, row=1)

# 1.2.2. frame editor
frameEdit = LabelFrame(animEdit, text="Frame Editor")
frameEdit.grid(column=0, row=0)

# 1.2.2.1. frame viewer
frameView = Canvas(frameEdit)
frameView.grid(column=0, row=0)
# TODO: add stuff to the frame viewer

# 1.2.2.2. point editor
pointEdit = LabelFrame(frameEdit, text="Point Editor")
pointEdit.grid(column=1, row=0)

# 1.2.2.2.1. point editor title box
pointEditTitleBox = Label(pointEdit, text="Points")
pointEditTitleBox.grid(column=0, row=0, columnspan=2)

# 1.2.2.2.2. point list
pointList = Canvas(pointEdit)
pointList.grid(column=0, row=1)
# TODO: add point editor boxes to the point list

# 1.2.2.2.3. point list scroll bar
pointListScroll = Scrollbar(pointEdit, command=pointList.yview)
pointListScroll.grid(column=1, row=1)

root.mainloop()
