import matplotlib.pyplot as plt
import pandas as pd
from math import ceil

from data import *
from modeling import *
from utils import *


def main():
    file1 = pd.read_csv("collected_data/lp_no_led.csv", skiprows=6)

    fig = plt.figure(figsize=(14, 6))
    fig.text(
        0.05, 0.5, "Consumo Instantâneo de Potência [W]", fontsize=20, va='center', rotation='vertical')
    fig.text(0.5, 0.01, "Tempo [s]", fontsize=20, ha='center')

    power = filter(file1["Curr avg 1"] * file1["Volt avg 1"], 4)

    plt.plot(power, 'b')

    plt.xticks(np.linspace(0, len(power), 31), [ceil(x/10000)
                                                for x in np.linspace(0, len(power), 31)], fontsize=12)
    plt.yticks(fontsize=12)

    plt.ylim(0, 0.5)
    plt.grid()
    fig.savefig("low_power.eps", bbox_inches='tight')


if __name__ == "__main__":
    main()
