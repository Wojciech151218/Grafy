import os
import pandas as pd
import random
from xlsxwriter.utility import xl_rowcol_to_cell
import sys

# Function to generate random RGB color in hexadecimal format
def random_color():
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    return f'{r:02x}{g:02x}{b:02x}'

# Function to read data from text files and create sheets in Excel workbook with charts
def create_excel_with_charts(directory, output_directory):
    excel_file_path = os.path.join(output_directory, "data_with_charts.xlsx")
    with pd.ExcelWriter(excel_file_path, engine='xlsxwriter') as writer:
        for filename in os.listdir(directory):
            if filename.endswith(".txt"):
                file_path = os.path.join(directory, filename)
                sheet_name = os.path.splitext(filename)[0]  # Use file name as sheet name

                # Read data from text file
                with open(file_path, 'r') as file:
                    lines = file.readlines()
                    header = lines[0].strip().split()  # Header as list of strings
                    data = [list(map(float, line.strip().split())) for line in lines[1:]]  # Convert data to list of lists of floats

                # Create DataFrame
                df = pd.DataFrame(data, columns=header)

                # Write DataFrame to Excel sheet
                df.to_excel(writer, sheet_name=sheet_name, index=False)

                # Create chart
                workbook = writer.book
                worksheet = writer.sheets[sheet_name]
                chart = workbook.add_chart({'type': 'line'})  # Change chart type if needed
                chart.set_title({'name': sheet_name})  # Set chart title to sheet name

                # Add series to chart with random colors
                num_cols = len(header)
                for col_num in range(1, num_cols):
                    color = random_color()  # Generate random color
                    chart.add_series({
                        'categories': [sheet_name, 1, 0, len(data), 0],  # Category (x-axis) values
                        'values': [sheet_name, 1, col_num, len(data), col_num],  # Data (y-axis) values
                        'name': f"={sheet_name}!${xl_rowcol_to_cell(0, col_num)}",  # Series name from header
                        'marker': {'type': 'circle', 'size': 8, 'border': {'color': 'black'}, 'fill': {'color': '#' + color}},  # Marker customization
                        'line': {'color': '#' + color, 'width': 2},  # Line customization
                    })

                # Insert chart into worksheet
                worksheet.insert_chart('D2', chart)

    print(f"\nData and charts saved to {excel_file_path}")

# Provide the directory containing the text files
directory = sys.argv[1]

# Provide the output directory for the Excel file
output_directory = sys.argv[2]

create_excel_with_charts(directory, output_directory)
