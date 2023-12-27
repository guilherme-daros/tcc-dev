from modeling import *
from data import *


def calc_improvement(p, dw, interval):
    bl = baseline_tx_total(p, dw, interval)
    bc = proposed_tx_total(p, dw, interval)

    return (bl-bc)/bl


def get_min_max_improv(model, tx_interval):
    results = {}

    for layer_width, model_depths in model_exec_time.items():
        for model_depth, model_time in model_depths.items():
            for data_window, feats_time in feats_exec_time.items():

                i_model = model | {
                    "t_uC_model": model_time,
                    "t_uC_feats": feats_time
                }

                imp = calc_improvement(
                    i_model, int(data_window), tx_interval)

                results = results | {
                    f"dw{data_window}_{layer_width}_{model_depth}": imp
                }
    data = {
        "models": [key for key in results.keys()],
        "improvement": [value for key, value in results.items()],
    }

    min_index = data["improvement"].index(min(data["improvement"]))
    max_index = data["improvement"].index(max(data["improvement"]))

    return {
        "max": {
            "name": data['models'][min_index],
            "improvement":  data['improvement'][min_index]*100,
        },
        "min": {
            "name": data['models'][max_index],
            "improvement":  data['improvement'][max_index]*100,
        },
    }


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
