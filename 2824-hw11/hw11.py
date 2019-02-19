from random import *


def others(choice):
    if choice == 0:
        return randrange(1,3,1)

    if choice == 1:
        return randrange(0,3,2)

    if choice == 2:
        return randrange(0,2,1)



# The number of times the contestant wins on the switch
wSwitch = 0

# The number of times the contestant wins without the switch
nSwitch = 0

# Number of times to run the simulation
N = 100

# Everything goes in a for loop

for x in range(0,N):

    # First we want to define a Boolean array to see where the car is
    doors = [False]

    doors = doors*3

    # Now we want to determine a random door to put the car in
    index = randrange(0,3,1)

    doors[index] = True

    # Now determining what door the contestant chooses
    choice = randrange(0,3,1)

    # Now we choose a door to open and show the goat in
    opened = others(index)

    # Now the contestant is going to switch
    for x in range(0,3):
        if (x != choice and x != opened):
            fChoice = x

    # If the contestant won we increment wSwitch
    if (index == fChoice):
        wSwitch += 1


# Now seeing what happens when you don't switch
for x in range(0,N):
    index = randrange(0,3,1)
    choice = randrange(0,3,1)

    if (index == choice):
        nSwitch += 1

print "Percentage winning while switching:"
print "%"+str(wSwitch)
print "Percentage winning not switching:"
print "%"+str(nSwitch)
