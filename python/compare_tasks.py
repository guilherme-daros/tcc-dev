import numpy as np
import matplotlib.pyplot as plt

from data import *
from modeling import *
from utils import *


def get_prop_energy(p, interval, dw):
    results = {}

    for layer_width, model_depths in model_exec_time.items():
        for model_depth, model_time in model_depths.items():
            for data_window, feats_time in feats_exec_time.items():

                i_p = p | {
                    "t_uC_model": model_time,
                    "t_uC_feats": feats_time
                }

                total_energy = proposed_tx_total(
                    i_p, int(data_window), interval)

                energy = [
                    p["P_uC_feats"] * feats_time,
                    p["P_uC_model"] * model_time,
                    p["P_tx"] * p["t_tx"],
                ]
                if int(data_window) == dw:
                    results = results | {
                        f"{layer_width[2:]}:{model_depth[2:]}": energy
                    }

    return results


def main():
    results = get_prop_energy(picoW, 0.1, 432)

    plot_labels = results.keys()
    at = [x[0]*1000 for x in results.values()]
    md = [x[1]*1000 for x in results.values()]
    tx = [x[2]*1000 for x in results.values()]

    data = list(zip(plot_labels, at, md, tx))
    data.sort(key=lambda i: i[2])

    plot_labels = [x[0] for x in data]
    at = [x[1] for x in data]
    md = [x[2] for x in data]
    tx = [x[3] for x in data]

    fig = plt.figure(figsize=(16, 8))
    fig.text(0.08, 0.5, "Energia consumida na execução [mJ]", fontsize=20,
             va='center', rotation='vertical')
    fig.text(0.5, 0.0005, "Modelo Utilizado", fontsize=20, ha='center')

    plt.plot(at, marker='o', label="Atributos")
    plt.plot(md, marker='o', label="Inferência")
    plt.plot(tx, marker='o', label="Transmissão")

    sizes = [int(x.split(":")[0])*int(x.split(":")[1])
             for x in results.keys()]

    plt.grid()
    plt.xticks(ticks=range(len(plot_labels)),
               labels=plot_labels, rotation=45, fontsize=15)
    plt.yticks(fontsize=15)
    plt.legend(fontsize='x-large')
    plt.savefig("compare_tasks.png", bbox_inches='tight')


if __name__ == "__main__":
    main()
