Ping Pong game! 🏓



⭐ Another funny project using an Atmega32 microcontroller, It is a Ping pong game. The two microcontrollers depend on the interrupt pin to start each other. It was a funny challenge to apply my knowledge in embedded systems.



⚫Let's discuss its operation:

- In this project, I tried to access different positions on LCD to draw different patterns like (The racket, and Ball) I also used some delays to simulate the ball movement.

- The first microcontroller will send a signal to the interrupt pin to start the second microcontroller.

- The game generates a random movement of the ball to increase the difficulty and add some actions!

- You can change the direction of the rocket by pressing the button.

- When one of the players loses, a "You Lose" message will appear on his LCD.




⚫Hardware Components:-

1. LCD

2. Button



⚫Software Layers:-

1- MCAL => DIO, GIE & EXTI

2- HAL    => LCD (4 Bit Mode).



⚫GitHub link:-

https://github.com/Kirolos107/PingPong_Game



⚫Note:

- Every line in the code is explained by a comment.

- Do not hesitate to ask for clarification on any point.



🔸 Extraordinary thanks and appreciation to Eng. Amgad Samir for his efforts and unlimited support with me.
