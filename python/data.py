picoW = {
    "P_idle": 0.006324398171941891,
    "P_tx": 0.23195203695284516,
    "P_uC_model": 0.10607053373391245,
    "P_uC_feats": 0.09216893532589153,
    "t_tx": 25*0.1052e-3,
}

model_exec_time = {
    "lw4": {
        "md1": 0.000327,
        "md2": 0.000367,
        "md4": 0.000451,
        "md8": 0.000615,
    },
    "lw8": {
        "md1": 0.000533,
        "md2": 0.000645,
        "md4": 0.000869,
        "md8": 0.001316,
    },
    "lw16": {
        "md1": 0.001067,
        "md2": 0.001444,
        "md4": 0.002222,
        "md8": 0.003750,
    },
    "lw32": {
        "md1": 0.002648,
        "md2": 0.004081,
        "md4": 0.006955,
        "md8": 0.012719,
    },
    "lw64": {
        "md1": 0.007879,
        "md2": 0.013453,
        "md4": 0.024646,
        "md8": 0.047046,
    },
}

feats_exec_time = {
    "54":	0.001507,
    "108":	0.002926,
    "216":	0.005785,
    "432":	0.011600
}

picoW_smallestmodel = picoW | {
    "t_uC_model": model_exec_time["lw4"]["md1"],
    "t_uC_feats": feats_exec_time["54"]
}

picoW_biggestmodel = picoW | {
    "t_uC_model": model_exec_time["lw64"]["md8"],
    "t_uC_feats": feats_exec_time["432"]
}
