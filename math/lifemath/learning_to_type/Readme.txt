Last week, I gave Arya a challenge. If she could type a 100 page novel out on her computer, I'd give her an unlimited supply of ice cream for two weeks. Now the idea was that she would learn how to type. I suggested she start by doing some online typing-tutor lessons, otherwise it may take her forever to type 100 pages.

However it wasn't quite clear how long she should learn, and when she should start typing the novel. This is of course, a basic Calculus 101 problem, and given that she knows no calculus, I had to find a way to teach her how to perform this excercise without her knowing calculus!

Enter Matlab, the most wonderful software for learning Math. I wrote this program as a way to explain the steps in finding the answer:
1. Model the learning process
2. Estimate the size of the task
3. Find the objective function to minimize. This function should be the the total time (to learn + type)

The file optLearningTime.m has the function used to perform the optimization steps

The file optLearningTime_Tests.m has a script to find and print the optimum learning time for a set number of pages to be typed, and then graph the results for a large number of different pages to be typed.