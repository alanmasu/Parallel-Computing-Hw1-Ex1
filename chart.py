import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

filename = 'T4-resoults'

# Set the style
sns.set_style("whitegrid")
sns.set_context("paper", font_scale=1.5, rc={"lines.linewidth": 2.5})

# Read the data
df = pd.read_csv(filename + '.csv')
df_integral = pd.read_csv('resoults.csv')

print(df)
print(df_integral)

# Create a scatter plot
sns.lineplot(x='job', y='wall_time1', data=df, label='Task 1', color='red')
sns.lineplot(x='job', y='wall_time2', data=df, label='Task 2', color='blue')

# Add title and axis names
plt.title('Wall time')
plt.xlabel('Job')
plt.ylabel('Time (s)')
plt.legend()
plt.savefig(filename + '.png')
plt.show()
