import os
import shutil
import subprocess

method = 2

# 1. read the path from "copy_to_path.txt"
dst_path = ""
with open(os.path.join(os.getcwd(), "copy_to_path.txt"), mode='rt') as file:
    dst_path = file.readline()
#print(dst_path)

src_path = os.getcwd()

if method == 1:
    files_to_copy = os.listdir(src_path)

    # 2. get rid of any files not ending in '.p8"
    index = 0
    while index < len(files_to_copy):
        fname = files_to_copy[index]
        extension = fname[-3:]
        if extension != ".p8":
            files_to_copy = files_to_copy[:index] + files_to_copy[index+1:]
        else:
            index += 1

    print(files_to_copy)

    # 3. copy the files from the current working directory to the specified path
    for i in range(len(files_to_copy)):
        fname = files_to_copy[i]
        shutil.copy(os.path.join(src_path, fname), os.path.join(dst_path, fname))
        print(f"copied {fname}")
elif method == 2:
    # 2. minify
    src_fname = "jumpnslash.p8"
    dst_fname = "jumpnslash_minified.p8"
    cmd = f'.\\shrinko8.exe "{os.path.join(src_path, src_fname)}" "{os.path.join(dst_path, dst_fname)}" --minify-safe-only'
    print(cmd)
    subprocess.run(['powershell', cmd], shell=True)
