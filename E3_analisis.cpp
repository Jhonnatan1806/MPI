import csv

def main():
	with open('E3_Adivina_mi_numero.csv', newline='') as File:  
	    reader = csv.reader(File)
	    for row in reader:
	        print(row)

if __name__ == '__main__':
	main()