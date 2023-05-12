import csv
import sys


def main():

    if len(sys.argv) != 3:
        sys.exit("python dna.py data.csv sequence.txt")

    database = []

    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)

    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read()

    subsequences = list(database[0].keys())[1:]

    result = {}
    for subsequence in subsequences:
        result[subsequence] = longest_match(dna_sequence, subsequence)

    for person in database:
        match = 0
        for subsequence in subsequences:
            if int(person[subsequence]) == result[subsequence]:
                match += 1

        if match == len(subsequences):
            print(person["name"])
            return

    print("no match")
    return


"""
    # TODO: Check for command-line usage
    if (len(sys.argv) != 3):
        print("Invalid command line argument ")
    else:
        # TODO: Read database file into a variable
    # CSV
        with open(str(sys.argv[2]), 'r') as csv_file:
            csv_reader = csv.reader(csv_file)
        # TODO: Read DNA sequence file into a variable
            for line in csv_reader:
                str_dna = ''.join(line)
                #print(str_dna)

        with open(str(sys.argv[1]), 'r') as f:
            txt = open(str(sys.argv[1]), 'r')
            data = [line.split(',') for line in txt.readlines()]
            # for line in f:
            #     print(line, end='')


    #print (data)
    new_dna = list(str_dna)
    new_dna = new_dna
    #print(new_dna)

    aatg = 0
    agatc = 0
    tatc = 0
    a = 'A'
    t = 'T'
    g = 'G'
    c = 'C'


    for i in range(len(new_dna)):
        #agatc
        if new_dna[i] == a and new_dna[i + 1] == g and new_dna[i + 2] == a and new_dna[i + 3] == t and new_dna[i + 4] == c :
            agatc += 1
        #aatg
        elif new_dna[i] == a and new_dna[i + 1] == a and new_dna[i + 2] == t and new_dna[i + 3] == g:
            aatg += 1
        #tatc
        elif new_dna[i] == t and new_dna[i + 1] == a and new_dna[i + 2] == t and new_dna[i + 3] == c:
            tatc += 1

    agatc = "{}".format(agatc)
    aatg = "{}".format(aatg)
    tatc = "{}".format(tatc)

    # print(agatc)
    # print(aatg)
    # print(tatc)

    for i in range(len(data)):
        for j in range(len(data)):
            if data[i][1] ==  agatc and data[i][2] == aatg and data[i][3].strip()  == tatc :
                print(data[i][0])
                break

    # TODO: Check database for matching profiles
"""



def longest_match(sequence, subsequence):
    # Returns length of longest run of subsequence in sequence.

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

