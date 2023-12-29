from modeling import *
from data import *


def calc_improvement(p, dw, interval):
    bl = baseline_tx_total(p, dw, interval)
    bc = proposed_tx_total(p, dw, interval)

    return (bl-bc)/bl


def get_improvment(model, tx_interval):
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
    return results


def get_consumed_energy(model, tx_interval):
    results = get_improvment(model, tx_interval)
    data = {
        "models": [key for key in results.keys()],
        "improvement": [value for key, value in results.items()],
    }

    return data


def get_min_max_improv(model, tx_interval):

    data = get_consumed_energy(model, tx_interval)

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
