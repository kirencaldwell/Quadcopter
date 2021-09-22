import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl
import sys

mpl.rcParams['figure.figsize'] = (16.0, 8.0)
mpl.rcParams['grid.color'] = (0.9, 0.9, 0.9)
mpl.rcParams['grid.linestyle'] = '-'
mpl.rcParams['grid.linewidth'] = 0.5
mpl.rcParams['lines.markersize'] = 5
mpl.rcParams['figure.dpi'] = 100
mpl.rcParams['font.size'] = 8
mpl.rcParams['legend.fontsize'] = 'small'
mpl.rcParams['figure.titlesize'] = 'small'

df = pd.read_csv("bazel-out/k8-fastbuild/bin/main.runfiles/Quadcopter/quadcopter_onboard.csv")
df.rename(columns=df.iloc[0]).drop(df.index[0])

fig, ax = plt.subplots(3)
ax[0].plot(df.t, df.x0, linewidth=4)
ax[0].grid(True)
ax[1].plot(df.t, df.x1, linewidth=4)
ax[1].grid(True)
ax[2].plot(df.t, df.x2, linewidth=4)
ax[2].grid(True)
plt.show()

fig, ax = plt.subplots(2)
ax[0].plot(df.x0, df.x1, linewidth=4)
ax[0].grid(True)
ax[1].plot(df.t, df.x2, linewidth=4)
ax[1].grid(True)
plt.show()


fig, axs = plt.subplots(3, 3)
for i in range(0, 3):
    for j in range(0, 3):
        desired_rot = "Rd" + str(i) + str(j)
        Rij_des = df.filter(regex=desired_rot)
        true_rot = "R" + str(i) + str(j)
        Rij_true = df.filter(regex=true_rot)
        axs[i,j].plot(df.t, Rij_true, linewidth=4)
        axs[i,j].plot(df.t, Rij_des, linewidth=2)
        axs[i,j].set_ylim([-1.1, 1.1])
        axs[i,j].grid(True)
axs[i,j].legend(["true", "desired"])
plt.show()

fig, ax = plt.subplots(3)
ax[0].plot(df.t, df.W0, linewidth=4)
ax[0].grid(True)
ax[1].plot(df.t, df.W1, linewidth=4)
ax[1].grid(True)
ax[2].plot(df.t, df.W2, linewidth=4)
ax[2].grid(True)
plt.show()

fig, ax = plt.subplots(4)
ax[0].plot(df.t, df.M0, linewidth=4)
ax[0].grid(True)
ax[1].plot(df.t, df.M1, linewidth=4)
ax[1].grid(True)
ax[2].plot(df.t, df.M2, linewidth=4)
ax[2].grid(True)
plt.show()