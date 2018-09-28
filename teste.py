import os, csv

def InsereLinhaCSV(csvPath, msg):
    filemode = 'a';
    if not os.path.isfile(csvPath):
        filemode = 'w'
    with open(csvPath, mode=filemode) as csv_file:
        csv_file.write(msg  + "\n")


def lowerFile(path):
    qbfile = open(path, "r")
    for line in qbfile:
        print(line.lower())

    qbfile.close()


# path = 'test.csv'
# for x in range(1, 10):
#     InsereLinhaCSV(path, 'We are on time %d' % (x))

lowerFile('aaaa')
