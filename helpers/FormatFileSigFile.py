import csv

def write_columns_to_txt(csv_file, txt_file):
  with open(csv_file, 'r') as file:
    reader = csv.reader(file)

    with open(txt_file, 'w') as output_file:
      for row in reader:
        file_sig = row[0].split('(')[0].replace(' ', '')[:8].upper()
        output_file.write(file_sig + '\n' + row[1] + '\n')

csv_file = '../data/File-signatures.csv'
txt_file = '../data/FileExtensions'
write_columns_to_txt(csv_file, txt_file)