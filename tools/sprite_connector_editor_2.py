# language imports
import os
import os.path
import tkinter as tk
import tkinter.ttk as ttk
import json
import sys
from functools import partial

sys.path.append("../tools")

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

        # constants

        self.POINT_DATA_FILENAME: str = "points.json"
        self.FRAME_RELIEF: str = "groove"

        self.basePath: str = os.path.join("..", "jumpnslash-cpp", "Jump-n-Slash", "assets", "textures")
        self.basePath = os.path.abspath(self.basePath)

        # options for...
        #             currEntity  currAnim   currSpr  currPoint
        #                  vvv       vvv       vvv       vvv
        self.navTree: dict[str, dict[str, dict[str, dict[str, dict[str, float | None]]]]] = {}

        # populate the navtree
        self.PopulateNavTree()

        self.unsavedChanges = False
        
        self.entityList: list[str] = list(self.navTree.keys())
        self.currEntity: str = None
        self.entityPath: str = None

        self.animList: list[str] = None
        self.currAnim: str = None
        self.animPath: str = None

        self.sprList: list[str] = None
        self.currSpr: str = None
        self.sprPath: str = None
        self.sprIndex: int = None

        ##########################
        # create entity selector #
        ##########################

        self.wEntitySelector: ttk.Labelframe = ttk.Labelframe(self.root, text="Entity Selector")
        # self.wEntitySelector.config(relief=self.FRAME_RELIEF)
        self.wEntitySelector.grid(column=0, row=0, rowspan=2, sticky="nsew")

        self.ES_wButtonList: tk.Canvas = tk.Canvas(self.wEntitySelector)
        self.ES_wButtonList.grid(column=0, row=0)

        self.ES_buttonList: list[ttk.Button] = []
        for i in range(len(self.entityList)):
            entityName: str = self.entityList[i]
            button: ttk.Button = ttk.Button(self.ES_wButtonList, text=entityName, command=partial(self.SelectEntity, entityName))
            button.grid(column=0, row=i)

        # TODO: create vertical scroll bar for entity selector

        #############################
        # create animation selector #
        #############################

        self.wAnimationSelector: ttk.Labelframe = ttk.Labelframe(self.root, text="Animation Selector")
        # self.wAnimationSelector.config(relief=self.FRAME_RELIEF)
        self.wAnimationSelector.grid(column=1, row=0, rowspan=2, sticky="nsew")

        # self.AS_wTitle: ttk.Label = ttk.Label(self.wAnimationSelector, text="Animation Selector")
        # self.AS_wTitle.grid(column=0, row=0) # TODO: add columnspan=2 when a scroll bar gets added

        self.AS_wButtonList: tk.Canvas = tk.Canvas(self.wAnimationSelector)
        self.AS_wButtonList.grid(column=0, row=0)

        # a dict of all animation buttons that may be used at any point.
        # they will be added and removed from the GUI as needed, but all must be created on startup.
        # it has the following structure:
        #                 entity name
        #                         |   list of ttk Buttons, one button for each animation that entity has
        #                        vvv  vvvvvvvvvvvvvvvv
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

        self.wSpriteSelector: ttk.Labelframe = ttk.Labelframe(self.root, text="Sprite Selector")
        # self.wSpriteSelector.config(relief=self.FRAME_RELIEF)
        self.wSpriteSelector.grid(column=2, row=1, columnspan=2, sticky="nsew")

        # self.SS_wTitle = ttk.Label(self.wSpriteSelector, text="Sprite Selector")
        # self.SS_wTitle.grid(column=0, row=0)

        self.SS_wButtonList: tk.Canvas = tk.Canvas(self.wSpriteSelector)
        self.SS_wButtonList.grid(column=0, row=0)

        # a dict of all sprite buttons that may be used at any point.
        # they will be added and removed from the GUI as needed, but all must be created on startup
        # it has the following structure:
        #                             animation name
        #                entity name        |   a list of ttk Buttons, one button for each sprite/frame in that animation
        #                        vvv       vvv  vvvvvvvvvvvvvvvv
        self.SS_buttonDict: dict[str, dict[str, list[ttk.Button]]] = {}
        #   value2 - a list of tk PhotoImages, one image for each sprite/frame in that animation
        self.SS_imgDict: dict[str, dict[str, list[tk.PhotoImage]]] = {}

        # populate the SS_buttonDict and SS_imgDict dictionaries
        for entityName in self.navTree.keys():
            self.SS_buttonDict[entityName] = {}
            self.SS_imgDict[entityName] = {}
            for animName in self.navTree[entityName].keys():
                self.SS_buttonDict[entityName][animName] = []
                self.SS_imgDict[entityName][animName] = []
                spriteFilenameList: list = list(self.navTree[entityName][animName].keys())
                for i in range(len(spriteFilenameList)):
                    sprName: str = spriteFilenameList[i]
                    imgPath: str = os.path.join(self.basePath, entityName, sprName)
                    # print(imgPath)
                    img: tk.PhotoImage = tk.PhotoImage(file=imgPath)
                    self.SS_imgDict[entityName][animName].append(img)
                    btn: ttk.Button = ttk.Button(self.SS_wButtonList, text=sprName, image=img, compound=tk.TOP, command=partial(self.SelectSprite, sprName, i))
                    self.SS_buttonDict[entityName][animName].append(btn)

        self.SS_activeButtonList: list[ttk.Button] = [] # this starts as an empty list because it will be set by the SelectAnimation function

        # TODO: create horizontal scroll bar for sprite selector

        ########################
        # create sprite viewer #
        ########################

        self.wSpriteViewer: ttk.Labelframe = ttk.Labelframe(self.root, text="Sprite Viewer")
        # self.wSpriteViewer.config(relief=self.FRAME_RELIEF)
        self.wSpriteViewer.grid(column=2, row=0, sticky="nsew")

        # self.SV_wTitle: ttk.Label = ttk.Label(self.wSpriteViewer, text="Sprite Viewer")
        # self.SV_wTitle.grid(column=0, row=0, columnspan=2)

        self.SV_wPointSliderH: ttk.Scale = ttk.Scale(self.wSpriteViewer, orient="horizontal")
        self.SV_wPointSliderH.config(state=tk.DISABLED) # TODO: make it so the horizontal point slider can be enabled
        self.SV_wPointSliderH.grid(column=1, row=0)

        self.SV_wPointSliderV: ttk.Scale = ttk.Scale(self.wSpriteViewer, orient="vertical")
        self.SV_wPointSliderV.config(state=tk.DISABLED) # TODO: make it so the vertical point slider can be enabled
        self.SV_wPointSliderV.grid(column=0, row=1)

        self.SV_wSpriteDisplay: tk.Canvas = tk.Canvas(self.wSpriteViewer)
        self.SV_wSpriteDisplay.grid(column=1, row=1)

        # more code goes here

        #######################
        # create point editor #
        #######################

        self.wPointEditor: ttk.Labelframe = ttk.Labelframe(self.root, text="Point Editor")
        # self.wPointEditor.config(relief=self.FRAME_RELIEF)
        self.wPointEditor.grid(column=3, row=0, sticky="nsew")

        # self.PE_wTitle: ttk.Label = ttk.Label(self.wPointEditor, text="Point Editor")
        # self.PE_wTitle.grid(column=0, row=0) # TODO: add columnspan=2 when a scroll bar gets added

        self.PE_wPointList: tk.Canvas = tk.Canvas(self.wPointEditor)
        self.PE_wPointList.grid(column=0, row=0)

        # TODO: create editors for any points that exist
        # a dict of all point editor list items that may be used at any point (new ones may be added during runtime)
        # they will be added and removed from the GUI as needed, but all must be created on startup
        # it has the following structure:
        #                                                        "frame" or   the frame containing
        #                   entity name                      "nameLabel" or   the following widgets:
        #                       |    animation name           "posLabel" or     |     the point name label or
        #                       |         |  sprite filename       "button"     |     the point position label
        #                       |         |         |   point name      |       |       |                  the "set point" button
        #                      vvv       vvv       vvv       vvv       vvv  vvvvvvvvv   vvvvvvvvv   vvvvvvvvvv
        self.PE_itemDict: dict[str, dict[str, dict[str, dict[str, dict[str, ttk.Frame | ttk.Label | ttk.Button]]]]] = {}
        # populate the point editor items dict
        for entityName in self.navTree.keys():
            self.PE_itemDict[entityName] = {}
            for animName in self.navTree[entityName].keys():
                self.PE_itemDict[entityName][animName] = {}
                for spriteFilename in self.navTree[entityName][animName].keys():
                    self.PE_itemDict[entityName][animName][spriteFilename] = {}
                    for pointName in self.navTree[entityName][animName][spriteFilename].keys():
                        self.PointEditor_CreateItem(entityName, animName, spriteFilename, pointName)

        self.PE_activeItemList: list[dict[str, ttk.Frame | ttk.Label | ttk.Button]] = []

        '''
        # the following is a sample point
        frame: ttk.Frame = ttk.Frame(self.PE_wPointList)
        frame.config(borderwidth=5, relief="groove")
        frame.grid(column=0, row=0)
        pointName: str = "pointName1"
        pointNameLabel: ttk.Label = ttk.Label(frame, text=pointName)
        pointNameLabel.grid(column=0, row=0)
        pointPosLabel: ttk.Label = ttk.Label(frame, text="Position: Not Set") # TODO: modify the text in this label when the point position changes (should either show "Not Set" or "(x, y)")
        pointPosLabel.grid(column=0, row=1)
        setPointButton: ttk.Button = ttk.Button(frame, text="Set Point") # TODO: add a command to be executed when this button is pressed
        setPointButton.grid(column=0, row=2)
        '''

        self.PE_wAddPointButton: ttk.Button = ttk.Button(self.wPointEditor, text="Add Point", command=partial(self.OpenPopupAddPoint))
        self.PE_wAddPointButton.config(state=tk.DISABLED)
        self.PE_wAddPointButton.grid(column=0, row=1)

        self.PE_wSaveChangesButton: ttk.Button = ttk.Button(self.wPointEditor, text="Save Changes")
        self.PE_wSaveChangesButton.config(state=tk.DISABLED)
        self.PE_wSaveChangesButton.grid(column=0, row=2)
        # TODO: make it possible to enable this button
        # TODO: add a command to be executed when this button is pressed

        # TODO: create a vertical scroll bar for point editor

        ###################################
        # create "add point" popup window #
        ###################################

        self.popup_window: tk.Toplevel = None # NOTE: this window and the widgets it contains will be created later

    ############################
    # select <thing> functions #
    ############################

    def SelectEntity(self, entity: str) -> None:
        path: str = os.path.join(self.basePath, entity)
        assert os.path.isdir(path), f"path is: {path}"
        self.entityPath = path # set the entity path
        self.currEntity = entity # set the current entity name
        self.animList = list(self.navTree[self.currEntity].keys()) # set the animation list

        # TODO: clear sprite viewer canvas

        self.PointEditor_ClearItems()

        self.SpriteSelector_ClearButtons()

        self.AnimationSelector_ClearButtons()

        self.AnimationSelector_AddButtons()

        print(f"Entity \"{self.currEntity}\" selected")

    '''function to select an animation (this will be called when an animation button is pressed)'''
    def SelectAnimation(self, anim: str) -> None:
        path: str = self.entityPath
        assert os.path.isdir(path), f"path is: {path}"
        self.animPath = path
        self.currAnim = anim
        self.sprList = self.navTree[self.currEntity][self.currAnim]

        # TODO: clear sprite viewer canvas

        self.PointEditor_ClearItems()

        self.SpriteSelector_ClearButtons()

        self.SpriteSelector_AddButtons()
        
        print(f"Animation \"{self.currAnim}\" selected")

    '''function to select a sprite (this will be called when a sprite button is pressed)'''
    def SelectSprite(self, sprFilename: str, index: int) -> None:
        path: str = os.path.join(self.animPath, sprFilename)
        assert os.path.isfile(path), f"path is: {path}"
        self.sprPath = path
        self.currSpr = sprFilename

        self.PointEditor_AddItems(self.currEntity, self.currAnim, self.currSpr)

        # TODO: place sprite on canvas

        # TODO: the following code is messy. clean that shit up lol
        # modify GUI elements once a sprite is selected
        self.PE_wAddPointButton.config(state=tk.ACTIVE) # enable the "Add Point" button
        image: tk.PhotoImage = self.SS_imgDict[self.currEntity][self.currAnim][index]
        self.SV_wSpriteDisplay.config(width=image.width(), height=image.height())
        self.SV_wSpriteDisplay.create_image(0, 0, image=image, anchor="nw")
        self.SV_wPointSliderH.config(length=image.width(), from_=0.0, to=image.width() - 1)
        self.SV_wPointSliderV.config(length=image.height(), from_=0.0, to=image.height() - 1)

        print(f"Sprite \"{self.currSpr}\" selected")

    '''function to select a point (this will be called when the "set point" button is clicked)'''
    def SelectPoint(self) -> None:
        # TODO: enable sliders on canvas
        assert False

    ##########################################
    # add/remove items to/from GUI functions #
    ##########################################

    '''add animation buttons to animation selector GUI'''
    def AnimationSelector_AddButtons(self) -> None:
        # add the new buttons to the list
        self.AS_activeButtonList = self.AS_buttonDict[self.currEntity]
        for i in range(len(self.AS_activeButtonList)):
            # place the button in the GUI
            self.AS_activeButtonList[i].grid(column=0, row=i)

    '''remove animation buttons from the animation selector GUI'''
    def AnimationSelector_ClearButtons(self) -> None:
        # remove existing buttons from the list of animation buttons, if necessary
        if len(self.AS_activeButtonList) > 0:
            for button in self.AS_activeButtonList:
                button.grid_remove()

    '''add sprite buttons to sprite selector GUI'''
    def SpriteSelector_AddButtons(self) -> None:
        # add the new buttons to the list
        self.SS_activeButtonList = self.SS_buttonDict[self.currEntity][self.currAnim]
        for i in range(len(self.SS_activeButtonList)):
            # place the button in the gui
            self.SS_activeButtonList[i].grid(column=i, row=0)

    '''remove sprite buttons from the sprite selector GUI'''
    def SpriteSelector_ClearButtons(self) -> None:
        # remove existing buttons from the list, if necessary
        if len(self.SS_activeButtonList) > 0:
            for button in self.SS_activeButtonList:
                button.grid_remove()

    '''add point item editors to the point editor GUI'''
    def PointEditor_AddItems(self, entityName: str, animName: str, sprFilename: str) -> None:
        points: dict[str, dict[str, float | None]] = self.navTree[entityName][animName][sprFilename]
        pointNameList: list[str] = list(points.keys())
        for i in range(len(pointNameList)):
            pointName: str = pointNameList[i]
            itemFrame: ttk.Frame = self.PE_itemDict[entityName][animName][sprFilename][pointName]["frame"]
            itemFrame.grid(column=0, row=i)

    '''remove point item editors from the point editor GUI'''
    def PointEditor_ClearItems(self) -> None:
        # remove existing item editors from the list, if necessary
        if len(self.PE_activeItemList) > 0:
            for item in self.PE_activeItemList:
                item["frame"].grid_remove()

    def PointEditor_CreateItem(self, entityName: str, animName: str, sprFilename: str, pointName: str) -> None:
        jns.PrintDict(self.PE_itemDict)
        itemFrame: ttk.Frame = ttk.Frame(self.PE_wPointList)
        nameLabel: ttk.Label = ttk.Label(itemFrame, text=pointName)
        nameLabel.grid(column=0, row=0, columnspan=2)
        posText: str
        # TODO: turn the following branching if statement into a function so the "set point" button is able to change the position text
        if self.navTree[entityName][animName][sprFilename][pointName]["posX"] == None:
            posText = "Not Set"
        else:
            posX: float = self.navTree[entityName][animName][sprFilename][pointName]["posX"]
            posY: float = self.navTree[entityName][animName][sprFilename][pointName]["posY"]
            posText = f"({posX}, {posY})"
        posLabel: ttk.Label = ttk.Label(itemFrame, text=posText)
        posLabel.grid(column=0, row=1)
        setPointButton: ttk.Button = ttk.Button(itemFrame, text="Set Point") # TODO: add a command to make this button work
        setPointButton.grid(column=1, row=1)
        self.PE_itemDict[entityName][animName][sprFilename][pointName] = {
            "frame": itemFrame,
            "nameLabel": nameLabel,
            "posLabel": posLabel,
            "button": setPointButton
        }
        jns.PrintDict(self.PE_itemDict)

    ##########################
    # popup window functions #
    ##########################

    def WriteStringVar(self, var, index, mode) -> None:
        print(f"Traced variable {self.popup_pointName.get()}")

    def OpenPopupAddPoint(self) -> None:
        self.popup_window = tk.Toplevel(self.root)
        self.popup_pointName: tk.StringVar = tk.StringVar()
        self.popup_pointName.trace_add("write", self.WriteStringVar)
        self.popup_descLabel: ttk.Label = ttk.Label(self.popup_window, text="Please enter the name of the new point in the text box below, and then click the \"confirm\" button.")
        self.popup_descLabel.grid(column=0, row=0)
        self.popup_textBox: ttk.Entry = ttk.Entry(self.popup_window, textvariable=self.popup_pointName)
        self.popup_textBox.grid(column=0, row=1)
        self.popup_confirmButton: ttk.Button = ttk.Button(self.popup_window, text="Confirm", command=partial(self.ClosePopupAddPoint, self.popup_window, self.popup_pointName))
        self.popup_confirmButton.grid(column=0, row=2)

    def ClosePopupAddPoint(self, popup: tk.Toplevel, pointName: tk.StringVar) -> None:
        assert pointName.get() is not None # make sure they actually put something in for the name
        assert len(pointName.get()) > 0 # make sure the name is not an empty string
        assert pointName.get().isalnum() == True # make sure the name of the point is alphanumeric

        # check if the point name already exists
        nameExists: bool = self.PointNameExists(self.currEntity, pointName.get())
        if nameExists == True:
            assert False # TODO: make them re-enter the name
        else:
            # close the popup
            popup.destroy()
            # add the point to the point data
            self.AddNewPoint(self.currEntity, self.currAnim, self.currSpr, pointName.get())
            # TODO: refresh point list
            self.PointEditor_ClearItems()
            self.PointEditor_AddItems(self.currEntity, self.currAnim, self.currSpr)

    #####################
    # navtree functions #
    #####################

    def AddNewPoint(self, entityName: str, animName: str, sprFilename: str, pointName: str) -> None:
        assert entityName in self.navTree.keys()
        #jns.PrintDict(self.navTree[entityName])
        for animName in self.navTree[entityName].keys():
            for sprFilename in self.navTree[entityName][animName].keys():
                pointData: dict = {
                    "posX": None,
                    "posY": None
                }
                self.navTree[entityName][animName][sprFilename][pointName] = pointData
        #jns.PrintDict(self.navTree[entityName])
        self.PointEditor_CreateItem(entityName, animName, sprFilename, pointName)
        self.unsavedChanges = True

    def PointNameExists(self, entityName: str, pointName: str) -> bool:
        #self.ValidateData()
        animName: str = list(self.navTree[entityName].keys())[0]
        sprFilename: str = list(self.navTree[entityName][animName].keys())[0]
        if pointName in self.navTree[entityName][animName][sprFilename].keys():
            return True
        else:
            return False
        
    def ValidateData(self) -> None:
        # TODO: for each entity, make sure that the same point names exist for every sprite in every animation
        assert False


    ##################
    # json functions #
    ##################

    def LoadPointsFromJson(self) -> None:
        assert False

    def ReadJsonFile(self, entityPath: str) -> dict | None:
        data: dict | None
        pathToJson: str = os.path.join(entityPath, self.POINT_DATA_FILENAME)
        if os.path.exists(pathToJson) == True:
            with open(self.POINT_DATA_FILENAME, 'r') as jsonFile:
                data = json.loads(jsonFile)
            print(f"loaded the following data from {pathToJson}: ")
            jns.PrintDict(data)
        else:
            data = None
            print(f"no json data exists for {entityPath}")
        
        return data

    def WriteJsonFile(self, data: dict) -> None:
        assert self.entityPath is not None
        filePath: str = os.path.join(self.entityPath, self.POINT_DATA_FILENAME)
        with open(filePath, 'w') as jsonFile:
            output: str = json.dumps(data)
            print(output, file=jsonFile)
            print(f"the following data has been written to {filePath}:\n{output}")

    ###################
    # other functions #
    ###################

    def Run(self) -> None:
        self.root.mainloop()

    def PopulateNavTree(self) -> None:
        subdirectories: list[str] = jns.GetFoldersAtPath(self.basePath)
        # STEP 1: create dict keys for each entityName
        for entityName in subdirectories:
            # create a sub-dictionary for each directory in the textures folder
            self.navTree[entityName] = {}
            #print(entityName)
            
            currDirectory: str = os.path.join(self.basePath, entityName)

            # get a list of files in the directory
            files: list[str] = jns.GetFilesWithConvention(currDirectory, jns.CONVENTION_SPR_ENTITY)
            animations: list[str] = [] # create an empty animation list, to be populated momentarily
            for file in files:
                # get the animation name by splitting the file name at the underscore and only keeping the first substring
                animName = file.split("_")[0] # NOTE: if the naming convention for entity sprite files changes, this may no longer work!
                if animName not in animations:
                    animations.append(animName) # only add unique animation names to the list

            # STEP 2: load point data from the json file in this directory (if it exists)
            #          list of point names       sprite filename
            #      "pointNames"      |             |       point name (from the list of point names)
            #      or "sprites"      |             |         |       "posX" or "posY"
            #                |       |             |         |         |    pos    only None if point is not set
            #               vvv  vvvvvvvvv        vvv       vvv       vvv  vvvvv   vvvv
            pointData: dict[str, list[str] | dict[str, dict[str, dict[str, float | None]]]] = self.ReadJsonFile(currDirectory)
            
            # STEP 3: create dict keys for each animName
            for animName in animations:
                #print(f"\t{animName}")
                self.navTree[entityName][animName] = {}
                for spriteFilename in files:
                    
                    # STEP 4: create dict keys for each spriteFilename
                    if animName in spriteFilename:
                        self.navTree[entityName][animName][spriteFilename] = {}
                        #print(f"\t\t{spriteFilename}")

                        # STEP 5: create dict keys for each pointName (if any point data was read. otherwise, do nothing)
                        if pointData is not None:
                            for point in pointData["sprites"][spriteFilename].keys(): # TODO: bad boy! create a constant instead of using string literals!
                                self.navTree[entityName][animName][spriteFilename][point] = pointData["sprites"][point] # TODO: ^^^ditto^^^

        # STEP 6: remove any entityName entries whose value is an empty dict
        entriesToRemove: list[str] = []
        for entry in self.navTree.keys():
            # if an entityName has no animName entries, add the entityName to a list of keys to be removed
            if len(self.navTree[entry].keys()) == 0: 
                entriesToRemove.append(entry)
        for entry in entriesToRemove:
            del self.navTree[entry]

        # sanity check: print the navtree
        print("navTree:")
        jns.PrintDict(self.navTree)

app: App = App()
app.Run()
