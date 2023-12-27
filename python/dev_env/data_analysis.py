import os
import pandas as pd
import numpy as np 
import matplotlib.pyplot as plt

start = 74000
end   = start + 70000
plot  = True 

data = pd.read_csv(f"collected_data/beacon_10s_radiooff.csv", skiprows=6)
current = np.mean(data["Curr avg 1"][start:end])
voltage = np.mean(data["Volt avg 1"][start:end])
print(end - start)
print(current * voltage)
if plot == True:
    plt.plot(data["Curr avg 1"][start:end])
    plt.ylim(bottom=0, top=0.15)
    plt.show()

