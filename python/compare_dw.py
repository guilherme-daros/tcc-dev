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

    plt.style.use('ggplot')

    plt.figure(figsize=(14, 6))
    plt.plot(plot_data54, marker='o', label="Janela = 54 amostras")
    plt.plot(plot_data108, marker='o', label="Janela = 108 amostras")
    plt.plot(plot_data216, marker='o', label="Janela = 216 amostras")
    plt.plot(plot_data432, marker='o', label="Janela = 432 amostras")

    plt.grid()
    plt.xticks(ticks=range(len(plot_labels)),
               labels=plot_labels, rotation=45, fontsize=10)
    plt.ylim((40, 50))
    plt.legend()
    plt.xlabel("Used Model", fontsize=16)
    plt.ylabel("Improvements [%]", fontsize=16)
    plt.savefig("compare_datawindow.png", bbox_inches='tight')
    # plt.show()


if __name__ == "__main__":
    main()
