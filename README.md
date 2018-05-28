## Understanding Problem
- Students regularly use Dining Hall and they are usually short on time.
- Students should attend the lectures on time, but there is usually long waiting queues at Dining Hall.
- Students does not have the information whether the queue is long or not, so this lack of information causes misutilization of Dining Hall, time of students and money of students
- Long waiting times cause some students to leave dining hall because they don’t want to spend 15-20 minutes waiting in line. 

- Especially north campus dining hall may have quite human congestion depending on hours of exams and lectures with huge attendance. 

- Students may prefer  other places to eat and those places are more expensive, so students spend more money.

## Defining the Problem
- **Misutilization of students’ time and money because of long queues at Dining Hall is a fact that can not be overlooked!**

## Solution 
- We can develop a system that detects queue length and broadcasts it over the internet.
We will be using sensors and transmit the sensor data over wifi. 
Since the data will be broadcasted momentarily, students will effectively decide on time to have dinner.
Students may prefer other alternatives if they are in hurry.
- Infrared sensors will be placed to the ceilings of dining hall with proper distances between them along waiting lines.. 
If it senses a person under it, that means the queue is at least that long. Depending the values from other sensors, the server will estimate queue length.
It will send this values to the server via wifi.
After analyzing data,  a slack bot will be used to convert results from server to understandable format for students.

![](https://github.com/bounIoT/QueueDetection/blob/master/Pictures/490-1.png)

![](https://github.com/bounIoT/QueueDetection/blob/master/Pictures/490-2.png)

#### Students will be able to learn the state of the Dining Hall Queue from SlackBot:

![](https://github.com/bounIoT/QueueDetection/blob/master/Pictures/490-slack.png)
