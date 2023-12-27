import matplotlib.pyplot as plt

from data import *
from modeling import *

plot = False

def main():
    E_base_arr = baseline_tx_cycle(picoW, 20, 1)
    E_prop_arr1 = proposed_tx_cycle(picoW_smallmodel, 20, 1)
    E_prop_arr2 = proposed_tx_cycle(picoW_bigmodel, 20, 1, )

    print(np.sum(E_prop_arr1)/100_000)
    print(np.sum(E_prop_arr2)/100_000)
    
    print(proposed_tx_total(picoW_smallmodel, 54, 0.1))
    print(proposed_tx_total(picoW_bigmodel, 432, 0.1))

    if plot == True:
        plt.figure()
        plt.plot(E_prop_arr1)
        plt.show()
        plt.figure()
        plt.plot(E_prop_arr2)
        plt.show()

if __name__ == "__main__":
    main()

