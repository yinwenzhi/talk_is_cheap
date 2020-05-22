# 这种方法只使用于弹出的窗口，不适用于jupyter
import matplotlib.pyplot as plt
from IPython import display # 动态刷新

ax = []                    # 定义一个 x 轴的空列表用来接收动态的数据
ay = []                    # 定义一个 y 轴的空列表用来接收动态的数据
plt.ion()                  # 开启一个画图的窗口
for i in range(100):       # 遍历0-99的值
    ax.append(i)           # 添加 i 到 x 轴的数据中
    ay.append(i**2)        # 添加 i 的平方到 y 轴的数据中
    
    plt.plot(ax,ay)        # 画出当前 ax 列表和 ay 列表中的值的图形
    plt.draw()
    plt.pause(0.1)         # 暂停一秒
    
