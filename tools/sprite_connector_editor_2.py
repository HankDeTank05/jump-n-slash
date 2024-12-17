# language imports
import os
import os.path
import tkinter as tk
import tkinter.ttk as ttk
from typing import ClassVar
from functools import partial

# game imports
import jnscommon as jns

class App:

    def __init__(self) -> None:

        # create the application window
        
        self.root = tk.Tk()
        self.root.title("Sprite Connector Editor")
        self.root.config(bg="black")
        # self.root.minsize(width = 1280, height = 720)

        ########################################
        # create required non-widget variables #
        ########################################

        self.basePath: str = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures")
        self.basePath = os.path.abspath(self.basePath)

        self.pointDataFilename: str = "points.json"

        # a dict of point data for a given entity.
        # this data will be loaded (or created, if it does not exist) when an entity is selected.
        # it uses the structure described in this slide deck: https://docs.google.com/presentation/d/1PLaKS3PRtIwJiQ7IzcTYcf-TwL2bH8FPD6039gOLogA/edit#slide=id.g323f716582b_0_1
        self.pointData: 

        self.navTree: dict[str, dict[str, list[str]]] = {}

        # populate the navtree
        subdirectories: list[str] = jns.GetFoldersAtPath(self.basePath)
        for directory in subdirectories:
            # create a sub-dictionary for each directory in the textures folder
            self.navTree[directory] = {}
            #print(directory)
            
            # get a list of files in the directory
            files: list[str] = jns.GetFilesWithConvention(os.path.join(self.basePath, directory), jns.CONVENTION_ENTITY)
            animations: list[str] = [] # create an empty animation list, to be populated momentarily
            for file in files:
                # get the animation name by splitting the file name at the underscore and only keeping the first substring
                # NOTE: if the naming convention for entity sprite files changes, this may no longer work!
                animName = file.split("_")[0]
                if animName not in animations:
                    animations.append(animName) # only add unique animation names to the list
            
            for animationName in animations:
                #print(f"\t{animationName}")
                self.navTree[directory][animationName] = []
                for fileName in files:
                    if animationName in fileName:
                        self.navTree[directory][animationName].append(fileName)
                        #print(f"\t\t{fileName}")

        # remove any dict entries with empty values
        entriesToRemove: list[str] = []
        for entry in self.navTree.keys():
            # remove its entry from the navtree if an entity has no animations
            if len(self.navTree[entry].keys()) == 0: 
                entriesToRemove.append(entry)
        for entry in entriesToRemove:
            del self.navTree[entry]

        # sanity check: print the navtree
        print("navTree:")
        for entity in self.navTree.keys():
            print(entity)
            # print the animations
            for animation in self.navTree[entity].keys():
                print(f"\t{animation}")
                for sprite in self.navTree[entity][animation]:
                    print(f"\t\t{sprite}")
        
        self.entityList: list[str] = list(self.navTree.keys())
        self.currEntity: str = None
        self.entityPath: str = None

        self.animList: list[str] = None
        self.currAnim: str = None
        self.animPath: str = None

        self.sprList: list[str] = None
        self.currSpr: str = None
        self.sprPath: str = None

        ##########################
        # create entity selector #
        ##########################

        self.wEntitySelector: ttk.Frame = ttk.Frame(self.root)
        self.wEntitySelector.grid(column=0, row=0, rowspan=2, sticky="nsew")

        self.ES_wTitle: ttk.Label = ttk.Label(self.wEntitySelector, text="Entity Selector")
        self.ES_wTitle.grid(column=0, row=0) # TODO: add columnspan=2 when a scroll bar gets added

        self.ES_wButtonList: tk.Canvas = tk.Canvas(self.wEntitySelector)
        self.ES_wButtonList.grid(column=0, row=1)

        self.ES_buttonList: list[ttk.Button] = []
        for i in range(len(self.entityList)):
            entityName: str = self.entityList[i]
            button: ttk.Button = ttk.Button(self.ES_wButtonList, text=entityName, command=partial(self.SelectEntity, entityName))
            button.grid(column=0, row=i)

        # TODO: create vertical scroll bar for entity selector

        #############################
        # create animation selector #
        #############################

        self.wAnimationSelector: ttk.Frame = ttk.Frame(self.root)
        self.wAnimationSelector.grid(column=1, row=0, rowspan=2, sticky=[tk.N])

        self.AS_wTitle: ttk.Label = ttk.Label(self.wAnimationSelector, text="Animation Selector")
        self.AS_wTitle.grid(column=0, row=0) # TODO: add columnspan=2 when a scroll bar gets added

        self.AS_wButtonList: tk.Canvas = tk.Canvas(self.wAnimationSelector)
        self.AS_wButtonList.grid(column=0, row=1)

        # a dict of all animation buttons that may be used at any point.
        # they will be added and removed from the GUI as needed, but all must be created on startup.
        # it uses the following structure:
        # key - a string, the entity name
        # value - a list of ttk Buttons, one button for each animation that entity has
        self.AS_buttonDict: dict[str, list[ttk.Button]] = {}

        # populate the AS_buttonDict dictionary
        for entity in self.navTree.keys():
            self.AS_buttonDict[entity] = []
            animList: list[str] = list(self.navTree[entity].keys())
            for i in range(len(animList)):
                animName: str = animList[i]
                btn: ttk.Button = ttk.Button(self.AS_wButtonList, text=animName, command=partial(self.SelectAnimation, animName))
                self.AS_buttonDict[entity].append(btn)
        
        self.AS_activeButtonList: list[ttk.Button] = [] # this starts as an empty list because it will be set by the SelectEntity function

        # TODO: create vertical scroll bar for animation selector

        ##########################
        # create sprite selector #
        ##########################

        self.wSpriteSelector: ttk.Frame = ttk.Frame(self.root)
        self.wSpriteSelector.grid(column=2, row=1) # TODO: add columnspan=2 when a scroll bar gets added

        self.SS_wButtonList: tk.Canvas = tk.Canvas(self.wSpriteSelector)
        self.SS_wButtonList.grid(column=0, row=0)

        # a dict of all sprite buttons that may be used at any point.
        # they will be added and removed from the GUI as needed, but all must be created on startup
        # it uses the following structure:
        # key1 - a string, the entity name
        # value1 - a dictionary, where the keys/values have the following format:
        #   key2 - a string, the animation name
        #   value2 - a list of ttk Buttons, one button for each sprite/frame in that animation
        self.SS_buttonDict: dict[str, dict[str, list[ttk.Button]]] = {}
        self.SS_imgDict: dict[str, dict[str, list[tk.PhotoImage]]] = {}

        # populate the SS_buttonDict and SS_imgDict dictionaries
        for entity in self.navTree.keys():
            self.SS_buttonDict[entity] = {}
            self.SS_imgDict[entity] = {}
            for animName in self.navTree[entity].keys():
                self.SS_buttonDict[entity][animName] = []
                self.SS_imgDict[entity][animName] = []
                for sprName in self.navTree[entity][animName]:
                    imgPath: str = os.path.join(self.basePath, entity, sprName)
                    print(imgPath)
                    img: tk.PhotoImage = tk.PhotoImage(file=imgPath)
                    self.SS_imgDict[entity][animName].append(img)
                    btn: ttk.Button = ttk.Button(self.SS_wButtonList, text=sprName, image=img, compound=tk.TOP, command=partial(self.SelectSprite, sprName))
                    self.SS_buttonDict[entity][animName].append(btn)

        self.SS_activeButtonList: list[ttk.Button] = [] # this starts as an empty list because it will be set by the SelectAnimation function

        # TODO: create horizontal scroll bar for sprite selector

        ########################
        # create sprite viewer #
        ########################

        self.wSpriteViewer: tk.Canvas = tk.Canvas(self.root)
        self.wSpriteViewer.grid(column=2, row=0)

        # more code goes here

        #######################
        # create point editor #
        #######################

        self.wPointEditor: ttk.Frame = ttk.Frame(self.root)
        self.wPointEditor.grid(column=3, row=0)

        self.PE_wTitle: ttk.Label = ttk.Label(self.wPointEditor, text="Point Editor")
        self.PE_wTitle.grid(column=0, row=0) # TODO: add columnspan=2 when a scroll bar gets added

        self.PE_wPointList: tk.Canvas = tk.Canvas(self.wPointEditor)
        self.PE_wPointList.grid(column=0, row=1)

        self.PE_wAddPointButton: ttk.Button = ttk.Button(self.wPointEditor, text="Add Point", default="disabled")
        self.PE_wAddPointButton.grid(column=0, row=2)
        # TODO: make it possible to enable this button
        # TODO: add a command to be executed when this button is pressed

        # TODO: create a vertical scroll bar for point editor

    def SelectEntity(self, entity: str) -> None:
        path: str = os.path.join(self.basePath, entity)
        assert os.path.isdir(path), f"path is: {path}"
        self.entityPath = path # set the entity path
        self.currEntity = entity # set the current entity name
        self.animList = list(self.navTree[self.currEntity].keys()) # set the animation list

        self.ClearButtonsAnimationSelector()

        self.AddButtonsAnimationSelector()

        self.ClearButtonsSpriteSelector()

        # TODO: load point data from a json file. if it doesn't exist, create one

        print(f"Entity \"{self.currEntity}\" selected")

    '''function to select an animation (this will be called when an animation button is pressed)'''
    def SelectAnimation(self, anim: str) -> None:
        path: str = self.entityPath
        assert os.path.isdir(path), f"path is: {path}"
        self.animPath = path
        self.currAnim = anim
        self.sprList = self.navTree[self.currEntity][self.currAnim]

        self.ClearButtonsSpriteSelector()

        self.AddButtonsSpriteSelector()
        
        print(f"Animation \"{self.currAnim}\" selected")

    '''function to select a sprite (this will be called when a sprite button is pressed)'''
    def SelectSprite(self, spr: str) -> None:
        path: str = os.path.join(self.animPath, spr)
        assert os.path.isfile(path), f"path is: {path}"
        self.sprPath = path
        self.currSpr = spr
        print(f"Sprite \"{self.currSpr}\" selected")

    '''remove animation buttons from the animation selector GUI'''
    def ClearButtonsAnimationSelector(self) -> None:
        # remove existing buttons from the list of animation buttons, if necessary
        if len(self.AS_activeButtonList) > 0:
            for button in self.AS_activeButtonList:
                button.grid_remove()

    '''remove sprite buttons from the sprite selector GUI'''
    def ClearButtonsSpriteSelector(self) -> None:
        # remove existing buttons from the list, if necessary
        if len(self.SS_activeButtonList) > 0:
            for button in self.SS_activeButtonList:
                button.grid_remove()

    '''add animation buttons to animation selector GUI'''
    def AddButtonsAnimationSelector(self) -> None:
        # add the new buttons to the list
        self.AS_activeButtonList = self.AS_buttonDict[self.currEntity]
        for i in range(len(self.AS_activeButtonList)):
            # place the button in the GUI
            self.AS_activeButtonList[i].grid(column=0, row=i)

    '''add sprite buttons to sprite selector GUI'''
    def AddButtonsSpriteSelector(self) -> None:
        # add the new buttons to the list
        self.SS_activeButtonList = self.SS_buttonDict[self.currEntity][self.currAnim]
        for i in range(len(self.SS_activeButtonList)):
            # place the button in the gui
            self.SS_activeButtonList[i].grid(column=i, row=0)

    def LoadPointsFromJSON(self) -> None:
        pass


    def Run(self) -> None:
        self.root.mainloop()

app: App = App()
app.Run()
