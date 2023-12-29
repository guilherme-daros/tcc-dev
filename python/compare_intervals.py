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
    plt.style.use('ggplot')

    plt.figure(figsize=(12, 6))
    plt.scatter(plot_data_x, plot_data_y, marker="_", s=300, label="picoW")

    plt.grid()
    plt.legend()
    plt.xlabel("Interval Between Transmissions [s]", fontsize=16)
    plt.ylabel("Improvement [%]", fontsize=16)

    plt.savefig("compare_intervals.png", bbox_inches='tight')
    # plt.show()


if __name__ == "__main__":
    main()
