import matplotlib.pyplot as plt

from data import *
from modeling import *

plot = True


def main():
    E_base_arr = baseline_tx_cycle(picoW, 50, 0.1)
    E_prop_arr1 = proposed_tx_cycle(picoW_smallestmodel, 50, 0.1)
    E_prop_arr2 = proposed_tx_cycle(picoW_biggestmodel, 50, 0.1)

    fig, axs = plt.subplots(nrows=3, ncols=1, sharex=True, figsize=(14, 6))
    fig.text(
        0.07, 0.5, "Instant Power Consumption [W]", fontsize=16, va='center', rotation='vertical')
    fig.text(0.5, 0.05, "Time [s]", fontsize=16, ha='center')

    axs[0].plot(E_base_arr, 'b', label="baseline")
    axs[1].plot(E_prop_arr1, 'g', label="best_case")
    axs[2].plot(E_prop_arr2, 'r', label="wrst_case")

    for ax in axs:
        ax.set_xticks([])
        ax.set_yscale("log")
        ax.legend()

    fig.savefig("compare_cycles.png", bbox_inches='tight')
    # plt.show()


if __name__ == "__main__":
    main()
