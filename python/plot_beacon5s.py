import matplotlib.pyplot as plt
import pandas as pd
from math import ceil

from data import *
from modeling import *

from utils import *


def main():
    file1 = pd.read_csv("collected_data/beacon_5s.csv", skiprows=6)

    fig = plt.figure(figsize=(14, 6))
    fig.text(
        0.07, 0.5, "Consumo Instantâneo de Potência [W]", fontsize=16, va='center', rotation='vertical')
    fig.text(0.5, 0.03, "Tempo [s]", fontsize=16, ha='center')

    power = filter(file1["Curr avg 1"] * file1["Volt avg 1"], 8)

    plt.plot(power, 'b')

    plt.xticks(np.linspace(0, len(power), 31), [ceil(x/10000)
               for x in np.linspace(0, len(power), 31)])

    plt.ylim(0, 0.4)
    plt.grid()
    fig.savefig("beacon5s.eps", bbox_inches='tight')


if __name__ == "__main__":
    main()
