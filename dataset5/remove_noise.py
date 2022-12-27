import numpy as np
import matplotlib.pyplot as plt

N = 9982          # サンプル数
dt = 0.001          # サンプリング周期 [s]
f1, f2 = 50, 120    # 周波数 [Hz]

path = "input_data.txt"
with open(path, 'rb') as f:
    print(f.read())
# F = np.fft.fft(x) # 変換結果
# freq = np.fft.fftfreq(N, d=dt) # 周波数

# fig, ax = plt.subplots()
# ax.plot(t, x)
# # ax.set_xlim(0, 0.1)
# ax.set_xlabel("Time [s]")
# ax.set_ylabel("Signal")
# ax.grid()
# plt.show()