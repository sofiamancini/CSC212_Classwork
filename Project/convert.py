import pandas as pd
import csv

# Load the CSV file without a header and assign column names
df = pd.read_csv('private.csv', skiprows=1, header=None, names=['NAME', 'CITY', 'STATE', 'LAT', 'LON'])

# Combine the columns
df['NAME, CITY, STATE'] = df['NAME'] + ', ' + df['CITY'] + ', ' + df['STATE']

# Drop the original columns if you no longer need them
df.drop(['NAME', 'CITY', 'STATE'], axis=1, inplace=True)

# Reorder the columns
df = df[['NAME, CITY, STATE', 'LAT', 'LON']]

# Ensure LAT and LON are floats (this step will catch any conversion errors)
df['LAT'] = df['LAT'].astype(float)
df['LON'] = df['LON'].astype(float)

# Convert LAT and LON to numeric, coercing errors to NaN
df['LAT'] = pd.to_numeric(df['LAT'], errors='coerce')
df['LON'] = pd.to_numeric(df['LON'], errors='coerce')

# Print first few rows and data types for verification
print(df.head())
print(df.dtypes)

# Save the new dataframe to a new TSV file (tab-separated values)
df.to_csv('private.txt', index=False, sep='\t', quoting=csv.QUOTE_NONE, escapechar=' ')