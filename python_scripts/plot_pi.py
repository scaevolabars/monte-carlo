import matplotlib.pyplot as plt
import pandas as pd
import numpy as np


path = "D:\\documentarium\\repositories\\monte-carlo\\exercises\\"
points = pd.read_csv(path + "coordinates.csv")

points['distance'] = points.apply(lambda x: np.sqrt(x[0] ** 2 + x[1] ** 2), axis=1)

col = np.where(points['distance'].values <= 1.0, 'g', 'r')
N = points.shape[0]
A = points[points.distance <= 1.0].shape[0]

plt.scatter(x=points['x'], y=points['y'], c=col, s=1)
plt.axis('equal')
plt.title(f'Number of simulations:{N} '
          f'Number of accepted points:{A} '
          f'Pi = {4*A/N}'
          , fontsize=8)

plt.savefig(path + "circle_pi.png", dpi = 400)
