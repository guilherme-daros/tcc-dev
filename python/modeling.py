import numpy as np

def baseline_tx_cycle(p, n, t):
    """
    will return an array with average power comsumption for 
    each 10 us on a interval for baseline model
    """
    kUs = 1000 * 100

    tx_avg_power = np.array([])

    for n_i in range(n):
        idle_time = np.full(int((t - p["t_tx"]) * kUs), p["P_idle"])
        tx_time = np.full(int(p["t_tx"] * kUs), p["P_tx"])
        tx_avg_power = np.concatenate((tx_avg_power, idle_time, tx_time))

    return tx_avg_power

def proposed_tx_cycle(p, n, t):
    """
    will return an array with average power comsumption for 
    each 10 us on a interval for proposed model
    """
    kUs = 1000 * 100

    idle_time = np.full(int(t * kUs)*(n - 1), p["P_idle"])
    
    idle = int(t*kUs - p["t_tx"]*kUs - p["t_uC"]*kUs)
    
    last_idle_time = np.full(idle, p["P_idle"])
    
    uC_time = np.full(int(p["t_uC"]*kUs), p["P_uC"])
    tx_time = np.full(int(p["t_tx"]*kUs), p["P_tx"])
    
    tx_avg_power = np.concatenate((idle_time, last_idle_time,  uC_time, tx_time))
           
    return tx_avg_power

def baseline_tx_total(p, n, t):
    return n * (p["P_idle"]*(t - p["t_tx"]) + p["P_tx"]*p["t_tx"])

def proposed_tx_total(p, n, t):
    return p["P_idle"]*(t * (n-1)) + p["P_idle"]*(t - p["t_tx"] - p["t_uC"]) + p["P_uC"]*p["t_uC"] + p["P_tx"]*p["t_tx"]
