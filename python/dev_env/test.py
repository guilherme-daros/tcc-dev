import numpy as np

P_idle = 6.324e-3        # W
P_tx   = 234e-3          # W
P_uC   = 104e-3          # W

t      = 1               # s
t_tx   = 25*0.1052e-3    # s
t_tx = 25*0.1052e-3
kUs = 1000 * 1000


def teste(t):  
    size = int((t - t_tx) * kUs)
    print(size)
    idle_time = np.full(size, P_idle)
    print(idle_time)

if __name__ == "__main__":
    teste(58645e-6)
