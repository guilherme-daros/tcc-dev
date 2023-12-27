import matplotlib.pyplot as plt

n = 432

## cell
P_idle = 6.324e-3        # W
t      = 0.5             # s
t_tx   = 25*0.1052e-3    # s
P_tx   = 234e-3          # W
P_uC   = 104e-3          # W

E_c1 = lambda n       : n     * P_idle*(t - t_tx)                     + n*P_tx*t_tx
E_c2 = lambda n, t_uC : (n-1) * P_idle*(t) + P_idle*(t - t_tx - t_uC) + P_tx*t_tx   + P_uC*t_uC

bl = E_c1(n)
bc = E_c2(n, 1834e-6)
wc = E_c2(n, 58645e-6)

print(f"In a {n*t}s window, we use:")
print(f"Baseline: \t{bl:.5f} J")
print(f"BestCase: \t{bc:.5f} J, {(bl-bc)/bl * 100:.2f}% better")
print(f"WrstCase: \t{wc:.5f} J, {(bl-wc)/bl * 100:.2f}% better")
