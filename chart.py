#importo le librerie
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

filename = 'Benchmark-resoults'
img_filename = 'b-resoults'

# Set the style
sns.set_style("whitegrid")
# sns.set_context("paper", font_scale=1.5, rc={"lines.linewidth": 2.5})

# Read the data
df = pd.read_csv(filename + '.csv')

print(df)

# Filter the data
df_serial = df[df['notes'] == 'not_vectorized']
df_avx = df[df['notes'] == 'avx']
df_ftree = df[df['notes'] == 'ftree']


print(df_serial)
print(df_avx)
print(df_ftree)

# Create a scatter plot
sns.lineplot(x='n', y='wall_clock_time_routine2', data=df_serial, label='Serial', color='red')
sns.lineplot(x='n', y='wall_clock_time_routine2', data=df_avx, label='Vectorized-avx', color='blue')

# Add title and axis names
plt.title('Wall time')
plt.xlabel('Size')
plt.ylabel('Time [s]')
#plt.ylabel('$log_2(t) [s]$')
plt.xscale('log')
# plt.yscale('log')
plt.xticks([16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32786, 65536, 131072, 262144, 524288, 1048576, 2097152, 4194304],['$2^4$', '$2^5$', '$2^6$', '$2^7$', '$2^8$', '$2^9$', '$2^{10}$', '$2^{11}$', '$2^{12}$', '$2^{13}$', '$2^{14}$', '$2^{15}$', '$2^{16}$', '$2^{17}$', '$2^{18}$', '$2^{19}$', '$2^{20}$', '$2^{21}$', '$2^{22}$'])
plt.legend()
plt.savefig(img_filename + '.png')
plt.show()

plt.yscale('log')
plt.savefig(img_filename + '-log.png')
