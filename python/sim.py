import matplotlib.pyplot as plt

n = 400

P_idle = 6.324e-3        # W
t      = 1               # s
t_tx   = 25*0.1052e-3    # s
P_tx   = 234e-3 - P_idle # W
P_uC   = 104e-3 - P_idle # W

E_c1 = lambda n    : n*P_idle*t + n*P_tx*t_tx
E_c2 = lambda n, m : n*P_idle*t + P_tx*t_tx + P_uC*m

bl = E_c1(n)
bc = E_c2(n, 1834e-6)
wc = E_c2(n, 58645e-6)

print(f"In a {n*t}s window, we use:")
print(f"Baseline: \t{bl:.5f} J")
print(f"BestCase: \t{bc:.5f} J, {(bl-bc)/bl * 100:.2f}% better")
print(f"WrstCase: \t{wc:.5f} J, {(bl-wc)/bl * 100:.2f}% better")
