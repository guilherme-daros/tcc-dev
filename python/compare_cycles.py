import matplotlib.pyplot as plt

from data import *
from modeling import *


def main():
    E_base_arr = baseline_tx_cycle(picoW, 54, 0.1)
    E_prop_arr = proposed_tx_cycle(picoW_biggestmodel, 54, 0.1)

    fig, axs = plt.subplots(nrows=2, ncols=1, figsize=(14, 6))
    fig.text(
        0.07, 0.5, "Consumo Instantâneo de Potência [W]", fontsize=16, va='center', rotation='vertical')
    fig.text(0.5, 0.03, "Tempo [s]", fontsize=16, ha='center')

    axs[0].plot(E_base_arr, 'b', label="baseline")
    axs[1].plot(E_prop_arr, 'r', label="proposed")

    plt.setp(axs, xticks=np.linspace(0, len(E_base_arr), 11), xticklabels=[
        int(x/10000) for x in np.linspace(0, len(E_base_arr), 11)])

    for ax in axs:
        ax.set_yscale("log")
        ax.legend(loc="upper left")

    fig.savefig("compare_cycles.png", bbox_inches='tight')

    fig, axs = plt.subplots(nrows=2, ncols=1, figsize=(14, 6))
    fig.text(
        0.07, 0.5, "Consumo Instantâneo de Potência [W]", fontsize=16, va='center', rotation='vertical')
    fig.text(0.5, 0.03, "Tempo [s]", fontsize=16, ha='center')

    axs[0].plot(E_base_arr, 'b', label="baseline")
    axs[1].plot(E_prop_arr, 'r', label="proposed")

    plt.setp(axs, xticks=np.linspace(0, len(E_base_arr), 51), xticklabels=[
        int(x/10000) for x in np.linspace(0, len(E_base_arr), 51)])

    for ax in axs:
        ax.set_yscale("log")
        ax.legend(loc="upper left")
        ax.set_xlim(465000, 545000)

    fig.savefig("compare_cycles_zoom.png", bbox_inches='tight')

    # plt.show()


if __name__ == "__main__":
    main()
