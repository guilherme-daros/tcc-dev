from data import *
from modeling import *
from utils import *

import matplotlib.pyplot as plt


def get_plot_data(model, intervals):
    result = {}
    for interval in intervals:
        result = result | {f"{interval}": get_min_max_improv(model, interval)}

    plot_data_x = []
    plot_data_y = []
    for key, value in result.items():
        plot_data_x.append(key)
        plot_data_y.append(value["max"]["improvement"])
        plot_data_x.append(key)
        plot_data_y.append(value["min"]["improvement"])

    return plot_data_x, plot_data_y


def main():
    plot_data_x, plot_data_y = get_plot_data(
        picoW, [0.1, 0.2, 0.5, 1, 2, 5])

    plt.figure(figsize=(12, 6))
    plt.grid(linestyle='-.')

    plt.scatter(plot_data_x, plot_data_y, marker="_", s=250, linewidths=3)
    plt.yticks(fontsize=15)

    plt.xticks([0, 1, 2, 3, 4, 5], [
               f"{t}s" for t in [0.1, 0.2, 0.5, 1, 2, 5]], fontsize=15)

    plt.xlabel("Intervalo entre Transmissões [s]", fontsize=20)
    plt.ylabel("Melhora [%]", fontsize=20)

    plt.savefig("compare_intervals.eps", bbox_inches='tight')
    # plt.show()


if __name__ == "__main__":
    main()
