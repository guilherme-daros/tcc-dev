import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


file1 = pd.read_csv("collected_data/beacon_5s.csv", skiprows=6)
plt.figure()
plt.plot(file1["Curr avg 1"][50000:])

file2 = pd.read_csv("collected_data/beacon_10s.csv", skiprows=6)
plt.figure()
plt.plot(file2["Curr avg 1"][50000:])
plt.show()
