#importo le librerie
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

filename = 'T4-resoults'
img_filename = 'resoults'

# Set the style
sns.set_style("whitegrid")
sns.set_context("paper", font_scale=1.5, rc={"lines.linewidth": 2.5})

# Read the data
df = pd.read_csv(filename + '.csv')
df_integral = pd.read_csv('resoults.csv')

# Filter the data
df_filter = df_integral[df_integral['notes'] == 'avx']

print(df)
# print(df_integral)
print(df_filter)



print(df)

# Create a scatter plot
sns.lineplot(x='job', y='wall_time1', data=df, label='Serial', color='red')
sns.lineplot(x='job', y='wall_time2', data=df, label='Parallel', color='blue')

sns.lineplot(x='job', y='wall_time1', data=df_filter, label='Serial_AVX', color='red', linestyle='dashed')
sns.lineplot(x='job', y='wall_time2', data=df_filter, label='Parallel_AVX', color='blue', linestyle='dashed')

#sns.lineplot(x='job', y='wall_time3', data=df, label='Task 3', color='green')

# Add title and axis names
plt.title('Wall time')
plt.xlabel('Job')
plt.ylabel('Time (s)')
plt.legend()
plt.savefig(img_filename + '.png')
plt.show()
