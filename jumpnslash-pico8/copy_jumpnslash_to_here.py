import os
import shutil

src_path = ""
with open(os.path.join(os.getcwd(), "copy_to_path.txt"), mode='rt') as file:
    src_path = file.readline()

dst_path = os.getcwd()

fname = "jumpnslash.p8"

shutil.copy(os.path.join(src_path, fname), os.path.join(dst_path, fname))
