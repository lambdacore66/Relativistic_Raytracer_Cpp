import imageio.v2 as iio
import glob
import os
import sys

fps_cmd = int(sys.argv[1])

loadpath = os.getcwd()+'/frames/'
outpath = os.getcwd()

fileList = []
for file in os.listdir(loadpath):
    if file.startswith('frame'):
        complete_path = loadpath + file
        fileList.append(complete_path)

writer = iio.get_writer('render.mp4', fps = fps_cmd)

for im in fileList:
    writer.append_data(iio.imread(im))
writer.close()

