#Simplified Hangul

import sys

result = []

class Shangul:
    def __init__(self, rows, columns, char_map):
        self.rows = rows
        self.columns = columns
        self.char_map = char_map
    
    def translate(self):
        letter_coords = []

        for i in range(self.columns):
            for j in range(self.rows):
                if self.char_map[j][i] == '#' and \
                   self.char_map[j - 1][i] == '.' and \
                   self.char_map[j][i - 1] == '.' and \
                   self.char_map[j - 1][i - 1] == '.':
                       letter_coords.append((j, i))

        self.filter_coords(letter_coords)
        self.identify(letter_coords)

    def filter_coords(self, letter_coords):
        for coords in letter_coords:
            is_valid = True
            j = coords[0]
            i = coords[1]

            while self.char_map[j][i] == '#' and is_valid:
                if self.char_map[j][i - 1] == '#':
                    is_valid = False
                
                j += 1

            if not is_valid:
                letter_coords.remove(coords)

    def identify(self, letter_coords):
        result = ''

        for coords in letter_coords:
            j = coords[0]
            i = coords[1]

            if self.char_map[j + 1][i] == '#':
                letter_found = False

                while self.char_map[j][i] == '#':
                    if self.char_map[j][i + 1] == '#':
                        if self.char_map[j + 1][i] == '#':
                            result += 'a'
                            letter_found = True
                        else:
                            result += 'n'
                            letter_found = True
                    j += 1
                
                if not letter_found:
                    result += 'i'
            else:
                while self.char_map[j][i] == '#':
                    if self.char_map[j][i + 1] == '#':
                        if self.char_map[j + 1][i] == '#':
                            result += 'u'
                        
                        if self.char_map[j - 1][i] == '#':
                            result += 'o'
                    else:
                        if self.char_map[j - 1][i] == '#' and \
                           self.char_map[j + 1][i] == '#':
                               result += 'eo'

                        elif self.char_map[j + 1][i] == '#':
                            result += 'g'

                    i += 1

        print result

def process_input(rows, columns):
    char_map = []
    for i in range(rows):
        line = tuple(sys.stdin.readline()[:columns])
        char_map.append(line)
    
    result.append(Shangul(rows, columns, char_map))

def main():
    while True:
        rows, columns = map(int, sys.stdin.readline().strip().split())

        if rows == 0 and columns == 0:
            break

        process_input(rows, columns)
    
    map(lambda x: x.translate(), result)

if __name__ == "__main__":
    main()
