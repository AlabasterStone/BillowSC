'''
MIT License\n
Copyright (c) zhangsn 2022\n
All right reserved\n
version 0.1.5[dev]\n
'''

import logging
import json
from zipfile import ZipFile
from typing import Any, Dict, List

# set logger
logging.basicConfig(level=logging.DEBUG)


class scProjectMonitor:
    def __init__(self, id: str, mode: str, opcode: str, params: dict, spriteName: str | None, value: int, visible: bool, sliderMin: int, sliderMax: int, isDiscrete: bool) -> None:
        self.id = id
        self.mode = mode
        self.opcode = opcode
        self.params = params
        self.spriteName = spriteName
        self.value = value
        self.visible = visible
        self.sliderMin = sliderMin
        self.sliderMax = sliderMax
        self.isDiscrete = isDiscrete

    # TODO: compile monitor
    # return C++ code
    def compile(self) -> str:
        # TODO: id有非法字符，变量名需要更换
        return f"scMonitor {self.id}"


class scProjectBlock:
    def __init__(self, blockID: str, opcode: str, nextID: str, parentID: str, inputs: dict, topLevel: bool) -> None:
        self.blockID = blockID
        self.opcode = opcode
        self.nextID = nextID
        self.parentID = parentID
        self.inputs = inputs
        self.topLevel = topLevel

    # TODO: compile block
    # return C++ code
    def compile(self) -> str:
        return ""


class scProjectSprite:
    def __init__(self, isStage: bool, name: str, variables, lists, broadcasts, blocks: List[scProjectBlock], currentCostume: int, costumes, sounds, volume: int, layerOrder: int, tempo: int) -> None:
        self.isStage = isStage
        self.name = name
        self.varibles = variables
        self.lists = lists
        self.broadcasts = broadcasts
        self.blocks = blocks
        self.currentCostume = currentCostume
        self.costumes = costumes
        self.sounds = sounds
        self.volume = volume
        self.layerOrder = layerOrder
        self.tempo = tempo

    # TODO: compile sprite
    # return C++ code
    def compile(self) -> str:
        return ""


class scProjectTarget:
    def __init__(self, sprites: List[scProjectSprite]) -> None:
        self.sprites = sprites

    # TODO: compile object
    # return C++ code
    def compile(self) -> str:
        return ""


class scProjectObject:
    def __init__(self, targets: scProjectTarget, monitors: List[scProjectMonitor], extensions: list) -> None:
        self.targets = targets
        self.monitors = monitors
        self.extensions = extensions

    # TODO: compile object
    # return C++ code
    def compile(self) -> str:
        code = "using namespace billow;"
        code += self.targets.compile()
        for monitor in self.monitors:
            code += monitor.compile()
        return code

# It takes a .sb3 file and parses it into a Python object


class billowProject:
    def __init__(self, scFilePath: str, scFileTargetDir: str) -> None:
        self.scFilePath = scFilePath
        self.scFileTargetDir = scFileTargetDir
        self.scJsonFilePath = f"{scFileTargetDir}/project.json"
        self.unpackZip()

    def unpackZip(self):
        try:
            ZipFile(self.scFilePath, "r").extractall(self.scFileTargetDir)
        except Exception as e:
            logging.error(e)

    def parseSb3Json(self) -> scProjectObject:
        with open(self.scJsonFilePath, "r", encoding="utf-8") as scJsonFileHandle:
            scJsonObject = json.load(scJsonFileHandle)
            scJsonTargets = scJsonObject["targets"]
            scSpritesList = []
            for target in scJsonTargets:
               isStage = target["isStage"]
               name = target["name"]
               variables = target["variables"]
               lists = target["lists"]
               broadcasts = target["broadcasts"]
               blocks = target["blocks"]
               scBlocksList = []
               for blockID, block in blocks.items():
                    if type(block) == Dict:
                        opcode = block['opcode']
                        nextID = block["next"]
                        parentID = block["parent"]
                        inputs = block["inputs"]
                        topLevel = block["topLevel"]
                        scBlocksList.append(scProjectBlock(
                            blockID, opcode, nextID, parentID, inputs, topLevel))
                    elif type(block) == List:
                        pass
               currentCostume = target["currentCostume"]
               costumes = target["costumes"]
               sounds = target["sounds"]
               volume = target["volume"]
               layerOrder = target["layerOrder"]
               tempo = target["tempo"]
               scSpritesList.append(scProjectSprite(isStage, name, variables, lists, broadcasts,
                                    scBlocksList, currentCostume, costumes, sounds, volume, layerOrder, tempo))
            monitors = scJsonObject["monitors"]
            extensions = scJsonObject["extensions"]
            return scProjectObject(scProjectTarget(scSpritesList), monitors, extensions)

# standard compiler


class billowStandard:
    def __init__(self) -> None:
        pass

    def compile(self) -> Any:
        pass

#test function


def testing():
    import pathlib
    import shutil
    if pathlib.Path("./test/testproject").exists():
        shutil.rmtree("./test/testproject")

    obj = billowProject("./test/testproject.sb3",
                        "./test/testproject").parseSb3Json()
    logging.debug(obj.targets.sprites[0].currentCostume)


testing()
