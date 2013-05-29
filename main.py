import random
import math
import time
seconds_in_a_year = 31556926
average_arrival_rate = 90
average_service_rate = 45
total_cars = 0
cars_rejected = 0
seconds_waited = 0
seconds_passed = 0
meals_served = 0
profit = 0
driveway = []
while seconds_passed < seconds_in_a_year:
	if len(driveway) > 0 and driveway[0] <= 0:
		driveway.pop(0)
	car_shows_up = random.random() <= (1 / average_arrival_rate)
	if car_shows_up:
		total_cars += 1
		car_enters = len(driveway) < 10
		if car_enters:
			driveway.append(average_service_rate)
			meals_served += 1
			profit += 2.75
		else:
			cars_rejected += 1
	for index, car in enumerate(driveway):
		driveway[index] = car - 1
		seconds_waited += 1
	seconds_passed += 1
print()
print("total_cars:", total_cars)
print("cars_rejected:", cars_rejected)
print("seconds_waited:", seconds_waited)
print("seconds_passed:", seconds_passed)
print("meals_served:", meals_served)
print("profit:", profit)
print("driveway:", driveway)