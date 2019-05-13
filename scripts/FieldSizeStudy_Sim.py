import numpy as np
from matplotlib import pylab as plt

field_sizes=np.array(["3x3","5x5","7x7","10x10"])
gamma=True 
electron=True

Field3x3-PS-Input_Gamma_FullRun
for field in range(0,len(field_sizes)):
	file_loc="/mnt/shared/home/lb8075/RadiotherapyBeam/gateSplitDir/.Gate/Field"+field_sizes[field]+"-PS-Input_Gamma_FullRun/Total_Edep.root"
