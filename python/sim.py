from data import *
from modeling import *
from utils import *

import matplotlib.pyplot as plt

from utils import *
from data import *

plot_data_x, plot_data_y = get_plot_data(picoW, [0.1, 0.2, 0.5, 1, 2, 5])

plt.scatter(plot_data_x, plot_data_y, marker="_", s=300, label="picoW")
plt.legend()
plt.ylim((0, 100))
plt.xlim((0.05, 6))
plt.show()
