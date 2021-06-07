#Mike Zeng
#CECS 424-05
#Assignment 3

#data structures
numbers = [645.32, 37.40, 76.30, 5.40, -34.23, 1.11, -34.94, 23.37, 635.46, -876.22, 467.73, 62.26]
people = {'Hal':20, 'Susann':31, 'Dwight':19, 'Kassandra': 21, 'Lawrence': 25, 'Cindy': 22, 'Cory': 27, 'Mac': 19, 'Romana': 27, 'Doretha': 32, 'Danna': 20, 'Zara': 23, 'Rosalyn': 26, 'Risa': 24, 'Benny':28, 'Juan': 33, 'Natalie': 25}
#displaying and ordering the numbers list
print("Numbers list:", numbers)
print("Ordered numbers:", sorted(numbers))
#displaying and ordering the people list: first by name then by descending age
print("List of people:", people)
speople = {}    #sort people alphabetically
for i in sorted(people):
    speople[i] = people[i]
print("Ordered people by name alphabetically:", sorted(speople.items(), key = lambda kv:(kv[0],kv[1])))     #orders the dictionary by key in asc. order
print("Ordered people by age descending:", sorted(speople.items(), key = lambda kv:(-kv[1],kv[0])))         #orders the dictionary by value in desc. order (by negating the value element, thus keeping key intact alphabetically)