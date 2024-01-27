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

    fig = plt.figure(figsize=(16, 8))
    fig.text(0.08, 0.5, "Melhora [%]", fontsize=20,
             va='center', rotation='vertical')
    fig.text(0.5, 0.0005, "Modelo Utilizado", fontsize=20, ha='center')
    plt.plot(plot_data54, marker='o', label="Janela = 54 amostras")
    plt.plot(plot_data108, marker='o', label="Janela = 108 amostras")
    plt.plot(plot_data216, marker='o', label="Janela = 216 amostras")
    plt.plot(plot_data432, marker='o', label="Janela = 432 amostras")

    plt.grid()
    plt.xticks(ticks=range(len(plot_labels)),
               labels=plot_labels, rotation=45, fontsize=15)
    plt.yticks(fontsize=15)
    plt.ylim((34, 50))
    plt.legend(fontsize='x-large')
    plt.savefig("compare_datawindow.eps", bbox_inches='tight')
    # plt.show()


if __name__ == "__main__":
    main()
