from data import *
from modeling import *
from utils import *

import matplotlib.pyplot as plt


def get_plot_data(model, interval, dw):
    result = get_improvment(model, interval)

    labels = [key[6:] for key, value in result.items() if f"dw{dw}" in key]
    data = [value * 100 for key, value in result.items() if f"dw{dw}" in key]

    return labels, data


def main():
    plot_labels, plot_data54 = get_plot_data(picoW, 0.1, 54)
    plot_labels, plot_data108 = get_plot_data(picoW, 0.1, 108)
    plot_labels, plot_data216 = get_plot_data(picoW, 0.1, 216)
    plot_labels, plot_data432 = get_plot_data(picoW, 0.1, 432)

    plt.plot(plot_data54, label="54")
    plt.plot(plot_data108, label="108")
    plt.plot(plot_data216, label="216")
    plt.plot(plot_data432, label="432")

    plt.xticks(ticks=range(len(plot_labels)), labels=plot_labels, rotation=45)
    plt.ylim((30, 60))
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
